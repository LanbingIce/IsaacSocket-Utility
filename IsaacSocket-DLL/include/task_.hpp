#pragma once
#include "utils.hpp"
#include <Poco/TaskManager.h>
#include <state.hpp>
#include "module.hpp"
#include "function_.hpp"
#include "udata.hpp"

namespace task_ {
	struct _Task : Poco::Task {
		_Task(std::function<void()> callback) : Task(""), callback(callback) {
		}
		std::function < void()> callback;
		void runTask() {
			callback();
		}
	};

	static int RunCallback() {

		int top = lua_gettop(L);

		lua_getglobal(L, "_ISAAC_SOCKET");
		lua_pushstring(L, "TaskContinuation");
		lua_gettable(L, -2);

		std::lock_guard<std::mutex> lock(local.responsesMutex);

		for (auto it = local.map.begin(); it != local.map.end(); ++it) {
			lua_pushinteger(L, it->first);
			lua_gettable(L, -2);
			if (!lua_isfunction(L, -1))
			{
				lua_pop(L, 1);
				continue;
			}
			lua_pushstring(L, it->second.c_str());

			_LUA_PCALL(1,0);

			lua_pushinteger(L, it->first);
			lua_pushnil(L);
			lua_settable(L, -3);
		}

		local.map.clear();
		lua_settop(L, top);
		return 0;
	}

	static size_t New() {
		auto task = NEW_CPPDATA(Task);
		return task->id;
	}

	static void Run(std::function <void()> callback)
	{
		local.taskManager.start(new _Task(callback));
	}
}
