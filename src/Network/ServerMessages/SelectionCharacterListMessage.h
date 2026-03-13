#pragma once
#include "BaseServerMessage.h"
#include <cstdint>

struct CharacterInfoInMsg
{
    int64_t CharacterId;
    char SurName[60];
    char FirstName[60];
};

struct SelectionCharacterListMessage : BaseServerMessage
{
    ServerMessageType MessageType = ServerMessageType::SelectionCharacterList;
    int8_t CharacterCount;
    CharacterInfoInMsg Characters[100];
};

