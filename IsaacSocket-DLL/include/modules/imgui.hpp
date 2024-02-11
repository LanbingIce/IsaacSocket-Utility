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
	static int Checkbox(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, boolean, bool, v);

		local.lua.lua_pushboolean(L, ImGui::Checkbox(label, &v));
		local.lua.lua_pushboolean(L, v);
		return 2;
	}

	static int SliderFloat(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, number, float, v);
		ARG(3, number, float, v_min);
		ARG(4, number, float, v_max);
		ARG_DEF(5, string, const char*, format, "%.3f");
		ARG_DEF(6, integer, int, flags, 0);

		local.lua.lua_pushboolean(L, ImGui::SliderFloat(label, &v, v_min, v_max, format, flags));
		local.lua.lua_pushnumber(L, v);
		return 2;
	}

	static int SliderInt(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v);
		ARG(3, number, float, v_min);
		ARG(4, number, float, v_max);
		ARG_DEF(5, string, const char*, format, "%d");
		ARG_DEF(6, integer, int, flags, 0);

		local.lua.lua_pushboolean(L, ImGui::SliderInt(label, &v, v_min, v_max, format, flags));
		local.lua.lua_pushinteger(L, v);
		return 2;
	}

	static int InputInt(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v);
		ARG_DEF(3, integer, int, step, 1);
		ARG_DEF(4, integer, int, step_fast, 100);
		ARG_DEF(5, integer, ImGuiInputTextFlags, flags, 0);

		local.lua.lua_pushboolean(L, ImGui::InputInt(label, &v, step_fast, flags));
		local.lua.lua_pushinteger(L, v);
		return 2;
	}

	static int SameLine(lua_State* L) {
		ARG_DEF(1, number, float, offset_from_start_x, 0.0F);
		ARG_DEF(2, number, float, spacing_w, -1.0F);

		ImGui::SameLine(offset_from_start_x, spacing_w);
		return 0;
	}

	static void Init() {
		DEFMOD(ImGui);
		DEF(Begin);
		DEF(End);
		DEF(Button);
		DEF(Text);
		DEF(Checkbox);
		DEF(SliderFloat);
		DEF(SliderInt);
		DEF(InputInt);
		DEF(SameLine);
		ENDMOD();
	}
}
