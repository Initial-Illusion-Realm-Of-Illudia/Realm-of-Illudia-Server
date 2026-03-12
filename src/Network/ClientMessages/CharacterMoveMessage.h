#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

struct CharacterMoveMessage : BaseClientMessage
{
	int16_t MoveKind;
	double_t OldX;
	double_t OldY;
	double_t OldZ;
	float_t MoveX;
	float_t MoveY;
	float_t MoveZ;
    float_t Facing;
    float_t HeadPitch;
    float_t HeadYaw;
};
