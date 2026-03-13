#pragma once

/**
 * @brief Client message types
 */
enum class ClientMessageType
{
    Authenticate = 0,
    SelectCharacter = 20,
    ChangeName = 21,
    ChangeAppearance = 22,
    CharacterMove = 40,
    RequestCharacterInformation = 80
};

/**
 * @brief Base client message
 * 
 * All client messages must inherit from this struct.
 */
struct BaseClientMessage
{
    ClientMessageType MessageType;
};
