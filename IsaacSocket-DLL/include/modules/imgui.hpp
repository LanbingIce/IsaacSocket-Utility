#pragma once

#include "module.hpp"
#include <imgui/imgui.h>

namespace imgui {

	static int Begin(lua_State* L) {
		ARG(1, string, const char*, name);
		ARG_DEF(2, boolean, bool, p_open, true);
		ARG_DEF(3, integer, int, flags, 0);

		local.lua.lua_pushboolean(L, ImGui::Begin(name, &p_open, flags));
		local.lua.lua_pushboolean(L, p_open);
		return 2;
	}

	static int End(lua_State* L) {
		ImGui::End();
		return 0;
	}

	static int Button(lua_State* L) {
		ARG(1, string, const char*, label);

		RET(boolean, ImGui::Button(label));
	}

	static int Text(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::Text("%s", text);
		return 0;
	}


	static void Init() {
		DEFMOD(ImGui);
		DEF(Begin);
		DEF(End);
		DEF(Button);
		DEF(Text);
		ENDMOD();
	}
}
