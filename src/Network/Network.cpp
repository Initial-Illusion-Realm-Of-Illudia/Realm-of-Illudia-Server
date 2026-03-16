#include "Network.h"
#ifdef _WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

void Network::Start()
{
    this->running = true;
    
    #ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return;
    }
    #endif

    this->udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    this->tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    this->pollThread = std::thread(&Network::Poll, this);
}

void Network::Stop()
{
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
