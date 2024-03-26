#pragma once
#include "pch.h"

namespace task_ {
	int RunCallback();

	size_t New();

	void Run(std::function <void()> callback);
}
