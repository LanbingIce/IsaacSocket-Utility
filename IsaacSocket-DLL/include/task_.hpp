#pragma once
#include "utils.hpp"
#include <Poco/TaskManager.h>
#include <state.hpp>
#include "module.hpp"
#include "function_.hpp"


namespace task_ {
	struct _Task : Poco::Task {
		_Task(std::function<void()> callback) : Task(""), callback(callback) {
		}
		std::function < void()> callback;
		void runTask() {
			callback();
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

	static void RunCallback() {

		lua_State* L = local.isaac->luaEngine->L;
		int top = lua_gettop(L);

		lua_getglobal(L, "_ISAAC_SOCKET");
		lua_pushstring(L, "TaskContinuation");
		lua_gettable(L, -2);

		std::lock_guard<std::mutex> lock(local.responsesMutex);

		for (auto it = local.map.begin(); it != local.map.end(); ++it) {
			lua_pushinteger(L, it->first);
			lua_gettable(L, -2);
			lua_pushstring(L, it->second.c_str());
			if (lua_isfunction(L, -2) && lua_pcall(L, 1, 0, 0) != 0) {
				string _err;
				if (lua_isstring(L, -1)) {
					_err = lua_tostring(L, -1);
				}
				else {
					_err = "unknow error!";
				}
				lua_pop(L, 1);
				_err.append("\n");
				function_::ConsoleOutput(_err, 0xFFF08080);
			}
			lua_pushinteger(L, it->first);
			lua_pushnil(L);
			lua_settable(L, -3);
		}

		local.map.clear();
		lua_settop(L, top);
	}

	static size_t New() {
		lua_State* L = local.isaac->luaEngine->L;
		auto task = NEW_CPPDATA(Task);
		return task->id;
	}

	static void Run(std::function <void()> callback)
	{
		local.taskManager.start(new _Task(callback));
	}
}
