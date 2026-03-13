#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

/**
 * @brief Client tells it wants to know about a character
 * 
 * The server will not send character information unless the client has requested it.
 * Here the client can tell if it wans to know for example
 * stats, appearance, dressup, etc.
 * The client can also Subscribe / Unsubscribe to receive updates about the character.
 */
struct RequestCharacterInformation : BaseClientMessage
{
    ClientMessageType MessageType = ClientMessageType::RequestCharacterInformation;
    int64_t CharacterID;
    int8_t FlagsAndTypes; /** < See Game/Character/CharacterInformationFlags.h */
};
