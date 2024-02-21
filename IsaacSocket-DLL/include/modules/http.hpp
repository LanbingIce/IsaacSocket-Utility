#pragma once

#include "module.hpp"
#include "handle.hpp"
#include "async.hpp"
/* #define CPPHTTPLIB_OPENSSL_SUPPORT */
#include <httplib.h>

namespace http {

inline auto* client_cache() {
    static KVCache<std::string, httplib::Client> table;
    return &table;
}

static httplib::Client &getClient(std::string const &base) {
    return client_cache()->find(base, [&] {
        return httplib::Client(base);
    });
}

static const char *httpErrorString(httplib::Error e) {
    static const char *const what[] = {
        "Success",
        "Unknown",
        "Connection",
        "BindIPAddress",
        "Read",
        "Write",
        "ExceedRedirectCount",
        "Canceled",
        "SSLConnection",
        "SSLLoadingCerts",
        "SSLServerVerification",
        "UnsupportedMultipartBoundaryChars",
        "Compression",
        "ConnectionTimeout",
        "ProxyConnection",
        "Unknown",
    };
    return what[static_cast<int>(e)];
}

static int RequestGet(lua_State* L) {
    ARG(1, stdstring, std::string, base);
    ARG(2, stdstring, std::string, uri);
    ARG_DEF(3, mapstringstring<httplib::Params>, httplib::Params, params, {});
    ARG_DEF(4, mapstringstring<httplib::Headers>, httplib::Headers, headers, {});

    ASYNC_BEGIN(=);
    httplib::Client cli(base);
    auto resp = std::make_shared<httplib::Result>(cli.Get(uri, params, headers));
    ASYNC_RET(=);
    auto &res = *resp;
    if (!res) [[unlikely]] {
        RET_TABLE();
        RET_TABLE_KEY(string, "error", integer, (int)res.error());
        RET_TABLE_KEY(string, "status", integer, 0);
        RET_TABLE_KEY(string, "reason", string, httpErrorString(res.error()));
        RET_TABLE_END();
    }
    RET_TABLE();
    RET_TABLE_KEY(string, "error", integer, 0);
    RET_TABLE_KEY(string, "status", integer, res->status);
    RET_TABLE_KEY(string, "body", stdstringview, res->body);
    RET_TABLE_KEY(string, "reason", stdstringview, res->reason);
    RET_TABLE_KEY(string, "location", stdstringview, res->location);
    RET_TABLE_KEY(string, "headers", mapstringstring<httplib::Headers>, res->headers);
    RET_TABLE_END();
    ASYNC_END();
}

static int RequestPost(lua_State* L) {
    ARG(1, stdstring, std::string, base);
    ARG(2, stdstring, std::string, uri);
    ARG(3, stdstringview, std::string_view, content);
    ARG(4, stdstring, std::string, contentType);
    ARG_DEF(5, mapstringstring<httplib::Headers>, httplib::Headers, headers, {});
    ARG_DEF(6, stdstring, std::string, method, "POST");

    ASYNC_BEGIN(=);
    httplib::Client cli(base);
    auto res = cli.PostEx(method, uri, headers, content.data(), content.size(), contentType);
    ASYNC_RET(&);
    if (!res) [[unlikely]] return 0;
    RET_TABLE();
    RET_TABLE_KEY(string, "status", integer, res->status);
    RET_TABLE_KEY(string, "body", stdstringview, res->body);
    RET_TABLE_KEY(string, "reason", stdstringview, res->reason);
    RET_TABLE_KEY(string, "location", stdstringview, res->location);
    RET_TABLE_KEY(string, "headers", mapstringstring<httplib::Headers>, res->headers);
    RET_TABLE_END();
    ASYNC_END();
}

static int FreeClient(lua_State* L) {
    ARG(1, stdstring, std::string, base);
    client_cache()->destroy(base);
    return 0;
}

static void Init() {
    MODULE_BEGIN(Http);
    MODULE_FUNC(RequestGet);
    MODULE_FUNC(RequestPost);
    MODULE_FUNC(FreeClient);
    MODULE_END();
}

/* example:
if IsaacSocket and Input.IsButtonTriggered(Keyboard.KEY_A, 0) then
    local job = IsaacSocket.Http.RequestGet("https://www.lua.org", "/manual/5.2/manual.html"):Then(function (res)
        if res.status == 200 then
            print(res.body)
        end
    end)
    -- you may optionally call job:Cancel() to try cancel the job
end
*/

}
