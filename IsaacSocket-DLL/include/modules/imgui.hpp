#pragma once

#include "module.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

namespace imgui {
	static ::ImVec2 VEC2_0 = ::ImVec2(0, 0);
	static ::ImVec4 VEC4_0 = ::ImVec4(0, 0, 0, 0);
	static ::ImVec2 VEC2_1 = ::ImVec2(1, 1);
	static ::ImVec4 VEC4_1 = ::ImVec4(1, 1, 1, 1);

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

	static int ArrowButton(lua_State* L) {
		ARG(1, string, const char*, str_id);
		ARG(2, integer, ImGuiDir, dir);
		RET(boolean, ImGui::ArrowButton(str_id, dir));
	}

	static int Begin(lua_State* L) {
		ARG(1, string, const char*, name);
		ARG_DEF(2, boolean, bool, open, true);
		ARG_DEF(3, integer, int, flags, 0);

		local.lua.lua_pushboolean(L, ImGui::Begin(name, &open, flags));
		local.lua.lua_pushboolean(L, open);
		return 2;
	}

	static int BeginCombo(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, const char*, preview_value);
		ARG_DEF(3, integer, int, flags, 0);
		RET(boolean, ImGui::BeginCombo(label, preview_value, flags));
	}

	static int BeginGroup(lua_State* L) {
		ImGui::BeginGroup();
		return 0;
	}

	static int BeginMainMenuBar(lua_State* L) {
		RET(boolean, ImGui::BeginMainMenuBar());
	}

	static int BeginMenu(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_DEF(2, boolean, bool, enabled, true);
		RET(boolean, ImGui::BeginMenu(label, enabled));
	}

	static int BeginMenuBar(lua_State* L) {
		RET(boolean, ImGui::BeginMenuBar());
	}

	static int Button(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_UDATA_DEF(2, ImVec2, ::ImVec2*, size, &VEC2_0);
		RET(boolean, ImGui::Button(label, *size));
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

	static int Checkbox(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, boolean, bool, v);

		local.lua.lua_pushboolean(L, ImGui::Checkbox(label, &v));
		local.lua.lua_pushboolean(L, v);
		return 2;
	}

	static int Combo(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, current_item);

		if (local.lua.lua_isstring(L, 3))
		{
			ARG(3, string, const char*, items_separated_by_zeros);
			ARG_DEF(4, integer, int, height_in_items, -1);
			local.lua.lua_pushboolean(L, ImGui::Combo(label, &current_item, items_separated_by_zeros, height_in_items));
		}
		else
		{
			ARG(3, vectorcstring, vector<const char*>, items);
			ARG(4, integer, size_t, items_count);
			ARG_DEF(5, integer, int, height_in_items, -1);
			if (items_count > items.size())
			{
				items_count = items.size();
			}
			const char** arr = items.data();
			local.lua.lua_pushboolean(L, ImGui::Combo(label, &current_item, arr, items_count, height_in_items));
		}
		local.lua.lua_pushinteger(L, current_item);
		return 2;
	}

	static int End(lua_State* L) {
		ImGui::End();
		return 0;
	}

	static int EndCombo(lua_State* L) {
		ImGui::EndCombo();
		return 0;
	}

	static int EndGroup(lua_State* L) {
		ImGui::EndGroup();
		return 0;
	}

	static int EndMainMenuBar(lua_State* L) {
		ImGui::EndMainMenuBar();
		return 0;
	}

	static int EndMenu(lua_State* L) {
		ImGui::EndMenu();
		return 0;
	}

	static int EndMenuBar(lua_State* L) {
		ImGui::EndMenuBar();
		return 0;
	}

	static int GetClipboardText(lua_State* L) {
		RET(string, ImGui::GetClipboardText());
	}

	static int GetIO(lua_State* L) {
		ImGuiIO** p_io = (ImGuiIO**)local.lua.lua_newuserdata(L, sizeof(ImGuiIO*));
		SET_METATABLE(p_ImGuiIO);
		*p_io = &ImGui::GetIO();
		return 1;
	}

	static int GetItemRectSize(lua_State* L) {
		::ImVec2* p_vec = (::ImVec2*)local.lua.lua_newuserdata(L, sizeof(::ImVec2));
		SET_METATABLE(ImVec2);
		*p_vec = ImGui::GetItemRectSize();
		return 1;
	}

	static int GetTime(lua_State* L) {
		RET(number, ImGui::GetTime());
	}

	static int GetVersion(lua_State* L) {
		RET(string, ImGui::GetVersion());
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

	static int Image(lua_State* L) {
		ARG(1, integer, ImTextureID, user_texture_id);
		ARG_UDATA(2, ImVec2, ::ImVec2*, image_size);
		ARG_UDATA_DEF(3, ImVec2, ::ImVec2*, uv0, &VEC2_0);
		ARG_UDATA_DEF(4, ImVec2, ::ImVec2*, uv1, &VEC2_1);
		ARG_UDATA_DEF(5, ImVec4, ::ImVec4*, tint_col, &VEC4_1);
		ARG_UDATA_DEF(6, ImVec4, ::ImVec4*, border_col, &VEC4_0);
		ImGui::Image(user_texture_id, *image_size, *uv0, *uv1, *tint_col, *border_col);
		return 0;
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

	static int LabelText(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, string, const char*, text);
		ImGui::LabelText(label, "%s", text);
		return 0;
	}

	static int MenuItem(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG_DEF(2, string, const char*, shortcut, (const char*)0);
		ARG_DEF(3, boolean, bool, selected, false);
		ARG_DEF(4, boolean, bool, enabled, true);
		RET(boolean, ImGui::MenuItem(label, shortcut, selected, enabled));
	}

	static int PopStyleColor(lua_State* L) {
		ARG_DEF(1, integer, int, count, 1);
		ImGui::PopStyleColor(count);
		return 0;
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

	static int RadioButton(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, integer, int, v);
		ARG(3, integer, int, v_button);

		local.lua.lua_pushboolean(L, ImGui::RadioButton(label, &v, v_button));
		local.lua.lua_pushinteger(L, v);
		return 2;
	}

	static int SameLine(lua_State* L) {
		ARG_DEF(1, number, float, offset_from_start_x, 0.0F);
		ARG_DEF(2, number, float, spacing_w, -1.0F);

		ImGui::SameLine(offset_from_start_x, spacing_w);
		return 0;
	}

	static int Selectable(lua_State* L) {
		ARG(1, string, const char*, label);
		ARG(2, boolean, bool, selected);
		ARG_DEF(3, integer, ImGuiSelectableFlags, flags, 0);
		ARG_UDATA_DEF(4, ImVec2, ::ImVec2*, size_arg, &VEC2_0);
		local.lua.lua_pushboolean(L, ImGui::Selectable(label, selected, flags, *size_arg));
		local.lua.lua_pushinteger(L, selected);
		return 2;
	}

	static int SetClipboardText(lua_State* L) {
		ARG(1, string, const char*, text);
		ImGui::SetClipboardText(text);
		return 0;
	}

	static int SetItemDefaultFocus(lua_State* L) {
		ImGui::SetItemDefaultFocus();
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

	static int ShowAboutWindow(lua_State* L) {
		ImGui::ShowAboutWindow();
		return 0;
	}

	static int ShowDebugLogWindow(lua_State* L) {
		ARG_DEF(1, boolean, bool, open, false);
		ImGui::ShowDebugLogWindow(&open);
		RET(boolean, open);
	}

	static int ShowDemoWindow(lua_State* L) {
		ARG_DEF(1, boolean, bool, open, false);
		ImGui::ShowDemoWindow(&open);
		RET(boolean, open);
	}

	static int ShowUserGuide(lua_State* L) {
		ImGui::ShowUserGuide();
		return 0;
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

	static int StyleColorsClassic(lua_State* L) {
		local.styleColor = state::CLASSIC;
		ImGui::StyleColorsClassic();
		return 0;
	}

	static int StyleColorsDark(lua_State* L) {
		local.styleColor = state::DARK;
		ImGui::StyleColorsDark();
		return 0;
	}

	static int StyleColorsLight(lua_State* L) {
		local.styleColor = state::LIGHT;
		ImGui::StyleColorsLight();
		return 0;
	}

	static int Text(lua_State* L) {
		ARG(1, string, const char*, fmt);
		ImGui::Text(fmt);
		return 0;
	}

	static int TextUnformatted(lua_State* L) {
		ARG(1, string, const char*, text);
		ARG_DEF(2, string, const char*, text_end, (const char*)0);
		ImGui::TextUnformatted(text);
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

	static void Init() {
		MODULE_BEGIN(ImGui);

		MODULE_FUNC(ImVec2);
		MODULE_FUNC(ImVec4);

		// 以上方法不是ImGui命名空间下的方法

		// MODULE_FUNC(AcceptDragDropPayload);
		// MODULE_FUNC(AlignTextToFramePadding);
		MODULE_FUNC(ArrowButton);
		MODULE_FUNC(Begin);
		// MODULE_FUNC(BeginChild);
		// MODULE_FUNC(BeginChildFrame);
		MODULE_FUNC(BeginCombo);
		// MODULE_FUNC(BeginDisabled);
		// MODULE_FUNC(BeginDragDropSource);
		// MODULE_FUNC(BeginDragDropTarget);
		MODULE_FUNC(BeginGroup);
		// MODULE_FUNC(BeginItemTooltip);
		// MODULE_FUNC(BeginListBox);
		MODULE_FUNC(BeginMainMenuBar);
		MODULE_FUNC(BeginMenu);
		MODULE_FUNC(BeginMenuBar);
		// MODULE_FUNC(BeginPopup);
		// MODULE_FUNC(BeginPopupContextItem);
		// MODULE_FUNC(BeginPopupContextVoid);
		// MODULE_FUNC(BeginPopupContextWindow);
		// MODULE_FUNC(BeginPopupModal);
		// MODULE_FUNC(BeginTabBar);
		// MODULE_FUNC(BeginTabItem);
		// MODULE_FUNC(BeginTable);
		// MODULE_FUNC(BeginTooltip);
		// MODULE_FUNC(Bullet);
		// MODULE_FUNC(BulletText);
		// MODULE_FUNC(BulletTextV);
		MODULE_FUNC(Button);
		// MODULE_FUNC(CalcItemWidth);
		MODULE_FUNC(CalcTextSize);
		// MODULE_FUNC(CaptureKeyboardFromApp);
		// MODULE_FUNC(CaptureMouseFromApp);
		MODULE_FUNC(Checkbox);
		// MODULE_FUNC(CheckboxFlags);
		// MODULE_FUNC(CloseCurrentPopup);
		// MODULE_FUNC(CollapsingHeader);
		// MODULE_FUNC(ColorButton);
		// MODULE_FUNC(ColorConvertFloat4ToU32);
		// MODULE_FUNC(ColorConvertHSVtoRGB);
		// MODULE_FUNC(ColorConvertRGBtoHSV);
		// MODULE_FUNC(ColorConvertU32ToFloat4);
		// MODULE_FUNC(ColorEdit3);
		// MODULE_FUNC(ColorEdit4);
		// MODULE_FUNC(ColorPicker3);
		// MODULE_FUNC(ColorPicker4);
		// MODULE_FUNC(Columns);
		MODULE_FUNC(Combo);		//重载2/3 未实现 bool ImGui::Combo(const char* label, int* current_item, const char* (*getter)(void* user_data, int idx), void* user_data, int items_count, int popup_max_height_in_items)
		// MODULE_FUNC(CreateContext);		//在c++中已调用
		// MODULE_FUNC(DebugCheckVersionAndDataLayout);
		// MODULE_FUNC(DebugFlashStyleColor);
		// MODULE_FUNC(DebugTextEncoding);
		// MODULE_FUNC(DestroyContext);
		// MODULE_FUNC(DragFloat);	
		// MODULE_FUNC(DragFloat2);
		// MODULE_FUNC(DragFloat3);
		// MODULE_FUNC(DragFloat4);
		// MODULE_FUNC(DragFloatRange2);
		// MODULE_FUNC(DragInt);
		// MODULE_FUNC(DragInt2);
		// MODULE_FUNC(DragInt3);
		// MODULE_FUNC(DragInt4);
		// MODULE_FUNC(DragIntRange2);
		// MODULE_FUNC(DragScalar);
		// MODULE_FUNC(DragScalarN);
		// MODULE_FUNC(Dummy);
		MODULE_FUNC(End);
		// MODULE_FUNC(EndChild);
		// MODULE_FUNC(EndChildFrame);
		MODULE_FUNC(EndCombo);
		// MODULE_FUNC(EndDisabled);
		// MODULE_FUNC(EndDragDropSource);
		// MODULE_FUNC(EndDragDropTarget);
		// MODULE_FUNC(EndFrame);
		MODULE_FUNC(EndGroup);
		// MODULE_FUNC(EndListBox);
		MODULE_FUNC(EndMainMenuBar);
		MODULE_FUNC(EndMenu);
		MODULE_FUNC(EndMenuBar);
		// MODULE_FUNC(EndPopup);
		// MODULE_FUNC(EndTabBar);
		// MODULE_FUNC(EndTabItem);
		// MODULE_FUNC(EndTable);
		// MODULE_FUNC(EndTooltip);
		// MODULE_FUNC(GetAllocatorFunctions);
		// MODULE_FUNC(GetBackgroundDrawList);
		MODULE_FUNC(GetClipboardText);
		// MODULE_FUNC(GetColorU32);
		// MODULE_FUNC(GetColumnIndex);
		// MODULE_FUNC(GetColumnOffset);
		// MODULE_FUNC(GetColumnsCount);
		// MODULE_FUNC(GetColumnWidth);
		// MODULE_FUNC(GetContentRegionAvail);
		// MODULE_FUNC(GetContentRegionMax);
		// MODULE_FUNC(GetCurrentContext);
		// MODULE_FUNC(GetCursorPos);
		// MODULE_FUNC(GetCursorPosX);
		// MODULE_FUNC(GetCursorPosY);
		// MODULE_FUNC(GetCursorScreenPos);
		// MODULE_FUNC(GetCursorStartPos);
		// MODULE_FUNC(GetDragDropPayload);
		// MODULE_FUNC(GetDrawData);
		// MODULE_FUNC(GetDrawListSharedData);
		// MODULE_FUNC(GetFont);
		// MODULE_FUNC(GetFontSize);
		// MODULE_FUNC(GetFontTexUvWhitePixel);
		// MODULE_FUNC(GetForegroundDrawList);
		// MODULE_FUNC(GetFrameCount);
		// MODULE_FUNC(GetFrameHeight);
		// MODULE_FUNC(GetFrameHeightWithSpacing);
		// MODULE_FUNC(GetID);
		MODULE_FUNC(GetIO);
		// MODULE_FUNC(GetItemID);
		// MODULE_FUNC(GetItemRectMax);
		// MODULE_FUNC(GetItemRectMin);
		MODULE_FUNC(GetItemRectSize);
		// MODULE_FUNC(GetKeyIndex);
		// MODULE_FUNC(GetKeyName);
		// MODULE_FUNC(GetKeyPressedAmount);
		// MODULE_FUNC(GetMainViewport);
		// MODULE_FUNC(GetMouseClickedCount);
		// MODULE_FUNC(GetMouseCursor);
		// MODULE_FUNC(GetMouseDragDelta);
		// MODULE_FUNC(GetMousePos);
		// MODULE_FUNC(GetMousePosOnOpeningCurrentPopup);
		// MODULE_FUNC(GetScrollMaxX);
		// MODULE_FUNC(GetScrollMaxY);
		// MODULE_FUNC(GetScrollX);
		// MODULE_FUNC(GetScrollY);
		// MODULE_FUNC(GetStateStorage);
		// MODULE_FUNC(GetStyle);
		// MODULE_FUNC(GetStyleColorName);
		// MODULE_FUNC(GetStyleColorVec4);
		// MODULE_FUNC(GetTextLineHeight);
		// MODULE_FUNC(GetTextLineHeightWithSpacing);
		MODULE_FUNC(GetTime);
		// MODULE_FUNC(GetTreeNodeToLabelSpacing);
		MODULE_FUNC(GetVersion);
		// MODULE_FUNC(GetWindowContentRegionMax);
		// MODULE_FUNC(GetWindowContentRegionMin);
		// MODULE_FUNC(GetWindowDrawList);
		// MODULE_FUNC(GetWindowHeight);
		MODULE_FUNC(GetWindowPos);
		MODULE_FUNC(GetWindowSize);
		// MODULE_FUNC(GetWindowWidth);
		MODULE_FUNC(Image);
		// MODULE_FUNC(ImageButton);
		// MODULE_FUNC(Indent);
		// MODULE_FUNC(InputDouble);
		// MODULE_FUNC(InputFloat);
		// MODULE_FUNC(InputFloat2);
		// MODULE_FUNC(InputFloat3);
		// MODULE_FUNC(InputFloat4);
		MODULE_FUNC(InputInt);
		// MODULE_FUNC(InputInt2);
		// MODULE_FUNC(InputInt3);
		// MODULE_FUNC(InputInt4);
		// MODULE_FUNC(InputScalar);
		// MODULE_FUNC(InputScalarN);
		MODULE_FUNC(InputText);		//不完全实现：最后两个参数 callback 和 user_data 参数无效
		MODULE_FUNC(InputTextMultiline);		//不完全实现：最后两个参数 callback 和 user_data 参数无效
		// MODULE_FUNC(InputTextWithHint);
		// MODULE_FUNC(InvisibleButton);
		// MODULE_FUNC(IsAnyItemActive);
		// MODULE_FUNC(IsAnyItemFocused);
		// MODULE_FUNC(IsAnyItemHovered);
		// MODULE_FUNC(IsAnyMouseDown);
		// MODULE_FUNC(IsItemActivated);
		// MODULE_FUNC(IsItemActive);
		// MODULE_FUNC(IsItemClicked);
		// MODULE_FUNC(IsItemDeactivated);
		// MODULE_FUNC(IsItemDeactivatedAfterEdit);
		// MODULE_FUNC(IsItemEdited);
		// MODULE_FUNC(IsItemFocused);
		// MODULE_FUNC(IsItemHovered);
		// MODULE_FUNC(IsItemToggledOpen);
		// MODULE_FUNC(IsItemVisible);
		// MODULE_FUNC(IsKeyChordPressed);
		// MODULE_FUNC(IsKeyDown);
		// MODULE_FUNC(IsKeyPressed);
		// MODULE_FUNC(IsKeyReleased);
		// MODULE_FUNC(IsMouseClicked);
		// MODULE_FUNC(IsMouseDoubleClicked);
		// MODULE_FUNC(IsMouseDown);
		// MODULE_FUNC(IsMouseDragging);
		// MODULE_FUNC(IsMouseHoveringRect);
		// MODULE_FUNC(IsMousePosValid);
		// MODULE_FUNC(IsMouseReleased);
		// MODULE_FUNC(IsPopupOpen);
		// MODULE_FUNC(IsRectVisible);
		// MODULE_FUNC(IsWindowAppearing);
		// MODULE_FUNC(IsWindowCollapsed);
		// MODULE_FUNC(IsWindowFocused);
		// MODULE_FUNC(IsWindowHovered);
		MODULE_FUNC(LabelText);
		// MODULE_FUNC(LabelTextV);
		// MODULE_FUNC(ListBox);
		// MODULE_FUNC(LoadIniSettingsFromDisk);
		// MODULE_FUNC(LoadIniSettingsFromMemory);
		// MODULE_FUNC(LogButtons);
		// MODULE_FUNC(LogFinish);
		// MODULE_FUNC(LogText);
		// MODULE_FUNC(LogTextV);
		// MODULE_FUNC(LogToClipboard);
		// MODULE_FUNC(LogToFile);
		// MODULE_FUNC(LogToTTY);
		// MODULE_FUNC(MemAlloc);	//可能会造成内存泄漏，不暴露给lua
		// MODULE_FUNC(MemFree);	//可能会造成内存泄漏，不暴露给lua
		MODULE_FUNC(MenuItem);
		// MODULE_FUNC(NewFrame);	//在c++中已调用
		// MODULE_FUNC(NewLine);
		// MODULE_FUNC(NextColumn);
		// MODULE_FUNC(OpenPopup);
		// MODULE_FUNC(OpenPopupOnItemClick);
		// MODULE_FUNC(PlotHistogram);
		// MODULE_FUNC(PlotLines);
		// MODULE_FUNC(PopAllowKeyboardFocus);
		// MODULE_FUNC(PopButtonRepeat);
		// MODULE_FUNC(PopClipRect);
		// MODULE_FUNC(PopFont);
		// MODULE_FUNC(PopID);
		// MODULE_FUNC(PopItemWidth);
		MODULE_FUNC(PopStyleColor);
		// MODULE_FUNC(PopStyleVar);
		// MODULE_FUNC(PopTabStop);
		// MODULE_FUNC(PopTextWrapPos);
		// MODULE_FUNC(ProgressBar);
		// MODULE_FUNC(PushAllowKeyboardFocus);
		// MODULE_FUNC(PushButtonRepeat);
		// MODULE_FUNC(PushClipRect);
		// MODULE_FUNC(PushFont);
		// MODULE_FUNC(PushID);
		// MODULE_FUNC(PushItemWidth);
		MODULE_FUNC(PushStyleColor);
		// MODULE_FUNC(PushStyleVar);
		// MODULE_FUNC(PushTabStop);
		// MODULE_FUNC(PushTextWrapPos);
		MODULE_FUNC(RadioButton);
		// MODULE_FUNC(Render);
		// MODULE_FUNC(ResetMouseDragDelta);
		MODULE_FUNC(SameLine);
		// MODULE_FUNC(SaveIniSettingsToDisk);
		// MODULE_FUNC(SaveIniSettingsToMemory);
		MODULE_FUNC(Selectable);
		// MODULE_FUNC(Separator);
		// MODULE_FUNC(SeparatorText);
		// MODULE_FUNC(SetAllocatorFunctions);
		MODULE_FUNC(SetClipboardText);
		// MODULE_FUNC(SetColorEditOptions);
		// MODULE_FUNC(SetColumnOffset);
		// MODULE_FUNC(SetColumnWidth);
		// MODULE_FUNC(SetCurrentContext);
		// MODULE_FUNC(SetCursorPos);
		// MODULE_FUNC(SetCursorPosX);
		// MODULE_FUNC(SetCursorPosY);
		// MODULE_FUNC(SetCursorScreenPos);
		// MODULE_FUNC(SetDragDropPayload);
		// MODULE_FUNC(SetItemAllowOverlap);
		MODULE_FUNC(SetItemDefaultFocus);
		// MODULE_FUNC(SetItemTooltip);
		// MODULE_FUNC(SetItemTooltipV);
		// MODULE_FUNC(SetKeyboardFocusHere);
		// MODULE_FUNC(SetMouseCursor);
		// MODULE_FUNC(SetNextFrameWantCaptureKeyboard);
		// MODULE_FUNC(SetNextFrameWantCaptureMouse);
		// MODULE_FUNC(SetNextItemAllowOverlap);
		// MODULE_FUNC(SetNextItemOpen);
		// MODULE_FUNC(SetNextItemWidth);
		// MODULE_FUNC(SetNextWindowBgAlpha);
		// MODULE_FUNC(SetNextWindowCollapsed);
		// MODULE_FUNC(SetNextWindowContentSize);
		// MODULE_FUNC(SetNextWindowFocus);
		// MODULE_FUNC(SetNextWindowPos);
		// MODULE_FUNC(SetNextWindowScroll);
		// MODULE_FUNC(SetNextWindowSize);
		// MODULE_FUNC(SetNextWindowSizeConstraints);
		// MODULE_FUNC(SetScrollFromPosX);
		// MODULE_FUNC(SetScrollFromPosY);
		MODULE_FUNC(SetScrollHereX);
		MODULE_FUNC(SetScrollHereY);
		MODULE_FUNC(SetScrollX);
		MODULE_FUNC(SetScrollY);
		// MODULE_FUNC(SetStateStorage);
		// MODULE_FUNC(SetTabItemClosed);
		// MODULE_FUNC(SetTooltip);
		// MODULE_FUNC(SetTooltipV);
		// MODULE_FUNC(SetWindowCollapsed);
		// MODULE_FUNC(SetWindowFocus);
		// MODULE_FUNC(SetWindowFontScale);
		MODULE_FUNC(SetWindowPos);
		MODULE_FUNC(SetWindowSize);
		MODULE_FUNC(ShowAboutWindow);
		MODULE_FUNC(ShowDebugLogWindow);
		MODULE_FUNC(ShowDemoWindow);
		// MODULE_FUNC(ShowFontSelector);
		// MODULE_FUNC(ShowIDStackToolWindow);
		// MODULE_FUNC(ShowMetricsWindow);
		// MODULE_FUNC(ShowStackToolWindow);
		// MODULE_FUNC(ShowStyleEditor);
		// MODULE_FUNC(ShowStyleSelector);
		MODULE_FUNC(ShowUserGuide);
		// MODULE_FUNC(SliderAngle);
		MODULE_FUNC(SliderFloat);
		// MODULE_FUNC(SliderFloat2);
		// MODULE_FUNC(SliderFloat3);
		// MODULE_FUNC(SliderFloat4);
		MODULE_FUNC(SliderInt);
		// MODULE_FUNC(SliderInt2);
		// MODULE_FUNC(SliderInt3);
		// MODULE_FUNC(SliderInt4);
		// MODULE_FUNC(SliderScalar);
		// MODULE_FUNC(SliderScalarN);
		// MODULE_FUNC(SmallButton);
		// MODULE_FUNC(Spacing);
		MODULE_FUNC(StyleColorsClassic);
		MODULE_FUNC(StyleColorsDark);
		MODULE_FUNC(StyleColorsLight);
		// MODULE_FUNC(TabItemButton);
		// MODULE_FUNC(TableAngledHeadersRow);
		// MODULE_FUNC(TableGetColumnCount);
		// MODULE_FUNC(TableGetColumnFlags);
		// MODULE_FUNC(TableGetColumnIndex);
		// MODULE_FUNC(TableGetColumnName);
		// MODULE_FUNC(TableGetRowIndex);
		// MODULE_FUNC(TableGetSortSpecs);
		// MODULE_FUNC(TableHeader);
		// MODULE_FUNC(TableHeadersRow);
		// MODULE_FUNC(TableNextColumn);
		// MODULE_FUNC(TableNextRow);
		// MODULE_FUNC(TableSetBgColor);
		// MODULE_FUNC(TableSetColumnEnabled);
		// MODULE_FUNC(TableSetColumnIndex);
		// MODULE_FUNC(TableSetupColumn);
		// MODULE_FUNC(TableSetupScrollFreeze);
		MODULE_FUNC(Text);	//不完全实现：只有第一个参数有效
		MODULE_FUNC(TextColored);
		// MODULE_FUNC(TextColoredV);
		// MODULE_FUNC(TextDisabled);
		// MODULE_FUNC(TextDisabledV);
		MODULE_FUNC(TextUnformatted);
		// MODULE_FUNC(TextV);
		MODULE_FUNC(TextWrapped);
		// MODULE_FUNC(TextWrappedV);
		// MODULE_FUNC(TreeNode);
		// MODULE_FUNC(TreeNodeEx);
		// MODULE_FUNC(TreeNodeExV);
		// MODULE_FUNC(TreeNodeV);
		// MODULE_FUNC(TreePop);
		// MODULE_FUNC(TreePush);
		// MODULE_FUNC(Unindent);
		// MODULE_FUNC(Value);
		// MODULE_FUNC(VSliderFloat);
		// MODULE_FUNC(VSliderInt);
		// MODULE_FUNC(VSliderScalar);

		MODULE_END();
	}
}
