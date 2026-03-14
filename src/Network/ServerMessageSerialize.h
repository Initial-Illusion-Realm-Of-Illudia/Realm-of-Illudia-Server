#pragma once
#include <ostream>
#include "Network.h"
#include "Marshaller.h"
#include "ServerMessages/BaseServerMessage.h"

class ServerMessageSerialize
{
private:
    Network* network;
    Marshaller* marshaller;
public:
    ServerMessageSerialize(Network* innetwork);
    ~ServerMessageSerialize();
    bool SerializeMessage(
        std::ostream& stream, int receiverID, BaseServerMessage& msg);
};
