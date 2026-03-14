#pragma once
/**
 * @brief Server message types
 */
enum class ServerMessageType
{
    SelectionCharacterList = 10,
    CharacterDiscover = 30,
    CharacterRegion = 31,
    CharacterMove = 60
};

/**
 * @brief Base client message
 * 
 * All client messages must inherit from this struct.
 */
struct BaseServerMessage
{
    ServerMessageType MessageType;
};
