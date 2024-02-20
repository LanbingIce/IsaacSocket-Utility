#pragma once

#include "module.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

namespace imgui {
	static ::ImVec2 VEC2_0 = ::ImVec2(0, 0);

	static int p_ImVec2__index(lua_State* L) {
		ARG_UDATA(1, p_ImVec2, ::ImVec2**, pp_vec);
		METATABLE_BEGIN(::ImVec2, **pp_vec);
		METATABLE_INDEX(number, x, float);
		METATABLE_INDEX(number, y, float);
		METATABLE_END();
	}

	static int ImVec2__index(lua_State* L) {
		ARG_UDATA(1, ImVec2, ::ImVec2*, p_vec);
		METATABLE_BEGIN(::ImVec2, *p_vec);
		METATABLE_INDEX(number, x, float);
		METATABLE_INDEX(number, y, float);
		METATABLE_END();
	}

	static int ImVec4__index(lua_State* L) {
		ARG_UDATA(1, ImVec4, ::ImVec4*, p_vec);
		METATABLE_BEGIN(::ImVec4, *p_vec);
		METATABLE_INDEX(number, x, float);
		METATABLE_INDEX(number, y, float);
		METATABLE_INDEX(number, z, float);
		METATABLE_INDEX(number, w, float);
		METATABLE_END();
	}

	static int p_ImGuiIO__index(lua_State* L) {
		ARG_UDATA(1, p_ImGuiIO, ImGuiIO**, pp_io);
		METATABLE_BEGIN(::ImGuiIO, **pp_io);
		METATABLE_INDEX(number, DeltaTime, float);
		METATABLE_INDEX_UDATA_P(p_ImVec2, DisplaySize, ::ImVec2*);

		METATABLE_END();
	}

	static int ImVec2(lua_State* L) {
		ARG(1, number, float, x);
		ARG(2, number, float, y);
		::ImVec2* vec = (::ImVec2*)local.lua.lua_newuserdata(L, sizeof(::ImVec2));
		SET_METATABLE(ImVec2);
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
		SET_METATABLE(ImVec4);
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

	static int TextUnformatted(lua_State* L) {
		ARG(1, string, const char*, text);
		ARG_DEF(2, string, const char*, text_end, (const char*)0);
		ImGui::TextUnformatted(text);
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

	static int RadioButton(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v);
		ARG(3, integer, int, v_button);

		local.lua.lua_pushboolean(L, ImGui::RadioButton(label, &v, v_button));
		local.lua.lua_pushinteger(L, v);
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

	static int GetItemRectSize(lua_State* L) {
		::ImVec2* p_vec = (::ImVec2*)local.lua.lua_newuserdata(L, sizeof(::ImVec2));
		SET_METATABLE(ImVec2);
		*p_vec = ImGui::GetItemRectSize();
		return 1;
	}

	static int GetWindowPos(lua_State* L) {
		::ImVec2* p_vec = (::ImVec2*)local.lua.lua_newuserdata(L, sizeof(::ImVec2));
		SET_METATABLE(ImVec2);
		*p_vec = ImGui::GetWindowPos();
		return 1;
	}

	static int GetWindowSize(lua_State* L) {
		::ImVec2* p_vec = (::ImVec2*)local.lua.lua_newuserdata(L, sizeof(::ImVec2));
		SET_METATABLE(ImVec2);
		*p_vec = ImGui::GetWindowSize();
		return 1;
	}

	static int SetWindowPos(lua_State* L) {
		if (local.lua.lua_isstring(L, 1))
		{
			ARG(1, string, const char*, name);
			ARG_UDATA(2, ImVec2, ::ImVec2*, pos);
			ARG(3, integer, ::ImGuiCond, cond);
			ImGui::SetWindowPos(name, *pos, cond);
		}
		else {
			ARG_UDATA(1, ImVec2, ::ImVec2*, pos);
			ARG(2, integer, ::ImGuiCond, cond);
			ImGui::SetWindowPos(*pos, cond);
		}
		return 0;
	}

	static int SetWindowSize(lua_State* L) {
		if (local.lua.lua_isstring(L, 1))
		{
			ARG(1, string, const char*, name);
			ARG_UDATA(2, ImVec2, ::ImVec2*, size);
			ARG(3, integer, ::ImGuiCond, cond);
			ImGui::SetWindowSize(name, *size, cond);
		}
		else {
			ARG_UDATA(1, ImVec2, ::ImVec2*, size);
			ARG(2, integer, ::ImGuiCond, cond);
			ImGui::SetWindowSize(*size, cond);
		}
		return 0;
	}

	static int BeginMainMenuBar(lua_State* L) {
		RET(boolean, ImGui::BeginMainMenuBar());
	}

	static int EndMainMenuBar(lua_State* L) {
		ImGui::EndMainMenuBar();
		return 0;
	}

	static int BeginMenuBar(lua_State* L) {
		RET(boolean, ImGui::BeginMenuBar());
	}

	static int EndMenuBar(lua_State* L) {
		ImGui::EndMenuBar();
		return 0;
	}

	static int BeginMenu(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_DEF(2, boolean, bool, enabled, true);
		RET(boolean, ImGui::BeginMenu(label, enabled));
	}

	static int EndMenu(lua_State* L) {
		ImGui::EndMenu();
		return 0;
	}

	static int MenuItem(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_DEF(2, string, const char*, shortcut, (const char*)0);
		ARG_DEF(3, boolean, bool, selected, false);
		ARG_DEF(4, boolean, bool, enabled, true);
		RET(boolean, ImGui::MenuItem(label, shortcut, selected, enabled));
	}

	static int GetIO(lua_State* L) {
		ImGuiIO** p_io = (ImGuiIO**)local.lua.lua_newuserdata(L, sizeof(ImGuiIO*));
		SET_METATABLE(p_ImGuiIO);
		*p_io = &ImGui::GetIO();
		return 1;
	}

	static int SetScrollX(lua_State* L) {
		ARG(1, number, float, scroll_x);
		ImGui::SetScrollX(scroll_x);
		return 0;
	}

	static int SetScrollY(lua_State* L) {
		ARG(1, number, float, scroll_y);
		ImGui::SetScrollY(scroll_y);
		return 0;
	}

	static int SetScrollHereX(lua_State* L) {
		ARG_DEF(1, number, float, center_x_ratio, 0.5F);
		ImGui::SetScrollHereX(center_x_ratio);
		return 0;
	}

	static int SetScrollHereY(lua_State* L) {
		ARG_DEF(1, number, float, center_y_ratio, 0.5F);
		ImGui::SetScrollHereY(center_y_ratio);
		return 0;
	}


	static int CalcTextSize(lua_State* L) {
		ARG(1, string, const char*, text);
		ARG_DEF(2, string, const char*, text_end, (const char*)0);
		ARG_DEF(3, boolean, bool, hide_text_after_double_hash, false);
		ARG_DEF(4, number, float, wrap_width, -1.0F);
		::ImVec2* p_vec = (::ImVec2*)local.lua.lua_newuserdata(L, sizeof(::ImVec2));
		SET_METATABLE(ImVec2);
		*p_vec = ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width);
		return 1;
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
		MODULE_FUNC(TextUnformatted);
		MODULE_FUNC(LabelText);
		MODULE_FUNC(TextColored);
		MODULE_FUNC(TextWrapped);
		MODULE_FUNC(Checkbox);
		MODULE_FUNC(RadioButton);
		MODULE_FUNC(SliderFloat);
		MODULE_FUNC(SliderInt);
		MODULE_FUNC(InputInt);
		MODULE_FUNC(SameLine);
		MODULE_FUNC(InputText);
		MODULE_FUNC(InputTextMultiline);

		MODULE_FUNC(PushStyleColor);
		MODULE_FUNC(PopStyleColor);

		MODULE_FUNC(StyleColorsClassic);
		MODULE_FUNC(StyleColorsLight);
		MODULE_FUNC(StyleColorsDark);

		MODULE_FUNC(SetWindowPos);
		MODULE_FUNC(SetWindowSize);
		MODULE_FUNC(GetWindowSize);
		MODULE_FUNC(GetWindowSize);
		MODULE_FUNC(GetItemRectSize);

		MODULE_FUNC(BeginMainMenuBar);
		MODULE_FUNC(EndMainMenuBar);
		MODULE_FUNC(BeginMenuBar);
		MODULE_FUNC(EndMenuBar);
		MODULE_FUNC(BeginMenu);
		MODULE_FUNC(EndMenu);
		MODULE_FUNC(MenuItem);

		MODULE_FUNC(GetIO);

		MODULE_FUNC(SetScrollX);
		MODULE_FUNC(SetScrollY);
		MODULE_FUNC(SetScrollHereX);
		MODULE_FUNC(SetScrollHereY);

		MODULE_FUNC(CalcTextSize);

		MODULE_END();
	}
}
