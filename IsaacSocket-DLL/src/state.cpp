#include "state.hpp"
#include "isaac_image.hpp"

#pragma warning(disable: 6387)//禁用警告 C6387

namespace state {
	isaac_image::IsaacImage& isaac = *(isaac_image::IsaacImage*)GetModuleHandleA(NULL);
	lua_State*& L = isaac.luaEngine->L;
	state::_LocalState local = state::_LocalState();
	state::_GlobalState& global = *[] {
		HANDLE hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(_GlobalState), "IsaacSocketSharedMemory");
		return (state::_GlobalState*)MapViewOfFile(hMapFile, FILE_MAP_WRITE, 0, 0, 0);
		}();
}

#pragma warning(default: 6387)//重新启用警告 C6387
