#include "module.hpp"
#include "udata.hpp"
#include "state.hpp"
#include "result.hpp"
#include "isaac_socket.hpp"
#include <myws/myws.hpp>

namespace udata {
    WebSocketClient::WebSocketClient(const string& url) : ws(url) {
        std::lock_guard lock(_mutex);
        id = ++nextId;

        ws.OnOpen = [this] {
            result::Push(std::make_shared<result::WebSocketOpenResult>(id));
            };

        ws.OnMessage = [this](const char* message, int len, bool isBinary) {
            result::Push(std::make_shared <result::WebSocketMessageResult>(id, len, message, isBinary));
            };

        ws.OnClose = [this](short closeStatus, const string& statusDescription) {
            result::Push(std::make_shared <result::WebSocketClosedResult>(id, closeStatus, statusDescription));
            };

        ws.OnError = [this](const string& message) {
            result::Push(std::make_shared <result::WebSocketErrorResult>(id, message));
            };
        ws.Connect();

    }

    int WebSocketClient::IsOpen(lua_State* L) {
        auto& uws = ARG_UDATA(1, WebSocketClient);
        RET(boolean, uws.ws.GetState() == myws::OPEN);
    }

    int WebSocketClient::IsClosed(lua_State* L) {
        auto& uws = ARG_UDATA(1, WebSocketClient);
        RET(boolean, uws.ws.GetState() >= myws::CLOSED);
    }

    int WebSocketClient::Send(lua_State* L) {
        auto& uws = ARG_UDATA(1, WebSocketClient);
        ARG(2, string, const char*, msg);
        ARG_DEF(3, boolean, bool, isBinary, false);
        int len = (int)luaL_len(L, 2);
        RET(integer, uws.ws.Send(msg, len, isBinary));
    }

    int WebSocketClient::Close(lua_State* L) {
        auto& uws = ARG_UDATA(1, WebSocketClient);
        ARG_DEF(2, integer, short, closeStatus, 1000);
        ARG_DEF(3, string, const char*, statusDescription, "");
        RET(boolean, uws.ws.Close(closeStatus, statusDescription));
    }

    int WebSocketClient::lua_index(lua_State* L) {
        auto& uws = ARG_UDATA(1, WebSocketClient);
        METATABLE_BEGIN(WebSocketClient, uws);
        METATABLE_INDEX(cfunction, IsOpen);
        METATABLE_INDEX(cfunction, IsClosed);
        METATABLE_INDEX(cfunction, Send);
        METATABLE_INDEX(cfunction, Close);
        METATABLE_END();
    }

    int WebSocketClient::lua_newindex(lua_State* L) {
        METATABLE_END();
    }

    WebSocketClient::~WebSocketClient() {
        LuaGuard luaGuard;

        if (ws.GetState() < myws::CLOSED)
        {
            RESULT_CALLBACK_BEGIN(errorCallbacks);
            MOD_CALLBACK_ARG(string, "IsaacSocket Disconnected");
            RESULT_CALLBACK_END();
        }

        lua_pushnil(L);
        int index = lua_gettop(L);
        SET_CALLBACK(index, openCallbacks);
        SET_CALLBACK(index, messageCallbacks);
        SET_CALLBACK(index, closedCallbacks);
        SET_CALLBACK(index, errorCallbacks);
    }
}

namespace web_socket
{
    static int Client(lua_State* L) {
        ARG(1, string, const char*, url);
        ARG_CALLBACK(2, callbackOnOpen);
        ARG_CALLBACK(3, callbackOnMessage);
        ARG_CALLBACK(4, callbackOnClosed);
        ARG_CALLBACK(5, callbackOnError);

        lua_settop(L, 5);

        auto& uws = NEW_UDATA(WebSocketClient, url);//6
        int id = uws.id;
        SET_CALLBACK(2, openCallbacks);
        SET_CALLBACK(3, messageCallbacks);
        SET_CALLBACK(4, closedCallbacks);
        SET_CALLBACK(5, errorCallbacks);

        return 1;
    }

    static RegisterModule InitModules = [] {
        MODULE_BEGIN(WebSocket);
        MODULE_FUNC(Client);
        MODULE_END();
        };
};
