#pragma once
#include <cstdint>
#include "BaseClientMessage.h"

struct AuthenticateMessage : BaseClientMessage
{
	char Token[64];
};
