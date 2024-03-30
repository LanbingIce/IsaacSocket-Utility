#include "module.hpp"
#include "udata.hpp"
#include "state.hpp"
#include "task_.hpp"

#include "Poco/Net/WebSocket.h"
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URI.h>

udata::WebSocketClient::WebSocketClient(const string& url) {
    {
        std::lock_guard lock(local.mutex);
        id = ++nextId;
    }
    task_::Run([&, url] {
        Poco::URI uri(url);
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/?encoding=text", Poco::Net::HTTPMessage::HTTP_1_1);
        Poco::Net::HTTPResponse response;
        request.set("origin", "http://www.websocket.org");
        auto webSocket = Poco::Net::WebSocket(session, request, response);
        webSocket.setReceiveTimeout(0);
        pWebSocket = &webSocket;
        string error;
        try {
            char buffer[1024];
            {
                std::lock_guard lock(local.mutex);
                local.pResults.push_back(std::make_shared<result::WebSocketOpenResult>(id));
            }
            while (true)
            {
                int flags;
                int len = pWebSocket->receiveFrame(buffer, 1024, flags);
                std::lock_guard lock(local.mutex);
                if (flags & pWebSocket->FRAME_OP_BINARY)
                {
                    local.pResults.push_back(std::make_shared<result::WebSocketMessageResult>(id, len, buffer, true));
                }
                else if (flags & pWebSocket->FRAME_OP_TEXT)
                {
                    local.pResults.push_back(std::make_shared<result::WebSocketMessageResult>(id, len, buffer, false));
                }
                else if (flags & pWebSocket->FRAME_OP_CLOSE)
                {
                    break;
                }

            }
        }
        catch (Poco::Exception& e) {
            error = e.displayText();
        }
        catch (std::exception e) {
            error = e.what();
        }
        if (error == "")
        {
            local.pResults.push_back(std::make_shared<result::WebSocketClosedResult>(id, 1000, "Close"));
        }
        else {
            local.pResults.push_back(std::make_shared<result::WebSocketErrorResult>(id, error));
        }
        pWebSocket->close();
        });
}

udata::WebSocketClient::~WebSocketClient() {
    pWebSocket->close();
}

int udata::WebSocketClient::IsOpen(lua_State* L) {
    auto& uws = ARG_UDATA(1, WebSocketClient);
    RET(boolean, uws.state == uws.OPEN);
}

int udata::WebSocketClient::IsClosed(lua_State* L) {
    auto& uws = ARG_UDATA(1, WebSocketClient);
    RET(boolean, uws.state == uws.CLOSED);
}

int udata::WebSocketClient::Send(lua_State* L) {
    auto& uws = ARG_UDATA(1, WebSocketClient);
    ARG(2, string, const char*, msg);
    ARG_DEF(3, boolean, bool, isBinary, false);

    size_t len = (size_t)luaL_len(L, 2);

    if (uws.state == OPEN)
    {
        auto& ws = *uws.pWebSocket;
        RET(integer, ws.sendFrame(msg, len, isBinary ? Poco::Net::WebSocket::FRAME_BINARY : Poco::Net::WebSocket::FRAME_TEXT));
    }
    return 0;
}

int udata::WebSocketClient::Close(lua_State* L) {
    auto& uws = ARG_UDATA(1, WebSocketClient);
    ARG_DEF(2, integer, short, closeStatus, 1000);
    ARG_DEF(3, string, const char*, statusDescription, "");

    if (uws.state == OPEN)
    {
        auto& ws = *uws.pWebSocket;
        uws.state = CLOSING;
        ws.shutdown(closeStatus, statusDescription);
        RET(boolean, true);
    }
    return 0;
}

int udata::WebSocketClient::lua_index(lua_State* L) {
    auto& ws = ARG_UDATA(1, udata::WebSocketClient);
    METATABLE_BEGIN(WebSocketClient, ws);
    METATABLE_INDEX(cfunction, IsOpen);
    METATABLE_INDEX(cfunction, IsClosed);
    METATABLE_INDEX(cfunction, Send);
    METATABLE_INDEX(cfunction, Close);
    METATABLE_END();
}

int udata::WebSocketClient::lua_newindex(lua_State* L) {
    METATABLE_END();
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
        SET_CALLBACK(6, webSocketClients);

        return 1;
    }

    static RegisterModule InitModules = [] {
        MODULE_BEGIN(WebSocket);
        MODULE_FUNC(Client);
        MODULE_END();
        };
};
