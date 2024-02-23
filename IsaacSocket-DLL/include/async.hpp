#pragma once

#include "handle.hpp"
#include "lua.hpp"
#include "state.hpp"

namespace async {

	using Resolve = std::function<void(std::function<int(lua_State*)>&&)>;
	using Promise = std::function<void(std::stop_token, Resolve)>;

	struct PromiseThread {
		std::atomic<int> ready;
		std::jthread thread;
		std::function<int(lua_State*)> result;
		std::exception_ptr error;

		explicit PromiseThread(Promise entry) : ready(0), thread([entry = std::move(entry), this](std::stop_token stoken) mutable {
			try {
				entry(stoken, [this](std::function<int(lua_State*)>&& result) {
					this->result = std::move(result);
					this->ready.store(1, std::memory_order_release);
					});
			}
			catch (...) {
				this->error = std::current_exception();
				this->ready.store(1, std::memory_order_release);
			}
			}) {}

		bool isReady() const {
			return ready.load(std::memory_order_acquire) != 0;
		}

		int getResult(lua_State* L) {
			if (error) [[unlikely]] {
				std::rethrow_exception(error);
				}
				if (!result) [[unlikely]] {
					throw std::invalid_argument("no result functor set");
					}
				int n = result(L);
				/* thread.detach(); */
				return n;
		}

		void cancelJob() {
			if (thread.joinable()) {
				thread.request_stop();
			}
		}
	};

	void luaPollPromises(lua_State* L);
	int luaPromiseThen(lua_State* L);
	int luaPromiseCancel(lua_State* L);
	int luaPromiseStatus(lua_State* L);
	HandleTable<PromiseThread>& promiseTable();

	inline int luaPromiseReturn(lua_State* L, Promise promise) {
		Handle h = promiseTable().create(std::make_unique<PromiseThread>(std::move(promise)));
		local.lua.lua_createtable(L, 0, 4);
		local.lua.lua_pushstring(L, "Id");
		local.lua.lua_pushinteger(L, (lua_Integer)h);
		local.lua.lua_settable(L, -3);
		local.lua.lua_pushstring(L, "Then");
		local.lua.lua_pushcfunction(L, luaPromiseThen);
		local.lua.lua_settable(L, -3);
		local.lua.lua_pushstring(L, "Cancel");
		local.lua.lua_pushcfunction(L, luaPromiseCancel);
		local.lua.lua_settable(L, -3);
		local.lua.lua_pushstring(L, "Status");
		local.lua.lua_pushcfunction(L, luaPromiseStatus);
		local.lua.lua_settable(L, -3);
		return 1;
	}

#define ASYNC_BEGIN(...) return async::luaPromiseReturn(L, [__VA_ARGS__] (std::stop_token stoken, async::Resolve resolve) -> void {
#define ASYNC_STOP_CHECK() do { if (stoken.stop_requested()) return; } while (0)
#define ASYNC_RET(...) resolve([__VA_ARGS__] (lua_State* L) -> int {
#define ASYNC_END() }); })

}
