#include "module.hpp"
#include "lua.hpp"
#include "config.hpp"
#include "udata.hpp"
#include "state.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

namespace imgui_ {
	static const ::ImVec2 VEC2_0 = ::ImVec2(0, 0);
	static const ::ImVec4 VEC4_0 = ::ImVec4(0, 0, 0, 0);
	static const ::ImVec2 VEC2_1 = ::ImVec2(1, 1);
	static const ::ImVec4 VEC4_1 = ::ImVec4(1, 1, 1, 1);
	static const ::ImVec2 VEC2_NEG_MIN_0 = ::ImVec2(-FLT_MIN, 0);

	static int ImVec2(lua_State* L) {
		ARG(1, number, float, x);
		ARG(2, number, float, y);
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec.x = x;
		vec.y = y;
		return 1;
	}

	static int ImVec4(lua_State* L) {
		ARG(1, number, float, x);
		ARG(2, number, float, y);
		ARG(3, number, float, z);
		ARG(4, number, float, w);
		auto& vec = NEW_UDATA_META(::ImVec4, udata::ImVec4);
		vec.x = x;
		vec.y = y;
		vec.z = z;
		vec.w = w;
		return 1;
	}

	static int GetIO(lua_State* L) {
		auto& p_io = NEW_UDATA_META(ImGuiIO*, udata::p_ImGuiIO);
		p_io = &ImGui::GetIO();
		return 1;
	}

	static int ShowDemoWindow(lua_State* L) {
		ARG_DEF(1, boolean, bool, open, true);
		ImGui::ShowDemoWindow(&open);
		RET(boolean, open);
	}

	static int ShowMetricsWindow(lua_State* L) {
		ARG_DEF(1, boolean, bool, open, true);
		ImGui::ShowMetricsWindow(&open);
		RET(boolean, open);
	}

	static int ShowDebugLogWindow(lua_State* L) {
		ARG_DEF(1, boolean, bool, open, true);
		ImGui::ShowDebugLogWindow(&open);
		RET(boolean, open);
	}

	static int ShowIDStackToolWindow(lua_State* L) {
		ARG_DEF(1, boolean, bool, open, true);
		ImGui::ShowIDStackToolWindow(&open);
		RET(boolean, open);
	}

	static int ShowAboutWindow(lua_State* L) {
		ARG_DEF(1, boolean, bool, open, true);
		ImGui::ShowAboutWindow(&open);
		RET(boolean, open);
	}

	static int ShowStyleSelector(lua_State* L) {
		ARG(1, string, const char*, label);
		RET(boolean, ImGui::ShowStyleSelector(label));
	}

	static int ShowFontSelector(lua_State* L) {
		ARG(1, string, const char*, label);
		ImGui::ShowFontSelector(label);
		return 0;
	}

	static int ShowUserGuide(lua_State* L) {
		ImGui::ShowUserGuide();
		return 0;
	}

	static int GetVersion(lua_State* L) {
		RET(string, ImGui::GetVersion());
	}

	static int StyleColorsDark(lua_State* L) {
		config::Set("IsaacSocket.StyleColors", state::DARK);
		if (lua_isnoneornil(L, 1))
		{
			ImGui::StyleColorsDark();
		}
		else
		{
			auto& dst = ARG_UDATA(1, ::ImGuiStyle);
			ImGui::StyleColorsDark(&dst);
		}
		return 0;
	}

	static int StyleColorsLight(lua_State* L) {
		config::Set("IsaacSocket.StyleColors", state::LIGHT);
		if (lua_isnoneornil(L, 1))
		{
			ImGui::StyleColorsLight();
		}
		else
		{
			auto& dst = ARG_UDATA(1, ::ImGuiStyle);
			ImGui::StyleColorsLight(&dst);
		}
		return 0;
	}

	static int StyleColorsClassic(lua_State* L) {
		config::Set("IsaacSocket.StyleColors", state::CLASSIC);
		if (lua_isnoneornil(L, 1))
		{
			ImGui::StyleColorsClassic();
		}
		else
		{
			auto& dst = ARG_UDATA(1, ::ImGuiStyle);
			ImGui::StyleColorsClassic(&dst);
		}
		return 0;
	}

	static int Begin(lua_State* L) {
		ARG(1, string, const char*, name);
		ARG_DEF(2, boolean, bool, open, true);
		ARG_DEF(3, integer, ImGuiWindowFlags, flags, 0);

		lua_pushboolean(L, ImGui::Begin(name, &open, flags));
		lua_pushboolean(L, open);
		return 2;
	}

	static int End(lua_State* L) {
		ImGui::End();
		return 0;
	}

	static int IsWindowAppearing(lua_State* L) {
		RET(boolean, ImGui::IsWindowAppearing());
	}

	static int IsWindowCollapsed(lua_State* L) {
		RET(boolean, ImGui::IsWindowCollapsed());
	}

	static int IsWindowFocused(lua_State* L) {
		ARG_DEF(1, integer, ImGuiFocusedFlags, flags, 0);
		RET(boolean, ImGui::IsWindowFocused(flags));
	}

	static int IsWindowHovered(lua_State* L) {
		ARG_DEF(1, integer, ImGuiHoveredFlags, flags, 0);
		RET(boolean, ImGui::IsWindowHovered(flags));
	}

	static int GetWindowPos(lua_State* L) {
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetWindowPos();
		return 1;
	}

	static int GetWindowSize(lua_State* L) {
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetWindowSize();
		return 1;
	}

	static int GetWindowWidth(lua_State* L) {
		RET(number, ImGui::GetWindowWidth());
	}

	static int GetWindowHeight(lua_State* L) {
		RET(number, ImGui::GetWindowHeight());
	}

	static int SetWindowPos(lua_State* L) {
		if (lua_isstring(L, 1))
		{
			ARG(1, string, const char*, name);
			auto& pos = ARG_UDATA(2, ::ImVec2);
			ARG_DEF(3, integer, ::ImGuiCond, cond, 0);
			ImGui::SetWindowPos(name, pos, cond);
		}
		else {
			auto& pos = ARG_UDATA(1, ::ImVec2);
			ARG_DEF(2, integer, ::ImGuiCond, cond, 0);
			ImGui::SetWindowPos(pos, cond);
		}
		return 0;
	}

	static int SetWindowSize(lua_State* L) {
		if (lua_isstring(L, 1))
		{
			ARG(1, string, const char*, name);
			auto& size = ARG_UDATA(2, ::ImVec2);
			ARG_DEF(3, integer, ::ImGuiCond, cond, 0);
			ImGui::SetWindowSize(name, size, cond);
		}
		else {
			auto& size = ARG_UDATA(1, ::ImVec2);
			ARG_DEF(2, integer, ::ImGuiCond, cond, 0);
			ImGui::SetWindowSize(size, cond);
		}
		return 0;
	}

	static int SetWindowFocus(lua_State* L) {
		if (lua_isstring(L, 1))
		{
			ARG(1, string, const char*, name);
			ImGui::SetWindowFocus(name);
		}
		else {
			ImGui::SetWindowFocus();
		}
		ARG(1, number, float, scale);
		return 0;
	}

	static int GetScrollX(lua_State* L) {
		RET(number, ImGui::GetScrollX());
	}

	static int GetScrollY(lua_State* L) {
		RET(number, ImGui::GetScrollY());
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

	static int GetScrollMaxX(lua_State* L) {
		RET(number, ImGui::GetScrollMaxX());
	}

	static int GetScrollMaxY(lua_State* L) {
		RET(number, ImGui::GetScrollMaxY());
	}

	static int SetScrollHereX(lua_State* L) {
		ARG_DEF(1, number, float, center_x_ratio, 0.5f);
		ImGui::SetScrollHereX(center_x_ratio);
		return 0;
	}

	static int SetScrollHereY(lua_State* L) {
		ARG_DEF(1, number, float, center_y_ratio, 0.5f);
		ImGui::SetScrollHereY(center_y_ratio);
		return 0;
	}

	static int PopFont(lua_State* L) {
		ImGui::PopFont();
		return 0;
	}

	static int PushStyleColor(lua_State* L) {
		ARG(1, integer, ImGuiCol, idx);
		if (lua_isinteger(L, 2))
		{
			ARG(2, integer, int, col);
			ImGui::PushStyleColor(idx, col);
		}
		else
		{
			auto& col = ARG_UDATA(2, ::ImVec4);
			ImGui::PushStyleColor(idx, col);
		}
		return 0;
	}

	static int PopStyleColor(lua_State* L) {
		ARG_DEF(1, integer, int, count, 1);
		ImGui::PopStyleColor(count);
		return 0;
	}

	static int GetFont(lua_State* L) {
		auto& p_font = NEW_UDATA_META(ImFont*, udata::p_ImFont);
		p_font = ImGui::GetFont();
		return 1;
	}

	static int Separator(lua_State* L) {
		ImGui::Separator();
		return 0;
	}

	static int SameLine(lua_State* L) {
		ARG_DEF(1, number, float, offset_from_start_x, 0.0f);
		ARG_DEF(2, number, float, spacing_w, -1.0f);

		ImGui::SameLine(offset_from_start_x, spacing_w);
		return 0;
	}

	static int NewLine(lua_State* L) {
		ImGui::NewLine();
		return 0;
	}

	static int Spacing(lua_State* L) {
		ImGui::Spacing();
		return 0;
	}

	static int Dummy(lua_State* L) {
		auto& size = ARG_UDATA(1, ::ImVec2);
		ImGui::Dummy(size);
		return 0;
	}

	static int Indent(lua_State* L) {
		ARG_DEF(1, number, float, indent_w, 0.0f);
		ImGui::Indent(indent_w);
		return 0;
	}

	static int Unindent(lua_State* L) {
		ARG_DEF(1, number, float, indent_w, 0.0f);
		ImGui::Unindent(indent_w);
		return 0;
	}

	static int BeginGroup(lua_State* L) {
		ImGui::BeginGroup();
		return 0;
	}

	static int EndGroup(lua_State* L) {
		ImGui::EndGroup();
		return 0;
	}

	static int TextUnformatted(lua_State* L) {
		ARG(1, string, const char*, text);
		ARG_DEF(2, string, const char*, text_end, NULL);
		ImGui::TextUnformatted(text, text_end);
		return 0;
	}

	static int Text(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::Text("%s", text);
		return 0;
	}

	static int TextColored(lua_State* L) {
		auto& col = ARG_UDATA(1, ::ImVec4);
		ARG(2, string, const char*, text);
		ImGui::TextColored(col, "%s", text);
		return 0;
	}

	static int TextDisabled(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::TextDisabled("%s", text);
		return 0;
	}

	static int TextWrapped(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::TextWrapped("%s", text);
		return 0;
	}

	static int LabelText(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, const char*, text);
		ImGui::LabelText(label, "%s", text);
		return 0;
	}

	static int SeparatorText(lua_State* L) {
		ARG(1, string, const char*, label);
		ImGui::SeparatorText(label);
		return 0;
	}

	static int Button(lua_State* L) {
		ARG(1, string, const char*, label);
		auto& size = ARG_UDATA_DEF(2, const ::ImVec2, VEC2_0);
		RET(boolean, ImGui::Button(label, size));
	}

	static int SmallButton(lua_State* L) {
		ARG(1, string, const char*, label);
		RET(boolean, ImGui::SmallButton(label));
	}

	static int ArrowButton(lua_State* L) {
		ARG(1, string, const char*, str_id);
		ARG(2, integer, ImGuiDir, dir);
		RET(boolean, ImGui::ArrowButton(str_id, dir));
	}

	static int Checkbox(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, boolean, bool, v);

		lua_pushboolean(L, ImGui::Checkbox(label, &v));
		lua_pushboolean(L, v);
		return 2;
	}

	static int RadioButton(lua_State* L) {
		ARG(1, string, const char*, label);
		if (lua_isinteger(L, 2))
		{
			ARG(2, integer, int, v);
			ARG(3, integer, int, v_button);
			lua_pushboolean(L, ImGui::RadioButton(label, &v, v_button));
			lua_pushinteger(L, v);
			return 2;
		}
		else
		{
			ARG(2, boolean, bool, active);
			RET(boolean, ImGui::RadioButton(label, active));
		}
	}

	static int ProgressBar(lua_State* L) {
		ARG(1, number, float, fraction);
		auto& size_arg = ARG_UDATA_DEF(2, const ::ImVec2, VEC2_NEG_MIN_0);
		ARG_DEF(3, string, const char*, overlay, NULL);
		ImGui::ProgressBar(fraction, size_arg, overlay);
		return 0;
	}

	static int Image(lua_State* L) {
		ARG(1, integer, ImTextureID, user_texture_id);
		auto& image_size = ARG_UDATA(2, ::ImVec2);
		auto& uv0 = ARG_UDATA_DEF(3, const ::ImVec2, VEC2_0);
		auto& uv1 = ARG_UDATA_DEF(4, const ::ImVec2, VEC2_1);
		auto& tint_col = ARG_UDATA_DEF(5, const ::ImVec4, VEC4_1);
		auto& border_col = ARG_UDATA_DEF(6, const ::ImVec4, VEC4_0);
		ImGui::Image(user_texture_id, image_size, uv0, uv1, tint_col, border_col);
		return 0;
	}

	static int ImageButton(lua_State* L) {
		ARG(1, string, const char*, str_id);
		ARG(2, integer, ImTextureID, user_texture_id);
		auto& image_size = ARG_UDATA(3, const ::ImVec2);
		auto& uv0 = ARG_UDATA_DEF(4, const ::ImVec2, VEC2_0);
		auto& uv1 = ARG_UDATA_DEF(5, const ::ImVec2, VEC2_1);
		auto& bg_col = ARG_UDATA_DEF(6, const ::ImVec4, VEC4_0);
		auto& tint_col = ARG_UDATA_DEF(7, const ::ImVec4, VEC4_1);
		RET(boolean, ImGui::ImageButton(str_id, user_texture_id, image_size, uv0, uv1, bg_col, tint_col));
	}

	static int BeginCombo(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, const char*, preview_value);
		ARG_DEF(3, integer, ImGuiComboFlags, flags, 0);
		RET(boolean, ImGui::BeginCombo(label, preview_value, flags));
	}

	static int EndCombo(lua_State* L) {
		ImGui::EndCombo();
		return 0;
	}

	static int Combo(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, current_item);

		if (lua_isstring(L, 3))
		{
			ARG(3, string, const char*, items_separated_by_zeros);
			ARG_DEF(4, integer, int, height_in_items, -1);
			lua_pushboolean(L, ImGui::Combo(label, &current_item, items_separated_by_zeros, height_in_items));
		}
		else
		{
			ARG(3, vectorcstring, vector<const char*>, items);
			ARG(4, integer, size_t, items_count);
			ARG_DEF(5, integer, int, height_in_items, -1);
			items.resize(items_count);
			lua_pushboolean(L, ImGui::Combo(label, &current_item, items.data(), items_count, height_in_items));
		}
		lua_pushinteger(L, current_item);
		return 2;
	}

	static int DragFloat(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, number, float, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, number, float, v_min, 0.0f);
		ARG_DEF(5, number, float, v_max, 0.0f);
		ARG_DEF(6, string, const char*, format, "%.3f");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);

		lua_pushboolean(L, ImGui::DragFloat(label, &v, v_speed, v_min, v_max, format, flags));
		lua_pushnumber(L, v);
		return 2;
	}

	static int DragFloat2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, number, float, v_min, 0.0f);
		ARG_DEF(5, number, float, v_max, 0.0f);
		ARG_DEF(6, string, const char*, format, "%.3f");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);
		v.resize(2);
		lua_pushboolean(L, ImGui::DragFloat2(label, v.data(), v_speed, v_min, v_max, format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int DragFloat3(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, number, float, v_min, 0.0f);
		ARG_DEF(5, number, float, v_max, 0.0f);
		ARG_DEF(6, string, const char*, format, "%.3f");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);
		v.resize(3);
		lua_pushboolean(L, ImGui::DragFloat3(label, v.data(), v_speed, v_min, v_max, format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int DragFloat4(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, number, float, v_min, 0.0f);
		ARG_DEF(5, number, float, v_max, 0.0f);
		ARG_DEF(6, string, const char*, format, "%.3f");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);
		v.resize(4);
		lua_pushboolean(L, ImGui::DragFloat4(label, v.data(), v_speed, v_min, v_max, format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int DragFloatRange2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, number, float, v_current_min);
		ARG(3, number, float, v_current_max);
		ARG_DEF(4, number, float, v_speed, 1.0f);
		ARG_DEF(5, number, float, v_min, 0.0f);
		ARG_DEF(6, number, float, v_max, 0.0f);
		ARG_DEF(7, string, const char*, format, "%.3f");
		ARG_DEF(8, string, const char*, format_max, NULL);
		ARG_DEF(9, integer, ImGuiSliderFlags, flags, 0);
		lua_pushboolean(L, ImGui::DragFloatRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, flags));
		lua_pushnumber(L, v_current_min);
		lua_pushnumber(L, v_current_max);
		return 3;
	}

	static int DragInt(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, integer, int, v_min, 0);
		ARG_DEF(5, integer, int, v_max, 0);
		ARG_DEF(6, string, const char*, format, "%d");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);
		lua_pushboolean(L, ImGui::DragInt(label, &v, v_speed, v_min, v_max, format, flags));
		lua_pushinteger(L, v);
		return 2;
	}

	static int DragInt2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, integer, int, v_min, 0);
		ARG_DEF(5, integer, int, v_max, 0);
		ARG_DEF(6, string, const char*, format, "%d");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);
		v.resize(2);
		lua_pushboolean(L, ImGui::DragInt2(label, v.data(), v_speed, v_min, v_max, format, flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int DragInt3(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, integer, int, v_min, 0);
		ARG_DEF(5, integer, int, v_max, 0);
		ARG_DEF(6, string, const char*, format, "%d");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);
		v.resize(3);
		lua_pushboolean(L, ImGui::DragInt3(label, v.data(), v_speed, v_min, v_max, format, flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int DragInt4(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG_DEF(3, number, float, v_speed, 1.0f);
		ARG_DEF(4, integer, int, v_min, 0);
		ARG_DEF(5, integer, int, v_max, 0);
		ARG_DEF(6, string, const char*, format, "%d");
		ARG_DEF(7, integer, ImGuiSliderFlags, flags, 0);
		v.resize(4);
		lua_pushboolean(L, ImGui::DragInt4(label, v.data(), v_speed, v_min, v_max, format, flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int DragIntRange2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v_current_min);
		ARG(3, integer, int, v_current_max);
		ARG_DEF(4, number, float, v_speed, 1.0f);
		ARG_DEF(5, integer, int, v_min, 0);
		ARG_DEF(6, integer, int, v_max, 0);
		ARG_DEF(7, string, const char*, format, "%d");
		ARG_DEF(8, string, const char*, format_max, NULL);
		ARG_DEF(9, integer, ImGuiSliderFlags, flags, 0);
		lua_pushboolean(L, ImGui::DragIntRange2(label, &v_current_min, &v_current_max, v_speed, v_min, v_max, format, format_max, flags));
		lua_pushinteger(L, v_current_min);
		lua_pushinteger(L, v_current_max);
		return 3;
	}

	static int SliderFloat(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, number, float, v);
		ARG(3, number, float, v_min);
		ARG(4, number, float, v_max);
		ARG_DEF(5, string, const char*, format, "%.3f");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);

		lua_pushboolean(L, ImGui::SliderFloat(label, &v, v_min, v_max, format, flags));
		lua_pushnumber(L, v);
		return 2;
	}

	static int SliderFloat2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG(3, number, float, v_min);
		ARG(4, number, float, v_max);
		ARG_DEF(5, string, const char*, format, "%.3f");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);
		v.resize(2);
		lua_pushboolean(L, ImGui::SliderFloat2(label, v.data(), v_min, v_max, format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int SliderFloat3(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG(3, number, float, v_min);
		ARG(4, number, float, v_max);
		ARG_DEF(5, string, const char*, format, "%.3f");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);
		v.resize(3);
		lua_pushboolean(L, ImGui::SliderFloat3(label, v.data(), v_min, v_max, format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int SliderFloat4(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG(3, number, float, v_min);
		ARG(4, number, float, v_max);
		ARG_DEF(5, string, const char*, format, "%.3f");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);
		v.resize(4);
		lua_pushboolean(L, ImGui::SliderFloat4(label, v.data(), v_min, v_max, format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int SliderAngle(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, number, float, v_rad);
		ARG_DEF(3, number, float, v_degrees_min, -360.0f);
		ARG_DEF(4, number, float, v_degrees_max, +360.0f);
		ARG_DEF(5, string, const char*, format, "%.0f deg");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);
		lua_pushboolean(L, ImGui::SliderAngle(label, &v_rad, v_degrees_min, v_degrees_max, format, flags));
		lua_pushnumber(L, v_rad);
		return 2;
	}

	static int SliderInt(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v);
		ARG(3, integer, int, v_min);
		ARG(4, integer, int, v_max);
		ARG_DEF(5, string, const char*, format, "%d");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);

		lua_pushboolean(L, ImGui::SliderInt(label, &v, v_min, v_max, format, flags));
		lua_pushinteger(L, v);
		return 2;
	}

	static int SliderInt2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG(3, integer, int, v_min);
		ARG(4, integer, int, v_max);
		ARG_DEF(5, string, const char*, format, "%d");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);
		v.resize(2);
		lua_pushboolean(L, ImGui::SliderInt2(label, v.data(), v_min, v_max, format, flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int SliderInt3(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG(3, integer, int, v_min);
		ARG(4, integer, int, v_max);
		ARG_DEF(5, string, const char*, format, "%d");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);
		v.resize(3);
		lua_pushboolean(L, ImGui::SliderInt3(label, v.data(), v_min, v_max, format, flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int SliderInt4(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG(3, integer, int, v_min);
		ARG(4, integer, int, v_max);
		ARG_DEF(5, string, const char*, format, "%d");
		ARG_DEF(6, integer, ImGuiSliderFlags, flags, 0);
		v.resize(4);
		lua_pushboolean(L, ImGui::SliderInt4(label, v.data(), v_min, v_max, format, flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int InputText(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, string, str);
		ARG_DEF(3, integer, ImGuiInputTextFlags, flags, 0);
		lua_pushboolean(L, ImGui::InputText(label, &str, flags));
		lua_pushstring(L, str.c_str());
		return 2;
	}

	static int InputTextMultiline(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, string, str);
		auto& size = ARG_UDATA_DEF(3, const ::ImVec2, VEC2_0);
		ARG_DEF(4, integer, ImGuiInputTextFlags, flags, 0);
		lua_pushboolean(L, ImGui::InputTextMultiline(label, &str, size, flags));
		lua_pushstring(L, str.c_str());
		return 2;
	}

	static int InputFloat(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, number, float, v);
		ARG_DEF(3, number, float, step, 0.0f);
		ARG_DEF(4, number, float, step_fast, 0.0f);
		ARG_DEF(5, string, const char*, format, "%.3f");
		ARG_DEF(6, integer, ImGuiInputTextFlags, flags, 0);
		lua_pushboolean(L, ImGui::InputFloat(label, &v, step, step_fast, format, flags));
		lua_pushnumber(L, v);
		return 2;
	}

	static int InputFloat2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG_DEF(3, string, const char*, format, "%.3f");
		ARG_DEF(4, integer, ImGuiInputTextFlags, flags, 0);
		v.resize(2);
		lua_pushboolean(L, ImGui::InputFloat2(label, v.data(), format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int InputFloat3(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG_DEF(3, string, const char*, format, "%.3f");
		ARG_DEF(4, integer, ImGuiInputTextFlags, flags, 0);
		v.resize(3);
		lua_pushboolean(L, ImGui::InputFloat3(label, v.data(), format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int InputFloat4(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorfloat, vector<float>, v);
		ARG_DEF(3, string, const char*, format, "%.3f");
		ARG_DEF(4, integer, ImGuiInputTextFlags, flags, 0);
		v.resize(4);
		lua_pushboolean(L, ImGui::InputFloat4(label, v.data(), format, flags));
		lua_pushvectorfloat(L, v);
		return 2;
	}

	static int InputInt(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v);
		ARG_DEF(3, integer, int, step, 1);
		ARG_DEF(4, integer, int, step_fast, 100);
		ARG_DEF(5, integer, ImGuiInputTextFlags, flags, 0);

		lua_pushboolean(L, ImGui::InputInt(label, &v, step_fast, flags));
		lua_pushinteger(L, v);
		return 2;
	}

	static int InputInt2(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG_DEF(3, integer, ImGuiInputTextFlags, flags, 0);
		v.resize(2);
		lua_pushboolean(L, ImGui::InputInt2(label, v.data(), flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int InputInt3(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG_DEF(3, integer, ImGuiInputTextFlags, flags, 0);
		v.resize(3);
		lua_pushboolean(L, ImGui::InputInt3(label, v.data(), flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int InputInt4(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, vectorint, vector<int>, v);
		ARG_DEF(3, integer, ImGuiInputTextFlags, flags, 0);
		v.resize(4);
		lua_pushboolean(L, ImGui::InputInt4(label, v.data(), flags));
		lua_pushvectorint(L, v);
		return 2;
	}

	static int InputDouble(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, number, double, v);
		ARG_DEF(3, number, double, step, 0.0);
		ARG_DEF(4, number, double, step_fast, 0.0);
		ARG_DEF(5, string, const char*, format, "%.6f");
		ARG_DEF(6, integer, ImGuiInputTextFlags, flags, 0);
		lua_pushboolean(L, ImGui::InputDouble(label, &v, step, step_fast, format, flags));
		lua_pushnumber(L, v);
		return 2;
	}

	static int TreeNode(lua_State* L) {
		if (lua_isnoneornil(L, 2))
		{
			ARG(1, string, const char*, label);
			RET(boolean, ImGui::TreeNode(label));
		}
		else
		{
			ARG(1, string, const char*, str_id);
			ARG(2, string, const char*, text);
			RET(boolean, ImGui::TreeNode(str_id, "%s", text));
		}
	}

	static int TreeNodeEx(lua_State* L) {
		ARG_DEF(2, integer, ImGuiTreeNodeFlags, flags, 0);
		if (lua_isnoneornil(L, 3))
		{
			ARG(1, string, const char*, label);
			RET(boolean, ImGui::TreeNodeEx(label, flags));
		}
		else
		{
			ARG(1, string, const char*, str_id);
			ARG(3, string, const char*, text);
			RET(boolean, ImGui::TreeNodeEx(str_id, flags, "%s", text));
		}
	}

	static int TreePush(lua_State* L) {
		ARG(1, string, const char*, str_id);
		ImGui::TreePush(str_id);
		return 0;
	}

	static int TreePop(lua_State* L) {
		ImGui::TreePop();
		return 0;
	}

	static int GetTreeNodeToLabelSpacing(lua_State* L) {
		RET(number, ImGui::GetTreeNodeToLabelSpacing());
	}

	static int Selectable(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, boolean, bool, selected);
		ARG_DEF(3, integer, ImGuiSelectableFlags, flags, 0);
		auto& size_arg = ARG_UDATA_DEF(4, const ::ImVec2, VEC2_0);
		lua_pushboolean(L, ImGui::Selectable(label, &selected, flags, size_arg));
		lua_pushboolean(L, selected);
		return 2;
	}

	static int BeginListBox(lua_State* L) {
		ARG(1, string, const char*, label);
		auto& size = ARG_UDATA_DEF(2, const ::ImVec2, VEC2_0);
		RET(boolean, ImGui::BeginListBox(label, size));
	}

	static int EndListBox(lua_State* L) {
		ImGui::EndListBox();
		return 0;
	}

	static int ListBox(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, current_item);
		ARG(3, vectorcstring, vector<const char* >, items);
		ARG(4, integer, int, items_count);
		ARG_DEF(5, integer, int, height_in_items, -1);
		items.resize(items_count);
		lua_pushboolean(L, ImGui::ListBox(label, &current_item, items.data(), items_count, height_in_items));
		lua_pushinteger(L, current_item);
		return 2;
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
		ARG_DEF(2, string, const char*, shortcut, NULL);
		ARG_DEF(3, boolean, bool, selected, false);
		ARG_DEF(4, boolean, bool, enabled, true);
		lua_pushboolean(L, ImGui::MenuItem(label, shortcut, &selected, enabled));
		lua_pushboolean(L, selected);
		return 2;
	}

	static int BeginTooltip(lua_State* L) {
		RET(boolean, ImGui::BeginTooltip());
	}

	static int EndTooltip(lua_State* L) {
		ImGui::EndTooltip();
		return 0;
	}

	static int SetTooltip(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::SetTooltip("%s", text);
		return 0;
	}

	static int BeginItemTooltip(lua_State* L) {
		RET(boolean, ImGui::BeginItemTooltip());
	}

	static int SetItemTooltip(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::SetItemTooltip("%s", text);
		return 0;
	}

	static int BeginPopup(lua_State* L) {
		ARG(1, string, const char*, str_id);
		ARG_DEF(2, integer, ImGuiWindowFlags, flags, 0);
		RET(boolean, ImGui::BeginPopup(str_id, flags));
	}

	static int EndPopup(lua_State* L) {
		ImGui::EndPopup();
		return 0;
	}

	static int OpenPopup(lua_State* L) {
		ARG_DEF(2, integer, ImGuiPopupFlags, popup_flags, 0);
		if (lua_isinteger(L, 1))
		{
			ARG(1, integer, ImGuiID, id);
			ImGui::OpenPopup(id, popup_flags);
		}
		else {
			ARG(1, string, const char*, str_id);
			ImGui::OpenPopup(str_id, popup_flags);
		}
		return 0;
	}

	static int BeginPopupContextItem(lua_State* L) {
		ARG_DEF(1, string, const char*, str_id, NULL);
		ARG_DEF(2, integer, ImGuiPopupFlags, popup_flags, ImGuiPopupFlags_MouseButtonRight);
		RET(boolean, ImGui::BeginPopupContextItem(str_id, popup_flags));
	}

	static int TableAngledHeadersRow(lua_State* L) {
		ImGui::TableAngledHeadersRow();
		return 0;
	}

	static int TableGetColumnCount(lua_State* L) {
		RET(integer, ImGui::TableGetColumnCount());
	}

	static int TableGetColumnIndex(lua_State* L) {
		RET(integer, ImGui::TableGetColumnIndex());
	}

	static int TableGetRowIndex(lua_State* L) {
		RET(integer, ImGui::TableGetRowIndex());
	}

	static int TableGetColumnName(lua_State* L) {
		ARG_DEF(1, integer, int, column_n, -1);
		RET(string, ImGui::TableGetColumnName(column_n));
	}

	static int TableGetColumnFlags(lua_State* L) {
		ARG_DEF(1, integer, int, column_n, -1);
		RET(integer, ImGui::TableGetColumnFlags(column_n));
	}

	static int TableSetColumnEnabled(lua_State* L) {
		ARG(1, integer, int, column_n);
		ARG(2, boolean, bool, enabled);
		ImGui::TableSetColumnEnabled(column_n, enabled);
		return 0;
	}

	static int TableSetBgColor(lua_State* L) {
		ARG(1, integer, ImGuiTableBgTarget, target);
		ARG(2, integer, ImU32, color);
		ARG_DEF(3, integer, int, column_n, -1);
		ImGui::TableSetBgColor(target, color, column_n);
		return 0;
	}

	static int Columns(lua_State* L) {
		ARG_DEF(1, integer, int, count, 1);
		ARG_DEF(2, string, const char*, id, NULL);
		ARG_DEF(3, boolean, bool, border, true);
		ImGui::Columns(count, id, border);
		return 0;
	}

	static int NextColumn(lua_State* L) {
		ImGui::NextColumn();
		return 0;
	}

	static int GetColumnIndex(lua_State* L) {
		RET(integer, ImGui::GetColumnIndex());
	}

	static int GetColumnWidth(lua_State* L) {
		ARG_DEF(1, integer, int, column_index, -1);
		RET(number, ImGui::GetColumnWidth(column_index));
	}

	static int SetColumnWidth(lua_State* L) {
		ARG(1, integer, int, column_index);
		ARG(2, number, float, width);
		ImGui::SetColumnWidth(column_index, width);
		return 0;
	}

	static int GetColumnOffset(lua_State* L) {
		ARG_DEF(1, integer, int, column_index, -1);
		RET(number, ImGui::GetColumnOffset(column_index));
	}

	static int SetColumnOffset(lua_State* L) {
		ARG(1, integer, int, column_index);
		ARG(2, number, float, offset_x);
		ImGui::SetColumnOffset(column_index, offset_x);
		return 0;
	}

	static int GetColumnsCount(lua_State* L) {
		RET(integer, ImGui::GetColumnsCount());
	}

	static int BeginTabBar(lua_State* L) {
		ARG(1, string, const char*, str_id);
		ARG_DEF(2, integer, ImGuiTabBarFlags, flags, 0);
		RET(boolean, ImGui::BeginTabBar(str_id, flags));
	}

	static int EndTabBar(lua_State* L) {
		ImGui::EndTabBar();
		return 0;
	}

	static int BeginTabItem(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_DEF(2, boolean, bool, open, true);
		ARG_DEF(3, integer, ImGuiTabItemFlags, flags, 0);
		lua_pushboolean(L, ImGui::BeginTabItem(label, &open, flags));
		lua_pushboolean(L, open);
		return 2;
	}

	static int EndTabItem(lua_State* L) {
		ImGui::EndTabItem();
		return 0;
	}

	static int TabItemButton(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_DEF(2, integer, ImGuiTabItemFlags, flags, 0);
		RET(boolean, ImGui::TabItemButton(label, flags));
	}

	static int SetTabItemClosed(lua_State* L) {
		ARG(1, string, const char*, tab_or_docked_window_label);
		ImGui::SetTabItemClosed(tab_or_docked_window_label);
		return 0;
	}

	static int BeginDisabled(lua_State* L) {
		ARG_DEF(1, boolean, bool, disabled, true);
		ImGui::BeginDisabled(disabled);
		return 0;
	}

	static int EndDisabled(lua_State* L) {
		ImGui::EndDisabled();
		return 0;
	}

	static int SetItemDefaultFocus(lua_State* L) {
		ImGui::SetItemDefaultFocus();
		return 0;
	}

	static int SetNextItemAllowOverlap(lua_State* L) {
		ImGui::SetNextItemAllowOverlap();
		return 0;
	}

	static int IsItemHovered(lua_State* L) {
		ARG_DEF(1, integer, ImGuiHoveredFlags, flags, 0);
		RET(boolean, ImGui::IsItemHovered(flags));
	}

	static int IsItemActive(lua_State* L) {
		RET(boolean, ImGui::IsItemActive());
	}

	static int IsItemFocused(lua_State* L) {
		RET(boolean, ImGui::IsItemFocused());
	}

	static int IsItemClicked(lua_State* L) {
		ARG_DEF(1, integer, ImGuiMouseButton, mouse_button, ImGuiMouseButton_Left);
		RET(boolean, ImGui::IsItemClicked(mouse_button));
	}

	static int IsItemVisible(lua_State* L) {
		RET(boolean, ImGui::IsItemVisible());
	}

	static int IsItemEdited(lua_State* L) {
		RET(boolean, ImGui::IsItemEdited());
	}

	static int IsItemActivated(lua_State* L) {
		RET(boolean, ImGui::IsItemActivated());
	}

	static int IsItemDeactivated(lua_State* L) {
		RET(boolean, ImGui::IsItemDeactivated());
	}

	static int IsItemDeactivatedAfterEdit(lua_State* L) {
		RET(boolean, ImGui::IsItemDeactivatedAfterEdit());
	}

	static int IsItemToggledOpen(lua_State* L) {
		RET(boolean, ImGui::IsItemToggledOpen());
	}

	static int IsAnyItemHovered(lua_State* L) {
		RET(boolean, ImGui::IsAnyItemHovered());
	}

	static int IsAnyItemActive(lua_State* L) {
		RET(boolean, ImGui::IsAnyItemActive());
	}

	static int IsAnyItemFocused(lua_State* L) {
		RET(boolean, ImGui::IsAnyItemFocused());
	}

	static int GetItemID(lua_State* L) {
		RET(integer, ImGui::GetItemID());
	}

	static int GetItemRectMin(lua_State* L) {
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetItemRectMin();
		return 1;
	}

	static int GetItemRectMax(lua_State* L) {
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetItemRectMax();
		return 1;
	}

	static int GetItemRectSize(lua_State* L) {
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetItemRectSize();
		return 1;
	}

	static int IsRectVisible(lua_State* L) {
		if (lua_isnoneornil(L, 2))
		{
			auto& size = ARG_UDATA(1, ::ImVec2);
			RET(boolean, ImGui::IsRectVisible(size));
		}
		else
		{
			auto& rect_min = ARG_UDATA(1, ::ImVec2);
			auto& rect_max = ARG_UDATA(2, ::ImVec2);
			RET(boolean, ImGui::IsRectVisible(rect_min, rect_max));
		}
	}

	static int GetTime(lua_State* L) {
		RET(number, ImGui::GetTime());
	}

	static int GetFrameCount(lua_State* L) {
		RET(integer, ImGui::GetFrameCount());
	}

	static int GetStyleColorName(lua_State* L) {
		ARG(1, integer, ImGuiCol, idx);
		RET(string, ImGui::GetStyleColorName(idx));
	}

	static int CalcTextSize(lua_State* L) {
		ARG(1, string, const char*, text);
		ARG_DEF(2, string, const char*, text_end, NULL);
		ARG_DEF(3, boolean, bool, hide_text_after_double_hash, false);
		ARG_DEF(4, number, float, wrap_width, -1.0f);
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width);
		return 1;
	}

	static int ColorConvertU32ToFloat4(lua_State* L) {
		ARG(1, integer, ImU32, in);
		auto& vec = NEW_UDATA_META(::ImVec4, udata::ImVec4);
		vec = ImGui::ColorConvertU32ToFloat4(in);
		return 1;
	}

	static int ColorConvertFloat4ToU32(lua_State* L) {
		auto& in = ARG_UDATA(1, ::ImVec4);
		RET(integer, ImGui::ColorConvertFloat4ToU32(in));
	}

	static int ColorConvertRGBtoHSV(lua_State* L) {
		ARG(1, number, float, r);
		ARG(2, number, float, g);
		ARG(3, number, float, b);
		float h, s, v;
		ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
		lua_pushnumber(L, h);
		lua_pushnumber(L, s);
		lua_pushnumber(L, v);
		return 3;
	}

	static int ColorConvertHSVtoRGB(lua_State* L) {
		ARG(1, number, float, h);
		ARG(2, number, float, s);
		ARG(3, number, float, v);
		float r, g, b;
		ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
		lua_pushnumber(L, r);
		lua_pushnumber(L, g);
		lua_pushnumber(L, b);
		return 3;
	}

	static int IsKeyDown(lua_State* L) {
		ARG(1, integer, ImGuiKey, key);
		RET(boolean, ImGui::IsKeyDown(key));
	}

	static int IsKeyPressed(lua_State* L) {
		ARG(1, integer, ImGuiKey, key);
		ARG_DEF(2, boolean, bool, repeat, true);
		RET(boolean, ImGui::IsKeyPressed(key, repeat));
	}

	static int IsKeyReleased(lua_State* L) {
		ARG(1, integer, ImGuiKey, key);
		RET(boolean, ImGui::IsKeyReleased(key));
	}

	static int IsKeyChordPressed(lua_State* L) {
		ARG(1, integer, ImGuiKeyChord, key_chord);
		RET(boolean, ImGui::IsKeyChordPressed(key_chord));
	}

	static int GetKeyName(lua_State* L) {
		ARG(1, integer, ImGuiKey, key);
		RET(string, ImGui::GetKeyName(key));
	}

	static int IsMouseDown(lua_State* L) {
		ARG(1, integer, ImGuiMouseButton, button);
		RET(boolean, ImGui::IsMouseDown(button));
	}

	static int IsMouseClicked(lua_State* L) {
		ARG(1, integer, ImGuiMouseButton, button);
		ARG_DEF(2, boolean, bool, repeat, false);
		RET(boolean, ImGui::IsMouseClicked(button, repeat));
	}

	static int IsMouseReleased(lua_State* L) {
		ARG(1, integer, ImGuiMouseButton, button);
		RET(boolean, ImGui::IsMouseReleased(button));
	}

	static int IsMouseDoubleClicked(lua_State* L) {
		ARG(1, integer, ImGuiMouseButton, button);
		RET(boolean, ImGui::IsMouseDoubleClicked(button));
	}

	static int GetMouseClickedCount(lua_State* L) {
		ARG(1, integer, ImGuiMouseButton, button);
		RET(integer, ImGui::GetMouseClickedCount(button));
	}

	static int IsMouseHoveringRect(lua_State* L) {
		auto& r_min = ARG_UDATA(1, const ::ImVec2);
		auto& r_max = ARG_UDATA(2, const ::ImVec2);
		ARG_DEF(3, boolean, bool, clip, true);
		RET(boolean, ImGui::IsMouseHoveringRect(r_min, r_max, clip));
	}

	static int IsMousePosValid(lua_State* L) {
		if (lua_isnoneornil(L, 1))
		{
			RET(boolean, ImGui::IsMousePosValid());
		}
		else
		{
			auto& mouse_pos = ARG_UDATA(1, const ::ImVec2);
			RET(boolean, ImGui::IsMousePosValid(&mouse_pos));
		}
	}

	static int IsAnyMouseDown(lua_State* L) {
		RET(boolean, ImGui::IsAnyMouseDown());
	}

	static int GetMousePos(lua_State* L) {
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetMousePos();
		return 1;
	}

	static int GetMousePosOnOpeningCurrentPopup(lua_State* L) {
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetMousePosOnOpeningCurrentPopup();
		return 1;
	}

	static int IsMouseDragging(lua_State* L) {
		ARG(1, integer, ImGuiMouseButton, button);
		ARG_DEF(2, number, float, lock_threshold, -1.0f);
		RET(boolean, ImGui::IsMouseDragging(button, lock_threshold));
	}

	static int GetMouseDragDelta(lua_State* L) {
		ARG_DEF(1, integer, ImGuiMouseButton, button, 0);
		ARG_DEF(2, number, float, lock_threshold, -1.0f);
		auto& vec = NEW_UDATA_META(::ImVec2, udata::ImVec2);
		vec = ImGui::GetMouseDragDelta(button, lock_threshold);
		return 1;
	}

	static int ResetMouseDragDelta(lua_State* L) {
		ARG_DEF(1, integer, ImGuiMouseButton, button, 0);
		ImGui::ResetMouseDragDelta(button);
		return 0;
	}

	static int GetMouseCursor(lua_State* L) {
		RET(integer, ImGui::GetMouseCursor());
	}

	static int SetMouseCursor(lua_State* L) {
		ARG(1, integer, ImGuiMouseCursor, cursor_type);
		ImGui::SetMouseCursor(cursor_type);
		return 0;
	}

	static int SetNextFrameWantCaptureMouse(lua_State* L) {
		ARG(1, boolean, bool, want_capture_mouse);
		ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse);
		return 0;
	}

	static int GetClipboardText(lua_State* L) {
		RET(string, ImGui::GetClipboardText());
	}

	static int SetClipboardText(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::SetClipboardText(text);
		return 0;
	}

	static int DebugTextEncoding(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::DebugTextEncoding(text);
		return 0;
	}

	static int DebugFlashStyleColor(lua_State* L) {
		ARG(1, integer, ImGuiCol, idx);
		ImGui::DebugFlashStyleColor(idx);
		return 0;
	}

	static int DebugStartItemPicker(lua_State* L) {
		ImGui::DebugStartItemPicker();
		return 0;
	}

	static int DebugCheckVersionAndDataLayout(lua_State* L) {
		ARG(1, string, const char*, version_str);
		ARG(2, integer, size_t, sz_io);
		ARG(3, integer, size_t, sz_style);
		ARG(4, integer, size_t, sz_vec2);
		ARG(5, integer, size_t, sz_vec4);
		ARG(6, integer, size_t, sz_drawvert);
		ARG(7, integer, size_t, sz_drawidx);
		RET(boolean, ImGui::DebugCheckVersionAndDataLayout(version_str, sz_io, sz_style, sz_vec2, sz_vec4, sz_drawvert, sz_drawidx));
	}

	static RegisterModule InitModules = [] {
		MODULE_BEGIN(ImGui);

		MODULE_FUNC(ImVec2);
		MODULE_FUNC(ImVec4);

		// 以上方法不是ImGui命名空间下的方法

		// Context creation and access
		// - Each context create its own ImFontAtlas by default. You may instance one yourself and pass it to CreateContext() to share a font atlas between contexts.
		// - DLL users: heaps and globals are not shared across DLL boundaries! You will need to call SetCurrentContext() + SetAllocatorFunctions()
		//   for each static/DLL boundary you are calling from. Read "Context and Memory Allocators" section of imgui.cpp for details.
		// MODULE_FUNC(CreateContext);
		// MODULE_FUNC(DestroyContext);   // NULL = destroy current context
		// MODULE_FUNC(GetCurrentContext);
		// MODULE_FUNC(SetCurrentContext);

		// Main
		MODULE_FUNC(GetIO);                                    // access the IO structure (mouse/keyboard/gamepad inputs, time, various configuration options/flags)
		// MODULE_FUNC(GetStyle);                                 // access the Style structure (colors, sizes). Always use PushStyleColor(), PushStyleVar() to modify style mid-frame!
		// MODULE_FUNC(NewFrame);                                 // start a new Dear ImGui frame, you can submit any command from this point until Render()/EndFrame().
		// MODULE_FUNC(EndFrame);                                 // ends the Dear ImGui frame. automatically called by Render(). If you don't need to render data (skipping rendering) you may call EndFrame() without Render()... but you'll have wasted CPU already! If you don't need to render, better to not create any windows and not call NewFrame() at all!
		// MODULE_FUNC(Render);                                   // ends the Dear ImGui frame, finalize the draw data. You can then get call GetDrawData().
		// MODULE_FUNC(GetDrawData);                              // valid after Render() and until the next call to NewFrame(). this is what you have to render.

		// Demo, Debug, Information
		MODULE_FUNC(ShowDemoWindow);        // create Demo window. demonstrate most ImGui features. call this to learn about the library! try to make it always available in your application!
		MODULE_FUNC(ShowMetricsWindow);     // create Metrics/Debugger window. display Dear ImGui internals: windows, draw commands, various internal state, etc.
		MODULE_FUNC(ShowDebugLogWindow);    // create Debug Log window. display a simplified log of important dear imgui events.
		MODULE_FUNC(ShowIDStackToolWindow); // create Stack Tool window. hover items with mouse to query information about the source of their unique ID.
		MODULE_FUNC(ShowAboutWindow);       // create About window. display Dear ImGui version, credits and build/system information.
		// MODULE_FUNC(ShowStyleEditor);    // add style editor block (not a window). you can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it uses the default style)
		MODULE_FUNC(ShowStyleSelector);       // add style selector block (not a window), essentially a combo listing the default styles.
		MODULE_FUNC(ShowFontSelector);        // add font selector block (not a window), essentially a combo listing the loaded fonts.
		MODULE_FUNC(ShowUserGuide);                            // add basic help/info block (not a window): how to manipulate ImGui as an end-user (mouse/keyboard controls).
		MODULE_FUNC(GetVersion);                               // get the compiled version string e.g. "1.80 WIP" (essentially the value for IMGUI_VERSION from the compiled version of imgui.cpp)

		// Styles
		MODULE_FUNC(StyleColorsDark);    // new, recommended style (default)
		MODULE_FUNC(StyleColorsLight);   // best used with borders and a custom, thicker font
		MODULE_FUNC(StyleColorsClassic); // classic imgui style

		// Windows
		// - Begin() = push window to the stack and start appending to it. End() = pop window from the stack.
		// - Passing 'bool* p_open != NULL' shows a window-closing widget in the upper-right corner of the window,
		//   which clicking will set the boolean to false when clicked.
		// - You may append multiple times to the same window during the same frame by calling Begin()/End() pairs multiple times.
		//   Some information such as 'flags' or 'p_open' will only be considered by the first call to Begin().
		// - Begin() return false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting
		//   anything to the window. Always call a matching End() for each Begin() call, regardless of its return value!
		//   [Important: due to legacy reason, Begin/End and BeginChild/EndChild are inconsistent with all other functions
		//    such as BeginMenu/EndMenu, BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding
		//    BeginXXX function returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
		// - Note that the bottom of window stack always contains a window called "Debug".
		MODULE_FUNC(Begin);
		MODULE_FUNC(End);

		// Child Windows
		// - Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window. Child windows can embed their own child.
		// - Before 1.90 (November 2023), the "ImGuiChildFlags child_flags = 0" parameter was "bool border = false".
		//   This API is backward compatible with old code, as we guarantee that ImGuiChildFlags_Border == true.
		//   Consider updating your old code:
		//      BeginChild("Name", size, false)   -> Begin("Name", size, 0); or Begin("Name", size, ImGuiChildFlags_None);
		//      BeginChild("Name", size, true)    -> Begin("Name", size, ImGuiChildFlags_Border);
		// - Manual sizing (each axis can use a different setting e.g. ImVec2(0.0f, 400.0f)):
		//     == 0.0f: use remaining parent window size for this axis.
		//      > 0.0f: use specified size for this axis.
		//      < 0.0f: right/bottom-align to specified distance from available content boundaries.
		// - Specifying ImGuiChildFlags_AutoResizeX or ImGuiChildFlags_AutoResizeY makes the sizing automatic based on child contents.
		//   Combining both ImGuiChildFlags_AutoResizeX _and_ ImGuiChildFlags_AutoResizeY defeats purpose of a scrolling region and is NOT recommended.
		// - BeginChild() returns false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting
		//   anything to the window. Always call a matching EndChild() for each BeginChild() call, regardless of its return value.
		//   [Important: due to legacy reason, Begin/End and BeginChild/EndChild are inconsistent with all other functions
		//    such as BeginMenu/EndMenu, BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding
		//    BeginXXX function returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]
		// MODULE_FUNC(BeginChild);
		// MODULE_FUNC(BeginChild);
		// MODULE_FUNC(EndChild);

		// Windows Utilities
		// - 'current window' = the window we are appending into while inside a Begin()/End() block. 'next window' = next window we will Begin() into.
		MODULE_FUNC(IsWindowAppearing);
		MODULE_FUNC(IsWindowCollapsed);
		MODULE_FUNC(IsWindowFocused); // is current window focused? or its root/child, depending on flags. see flags for options.
		MODULE_FUNC(IsWindowHovered); // is current window hovered and hoverable (e.g. not blocked by a popup/modal)? See ImGuiHoveredFlags_ for options. IMPORTANT: If you are trying to check whether your mouse should be dispatched to Dear ImGui or to your underlying app, you should not use this function! Use the 'io.WantCaptureMouse' boolean for that! Refer to FAQ entry "How can I tell whether to dispatch mouse/keyboard to Dear ImGui or my application?" for details.
		// MODULE_FUNC(GetWindowDrawList);                        // get draw list associated to the current window, to append your own drawing primitives
		MODULE_FUNC(GetWindowPos);                             // get current window position in screen space (note: it is unlikely you need to use this. Consider using current layout pos instead, GetCursorScreenPos())
		MODULE_FUNC(GetWindowSize);                            // get current window size (note: it is unlikely you need to use this. Consider using GetCursorScreenPos() and e.g. GetContentRegionAvail() instead)
		MODULE_FUNC(GetWindowWidth);                           // get current window width (shortcut for GetWindowSize().x)
		MODULE_FUNC(GetWindowHeight);                          // get current window height (shortcut for GetWindowSize().y)

		// Window manipulation
		// - Prefer using SetNextXXX functions (before Begin) rather that SetXXX functions (after Begin).
		// MODULE_FUNC(SetNextWindowPos); // set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc.
		// MODULE_FUNC(SetNextWindowSize);                  // set next window size. set axis to 0.0f to force an auto-fit on this axis. call before Begin()
		// MODULE_FUNC(SetNextWindowSizeConstraints); // set next window size limits. use 0.0f or FLT_MAX if you don't want limits. Use -1 for both min and max of same axis to preserve current size (which itself is a constraint). Use callback to apply non-trivial programmatic constraints.
		// MODULE_FUNC(SetNextWindowContentSize);                               // set next window content size (~ scrollable client area, which enforce the range of scrollbars). Not including window decorations (title bar, menu bar, etc.) nor WindowPadding. set an axis to 0.0f to leave it automatic. call before Begin()
		// MODULE_FUNC(SetNextWindowCollapsed);                 // set next window collapsed state. call before Begin()
		// MODULE_FUNC(SetNextWindowFocus);                                                       // set next window to be focused / top-most. call before Begin()
		// MODULE_FUNC(SetNextWindowScroll);                                  // set next window scrolling value (use < 0.0f to not affect a given axis).
		// MODULE_FUNC(SetNextWindowBgAlpha);                                          // set next window background color alpha. helper to easily override the Alpha component of ImGuiCol_WindowBg/ChildBg/PopupBg. you may also use ImGuiWindowFlags_NoBackground.
		MODULE_FUNC(SetWindowPos);                        // (not recommended) set current window position - call within Begin()/End(). prefer using SetNextWindowPos(), as this may incur tearing and side-effects.	 // set named window position.
		MODULE_FUNC(SetWindowSize);                      // (not recommended) set current window size - call within Begin()/End(). set to ImVec2(0, 0) to force an auto-fit. prefer using SetNextWindowSize(), as this may incur tearing and minor side-effects.	   // set named window size. set axis to 0.0f to force an auto-fit on this axis.
		// MODULE_FUNC(SetWindowCollapsed);                     // (not recommended) set current window collapsed state. prefer using SetNextWindowCollapsed().
		// MODULE_FUNC(SetWindowFocus);                                                           // (not recommended) set current window to be focused / top-most. prefer using SetNextWindowFocus().
		// MODULE_FUNC(SetWindowFontScale);                                            // [OBSOLETE] set font scale. Adjust IO.FontGlobalScale if you want to scale all windows. This is an old API! For correct scaling, prefer to reload font + rebuild ImFontAtlas + call style.ScaleAllSizes().
		// MODULE_FUNC(SetWindowCollapsed);   // set named window collapsed state
		MODULE_FUNC(SetWindowFocus);                                           // set named window to be focused / top-most. use NULL to remove focus.

		// Content region
		// - Retrieve available space from a given point. GetContentRegionAvail() is frequently useful.
		// - Those functions are bound to be redesigned (they are confusing, incomplete and the Min/Max return values are in local window coordinates which increases confusion)
		// MODULE_FUNC(GetContentRegionAvail);                                        // == GetContentRegionMax() - GetCursorPos()
		// MODULE_FUNC(GetContentRegionMax);                                          // current content boundaries (typically window boundaries including scrolling, or current column boundaries), in windows coordinates
		// MODULE_FUNC(GetWindowContentRegionMin);                                    // content boundaries min for the full window (roughly (0,0)-Scroll), in window coordinates
		// MODULE_FUNC(GetWindowContentRegionMax);                                    // content boundaries max for the full window (roughly (0,0)+Size-Scroll) where Size can be overridden with SetNextWindowContentSize(), in window coordinates

		// Windows Scrolling
		// - Any change of Scroll will be applied at the beginning of next frame in the first call to Begin().
		// - You may instead use SetNextWindowScroll() prior to calling Begin() to avoid this delay, as an alternative to using SetScrollX()/SetScrollY().
		MODULE_FUNC(GetScrollX);                                                   // get scrolling amount [0 .. GetScrollMaxX()]
		MODULE_FUNC(GetScrollY);                                                   // get scrolling amount [0 .. GetScrollMaxY()]
		MODULE_FUNC(SetScrollX);                                     // set scrolling amount [0 .. GetScrollMaxX()]
		MODULE_FUNC(SetScrollY);                                     // set scrolling amount [0 .. GetScrollMaxY()]
		MODULE_FUNC(GetScrollMaxX);                                                // get maximum scrolling amount ~~ ContentSize.x - WindowSize.x - DecorationsSize.x
		MODULE_FUNC(GetScrollMaxY);                                                // get maximum scrolling amount ~~ ContentSize.y - WindowSize.y - DecorationsSize.y
		MODULE_FUNC(SetScrollHereX);                    // adjust scrolling amount to make current cursor position visible. center_x_ratio=0.0: left, 0.5: center, 1.0: right. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead.
		MODULE_FUNC(SetScrollHereY);                    // adjust scrolling amount to make current cursor position visible. center_y_ratio=0.0: top, 0.5: center, 1.0: bottom. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead.
		// MODULE_FUNC(SetScrollFromPosX);  // adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.
		// MODULE_FUNC(SetScrollFromPosY);  // adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.

		// Parameters stacks (shared)
		// MODULE_FUNC(PushFont);                                         // use NULL as a shortcut to push default font
		MODULE_FUNC(PopFont);
		MODULE_FUNC(PushStyleColor);                        // modify a style color. always use this if you modify the style after NewFrame().
		MODULE_FUNC(PopStyleColor);
		// MODULE_FUNC(PushStyleVar);                     // modify a style float variable. always use this if you modify the style after NewFrame().
		// MODULE_FUNC(PushStyleVar);             // modify a style ImVec2 variable. always use this if you modify the style after NewFrame().
		// MODULE_FUNC(PopStyleVar);
		// MODULE_FUNC(PushTabStop);                                     // == tab stop enable. Allow focusing using TAB/Shift-TAB, enabled by default but you can disable it for certain widgets
		// MODULE_FUNC(PopTabStop);
		// MODULE_FUNC(PushButtonRepeat);                                  // in 'repeat' mode, Button*() functions return repeated true in a typematic manner (using io.KeyRepeatDelay/io.KeyRepeatRate setting). Note that you can call IsItemActive() after any Button() to tell if the button is held in the current frame.
		// MODULE_FUNC(PopButtonRepeat);

		// Parameters stacks (current window)
		// MODULE_FUNC(PushItemWidth);                                // push width of items for common large "item+label" widgets. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side).
		// MODULE_FUNC(PopItemWidth);
		// MODULE_FUNC(SetNextItemWidth);                             // set width of the _next_ common large "item+label" widget. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side)
		// MODULE_FUNC(CalcItemWidth);                                                // width of item given pushed settings and current cursor position. NOT necessarily the width of last item unlike most 'Item' functions.
		// MODULE_FUNC(PushTextWrapPos);                 // push word-wrapping position for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space
		// MODULE_FUNC(PopTextWrapPos);

		// Style read access
		// - Use the ShowStyleEditor() function to interactively see/edit the colors.
		MODULE_FUNC(GetFont);                                                      // get current font
		// MODULE_FUNC(GetFontSize);                                                  // get current font size (= height in pixels) of current font with current scale applied
		// MODULE_FUNC(GetFontTexUvWhitePixel);                                       // get UV coordinate for a while pixel, useful to draw custom shapes via the ImDrawList API
		// MODULE_FUNC(GetColorU32);              // retrieve given style color with style alpha applied and optional extra alpha multiplier, packed as a 32-bit value suitable for ImDrawList
		// MODULE_FUNC(GetColorU32);                                 // retrieve given color with style alpha applied, packed as a 32-bit value suitable for ImDrawList
		// MODULE_FUNC(GetColorU32);                 // retrieve given color with style alpha applied, packed as a 32-bit value suitable for ImDrawList
		// MODULE_FUNC(GetStyleColorVec4);                                // retrieve style color as stored in ImGuiStyle structure. use to feed back into PushStyleColor(), otherwise use GetColorU32() to get style color with style alpha baked in.

		// Layout cursor positioning
		// - By "cursor" we mean the current output position.
		// - The typical widget behavior is to output themselves at the current cursor position, then move the cursor one line down.
		// - You can call SameLine() between widgets to undo the last carriage return and output at the right of the preceding widget.
		// - Attention! We currently have inconsistencies between window-local and absolute positions we will aim to fix with future API:
		//    - Absolute coordinate:        GetCursorScreenPos(), SetCursorScreenPos(), all ImDrawList:: functions. -> this is the preferred way forward.
		//    - Window-local coordinates:   SameLine(), GetCursorPos(), SetCursorPos(), GetCursorStartPos(), GetContentRegionMax(), GetWindowContentRegion*(), PushTextWrapPos()
		// - GetCursorScreenPos() = GetCursorPos() + GetWindowPos(). GetWindowPos() is almost only ever useful to convert from window-local to absolute coordinates.
		// MODULE_FUNC(GetCursorScreenPos);                                           // cursor position in absolute coordinates (prefer using this, also more useful to work with ImDrawList API).
		// MODULE_FUNC(SetCursorScreenPos);                          // cursor position in absolute coordinates
		// MODULE_FUNC(GetCursorPos);                                                 // [window-local] cursor position in window coordinates (relative to window position)
		// MODULE_FUNC(GetCursorPosX);                                                // [window-local] "
		// MODULE_FUNC(GetCursorPosY);                                                // [window-local] "
		// MODULE_FUNC(SetCursorPos);                          // [window-local] "
		// MODULE_FUNC(SetCursorPosX);                                   // [window-local] "
		// MODULE_FUNC(SetCursorPosY);                                   // [window-local] "
		// MODULE_FUNC(GetCursorStartPos);                                            // [window-local] initial cursor position, in window coordinates

		// Other layout functions
		MODULE_FUNC(Separator);                                                    // separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator.
		MODULE_FUNC(SameLine);  // call between widgets or groups to layout them horizontally. X position given in window coordinates.
		MODULE_FUNC(NewLine);                                                      // undo a SameLine() or force a new line when in a horizontal-layout context.
		MODULE_FUNC(Spacing);                                                      // add vertical spacing.
		MODULE_FUNC(Dummy);                                      // add a dummy item of given size. unlike InvisibleButton(), Dummy() won't take the mouse click or be navigable into.
		MODULE_FUNC(Indent);                                  // move content position toward the right, by indent_w, or style.IndentSpacing if indent_w <= 0
		MODULE_FUNC(Unindent);                                // move content position back to the left, by indent_w, or style.IndentSpacing if indent_w <= 0
		MODULE_FUNC(BeginGroup);                                                   // lock horizontal starting position
		MODULE_FUNC(EndGroup);                                                     // unlock horizontal starting position + capture the whole group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)
		// MODULE_FUNC(AlignTextToFramePadding);                                      // vertically align upcoming text baseline to FramePadding.y so that it will align properly to regularly framed items (call if you have text on a line before a framed item)
		// MODULE_FUNC(GetTextLineHeight);                                            // ~ FontSize
		// MODULE_FUNC(GetTextLineHeightWithSpacing);                                 // ~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)
		// MODULE_FUNC(GetFrameHeight);                                               // ~ FontSize + style.FramePadding.y * 2
		// MODULE_FUNC(GetFrameHeightWithSpacing);                                    // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)

		// ID stack/scopes
		// Read the FAQ (docs/FAQ.md or http://dearimgui.com/faq) for more details about how ID are handled in dear imgui.
		// - Those questions are answered and impacted by understanding of the ID stack system:
		//   - "Q: Why is my widget not reacting when I click on it?"
		//   - "Q: How can I have widgets with an empty label?"
		//   - "Q: How can I have multiple widgets with the same label?"
		// - Short version: ID are hashes of the entire ID stack. If you are creating widgets in a loop you most likely
		//   want to push a unique identifier (e.g. object pointer, loop index) to uniquely differentiate them.
		// - You can also use the "Label##foobar" syntax within widget label to distinguish them from each others.
		// - In this header file we use the "label"/"name" terminology to denote a string that will be displayed + used as an ID,
		//   whereas "str_id" denote a string that is only used as an ID and not normally displayed.
		// MODULE_FUNC(PushID);                                     // push string into the ID stack (will hash string).
		// MODULE_FUNC(PushID);       // push string into the ID stack (will hash string).
		// MODULE_FUNC(PushID);                                     // push pointer into the ID stack (will hash pointer).
		// MODULE_FUNC(PushID);                                             // push integer into the ID stack (will hash integer).
		// MODULE_FUNC(PopID);                                                        // pop from the ID stack.
		// MODULE_FUNC(GetID);                                      // calculate unique ID (hash of whole ID stack + given parameter). e.g. if you want to query into ImGuiStorage yourself
		// MODULE_FUNC(GetID);
		// MODULE_FUNC(GetID);

		// Widgets: Text
		MODULE_FUNC(TextUnformatted); // raw text without formatting. Roughly equivalent to Text("%s", text) but: A) doesn't require null terminated string if 'text_end' is specified, B) it's faster, no memory copy is done, no buffer size limits, recommended for long chunks of text.
		MODULE_FUNC(Text); // formatted text
		// MODULE_FUNC(TextV);
		MODULE_FUNC(TextColored); // shortcut for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
		// MODULE_FUNC(TextColoredV);
		MODULE_FUNC(TextDisabled); // shortcut for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
		// MODULE_FUNC(TextDisabledV);
		MODULE_FUNC(TextWrapped); // shortcut for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. Note that this won't work on an auto-resizing window if there's no other widgets to extend the window width, yoy may need to set a size using SetNextWindowSize().
		// MODULE_FUNC(TextWrappedV);
		MODULE_FUNC(LabelText); // display text+label aligned the same way as value+label widgets
		// MODULE_FUNC(LabelTextV);
		// MODULE_FUNC(BulletText); // shortcut for Bullet()+Text()
		// MODULE_FUNC(BulletTextV);
		MODULE_FUNC(SeparatorText);                               // currently: formatted text with an horizontal line

		// Widgets: Main
		// - Most widgets return true when the value has been changed or when pressed/selected
		// - You may also use one of the many IsItemXXX functions (e.g. IsItemActive, IsItemHovered, etc.) to query widget state.
		MODULE_FUNC(Button);   // button
		MODULE_FUNC(SmallButton);                                 // button with (FramePadding.y == 0) to easily embed within text
		// MODULE_FUNC(InvisibleButton); // flexible button behavior without the visuals, frequently useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)
		MODULE_FUNC(ArrowButton);                  // square button with an arrow shape
		MODULE_FUNC(Checkbox);
		// MODULE_FUNC(CheckboxFlags);
		// MODULE_FUNC(CheckboxFlags);
		MODULE_FUNC(RadioButton);                    // use with e.g. if (RadioButton("one", my_value==1)) { my_value = 1; }	          // shortcut to handle the above pattern when value is an integer
		MODULE_FUNC(ProgressBar);
		// MODULE_FUNC(Bullet);                                                       // draw a small circle + keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses

		// Widgets: Images
		// - Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
		// - 'uv0' and 'uv1' are texture coordinates. Read about them from the same link above.
		// - Note that Image() may add +2.0f to provided size if a border is visible, ImageButton() adds style.FramePadding*2.0f to provided size.
		MODULE_FUNC(Image);
		MODULE_FUNC(ImageButton);

		// Widgets: Combo Box (Dropdown)
		// - The BeginCombo()/EndCombo() api allows you to manage your contents and selection state however you want it, by creating e.g. Selectable() items.
		// - The old Combo() api are helpers over BeginCombo()/EndCombo() which are kept available for convenience purpose. This is analogous to how ListBox are created.
		MODULE_FUNC(BeginCombo);
		MODULE_FUNC(EndCombo); // only call EndCombo() if BeginCombo() returns true!
		MODULE_FUNC(Combo);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"

		// Widgets: Drag Sliders
		// - CTRL+Click on any drag box to turn them into an input box. Manually input values aren't clamped by default and can go off-bounds. Use ImGuiSliderFlags_AlwaysClamp to always clamp.
		// - For all the Float2/Float3/Float4/Int2/Int3/Int4 versions of every function, note that a 'float v[X]' function argument is the same as 'float* v',
		//   the array syntax is just a way to document the number of elements that are expected to be accessible. You can pass address of your first element out of a contiguous set, e.g. &myvector.x
		// - Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
		// - Format string may also be set to NULL or use the default format ("%f" or "%d").
		// - Speed are per-pixel of mouse movement (v_speed=0.2f: mouse needs to move by 5 pixels to increase value by 1). For gamepad/keyboard navigation, minimum speed is Max(v_speed, minimum_step_at_given_precision).
		// - Use v_min < v_max to clamp edits to given limits. Note that CTRL+Click manual input can override those limits if ImGuiSliderFlags_AlwaysClamp is not used.
		// - Use v_max = FLT_MAX / INT_MAX etc to avoid clamping to a maximum, same with v_min = -FLT_MAX / INT_MIN to avoid clamping to a minimum.
		// - We use the same sets of flags for DragXXX() and SliderXXX() functions as the features are the same and it makes it easier to swap them.
		// - Legacy: Pre-1.78 there are DragXXX() function signatures that take a final `float power=1.0f' argument instead of the `ImGuiSliderFlags flags=0' argument.
		//   If you get a warning converting a float to ImGuiSliderFlags, read https://github.com/ocornut/imgui/issues/3361
		MODULE_FUNC(DragFloat);     // If v_min >= v_max we have no bound
		MODULE_FUNC(DragFloat2);
		MODULE_FUNC(DragFloat3);
		MODULE_FUNC(DragFloat4);
		MODULE_FUNC(DragFloatRange2);
		MODULE_FUNC(DragInt);  // If v_min >= v_max we have no bound
		MODULE_FUNC(DragInt2);
		MODULE_FUNC(DragInt3);
		MODULE_FUNC(DragInt4);
		MODULE_FUNC(DragIntRange2);
		// MODULE_FUNC(DragScalar);
		// MODULE_FUNC(DragScalarN);

		// Widgets: Regular Sliders
		// - CTRL+Click on any slider to turn them into an input box. Manually input values aren't clamped by default and can go off-bounds. Use ImGuiSliderFlags_AlwaysClamp to always clamp.
		// - Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
		// - Format string may also be set to NULL or use the default format ("%f" or "%d").
		// - Legacy: Pre-1.78 there are SliderXXX() function signatures that take a final `float power=1.0f' argument instead of the `ImGuiSliderFlags flags=0' argument.
		//   If you get a warning converting a float to ImGuiSliderFlags, read https://github.com/ocornut/imgui/issues/3361
		MODULE_FUNC(SliderFloat);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display.
		MODULE_FUNC(SliderFloat2);
		MODULE_FUNC(SliderFloat3);
		MODULE_FUNC(SliderFloat4);
		MODULE_FUNC(SliderAngle);
		MODULE_FUNC(SliderInt);
		MODULE_FUNC(SliderInt2);
		MODULE_FUNC(SliderInt3);
		MODULE_FUNC(SliderInt4);
		// MODULE_FUNC(SliderScalar);
		// MODULE_FUNC(SliderScalarN);
		// MODULE_FUNC(VSliderFloat);
		// MODULE_FUNC(VSliderInt);
		// MODULE_FUNC(VSliderScalar);

		// Widgets: Input with Keyboard
		// - If you want to use InputText() with std::string or any custom dynamic string type, see misc/cpp/imgui_stdlib.h and comments in imgui_demo.cpp.
		// - Most of the ImGuiInputTextFlags flags are only useful for InputText() and not for InputFloatX, InputIntX, InputDouble etc.
		MODULE_FUNC(InputText);
		MODULE_FUNC(InputTextMultiline);
		// MODULE_FUNC(InputTextWithHint);
		MODULE_FUNC(InputFloat);
		MODULE_FUNC(InputFloat2);
		MODULE_FUNC(InputFloat3);
		MODULE_FUNC(InputFloat4);
		MODULE_FUNC(InputInt);
		MODULE_FUNC(InputInt2);
		MODULE_FUNC(InputInt3);
		MODULE_FUNC(InputInt4);
		MODULE_FUNC(InputDouble);
		// MODULE_FUNC(InputScalar);
		// MODULE_FUNC(InputScalarN);

		// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little color square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
		// - Note that in C++ a 'float v[X]' function argument is the _same_ as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible.
		// - You can pass the address of a first float element out of a contiguous structure, e.g. &myvector.x
		// MODULE_FUNC(ColorEdit3);
		// MODULE_FUNC(ColorEdit4);
		// MODULE_FUNC(ColorPicker3);
		// MODULE_FUNC(ColorPicker4);
		// MODULE_FUNC(ColorButton); // display a color square/button, hover for details, return true when pressed.
		// MODULE_FUNC(SetColorEditOptions);                     // initialize current options (generally on application startup) if you want to select a default format, picker type, etc. User will be able to change many settings, unless you pass the _NoOptions flag to your calls.

		// Widgets: Trees
		// - TreeNode functions return true when the node is open, in which case you need to also call TreePop() when you are finished displaying the tree node contents.
		MODULE_FUNC(TreeNode);   // helper variation to easily decorelate the id from the displayed string. Read the FAQ about why and how to use ID. to align arbitrary text at the same level as a TreeNode() you can use Bullet().
		// MODULE_FUNC(TreeNodeV);
		// MODULE_FUNC(TreeNodeV);
		MODULE_FUNC(TreeNodeEx);
		// MODULE_FUNC(TreeNodeExV);
		// MODULE_FUNC(TreeNodeExV);
		MODULE_FUNC(TreePush);                                       // ~ Indent()+PushID(). Already called by TreeNode() when returning true, but you can call TreePush/TreePop yourself if desired.
		MODULE_FUNC(TreePop);                                                          // ~ Unindent()+PopID()
		MODULE_FUNC(GetTreeNodeToLabelSpacing);                                        // horizontal distance preceding label when using TreeNode*() or Bullet() == (g.FontSize + style.FramePadding.x*2) for a regular unframed TreeNode
		// MODULE_FUNC(CollapsingHeader);  // if returning 'true' the header is open. doesn't indent nor push on ID stack. user doesn't have to call TreePop().
		// MODULE_FUNC(CollapsingHeader); // when 'p_visible != NULL': if '*p_visible==true' display an additional small close button on upper right of the header which will set the bool to false when clicked, if '*p_visible==false' don't display the header.
		// MODULE_FUNC(SetNextItemOpen);                  // set next TreeNode/CollapsingHeader open state.

		// Widgets: Selectables
		// - A selectable highlights when hovered, and can display another color when selected.
		// - Neighbors selectable extend their highlight bounds in order to leave no gap between them. This is so a series of selected Selectable appear contiguous.
		MODULE_FUNC(Selectable); // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height	  // "bool* p_selected" point to the selection state (read-write), as a convenient helper.

		// Widgets: List Boxes
		// - This is essentially a thin wrapper to using BeginChild/EndChild with the ImGuiChildFlags_FrameStyle flag for stylistic changes + displaying a label.
		// - You can submit contents and manage your selection state however you want it, by creating e.g. Selectable() or any other items.
		// - The simplified/old ListBox() api are helpers over BeginListBox()/EndListBox() which are kept available for convenience purpose. This is analoguous to how Combos are created.
		// - Choose frame width:   size.x > 0.0f: custom  /  size.x < 0.0f or -FLT_MIN: right-align   /  size.x = 0.0f (default): use current ItemWidth
		// - Choose frame height:  size.y > 0.0f: custom  /  size.y < 0.0f or -FLT_MIN: bottom-align  /  size.y = 0.0f (default): arbitrary default height which can fit ~7 items
		MODULE_FUNC(BeginListBox); // open a framed scrolling region
		MODULE_FUNC(EndListBox);                                                       // only call EndListBox() if BeginListBox() returned true!
		MODULE_FUNC(ListBox);

		// Widgets: Data Plotting
		// - Consider using ImPlot (https://github.com/epezent/implot) which is much better!
		// MODULE_FUNC(PlotLines);
		// MODULE_FUNC(PlotLines);
		// MODULE_FUNC(PlotHistogram);
		// MODULE_FUNC(PlotHistogram);

		// Widgets: Value() Helpers.
		// - Those are merely shortcut to calling Text() with a format string. Output single value in "name: value" format (tip: freely declare more in your code to handle your types. you can add functions to the ImGui namespace)
		// MODULE_FUNC(Value);
		// MODULE_FUNC(Value);
		// MODULE_FUNC(Value);
		// MODULE_FUNC(Value);

		// Widgets: Menus
		// - Use BeginMenuBar() on a window ImGuiWindowFlags_MenuBar to append to its menu bar.
		// - Use BeginMainMenuBar() to create a menu bar at the top of the screen and append to it.
		// - Use BeginMenu() to create a menu. You can call BeginMenu() multiple time with the same identifier to append more items to it.
		// - Not that MenuItem() keyboardshortcuts are displayed as a convenience but _not processed_ by Dear ImGui at the moment.
		MODULE_FUNC(BeginMenuBar);                                                     // append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set on parent window).
		MODULE_FUNC(EndMenuBar);                                                       // only call EndMenuBar() if BeginMenuBar() returns true!
		// MODULE_FUNC(BeginMainMenuBar);                                                 // create and append to a full screen menu-bar.
		// MODULE_FUNC(EndMainMenuBar);                                                   // only call EndMainMenuBar() if BeginMainMenuBar() returns true!
		MODULE_FUNC(BeginMenu);                  // create a sub-menu entry. only call EndMenu() if this returns true!
		MODULE_FUNC(EndMenu);                                                          // only call EndMenu() if BeginMenu() returns true!
		MODULE_FUNC(MenuItem);  // return true when activated.             // return true when activated + toggle (*p_selected) if p_selected != NULL

		// Tooltips
		// - Tooltips are windows following the mouse. They do not take focus away.
		// - A tooltip window can contain items of any types. SetTooltip() is a shortcut for the 'if (BeginTooltip()) { Text(...); EndTooltip(); }' idiom.
		MODULE_FUNC(BeginTooltip);                                                     // begin/append a tooltip window.
		MODULE_FUNC(EndTooltip);                                                       // only call EndTooltip() if BeginTooltip()/BeginItemTooltip() returns true!
		MODULE_FUNC(SetTooltip);                     // set a text-only tooltip. Often used after a ImGui::IsItemHovered() check. Override any previous call to SetTooltip().
		// MODULE_FUNC(SetTooltipV);

		// Tooltips: helpers for showing a tooltip when hovering an item
		// - BeginItemTooltip() is a shortcut for the 'if (IsItemHovered(ImGuiHoveredFlags_ForTooltip) && BeginTooltip())' idiom.
		// - SetItemTooltip() is a shortcut for the 'if (IsItemHovered(ImGuiHoveredFlags_ForTooltip)) { SetTooltip(...); }' idiom.
		// - Where 'ImGuiHoveredFlags_ForTooltip' itself is a shortcut to use 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav' depending on active input type. For mouse it defaults to 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort'.
		MODULE_FUNC(BeginItemTooltip);                                                 // begin/append a tooltip window if preceding item was hovered.
		MODULE_FUNC(SetItemTooltip);                 // set a text-only tooltip if preceeding item was hovered. override any previous call to SetTooltip().
		// MODULE_FUNC(SetItemTooltipV);

		// Popups, Modals
		//  - They block normal mouse hovering detection (and therefore most mouse interactions) behind them.
		//  - If not modal: they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
		//  - Their visibility state (~bool) is held internally instead of being held by the programmer as we are used to with regular Begin*() calls.
		//  - The 3 properties above are related: we need to retain popup visibility state in the library because popups may be closed as any time.
		//  - You can bypass the hovering restriction by using ImGuiHoveredFlags_AllowWhenBlockedByPopup when calling IsItemHovered() or IsWindowHovered().
		//  - IMPORTANT: Popup identifiers are relative to the current ID stack, so OpenPopup and BeginPopup generally needs to be at the same level of the stack.
		//    This is sometimes leading to confusing mistakes. May rework this in the future.
		//  - BeginPopup(): query popup state, if open start appending into the window. Call EndPopup() afterwards if returned true. ImGuiWindowFlags are forwarded to the window.
		//  - BeginPopupModal(): block every interaction behind the window, cannot be closed by user, add a dimming background, has a title bar.
		MODULE_FUNC(BeginPopup);                         // return true if the popup is open, and you can start outputting to it.
		// MODULE_FUNC(BeginPopupModal); // return true if the modal is open, and you can start outputting to it.
		MODULE_FUNC(EndPopup);                                                                         // only call EndPopup() if BeginPopupXXX() returns true!

		// Popups: open/close functions
		//  - OpenPopup(): set popup state to open. ImGuiPopupFlags are available for opening options.
		//  - If not modal: they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
		//  - CloseCurrentPopup(): use inside the BeginPopup()/EndPopup() scope to close manually.
		//  - CloseCurrentPopup() is called by default by Selectable()/MenuItem() when activated (FIXME: need some options).
		//  - Use ImGuiPopupFlags_NoOpenOverExistingPopup to avoid opening a popup if there's already one at the same level. This is equivalent to e.g. testing for !IsAnyPopupOpen() prior to OpenPopup().
		//  - Use IsWindowAppearing() after BeginPopup() to tell if a window just opened.
		//  - IMPORTANT: Notice that for OpenPopupOnItemClick() we exceptionally default flags to 1 (== ImGuiPopupFlags_MouseButtonRight) for backward compatibility with older API taking 'int mouse_button = 1' parameter
		MODULE_FUNC(OpenPopup);                     // call to mark popup as open (don't call every frame!).		 // id overload to facilitate calling from nested stacks                    
		// MODULE_FUNC(OpenPopupOnItemClick);   // helper to open popup when clicked on last item. Default to ImGuiPopupFlags_MouseButtonRight == 1. (note: actually triggers on the mouse _released_ event to be consistent with popup behaviors)
		// MODULE_FUNC(CloseCurrentPopup);                                                                // manually close the popup we have begin-ed into.

		// Popups: open+begin combined functions helpers
		//  - Helpers to do OpenPopup+BeginPopup where the Open action is triggered by e.g. hovering an item and right-clicking.
		//  - They are convenient to easily create context menus, hence the name.
		//  - IMPORTANT: Notice that BeginPopupContextXXX takes ImGuiPopupFlags just like OpenPopup() and unlike BeginPopup(). For full consistency, we may add ImGuiWindowFlags to the BeginPopupContextXXX functions in the future.
		//  - IMPORTANT: Notice that we exceptionally default their flags to 1 (== ImGuiPopupFlags_MouseButtonRight) for backward compatibility with older API taking 'int mouse_button = 1' parameter, so if you add other flags remember to re-add the ImGuiPopupFlags_MouseButtonRight.
		MODULE_FUNC(BeginPopupContextItem);  // open+begin popup when clicked on last item. Use str_id==NULL to associate the popup to previous item. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!
		// MODULE_FUNC(BeginPopupContextWindow);// open+begin popup when clicked on current window.
		// MODULE_FUNC(BeginPopupContextVoid);  // open+begin popup when clicked in void (where there are no windows).

		// Popups: query functions
		//  - IsPopupOpen(): return true if the popup is open at the current BeginPopup() level of the popup stack.
		//  - IsPopupOpen() with ImGuiPopupFlags_AnyPopupId: return true if any popup is open at the current BeginPopup() level of the popup stack.
		//  - IsPopupOpen() with ImGuiPopupFlags_AnyPopupId + ImGuiPopupFlags_AnyPopupLevel: return true if any popup is open.
		// MODULE_FUNC(IsPopupOpen);                         // return true if the popup is open.

		// Tables
		// - Full-featured replacement for old Columns API.
		// - See Demo->Tables for demo code. See top of imgui_tables.cpp for general commentary.
		// - See ImGuiTableFlags_ and ImGuiTableColumnFlags_ enums for a description of available flags.
		// The typical call flow is:
		// - 1. Call BeginTable(), early out if returning false.
		// - 2. Optionally call TableSetupColumn() to submit column name/flags/defaults.
		// - 3. Optionally call TableSetupScrollFreeze() to request scroll freezing of columns/rows.
		// - 4. Optionally call TableHeadersRow() to submit a header row. Names are pulled from TableSetupColumn() data.
		// - 5. Populate contents:
		//    - In most situations you can use TableNextRow() + TableSetColumnIndex(N) to start appending into a column.
		//    - If you are using tables as a sort of grid, where every column is holding the same type of contents,
		//      you may prefer using TableNextColumn() instead of TableNextRow() + TableSetColumnIndex().
		//      TableNextColumn() will automatically wrap-around into the next row if needed.
		//    - IMPORTANT: Comparatively to the old Columns() API, we need to call TableNextColumn() for the first column!
		//    - Summary of possible call flow:
		//        - TableNextRow() -> TableSetColumnIndex(0) -> Text("Hello 0") -> TableSetColumnIndex(1) -> Text("Hello 1")  // OK
		//        - TableNextRow() -> TableNextColumn()      -> Text("Hello 0") -> TableNextColumn()      -> Text("Hello 1")  // OK
		//        -                   TableNextColumn()      -> Text("Hello 0") -> TableNextColumn()      -> Text("Hello 1")  // OK: TableNextColumn() automatically gets to next row!
		//        - TableNextRow()                           -> Text("Hello 0")                                               // Not OK! Missing TableSetColumnIndex() or TableNextColumn()! Text will not appear!
		// - 5. Call EndTable()
		// MODULE_FUNC(BeginTable);
		// MODULE_FUNC(EndTable);                                         // only call EndTable() if BeginTable() returns true!
		// MODULE_FUNC(TableNextRow); // append into the first cell of a new row.
		// MODULE_FUNC(TableNextColumn);                                  // append into the next column (or first column of next row if currently in last column). Return true when column is visible.
		// MODULE_FUNC(TableSetColumnIndex);                  // append into the specified column. Return true when column is visible.

		// Tables: Headers & Columns declaration
		// - Use TableSetupColumn() to specify label, resizing policy, default width/weight, id, various other flags etc.
		// - Use TableHeadersRow() to create a header row and automatically submit a TableHeader() for each column.
		//   Headers are required to perform: reordering, sorting, and opening the context menu.
		//   The context menu can also be made available in columns body using ImGuiTableFlags_ContextMenuInBody.
		// - You may manually submit headers using TableNextRow() + TableHeader() calls, but this is only useful in
		//   some advanced use cases (e.g. adding custom widgets in header row).
		// - Use TableSetupScrollFreeze() to lock columns/rows so they stay visible when scrolled.
		// MODULE_FUNC(TableSetupColumn);
		// MODULE_FUNC(TableSetupScrollFreeze);         // lock columns/rows so they stay visible when scrolled.
		// MODULE_FUNC(TableHeader);                     // submit one header cell manually (rarely used)
		// MODULE_FUNC(TableHeadersRow);                                  // submit a row with headers cells based on data provided to TableSetupColumn() + submit context menu
		MODULE_FUNC(TableAngledHeadersRow);                            // submit a row with angled headers for every column with the ImGuiTableColumnFlags_AngledHeader flag. MUST BE FIRST ROW.

		// Tables: Sorting & Miscellaneous functions
		// - Sorting: call TableGetSortSpecs() to retrieve latest sort specs for the table. NULL when not sorting.
		//   When 'sort_specs->SpecsDirty == true' you should sort your data. It will be true when sorting specs have
		//   changed since last call, or the first time. Make sure to set 'SpecsDirty = false' after sorting,
		//   else you may wastefully sort your data every frame!
		// - Functions args 'int column_n' treat the default value of -1 as the same as passing the current column index.
		// MODULE_FUNC(TableGetSortSpecs);                        // get latest sort specs for the table (NULL if not sorting).  Lifetime: don't hold on this pointer over multiple frames or past any subsequent call to BeginTable().
		MODULE_FUNC(TableGetColumnCount);                      // return number of columns (value passed to BeginTable)
		MODULE_FUNC(TableGetColumnIndex);                      // return current column index.
		MODULE_FUNC(TableGetRowIndex);                         // return current row index.
		MODULE_FUNC(TableGetColumnName);      // return "" if column didn't have a name declared by TableSetupColumn(). Pass -1 to use current column.
		MODULE_FUNC(TableGetColumnFlags);     // return column flags so you can query their Enabled/Visible/Sorted/Hovered status flags. Pass -1 to use current column.
		MODULE_FUNC(TableSetColumnEnabled);// change user accessible enabled/disabled state of a column. Set to false to hide the column. User can use the context menu to change this themselves (right-click in headers, or right-click in columns body with ImGuiTableFlags_ContextMenuInBody)
		MODULE_FUNC(TableSetBgColor);  // change the color of a cell, row, or column. See ImGuiTableBgTarget_ flags for details.

		// Legacy Columns API (prefer using Tables!)
		// - You can also use SameLine(pos_x) to mimic simplified columns.
		MODULE_FUNC(Columns);
		MODULE_FUNC(NextColumn);                                                       // next column, defaults to current row or next row if the current row is finished
		MODULE_FUNC(GetColumnIndex);                                                   // get current column index
		MODULE_FUNC(GetColumnWidth);                              // get column width (in pixels). pass -1 to use current column
		MODULE_FUNC(SetColumnWidth);                      // set column width (in pixels). pass -1 to use current column
		MODULE_FUNC(GetColumnOffset);                             // get position of column line (in pixels, from the left side of the contents region). pass -1 to use current column, otherwise 0..GetColumnsCount() inclusive. column 0 is typically 0.0f
		MODULE_FUNC(SetColumnOffset);                  // set position of column line (in pixels, from the left side of the contents region). pass -1 to use current column
		MODULE_FUNC(GetColumnsCount);

		// Tab Bars, Tabs
		// - Note: Tabs are automatically created by the docking system (when in 'docking' branch). Use this to create tab bars/tabs yourself.
		MODULE_FUNC(BeginTabBar);        // create and append into a TabBar
		MODULE_FUNC(EndTabBar);                                                        // only call EndTabBar() if BeginTabBar() returns true!
		MODULE_FUNC(BeginTabItem); // create a Tab. Returns true if the Tab is selected.
		MODULE_FUNC(EndTabItem);                                                       // only call EndTabItem() if BeginTabItem() returns true!
		MODULE_FUNC(TabItemButton);      // create a Tab behaving like a button. return true when clicked. cannot be selected in the tab bar.
		MODULE_FUNC(SetTabItemClosed);           // notify TabBar or Docking system of a closed tab/window ahead (useful to reduce visual flicker on reorderable tab bars). For tab-bar: call after BeginTabBar() and before Tab submissions. Otherwise call with a window name.

		// Logging/Capture
		// - All text output from the interface can be captured into tty/file/clipboard. By default, tree nodes are automatically opened during logging.
		// MODULE_FUNC(LogToTTY);                                 // start logging to tty (stdout)
		// MODULE_FUNC(LogToFile);   // start logging to file
		// MODULE_FUNC(LogToClipboard);                           // start logging to OS clipboard
		// MODULE_FUNC(LogFinish);                                                        // stop logging (close file, etc.)
		// MODULE_FUNC(LogButtons);                                                       // helper to display buttons for logging to tty/file/clipboard
		// MODULE_FUNC(LogText);                        // pass text data straight to log (without being displayed)
		// MODULE_FUNC(LogTextV);

		// Drag and Drop
		// - On source items, call BeginDragDropSource(), if it returns true also call SetDragDropPayload() + EndDragDropSource().
		// - On target candidates, call BeginDragDropTarget(), if it returns true also call AcceptDragDropPayload() + EndDragDropTarget().
		// - If you stop calling BeginDragDropSource() the payload is preserved however it won't have a preview tooltip (we currently display a fallback "..." tooltip, see #1725)
		// - An item can be both drag source and drop target.
		// MODULE_FUNC(BeginDragDropSource);                                      // call after submitting an item which may be dragged. when this return true, you can call SetDragDropPayload() + EndDragDropSource()
		// MODULE_FUNC(SetDragDropPayload);  // type is a user defined string of maximum 32 characters. Strings starting with '_' are reserved for dear imgui internal types. Data is copied and held by imgui. Return true when payload has been accepted.
		// MODULE_FUNC(EndDragDropSource);                                                                    // only call EndDragDropSource() if BeginDragDropSource() returns true!
		// MODULE_FUNC(BeginDragDropTarget);                                                          // call after submitting an item that may receive a payload. If this returns true, you can call AcceptDragDropPayload() + EndDragDropTarget()
		// MODULE_FUNC(AcceptDragDropPayload);          // accept contents of a given type. If ImGuiDragDropFlags_AcceptBeforeDelivery is set you can peek into the payload before the mouse button is released.
		// MODULE_FUNC(EndDragDropTarget);                                                            // only call EndDragDropTarget() if BeginDragDropTarget() returns true!
		// MODULE_FUNC(GetDragDropPayload);                                                           // peek directly into the current payload from anywhere. returns NULL when drag and drop is finished or inactive. use ImGuiPayload::IsDataType() to test for the payload type.

		// Disabling [BETA API]
		// - Disable all user interactions and dim items visuals (applying style.DisabledAlpha over current colors)
		// - Those can be nested but it cannot be used to enable an already disabled section (a single BeginDisabled(true) in the stack is enough to keep everything disabled)
		// - BeginDisabled(false) essentially does nothing useful but is provided to facilitate use of boolean expressions. If you can avoid calling BeginDisabled(False)/EndDisabled() best to avoid it.
		MODULE_FUNC(BeginDisabled);
		MODULE_FUNC(EndDisabled);

		// Clipping
		// - Mouse hovering is affected by ImGui::PushClipRect() calls, unlike direct calls to ImDrawList::PushClipRect() which are render only.
		// MODULE_FUNC(PushClipRect);
		// MODULE_FUNC(PopClipRect);

		// Focus, Activation
		// - Prefer using "SetItemDefaultFocus()" over "if (IsWindowAppearing()) SetScrollHereY()" when applicable to signify "this is the default item"
		MODULE_FUNC(SetItemDefaultFocus);                                              // make last item the default focused item of a window.
		// MODULE_FUNC(SetKeyboardFocusHere);                               // focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget.

		// Overlapping mode
		MODULE_FUNC(SetNextItemAllowOverlap);                                          // allow next item to be overlapped by a subsequent item. Useful with invisible buttons, selectable, treenode covering an area where subsequent items may need to be added. Note that both Selectable() and TreeNode() have dedicated flags doing this.

		// Item/Widgets Utilities and Query Functions
		// - Most of the functions are referring to the previous Item that has been submitted.
		// - See Demo Window under "Widgets->Querying Status" for an interactive visualization of most of those functions.
		MODULE_FUNC(IsItemHovered);                         // is the last item hovered? (and usable, aka not blocked by a popup, etc.). See ImGuiHoveredFlags for more options.
		MODULE_FUNC(IsItemActive);                                                     // is the last item active? (e.g. button being held, text field being edited. This will continuously return true while holding mouse button on an item. Items that don't interact will always return false)
		MODULE_FUNC(IsItemFocused);                                                    // is the last item focused for keyboard/gamepad navigation?
		MODULE_FUNC(IsItemClicked);                   // is the last item hovered and mouse clicked on? (**)  == IsMouseClicked(mouse_button) && IsItemHovered()Important. (**) this is NOT equivalent to the behavior of e.g. Button(). Read comments in function definition.
		MODULE_FUNC(IsItemVisible);                                                    // is the last item visible? (items may be out of sight because of clipping/scrolling)
		MODULE_FUNC(IsItemEdited);                                                     // did the last item modify its underlying value this frame? or was pressed? This is generally the same as the "bool" return value of many widgets.
		MODULE_FUNC(IsItemActivated);                                                  // was the last item just made active (item was previously inactive).
		MODULE_FUNC(IsItemDeactivated);                                                // was the last item just made inactive (item was previously active). Useful for Undo/Redo patterns with widgets that require continuous editing.
		MODULE_FUNC(IsItemDeactivatedAfterEdit);                                       // was the last item just made inactive and made a value change when it was active? (e.g. Slider/Drag moved). Useful for Undo/Redo patterns with widgets that require continuous editing. Note that you may get false positives (some widgets such as Combo()/ListBox()/Selectable() will return true even when clicking an already selected item).
		MODULE_FUNC(IsItemToggledOpen);                                                // was the last item open state toggled? set by TreeNode().
		MODULE_FUNC(IsAnyItemHovered);                                                 // is any item hovered?
		MODULE_FUNC(IsAnyItemActive);                                                  // is any item active?
		MODULE_FUNC(IsAnyItemFocused);                                                 // is any item focused?
		MODULE_FUNC(GetItemID);                                                        // get ID of last item (~~ often same ImGui::GetID(label) beforehand)
		MODULE_FUNC(GetItemRectMin);                                                   // get upper-left bounding rectangle of the last item (screen space)
		MODULE_FUNC(GetItemRectMax);                                                   // get lower-right bounding rectangle of the last item (screen space)
		MODULE_FUNC(GetItemRectSize);                                                  // get size of last item

		// Viewports
		// - Currently represents the Platform Window created by the application which is hosting our Dear ImGui windows.
		// - In 'docking' branch with multi-viewport enabled, we extend this concept to have multiple active viewports.
		// - In the future we will extend this concept further to also represent Platform Monitor and support a "no main platform window" operation mode.
		// MODULE_FUNC(GetMainViewport);                                                 // return primary/default viewport. This can never be NULL.

		// Background/Foreground Draw Lists
		// MODULE_FUNC(GetBackgroundDrawList);                                            // this draw list will be the first rendered one. Useful to quickly draw shapes/text behind dear imgui contents.
		// MODULE_FUNC(GetForegroundDrawList);                                            // this draw list will be the last rendered one. Useful to quickly draw shapes/text over dear imgui contents.

		// Miscellaneous Utilities
		MODULE_FUNC(IsRectVisible);                                  // test if rectangle (of given size, starting from cursor position) is visible / not clipped.  // test if rectangle (in screen space) is visible / not clipped. to perform coarse clipping on user's side.
		MODULE_FUNC(GetTime);                                                          // get global imgui time. incremented by io.DeltaTime every frame.
		MODULE_FUNC(GetFrameCount);                                                    // get global imgui frame count. incremented by 1 every frame.
		// MODULE_FUNC(GetDrawListSharedData);                                    // you may use this when creating your own ImDrawList instances.
		MODULE_FUNC(GetStyleColorName);                                    // get a string corresponding to the enum value (for display, saving, etc.).
		// MODULE_FUNC(SetStateStorage);                             // replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)
		// MODULE_FUNC(GetStateStorage);

		// Text Utilities
		MODULE_FUNC(CalcTextSize);

		// Color Utilities
		MODULE_FUNC(ColorConvertU32ToFloat4);
		MODULE_FUNC(ColorConvertFloat4ToU32);
		MODULE_FUNC(ColorConvertRGBtoHSV);
		MODULE_FUNC(ColorConvertHSVtoRGB);

		// Inputs Utilities: Keyboard/Mouse/Gamepad
		// - the ImGuiKey enum contains all possible keyboard, mouse and gamepad inputs (e.g. ImGuiKey_A, ImGuiKey_MouseLeft, ImGuiKey_GamepadDpadUp...).
		// - before v1.87, we used ImGuiKey to carry native/user indices as defined by each backends. About use of those legacy ImGuiKey values:
		//  - without IMGUI_DISABLE_OBSOLETE_KEYIO (legacy support): you can still use your legacy native/user indices (< 512) according to how your backend/engine stored them in io.KeysDown[], but need to cast them to ImGuiKey.
		//  - with    IMGUI_DISABLE_OBSOLETE_KEYIO (this is the way forward): any use of ImGuiKey will assert with key < 512. GetKeyIndex() is pass-through and therefore deprecated (gone if IMGUI_DISABLE_OBSOLETE_KEYIO is defined).
		MODULE_FUNC(IsKeyDown);                                            // is key being held.
		MODULE_FUNC(IsKeyPressed);                     // was key pressed (went from !Down to Down)? if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate
		MODULE_FUNC(IsKeyReleased);                                        // was key released (went from Down to !Down)?
		MODULE_FUNC(IsKeyChordPressed);                         // was key chord (mods + key) pressed, e.g. you can pass 'ImGuiMod_Ctrl | ImGuiKey_S' as a key-chord. This doesn't do any routing or focus check, please consider using Shortcut() function instead.
		// MODULE_FUNC(GetKeyPressedAmount);  // uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
		MODULE_FUNC(GetKeyName);                                           // [DEBUG] returns English name of the key. Those names a provided for debugging purpose and are not meant to be saved persistently not compared.
		// MODULE_FUNC(SetNextFrameWantCaptureKeyboard);        // Override io.WantCaptureKeyboard flag next frame (said flag is left for your application to handle, typically when true it instructs your app to ignore inputs). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting "io.WantCaptureKeyboard = want_capture_keyboard"; after the next NewFrame() call.

		// Inputs Utilities: Mouse specific
		// - To refer to a mouse button, you may use named enums in your code e.g. ImGuiMouseButton_Left, ImGuiMouseButton_Right.
		// - You can also use regular integer: it is forever guaranteed that 0=Left, 1=Right, 2=Middle.
		// - Dragging operations are only reported after mouse has moved a certain distance away from the initial clicking position (see 'lock_threshold' and 'io.MouseDraggingThreshold')
		MODULE_FUNC(IsMouseDown);                               // is mouse button held?
		MODULE_FUNC(IsMouseClicked);       // did mouse button clicked? (went from !Down to Down). Same as GetMouseClickedCount() == 1.
		MODULE_FUNC(IsMouseReleased);                           // did mouse button released? (went from Down to !Down)
		MODULE_FUNC(IsMouseDoubleClicked);                      // did mouse button double-clicked? Same as GetMouseClickedCount() == 2. (note that a double-click will also report IsMouseClicked() == true)
		MODULE_FUNC(GetMouseClickedCount);                      // return the number of successive mouse-clicks at the time where a click happen (otherwise 0).
		MODULE_FUNC(IsMouseHoveringRect);// is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but disregarding of other consideration of focus/window ordering/popup-block.
		MODULE_FUNC(IsMousePosValid);                    // by convention we use (-FLT_MAX,-FLT_MAX) to denote that there is no mouse available
		MODULE_FUNC(IsAnyMouseDown);                                                   // [WILL OBSOLETE] is any mouse button held? This was designed for backends, but prefer having backend maintain a mask of held mouse buttons, because upcoming input queue system will make this invalid.
		MODULE_FUNC(GetMousePos);                                                      // shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls
		MODULE_FUNC(GetMousePosOnOpeningCurrentPopup);                                 // retrieve mouse position at the time of opening popup we have BeginPopup() into (helper to avoid user backing that value themselves)
		MODULE_FUNC(IsMouseDragging);         // is mouse dragging? (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)
		MODULE_FUNC(GetMouseDragDelta);   // return the delta from the initial clicking position while the mouse button is pressed or was just released. This is locked and return 0.0f until the mouse moves past a distance threshold at least once (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)
		MODULE_FUNC(ResetMouseDragDelta);                   //
		MODULE_FUNC(GetMouseCursor);                                                // get desired mouse cursor shape. Important: reset in ImGui::NewFrame(), this is updated during the frame. valid before Render(). If you use software rendering by setting io.MouseDrawCursor ImGui will render those for you
		MODULE_FUNC(SetMouseCursor);                       // set desired mouse cursor shape
		MODULE_FUNC(SetNextFrameWantCaptureMouse);              // Override io.WantCaptureMouse flag next frame (said flag is left for your application to handle, typical when true it instucts your app to ignore inputs). This is equivalent to setting "io.WantCaptureMouse = want_capture_mouse;" after the next NewFrame() call.

		// Clipboard Utilities
		// - Also see the LogToClipboard() function to capture GUI into clipboard, or easily output text data to the clipboard.
		MODULE_FUNC(GetClipboardText);
		MODULE_FUNC(SetClipboardText);

		// Settings/.Ini Utilities
		// - The disk functions are automatically called if io.IniFilename != NULL (default is "imgui.ini").
		// - Set io.IniFilename to NULL to load/save manually. Read io.WantSaveIniSettings description about handling .ini saving manually.
		// - Important: default value "imgui.ini" is relative to current working dir! Most apps will want to lock this to an absolute path (e.g. same path as executables).
		// MODULE_FUNC(LoadIniSettingsFromDisk);                  // call after CreateContext() and before the first call to NewFrame(). NewFrame() automatically calls LoadIniSettingsFromDisk(io.IniFilename).
		// MODULE_FUNC(LoadIniSettingsFromMemory); // call after CreateContext() and before the first call to NewFrame() to provide .ini data from your own data source.
		// MODULE_FUNC(SaveIniSettingsToDisk);                    // this is automatically called (if io.IniFilename is not empty) a few seconds after any modification that should be reflected in the .ini file (and also by DestroyContext).
		// MODULE_FUNC(SaveIniSettingsToMemory);               // return a zero-terminated string with the .ini data which you can save by your own mean. call when io.WantSaveIniSettings is set, then save data by your own mean and clear io.WantSaveIniSettings.

		// Debug Utilities
		// - Your main debugging friend is the ShowMetricsWindow() function, which is also accessible from Demo->Tools->Metrics Debugger
		MODULE_FUNC(DebugTextEncoding);
		MODULE_FUNC(DebugFlashStyleColor);
		MODULE_FUNC(DebugStartItemPicker);
		MODULE_FUNC(DebugCheckVersionAndDataLayout); // This is called by IMGUI_CHECKVERSION() macro.

		// Memory Allocators
		// - Those functions are not reliant on the current context.
		// - DLL users: heaps and globals are not shared across DLL boundaries! You will need to call SetCurrentContext() + SetAllocatorFunctions()
		//   for each static/DLL boundary you are calling from. Read "Context and Memory Allocators" section of imgui.cpp for more details.
		// MODULE_FUNC(SetAllocatorFunctions);
		// MODULE_FUNC(GetAllocatorFunctions);
		// MODULE_FUNC(MemAlloc);
		// MODULE_FUNC(MemFree);

		MODULE_END();
		};
}
