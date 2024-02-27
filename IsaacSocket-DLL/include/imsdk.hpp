#pragma once
#include "pch.h"
#include "utils.hpp"

namespace imsdk {

#define _(ret,name,...) ret(*name)(__VA_ARGS__)=(decltype(name))GetProcAddress(hLuaModule, #name)
#pragma warning(disable: 6387)//禁用警告	C6387	“hLuaModule”可能是“0” : 这不符合函数“GetProcAddress”的规范。

	struct ImSDK
	{

		HMODULE hLuaModule = LoadLibraryW(utils::GetDataFilePathW(L"ImSDK.dll").c_str());

		_(const char*, TIMGetSDKVersion, void);

	};
#pragma warning(default: 6387)//重新启用警告C6387
#undef _
}
