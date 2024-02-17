#pragma once

#include "module.hpp"
#include <httplib.h>

namespace http {

static int RequestGet(lua_State* L) {
    ARG(1, string, const char *, base);
    ARG(2, string, const char *, uri);
    ARG(3, string, const char *, headers_);
    ARG(4, string, const char *, params_);
    httplib::Client cli(base);
    httplib::Headers headers;
    httplib::Params params;
    auto res = cli.Get(uri, params, headers);
    if (!res) [[unlikely]] return 0;
    RET_TABLE();
    RET_TABLE_KEY(string, "status", integer, res->status);
    RET_TABLE_KEY(string, "body", stdstring, res->body);
    RET_TABLE_KEY(string, "reason", stdstring, res->reason);
    RET_TABLE_KEY(string, "location", stdstring, res->location);
    RET_TABLE_END();
}

static int RequestPost(lua_State* L) {
    ARG(1, string, const char *, base);
    ARG(2, string, const char *, uri);
    ARG(3, string, const char *, headers_);
    ARG(4, string, const char *, content);
    ARG(5, string, const char *, contentType);
    httplib::Client cli(base);
    httplib::Headers headers;
    auto res = cli.Post(uri, headers, content, contentType);
    if (!res) [[unlikely]] return 0;
    RET_TABLE();
    RET_TABLE_KEY(string, "status", integer, res->status);
    RET_TABLE_KEY(string, "body", stdstring, res->body);
    RET_TABLE_KEY(string, "reason", stdstring, res->reason);
    RET_TABLE_KEY(string, "location", stdstring, res->location);
    RET_TABLE_END();
}

static void Init() {
    DEFMOD(WinAPI);
    DEF(RequestGet);
    ENDMOD();
}

}
