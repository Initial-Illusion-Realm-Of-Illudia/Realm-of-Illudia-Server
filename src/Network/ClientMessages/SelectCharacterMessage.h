#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

struct SelectCharacterMessage : BaseClientMessage
{
	int8_t Character;
};
