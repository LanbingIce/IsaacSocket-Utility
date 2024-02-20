#pragma once

#include "module.hpp"
#include <httplib.h>

namespace http {

static int RequestGet(lua_State* L) {
    ARG(1, stdstring, std::string, base);
    ARG(2, stdstring, std::string, uri);
    ARG(3, stdstring, std::string, headers_);
    ARG(4, stdstring, std::string, params_);
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
    ARG(1, stdstring, std::string, base);
    ARG(2, stdstring, std::string, uri);
    ARG(3, stdstring, std::string, headers_);
    ARG(4, stdstring, std::string, content);
    ARG(5, stdstring, std::string, contentType);
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
    MODULE_BEGIN(Http);
    MODULE_FUNC(RequestGet);
    MODULE_FUNC(RequestPost);
    MODULE_END();
}

}
