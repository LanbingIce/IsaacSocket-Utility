#include "module.hpp"
#include "async.hpp"
#include "isaac_socket.hpp"

namespace async {

HandleTable<Coroutine> &promiseTable() {
    static HandleTable<Coroutine> table;
    return table;
}

int luaPromiseStatus(lua_State* L) {
    lua_pushvalue(L, 1);
    lua_pushstring(L, "Id");
    lua_gettable(L, -2);
    ARG(-1, integer, Handle, h);
    if (auto *p = promiseTable().find(h)) {
        if (p->isReady()) {
            lua_pushstring(L, "READY");
        } else {
            lua_pushstring(L, "RUNNING");
        }
    } else {
        lua_pushstring(L, "CANCELED");
    }
    return 1;
}

int luaPromiseCancel(lua_State* L) {
    lua_pushvalue(L, 1);
    lua_pushstring(L, "Id");
    lua_gettable(L, -2);
    ARG(-1, integer, Handle, h);
    if (auto *p = promiseTable().find(h)) {
        p->cancelJob();
    }
    return 1;
}

int luaPromiseThen(lua_State *L) {
    lua_pushvalue(L, 1);
    lua_pushstring(L, "Id");
    lua_gettable(L, -2);
    ARG(-1, integer, Handle, h);
    if (!promiseTable().find(h)) [[likely]] {
        return 0;
    }
    // _ISAAC_SOCKET._PROMISES[promiseHandle] = arg1
    lua_getglobal(L, "_ISAAC_SOCKET");
    lua_pushstring(L, "_PROMISES");
    lua_gettable(L, -2);
    if (!lua_istable(L, -1)) [[unlikely]] {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushstring(L, "_PROMISES");
        lua_pushvalue(L, -2);
        lua_settable(L, -4);
    }
    lua_pushinteger(L, (lua_Integer)h);
    /* lua_pushstdstring(L, std::to_string(h)); */
    lua_pushvalue(L, 2);
    lua_settable(L, -3);
    lua_pop(L, 1);
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
        /* lua_pushinteger(L, 42); */
        // _ISAAC_SOCKET._PROMISES[promiseHandle](results...)
        lua_getglobal(L, "_ISAAC_SOCKET");
        lua_pushstring(L, "_PROMISES");
        lua_gettable(L, -2);
        if (!lua_istable(L, -1)) [[unlikely]] {
            lua_pop(L, 1);
            lua_newtable(L);
            lua_pushstring(L, "_PROMISES");
            lua_pushvalue(L, -2);
            lua_settable(L, -4);
        }
        lua_remove(L, -2);
        lua_pushinteger(L, (lua_Integer)h);
        /* lua_pushstdstring(L, std::to_string(h)); */
        lua_gettable(L, -2);
        lua_pushinteger(L, (lua_Integer)h);
        /* lua_pushstdstring(L, std::to_string(h)); */
        lua_pushnil(L);
        lua_settable(L, -4);
        lua_remove(L, -2);
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
        if (n >= 0 && !lua_isnoneornil(L, -1 - n)) [[likely]] {
            if(lua_pcall(L, n, 0, 0)!=LUA_OK){std::string _err="?";if(lua_isstring(L,-1)){_err=lua_tostring(L,-1);};lua_pop(L, 1);_err.append("\n");isaac_socket::ConsoleOutput(_err, 0xFFF08080);cw("Error in async callback:", _err.c_str());}
        }
        promiseTable().destroy(h);
    }
}

}
