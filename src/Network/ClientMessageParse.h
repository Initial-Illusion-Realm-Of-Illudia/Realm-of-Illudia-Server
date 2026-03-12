#pragma once
#include <istream>
#include "Network.h"
#include "Marshaller.h"
#include "ClientMessages/BaseClientMessage.h"

enum class ClientMessageType
{
	Authenticate,
	CharacterMove,
	NewCharacter,
	SelectCharacter
};

class ClientMessageParse
{
private:
	Network* network;
	Marshaller* marshaller;
public:
	ClientMessageParse(Network* innetwork);
	~ClientMessageParse();
	void ParseMessage(std::istream& msg);
};
