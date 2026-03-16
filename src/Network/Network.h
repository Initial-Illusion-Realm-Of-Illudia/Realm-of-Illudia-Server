#pragma once
#include "ClientMessages/BaseClientMessage.h"
#include "ServerMessages/BaseServerMessage.h"
#include "ClientData.h"
#include <map>
#include <functional>
#include <thread>

class Network
{
private:
    std::map<ClientMessageType, std::function<void(int, BaseClientMessage&)>> dispatchers;
    
    std::vector<std::tuple<int, std::string>> reliableSendQueue;
    std::vector<std::tuple<int, std::string>> unReliableSendQueue;
    
    std::vector<ClientData> clients;

    bool running;
    
    int udpSocket;
    int tcpSocket;
    
    std::thread reliableProcessThread;
    std::thread unReliableProcessThread;

    void reliableProcess();
    void unReliableProcess();

public:
    void Start();
    void Stop();
    void RegisterDispatcher(
        ClientMessageType type, std::function<void(int, BaseClientMessage&)> dispatcher);
    void Dispatch(int receiver, BaseClientMessage& msg);
    void Send(int receiver, BaseServerMessage& msg);
};
