#pragma once

#include "pch.h"

size_t reloadLibraryEntries(const char* libraryName, void* _mod = nullptr);
HMODULE reloadLibraryMain(const char* libraryName, bool checkTimestamp = false);
