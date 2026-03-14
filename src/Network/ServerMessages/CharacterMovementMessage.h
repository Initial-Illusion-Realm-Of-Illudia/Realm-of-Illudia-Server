#pragma once
#include "BaseServerMessage.h"
#include <cstdint>

struct CharacterMovementMessage : BaseServerMessage
{
    ServerMessageType MessageType = ServerMessageType::CharacterMove;
    int16_t SerialNumber;
    int64_t CharacterID;
    int16_t MoveKind;
    double X;
    double Y;
    double Z;
};
