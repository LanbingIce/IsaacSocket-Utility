#pragma once
#include "lua.hpp"
#include "result.hpp"

#include <myws/myws.hpp>
#include <glad/glad.h>
#include <Poco/Net/HTTPResponse.h>
namespace udata {
    struct HistoryItem
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };

    struct p_Options
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };

    struct Texture {
        GLuint textureId = 0;
        static int lua_index(lua_State* L);
        static int lua_newindex(lua_State* L);
        Texture& operator=(Texture&&) = delete;
        ~Texture();
    };

    struct LUA_WIN32_FIND_DATAW {
        WIN32_FIND_DATAW data;
        static int lua_index(lua_State* L);
        static int lua_newindex(lua_State* L);
    };

    struct ResponseResult
    {
        Poco::Net::HTTPResponse::HTTPStatus statusCode;
        string reasonPhrase;
        std::map<string, string> headers;
        string body;
        Poco::Net::HTTPResponse response;
        static int lua_index(lua_State* L);
        static int lua_newindex(lua_State* L);
    };

    struct Task {
        enum State
        {
            RUNNING,
            COMPLETED,
            FAULTED
        }state = RUNNING;
        int id;
        string error;
        std::any result;
        std::any executor;
        std::mutex _mutex;
        Task();
        static int IsCompletedSuccessfully(lua_State* L);
        static int IsFaulted(lua_State* L);
        static int IsCompleted(lua_State* L);
        static int GetResult(lua_State* L);
        static int Then(lua_State* L);
        static int lua_index(lua_State* L);
        static int lua_newindex(lua_State* L);
    };

    struct WebSocketClient {
        enum State
        {
            CONNECTING,
            OPEN,
            CLOSING,
            CLOSED
        }state = CONNECTING;
        int id;
        std::mutex _mutex;
        myws::MyWS ws;
        WebSocketClient(const string& url);
        ~WebSocketClient();
        static int IsOpen(lua_State* L);
        static int IsClosed(lua_State* L);
        static int Send(lua_State* L);
        static int Close(lua_State* L);
        static int lua_index(lua_State* L);
        static int lua_newindex(lua_State* L);
    };

    struct Image {
        std::vector<uint8_t> data;
        int width = 0, height = 0, channels = 0;
        static int lua_index(lua_State* L);
        static int lua_newindex(lua_State* L);
    };

    struct p_ImVec2
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };

    struct ImVec2
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };

    struct ImVec4
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };

    struct ImColor
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };

    struct p_ImGuiIO
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };

    struct p_ImFont
    {
        static int __index(lua_State* L);
        static int __newindex(lua_State* L);
    };
}
