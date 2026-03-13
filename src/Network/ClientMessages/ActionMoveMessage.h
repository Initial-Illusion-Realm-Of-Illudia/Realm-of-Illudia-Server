#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

/**
 * @brief Client tells it wants to move a character
 * 
 * Sent when the client wants to move a character.
 * Also contains the old position of the character,
 * facing direction (where the character is turned to, for visualaization),
 * head pitch, and head yaw (where the head look at, for visualization).
 */
struct ActionMoveMessage : BaseClientMessage
{
    ClientMessageType MessageType = ClientMessageType::CharacterMove;
    int16_t MoveKind; /** < See Game/Movement/MovementFlags.h, some is server only */
    double OldX; /** < Old position of the character, for reference */
    double OldY;
    double OldZ;
    float MoveX;
    float MoveY;
    float MoveZ;
    float Facing;
    float HeadPitch;
    float HeadYaw;
};
