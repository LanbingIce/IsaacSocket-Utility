#include "module.hpp"
#include "async.hpp"
#include "function_.hpp"

namespace async {

HandleTable<Coroutine> &promiseTable() {
    static HandleTable<Coroutine> table;
    return table;
}

int luaPromiseStatus(lua_State* L) {
    local.lua.lua_pushvalue(L, 1);
    local.lua.lua_pushstring(L, "Id");
    local.lua.lua_gettable(L, -2);
    ARG(-1, integer, Handle, h);
    if (auto *p = promiseTable().find(h)) {
        if (p->isReady()) {
            local.lua.lua_pushstring(L, "READY");
        } else {
            local.lua.lua_pushstring(L, "RUNNING");
        }
    } else {
        local.lua.lua_pushstring(L, "CANCELED");
    }
    return 1;
}

int luaPromiseCancel(lua_State* L) {
    local.lua.lua_pushvalue(L, 1);
    local.lua.lua_pushstring(L, "Id");
    local.lua.lua_gettable(L, -2);
    ARG(-1, integer, Handle, h);
    if (auto *p = promiseTable().find(h)) {
        p->cancelJob();
    }
    return 1;
}

int luaPromiseThen(lua_State *L) {
    local.lua.lua_pushvalue(L, 1);
    local.lua.lua_pushstring(L, "Id");
    local.lua.lua_gettable(L, -2);
    ARG(-1, integer, Handle, h);
    if (!promiseTable().find(h)) [[likely]] {
        return 0;
    }
    // _ISAAC_SOCKET._PROMISES[promiseHandle] = arg1
    auto top = local.lua.lua_gettop(L);
    local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
    local.lua.lua_pushstring(L, "_PROMISES");
    local.lua.lua_gettable(L, -2);
    if (!local.lua.lua_istable(L, -1)) [[unlikely]] {
        local.lua.lua_pop(L, 1);
        local.lua.lua_newtable(L);
        local.lua.lua_pushstring(L, "_PROMISES");
        local.lua.lua_pushvalue(L, -2);
        local.lua.lua_settable(L, -4);
    }
    local.lua.lua_pushinteger(L, (lua_Integer)h);
    /* local.lua.lua_pushstdstring(L, std::to_string(h)); */
    local.lua.lua_pushvalue(L, 2);
    local.lua.lua_settable(L, -3);
    local.lua.lua_settop(L, top);
    local.lua.lua_pop(L, 1);
    return 1;
}

void luaPollPromises(lua_State *L) {
    std::vector<Handle> readyHandles;
    for (auto &p: promiseTable().enumerate()) {
        /* cw("poll", reinterpret_cast<uintptr_t>(p.get())); */
        p->pollState();
        if (p->isReady()) {
            Handle h = (Handle)reinterpret_cast<uintptr_t>(p.get());
            readyHandles.push_back(h);
        }
    }
    for (auto h: readyHandles) {
        auto *p = promiseTable().find(h);
        if (!p || !p->isReady()) [[unlikely]] {
            continue;
        }
        auto top = local.lua.lua_gettop(L);
        /* local.lua.lua_pushinteger(L, 42); */
        // _ISAAC_SOCKET._PROMISES[promiseHandle](results...)
        local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
        local.lua.lua_pushstring(L, "_PROMISES");
        local.lua.lua_gettable(L, -2);
        if (!local.lua.lua_istable(L, -1)) [[unlikely]] {
            local.lua.lua_pop(L, 1);
            local.lua.lua_newtable(L);
            local.lua.lua_pushstring(L, "_PROMISES");
            local.lua.lua_pushvalue(L, -2);
            local.lua.lua_settable(L, -4);
        }
        local.lua.lua_remove(L, -2);
        local.lua.lua_pushinteger(L, (lua_Integer)h);
        /* local.lua.lua_pushstdstring(L, std::to_string(h)); */
        local.lua.lua_gettable(L, -2);
        local.lua.lua_pushinteger(L, (lua_Integer)h);
        /* local.lua.lua_pushstdstring(L, std::to_string(h)); */
        local.lua.lua_pushnil(L);
        local.lua.lua_settable(L, -4);
        local.lua.lua_remove(L, -2);
        int n = 0;
        try {
            n = p->getResult(L);
        } catch (std::exception const &e) {
            cw("Exception in async function:", e.what());
            n = -1;
        } catch (...) {
            cw("Exception in async function: unknown exception");
            n = -1;
        }
        if (n >= 0 && !local.lua.lua_isnoneornil(L, -1 - n)) [[likely]] {
            if(local.lua.lua_pcall(L, n, 0, 0)!=LUA_OK){std::string _err="?";if(local.lua.lua_isstring(L,-1)){_err=local.lua.lua_tostring(L,-1);};local.lua.lua_pop(L, 1);_err.append("\n");function_::ConsoleOutput(_err, 0xFFF08080);cw("Error in async callback:", _err.c_str());}
        }
        local.lua.lua_settop(L, top);
        promiseTable().destroy(h);
    }
}

}
