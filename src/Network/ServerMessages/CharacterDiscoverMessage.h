#pragma once
#include "BaseServerMessage.h"
#include <cstdint>

struct CharacterDiscoverMessage : BaseServerMessage
{
    ServerMessageType MessageType = ServerMessageType::CharacterDiscover;
    int64_t CharacterID;
    int32_t Avatar;
    int32_t HeadColor;
    int32_t BodyColor;
    char SurName[60];
    char FirstName[60];
};
