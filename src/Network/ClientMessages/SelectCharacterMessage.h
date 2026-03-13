#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

/**
 * @brief Client selects a character
 * 
 * The client sends this message to select a character to play as.
 * If the character is 0, then a new character is created.
 */
struct SelectCharacterMessage : BaseClientMessage
{
    int64_t Character; /** < 0 is always new character */
};
