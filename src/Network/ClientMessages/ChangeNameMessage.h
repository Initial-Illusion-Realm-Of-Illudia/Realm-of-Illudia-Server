#pragma once
#include <cstdint>
#include <string>
#include "BaseClientMessage.h"

/**
 * @brief Client tells it wants to change the name of a character
 * 
 * Sent when making a new character or when changing
 * the name of an existing character.
 */
struct ChangeNameMessage : BaseClientMessage
{
    ClientMessageType MessageType = ClientMessageType::ChangeName;
    char SureName[60];
    char FamilyName[60];
};

