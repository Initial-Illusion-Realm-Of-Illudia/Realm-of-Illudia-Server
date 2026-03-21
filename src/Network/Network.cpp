#include "Network.h"
#include <sstream>
#include <chrono>

void Network::Start()
{
    this->running = true;
    
    this->clientMessageParse = new ClientMessageParse(this);
    this->serverMessageSerialize = new ServerMessageSerialize(this);
    
    int iResult = 0;
    
    #ifdef _WIN32
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return;
    }
    #endif

    struct sockaddr_in serveraddr;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_family = AF_INET;

    this->udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    this->tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->makeNonBlocking(this->udpSocket);
    this->makeNonBlocking(this->tcpSocket);

    serveraddr.sin_port = htons(55550);
    iResult = bind(this->udpSocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    this->unreliableProcessThread = std::thread(&Network::unreliableProcess, this);

    serveraddr.sin_port = htons(55551);
    iResult = bind(this->tcpSocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(this->tcpSocket, 4096);

    #ifdef _WIN32
    WSAPOLLFD listen_fd {
        this->tcpSocket,
        POLLRDNORM,
        0
    };
    this->pollfds.push_back(listen_fd);
    #endif

    this->reliableProcessThread = std::thread(&Network::reliableProcess, this);
}

void Network::Stop()
{
    this->running = false;
    this->reliableProcessThread.join();
    this->unreliableProcessThread.join();

    closesocket(this->udpSocket);
    closesocket(this->tcpSocket);
    
    #ifdef _WIN32
    WSACleanup();
    #endif
}

void Network::makeNonBlocking(socket_t socket)
{
    #ifdef _WIN32
    unsigned long non_blocking = 1;
    ioctlsocket(socket, FIONBIO, &non_blocking);    
    #endif
}

void Network::unreliableProcess()
{
    // Send messages
    while (this->running)
    {
        // Copy & empty outgoing messages
        std::vector<std::tuple<int, std::string>> outgoingMessages;
        {
            std::lock_guard<std::mutex> lock(this->unreliableMutex);
            outgoingMessages = this->unreliableSendQueue;
            this->unreliableSendQueue.clear();
        }
        for (auto& message : outgoingMessages)
        {
            int receiver = std::get<0>(message);
            if (this->clients.size() >= receiver)
            {
                continue;
            }
            std::string msg = std::get<1>(message);
            sendto(this->udpSocket, msg.c_str(), msg.size(), 0,
                (struct sockaddr*)&this->clients[receiver].Addr,
                sizeof(this->clients[receiver].Addr));
        }

        // Now recive messages
        char buffer[1024];
        sockaddr_in6 clientaddr;
        int clientaddrlen = sizeof(clientaddr);
        // Poll here
        int bytesReceived = recvfrom(this->udpSocket, buffer, sizeof(buffer), 0,
            (struct sockaddr*)&clientaddr, &clientaddrlen);
        if (bytesReceived > 0)
        {
            // Process the received message
            std::string receivedMsg(buffer, max(bytesReceived, 1024));
            // Find the client by address
            auto clientKey = this->clientIDMap.find(clientaddr.sin6_addr);
            if (clientKey == this->clientIDMap.end())
            {
                // Need to get TCP first
                continue;
            }
            int clientID = clientKey->second;

            this->clientMessageParse->ParseMessage(
                clientID, std::stringstream(receivedMsg));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void Network::reliableProcess()
{
    while (this->running)
    {
        #ifdef _WIN32
        int pollRes = WSAPoll(
            this->pollfds.data(), this->pollfds.size(), 20);
        #endif

        if (pollRes > 0)
        {
            using my_vec_t = decltype(this->pollfds);
            for (my_vec_t::size_type i = 0; i < this->pollfds.size(); i++)
            {
                if (this->pollfds[i].revents & POLLRDNORM)
                {
                    // New connection
                    if (this->pollfds[i].fd == this->tcpSocket)
                    {
                        // Find new clients by listen to TCP connect 
                        socket_t new_socket;
                        struct sockaddr_in6 address;
                        socklen_t addrlen = sizeof(address);
                        if ((new_socket = accept(this->tcpSocket, (struct sockaddr*)&address, &addrlen)) < 0)
                        {
                            perror("accept");
                            exit(EXIT_FAILURE);
                        }

                        this->makeNonBlocking(new_socket);
                        char clientip[INET6_ADDRSTRLEN] = {};
                        inet_ntop(AF_INET6, &address.sin6_addr, clientip, INET6_ADDRSTRLEN);

                        this->clients.push_back(ClientData{
                            new_socket,
                            address.sin6_addr
                        });
                        this->clientIDMap[address.sin6_addr] = this->clients.size() - 1;

                        pollfd_t clientpoll {
                            new_socket,
                            POLLRDNORM,
                            0
                        };
                        this->pollfds.push_back(clientpoll);
                        //i = 0; // Begin again, see if there are more
                    }
                    // Read message
                    else
                    {
                        char buffer[1024];
                        struct sockaddr_in6 clientaddr;
                        int clientaddrlen = sizeof(clientaddr);
                        int bytesReceived = recv(
                            this->pollfds[i].fd, buffer, sizeof(buffer), 0);
                        if (bytesReceived > 0)
                        {
                            // Process the received message
                            std::string receivedMsg(buffer, max(bytesReceived, 1024));

                            this->clientMessageParse->ParseMessage(
                                i + 1, std::stringstream(receivedMsg));
                        }
                    }
                }
            }
        }

        // Send messages
        std::vector<std::tuple<int, std::string>> outgoingMessages;
        {
            std::lock_guard<std::mutex> lock(this->reliableMutex);
            outgoingMessages = this->reliableSendQueue;
            this->reliableSendQueue.clear();
        }

        for (auto& message : outgoingMessages)
        {
            int receiver = std::get<0>(message);
            if (this->clients.size() >= receiver)
            {
                continue;
            }
            std::string msg = std::get<1>(message);
            send(this->clients[receiver].ReliableHandle,
                msg.c_str(), msg.size(), 0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }    
}

void Network::RegisterDispatcher(
    ClientMessageType type, std::function<void(int, BaseClientMessage&)> dispatcher)
{
    this->dispatchers[type] = dispatcher;
}

void Network::Dispatch(int receiver, BaseClientMessage& msg)
{
    auto dispatcher = this->dispatchers.find(msg.MessageType);
    if (dispatcher == this->dispatchers.end())
    {
        return;
    }
    dispatcher->second(receiver, msg);
}

void Network::Send(int receiver, BaseServerMessage& msg)
{
}
