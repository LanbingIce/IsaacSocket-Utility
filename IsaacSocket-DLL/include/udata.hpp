#pragma once
#include "module.hpp"
#include <glad/glad.h>
namespace udata {
	struct Texture {
		GLuint textureId = 0;

		static int lua_index(lua_State* L) {
			ARG_CPPDATA(1, Texture, texture);
			METATABLE_BEGIN(Texture, *texture);
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

			ARG_CPPDATA(1, LUA_WIN32_FIND_DATAW, data);
			METATABLE_BEGIN(WIN32_FIND_DATAW, (*data).data);
			METATABLE_INDEX(stdwstring, cFileName);
			METATABLE_END();
		}
		static int lua_newindex(lua_State* L) {
			METATABLE_END();
		}

	};

	struct Task {
		inline static std::mutex mutex;
		inline static size_t nextId;
		size_t id;
		Task() {
			std::lock_guard lock(mutex);
			id = ++nextId;
		}

		static int Then(lua_State* L) {
			ARG_CPPDATA(1, Task, task);
			if (!lua_isfunction(L, 2))
			{
				return luaL_error(L, "bad argument #2: continuation should be function");
			}

			lua_getglobal(L, "_ISAAC_SOCKET");
			lua_pushstring(L, "TaskContinuation");
			lua_gettable(L, -2);
			lua_pushinteger(L, task->id);
			lua_pushvalue(L, 2);
			lua_settable(L, -3);
			return 0;
		}

		static int lua_index(lua_State* L) {
			ARG_CPPDATA(1, Task, task);
			METATABLE_BEGIN(Task, *task);
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
			ARG_CPPDATA(1, Image, image);
			METATABLE_BEGIN(Image, *image);
			METATABLE_INDEX(integer, width);
			METATABLE_INDEX(integer, height);
			METATABLE_INDEX(integer, channels);
			METATABLE_END();
		}

		static int lua_newindex(lua_State* L) {
			METATABLE_END();
		}
	};
}
