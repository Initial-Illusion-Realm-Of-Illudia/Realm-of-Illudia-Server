#pragma once
#include "ClientMessageParse.h"
#include "ServerMessageSerialize.h"
#include "ClientMessages/BaseClientMessage.h"
#include "ServerMessages/BaseServerMessage.h"
#include "ClientData.h"

#include <functional>
#include <map>
#include <mutex>
#include <thread>

#ifdef _WIN32
#include <ws2tcpip.h>
#include <WinSock2.h>
typedef WSAPOLLFD pollfd_t;
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

using socket_t = decltype(socket(0, 0, 0));

class Network
{
private:
    std::map<ClientMessageType, std::function<void(int, BaseClientMessage&)>> dispatchers;
    
    std::vector<std::tuple<int, std::string>> reliableSendQueue;
    std::vector<std::tuple<int, std::string>> unreliableSendQueue;
    socket_t udpSocket;
    socket_t tcpSocket;
    std::thread reliableProcessThread;
    std::thread unreliableProcessThread;
    std::mutex reliableMutex;
    std::mutex unreliableMutex;

    ClientMessageParse* clientMessageParse;
    ServerMessageSerialize* serverMessageSerialize;

    std::vector<ClientData> clients;
    std::map<struct in6_addr, int> clientIDMap;
    std::vector<pollfd_t> pollfds;

    bool running;

    void reliableProcess();
    void unreliableProcess();
    void makeNonBlocking(socket_t socket);

public:
    void Start();
    void Stop();
    void RegisterDispatcher(
        ClientMessageType type, std::function<void(int, BaseClientMessage&)> dispatcher);
    void Dispatch(int receiver, BaseClientMessage& msg);
    void SendReliable(int receiver, BaseServerMessage& msg);
    void SendUnreliable(int receiver, BaseServerMessage& msg);
};
