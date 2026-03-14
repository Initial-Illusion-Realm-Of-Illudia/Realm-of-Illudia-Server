#pragma once
#include "ClientMessages/BaseClientMessage.h"
#include "ServerMessages/BaseServerMessage.h"


class Network
{
public:
    void Start();
    void Stop();
    void Dispatch(int receiver, BaseClientMessage& msg);
    void Send(int receiver, BaseServerMessage& msg);
};
