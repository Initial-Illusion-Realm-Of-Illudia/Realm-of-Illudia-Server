#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

/**
 * @brief Client authenticates with the server
 * 
 * The client sends a token to the server to authenticate itself, the token
 * will be received when the client logs in (not done at this server).
 * The token is likely some kind of OAuth token.
 */
struct AuthenticateMessage : BaseClientMessage
{
    ClientMessageType MessageType = ClientMessageType::Authenticate;
    char Token[64];
};
