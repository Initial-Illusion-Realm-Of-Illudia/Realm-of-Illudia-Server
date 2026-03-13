#pragma once
#include <istream>
#include "Network.h"
#include "Marshaller.h"
#include "ClientMessages/BaseClientMessage.h"

class ClientMessageParse
{
private:
    Network* network;
    Marshaller* marshaller;
public:
    ClientMessageParse(Network* innetwork);
    ~ClientMessageParse();
    void ParseMessage(std::istream& msg);
};
