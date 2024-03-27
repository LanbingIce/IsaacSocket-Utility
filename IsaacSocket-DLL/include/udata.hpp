#pragma once
#include "module.hpp"
#include "lua.hpp"
#include "isaac_image.hpp"

#include <imgui/imgui.h>
#include <glad/glad.h>
namespace udata {
	struct HistoryItem
	{
		static int __index(lua_State* L) {
			auto& item = ARG_UDATA(1, isaac_image::HistoryItem);
			METATABLE_BEGIN(isaac_image::HistoryItem, item);
			METATABLE_INDEX(integer, time);
			METATABLE_INDEX(boolean, isTrinket);
			METATABLE_INDEX(integer, id);
			METATABLE_INDEX(integer, levelStage);
			METATABLE_INDEX(integer, stageType);
			METATABLE_INDEX(integer, roomType);
			METATABLE_INDEX(integer, itemPoolType);
			METATABLE_END();
		}

		static int __newindex(lua_State* L) {
			auto& item = ARG_UDATA(1, isaac_image::HistoryItem);
			METATABLE_BEGIN(isaac_image::HistoryItem, item);
			METATABLE_END();
		}
	};

	struct p_Options
	{
		static int __index(lua_State* L);
		static int __newindex(lua_State* L);
	};

	struct Texture {
		GLuint textureId = 0;

		static int lua_index(lua_State* L) {
			auto& texture = ARG_UDATA(1, udata::Texture);
			METATABLE_BEGIN(Texture, texture);
			METATABLE_INDEX(integer, textureId);
			METATABLE_END();
		}

		static int lua_newindex(lua_State* L) {
			METATABLE_END();
		}

		Texture& operator=(Texture&&) = delete;
		~Texture() {
			if (textureId) {
				glDeleteTextures(1, &textureId);
				textureId = 0;
			}
		}
	};

	struct LUA_WIN32_FIND_DATAW {
		WIN32_FIND_DATAW data;
		static int lua_index(lua_State* L) {

			auto& data = ARG_UDATA(1, udata::LUA_WIN32_FIND_DATAW);
			METATABLE_BEGIN(WIN32_FIND_DATAW, (data).data);
			METATABLE_INDEX(stdwstring, cFileName);
			METATABLE_END();
		}
		static int lua_newindex(lua_State* L) {
			METATABLE_END();
		}

	};

	struct Task {
		inline static size_t nextId;
		size_t id;
		Task() {
			std::lock_guard lock(local.mutex);
			id = ++nextId;
		}

		static int Then(lua_State* L) {
			auto& task = ARG_UDATA(1, udata::Task);
			if (!lua_isfunction(L, 2))
			{
				return luaL_error(L, "bad argument #2: continuation should be function");
			}

			lua_getglobal(L, "_ISAAC_SOCKET");
			lua_pushstring(L, "TaskContinuation");
			lua_gettable(L, -2);
			lua_pushinteger(L, task.id);
			lua_pushvalue(L, 2);
			lua_settable(L, -3);
			return 0;
		}

		static int lua_index(lua_State* L) {
			auto& task = ARG_UDATA(1, udata::Task);
			METATABLE_BEGIN(Task, task);
			METATABLE_INDEX(cfunction, Then);
			METATABLE_END();
		}

		static int lua_newindex(lua_State* L) {
			METATABLE_END();
		}
	};

	struct Image {
		std::vector<uint8_t> data;
		int width = 0, height = 0, channels = 0;

		static int lua_index(lua_State* L) {
			auto& image = ARG_UDATA(1, udata::Image);
			METATABLE_BEGIN(Image, image);
			METATABLE_INDEX(integer, width);
			METATABLE_INDEX(integer, height);
			METATABLE_INDEX(integer, channels);
			METATABLE_END();
		}

		static int lua_newindex(lua_State* L) {
			METATABLE_END();
		}
	};

	struct p_ImVec2
	{
		static int __index(lua_State* L) {
			auto& p_vec = ARG_UDATA(1, ::ImVec2*);
			METATABLE_BEGIN(::ImVec2, *p_vec);
			METATABLE_INDEX(number, x);
			METATABLE_INDEX(number, y);
			METATABLE_END();
		}

		static int __newindex(lua_State* L) {
			auto& p_vec = ARG_UDATA(1, ::ImVec2*);
			METATABLE_BEGIN(::ImVec2, *p_vec);
			METATABLE_NEWINDEX(number, x);
			METATABLE_NEWINDEX(number, y);
			METATABLE_END();
		}
	};

	struct ImVec2
	{
		static int __index(lua_State* L) {
			auto& vec = ARG_UDATA(1, ::ImVec2);
			METATABLE_BEGIN(::ImVec2, vec);
			METATABLE_INDEX(number, x);
			METATABLE_INDEX(number, y);
			METATABLE_END();
		}

		static int __newindex(lua_State* L) {
			auto& vec = ARG_UDATA(1, ::ImVec2);
			METATABLE_BEGIN(::ImVec2, vec);
			METATABLE_NEWINDEX(number, x);
			METATABLE_NEWINDEX(number, y);
			METATABLE_END();
		}
	};

	struct ImVec4
	{
		static int __index(lua_State* L) {
			auto& vec = ARG_UDATA(1, ::ImVec4);
			METATABLE_BEGIN(::ImVec4, vec);
			METATABLE_INDEX(number, x);
			METATABLE_INDEX(number, y);
			METATABLE_INDEX(number, z);
			METATABLE_INDEX(number, w);
			METATABLE_END();
		}

		static int __newindex(lua_State* L) {
			auto& vec = ARG_UDATA(1, ::ImVec4);
			METATABLE_BEGIN(::ImVec4, vec);
			METATABLE_NEWINDEX(number, x);
			METATABLE_NEWINDEX(number, y);
			METATABLE_NEWINDEX(number, z);
			METATABLE_NEWINDEX(number, w);
			METATABLE_END();
		}
	};

	struct ImColor
	{
		static int __index(lua_State* L) {
			METATABLE_END();
		}

		static int __newindex(lua_State* L) {
			METATABLE_END();
		}
	};

	struct p_ImGuiIO
	{
		static int __index(lua_State* L) {
			auto& p_io = ARG_UDATA(1, ImGuiIO*);
			METATABLE_BEGIN(::ImGuiIO, *p_io);
			METATABLE_INDEX(number, DeltaTime);
			METATABLE_INDEX_UDATA_P(udata::p_ImVec2, DisplaySize, ::ImVec2*);

			METATABLE_END();
		}

		static int __newindex(lua_State* L) {
			auto& p_io = ARG_UDATA(1, ImGuiIO*);
			METATABLE_BEGIN(::ImGuiIO, *p_io);
			METATABLE_END();
		}
	};

	struct p_ImFont
	{
		static int __index(lua_State* L) {
			auto& p_font = ARG_UDATA(1, ImFont*);
			METATABLE_BEGIN(ImFont, *p_font);
			METATABLE_INDEX(number, Scale);
			METATABLE_END();
		}

		static int __newindex(lua_State* L) {
			auto& p_font = ARG_UDATA(1, ImFont*);
			METATABLE_BEGIN(ImFont, *p_font);
			METATABLE_NEWINDEX(number, Scale);
			METATABLE_END();
		}
	};
}
