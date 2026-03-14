#pragma once
#include "BaseServerMessage.h"
#include <cstdint>

struct CharacterRegionMessage : BaseServerMessage
{
    ServerMessageType MessageType = ServerMessageType::CharacterRegion;
    int64_t CharacterID;
    int32_t RegionID;
};
