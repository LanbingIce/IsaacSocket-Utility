#pragma once
#include "pch.h"
#include "lua.hpp"
#include "Poco/Net/HTTPResponse.h"
namespace result {
    void Push(const std::any& result);
    std::any Pop();
    void Clear();

    struct RegisterResultType {
        inline static std::vector<std::function<bool(const std::any&, lua_State*)>> resultCallbacks;

        RegisterResultType(std::function<bool(const std::any&, lua_State*)>&& f) {
            resultCallbacks.emplace_back(std::move(f));
        }
    };

    struct Result
    {
        virtual ~Result() = 0 {}
    };

    struct TaskResult :Result {
        int id;
        TaskResult(int id) :id(id) {}
        virtual ~TaskResult() = 0 {}
    };

    struct ErrorResult :TaskResult
    {
        string error;
        ErrorResult(int id, const string& error) :TaskResult(id), error(error) {}
    };

    struct TIMRecvNewMsgResult :Result
    {
        string json_msg_array;
        string user_data;
        TIMRecvNewMsgResult(const string& json_msg_array, const string& user_data) :json_msg_array(json_msg_array), user_data(user_data) {}
    };

    struct TIMCommResult :Result
    {
        int32_t code;
        string desc;
        string json_params;
        string user_data;
        TIMCommResult(int32_t code, const string& desc, const string& json_params, const string& user_data) :code(code), desc(desc), json_params(json_params), user_data(user_data) {}
    };

    struct ResponseResult :TaskResult
    {
        string body;
        Poco::Net::HTTPResponse response;
        ResponseResult(int id, const string& body, const Poco::Net::HTTPResponse& response) :TaskResult(id), body(body), response(response) {}
    };

    struct WebSocketOpenResult :TaskResult
    {
        WebSocketOpenResult(int id) :TaskResult(id) {}
    };
    struct WebSocketMessageResult :TaskResult
    {
        string message;
        bool isBinary;
        WebSocketMessageResult(int id, int len, const char* message, bool isBinary) :TaskResult(id), message(message, len), isBinary(isBinary) {}
    };
    struct WebSocketClosedResult :TaskResult
    {
        short closeStatus;
        string statusDescription;
        WebSocketClosedResult(int id, short closeStatus, const string& statusDescription) :TaskResult(id), closeStatus(closeStatus), statusDescription(statusDescription) {}
    };
    struct WebSocketErrorResult :TaskResult
    {
        string message;
        WebSocketErrorResult(int id, const string& message) :TaskResult(id), message(message) {}
    };
}
