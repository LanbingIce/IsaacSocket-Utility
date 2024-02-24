#pragma once

#include "handle.hpp"
#include "lua.hpp"
#include "state.hpp"

namespace async {

struct Coroutine;

using Promise = std::function<void(Coroutine *)>;

struct Coroutine {
    int state;
    Promise promise;
    std::function<int(lua_State *)> result;
    
    Coroutine(Coroutine &&) = delete;

    explicit Coroutine(Promise promise): state(0), promise(std::move(promise)), result() {}

    void pollState() {
        promise(this);
    };

    bool isReady() const {
        return state == 1;
    }

    int getResult(lua_State *L) {
        if (!result) [[unlikely]] {
            return -1;
        }
        int n = result(L);
        return n;
    }

    void cancelJob() {
        state = 1;
    }
};

void luaPollPromises(lua_State *L);
int luaPromiseThen(lua_State *L);
int luaPromiseCancel(lua_State *L);
int luaPromiseStatus(lua_State *L);
HandleTable<Coroutine> &promiseTable();

inline int luaPromiseReturn(lua_State *L, Promise promise) {
    Handle h = promiseTable().create(std::make_unique<Coroutine>(std::move(promise)));
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

#define ASYNC_BEGIN(...) return async::luaPromiseReturn(L, [__VA_ARGS__] (async::Coroutine *coroutine) -> void {
#define ASYNC_YIELD() return;
#define ASYNC_RET(...) coroutine->result = [__VA_ARGS__] (lua_State* L) -> int {
#define ASYNC_END() }; coroutine->state = 1; })

}
