#pragma once
#include "Network.h"

class ClientData
{
public:
    socket_t ReliableHandle;
    struct in6_addr Addr;
    std::map<ClientMessageType, int16_t> IncommingSerial;
    std::map<ServerMessageType, int16_t> OutgoingSerial;
};
