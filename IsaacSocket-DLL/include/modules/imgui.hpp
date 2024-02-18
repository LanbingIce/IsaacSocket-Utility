#pragma once

#include "module.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

namespace imgui {
	static ::ImVec2 VEC2_0 = ::ImVec2(0, 0);
	static int ImVec2(lua_State* L) {
		ARG(1, number, float, x);
		ARG(2, number, float, y);
		::ImVec2* vec = (::ImVec2*)local.lua.lua_newuserdata(L, sizeof(::ImVec2));
		local.lua.luaL_newmetatable(L, "ImVec2");
		local.lua.lua_setmetatable(L, -2);
		vec->x = x;
		vec->y = y;
		return 1;
	}

	static int ImVec4(lua_State* L) {
		ARG(1, number, float, x);
		ARG(2, number, float, y);
		ARG(3, number, float, z);
		ARG(4, number, float, w);
		::ImVec4* vec = (::ImVec4*)local.lua.lua_newuserdata(L, sizeof(::ImVec4));
		local.lua.luaL_newmetatable(L, "ImVec4");
		local.lua.lua_setmetatable(L, -2);
		vec->x = x;
		vec->y = y;
		vec->z = z;
		vec->w = w;
		return 1;
	}

	static int ShowDemoWindow(lua_State* L) {
		ImGui::ShowDemoWindow();
		return 0;
	}

	static int Begin(lua_State* L) {
		ARG(1, string, const char*, name);
		ARG_DEF(2, boolean, bool, open, true);
		ARG_DEF(3, integer, int, flags, 0);

		local.lua.lua_pushboolean(L, ImGui::Begin(name, &open, flags));
		local.lua.lua_pushboolean(L, open);
		return 2;
	}

	static int End(lua_State* L) {
		ImGui::End();
		return 0;
	}

	static int Button(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_UDATA_DEF(2, ImVec2, ::ImVec2*, size, &VEC2_0);
		RET(boolean, ImGui::Button(label, *size));
	}

	static int Text(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::Text("%s", text);
		return 0;
	}

	static int LabelText(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, const char*, text);
		ImGui::LabelText(label, "%s", text);
		return 0;
	}

	static int TextColored(lua_State* L) {
		ARG_UDATA(1, ImVec4, ::ImVec4*, col);
		ARG(2, string, const char*, text);
		ImGui::TextColored(*col, "%s", text);
		return 0;

	}

	static int TextWrapped(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::TextWrapped("%s", text);
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
		ARG(3, integer, int, v_min);
		ARG(4, integer, int, v_max);
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

	static int InputText(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, string, str);
		ARG_DEF(3, integer, ImGuiInputTextFlags, flags, 0);
		local.lua.lua_pushboolean(L, ImGui::InputText(label, &str, flags));
		local.lua.lua_pushstring(L, str.c_str());
		return 2;
	}

	static int InputTextMultiline(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, string, str);
		ARG_UDATA_DEF(3, ImVec2, ::ImVec2*, size, &VEC2_0);
		ARG_DEF(4, integer, ImGuiInputTextFlags, flags, 0);
		local.lua.lua_pushboolean(L, ImGui::InputTextMultiline(label, &str, *size, flags));
		local.lua.lua_pushstring(L, str.c_str());
		return 2;
	}

	static int PushStyleColor(lua_State* L) {
		ARG(1, integer, ImGuiCol, idx);
		if (local.lua.lua_isinteger(L, 2))
		{
			ARG(2, integer, int, col);
			ImGui::PushStyleColor(idx, col);
		}
		else
		{
			ARG_UDATA(2, ImVec4, ::ImVec4*, col);
			ImGui::PushStyleColor(idx, *col);
		}
		return 0;
	}

	static int PopStyleColor(lua_State* L) {
		ARG_DEF(1, integer, int, count, 1);
		ImGui::PopStyleColor(count);
		return 0;
	}

	static int SetScrollHereY(lua_State* L) {
		ARG_DEF(1, number, float, center_y_ratio, 0.5F);
		ImGui::SetScrollHereY(center_y_ratio);
		return 0;
	}

	static int StyleColorsClassic(lua_State* L) {
		local.styleColor = state::CLASSIC;
		ImGui::StyleColorsClassic();
		return 0;
	}

	static int StyleColorsLight(lua_State* L) {
		local.styleColor = state::LIGHT;
		ImGui::StyleColorsLight();
		return 0;
	}

	static int StyleColorsDark(lua_State* L) {
		local.styleColor = state::DARK;
		ImGui::StyleColorsDark();
		return 0;
	}

	static void Init() {
		MODULE_BEGIN(ImGui);

		MODULE_FUNC(ImVec2);
		MODULE_FUNC(ImVec4);

		MODULE_FUNC(ShowDemoWindow);
		MODULE_FUNC(Begin);
		MODULE_FUNC(End);
		MODULE_FUNC(Button);
		MODULE_FUNC(Text);
		MODULE_FUNC(LabelText);
		MODULE_FUNC(TextColored);
		MODULE_FUNC(TextWrapped);
		MODULE_FUNC(Checkbox);
		MODULE_FUNC(SliderFloat);
		MODULE_FUNC(SliderInt);
		MODULE_FUNC(InputInt);
		MODULE_FUNC(SameLine);
		MODULE_FUNC(InputText);
		MODULE_FUNC(InputTextMultiline);

		MODULE_FUNC(PushStyleColor);
		MODULE_FUNC(PopStyleColor);
		MODULE_FUNC(SetScrollHereY);

		MODULE_FUNC(StyleColorsClassic);
		MODULE_FUNC(StyleColorsLight);
		MODULE_FUNC(StyleColorsDark);

		MODULE_END();
	}
}
