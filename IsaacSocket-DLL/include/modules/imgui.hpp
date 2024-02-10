﻿#pragma once

#include "module.hpp"
#include <imgui/imgui.h>

namespace imgui {

	static int Begin(lua_State* L) {
		ARG(1, string, const char*, name);
		ARG_DEF(2, integer, int, flags, 0);
		bool p_open;
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
		ARG(1, string, const char*, label);
		ImGui::Text("%s", label);
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
