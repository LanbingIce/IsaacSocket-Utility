#pragma once
#include "pch.h"

namespace state {
	enum State
	{
		NORMAL = 0,
		ON_CONNECTED = 1
	};
	struct StateData
	{
		int needReload;
		uint32_t lockedMTRandomValue;
		State state;
	};
}
