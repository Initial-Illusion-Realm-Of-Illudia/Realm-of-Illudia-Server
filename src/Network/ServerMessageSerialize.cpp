#include "ServerMessageSerialize.h"
#include "ServerMessages/CharacterDiscoverMessage.h"
#include "ServerMessages/CharacterMovementMessage.h"
#include "ServerMessages/CharacterRegionMessage.h"
#include "ServerMessages/SelectionCharacterListMessage.h"

ServerMessageSerialize::ServerMessageSerialize(Network* innetwork)
{
    this->network = innetwork;
    this->marshaller = new Marshaller();
}

ServerMessageSerialize::~ServerMessageSerialize()
{
    delete this->marshaller;
}

bool ServerMessageSerialize::SerializeMessage(
    std::ostream& stream, int receiverID, BaseServerMessage& msg)
{
    if (!this->marshaller->WriteU8(stream, (uint8_t)msg.MessageType))
    {
        return false;
    }

    switch (msg.MessageType)
    {
    case ServerMessageType::CharacterMove:
    {
        CharacterMovementMessage& cmMsg = (CharacterMovementMessage&)msg;
        if (!this->marshaller->WriteU16(stream, cmMsg.SerialNumber))
        {
            return false;
        }
        if (!this->marshaller->WriteU64(stream, cmMsg.CharacterID))
        {
            return false;
        }
        if (!this->marshaller->WriteU16(stream, cmMsg.MoveKind))
        {
            return false;
        }
        if (!this->marshaller->WriteDouble(stream, cmMsg.X))
        {
            return false;
        }
        if (!this->marshaller->WriteDouble(stream, cmMsg.Y))
        {
            return false;
        }
        if (!this->marshaller->WriteDouble(stream, cmMsg.Z))
        {
            return false;
        }
        this->network->Send(cmMsg);
        break;
    }
    case ServerMessageType::CharacterDiscover:
    {
        CharacterDiscoverMessage& cdMsg = (CharacterDiscoverMessage&)msg;
        if (!this->marshaller->WriteU64(stream, cdMsg.CharacterID))
        {
            return false;
        }
        if (!this->marshaller->WriteU32(stream, cdMsg.Avatar))
        {
            return false;
        }
        if (!this->marshaller->WriteU32(stream, cdMsg.HeadColor))
        {
            return false;
        }
        if (!this->marshaller->WriteU32(stream, cdMsg.BodyColor))
        {
            return false;
        }
        if (!this->marshaller->WriteCharArray(stream, cdMsg.SurName, 60))
        {
            return false;
        }
        if (!this->marshaller->WriteCharArray(stream, cdMsg.FirstName, 60))
        {
            return false;
        }
        this->network->Send(cdMsg);
        break;
    }
    case ServerMessageType::CharacterRegion:
    {
        CharacterRegionMessage& crMsg = (CharacterRegionMessage&)msg;
        if (!this->marshaller->WriteU64(stream, crMsg.CharacterID))
        {
            return false;
        }
        if (!this->marshaller->WriteU32(stream, crMsg.RegionID))
        {
            return false;
        }
        this->network->Send(receiverID, crMsg);
        break;
    }
    case ServerMessageType::SelectionCharacterList:
    {
        SelectionCharacterListMessage& scMsg = (SelectionCharacterListMessage&)msg;
        if (!this->marshaller->WriteU64(stream, scMsg.CharacterID))
        {
            return false;
        }
        if (!this->marshaller->WriteU32(stream, scMsg.CharacterCount))
        {
            return false;
        }
        for (int i = 0; i < scMsg.CharacterCount; i++)
        {
            if (!this->marshaller->WriteU64(stream, scMsg.CharacterIDs[i]))
            {
                return false;
            }
        }
        this->network->Send(receiverID, scMsg);
        break;
    }
    default:
        break;
    }

    return true;
}
