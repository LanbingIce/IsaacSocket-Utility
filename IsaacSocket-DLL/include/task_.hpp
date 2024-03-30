#pragma once
#include "pch.h"

#include <Poco/Task.h>

namespace task_ {
    Poco::Task* Run(std::function <void()> callback);
}
