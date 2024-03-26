#pragma once
#include "pch.h"

namespace task_ {
	size_t New();

	void Run(std::function <void()> callback);
}
