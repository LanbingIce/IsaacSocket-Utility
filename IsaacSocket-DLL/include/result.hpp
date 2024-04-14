#pragma once
#include "pch.h"
#include "lua.hpp"
#include "Poco/Net/HTTPResponse.h"
namespace result {
    void Push(const std::any& result);
    std::any Pop();
    void Clear();
    bool IsEmpty();

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
        std::string error;
        ErrorResult(int id, const std::string& error) :TaskResult(id), error(error) {}
    };

    struct TIMRecvNewMsgResult :Result
    {
        std::string json_msg_array;
        std::string user_data;
        TIMRecvNewMsgResult(const std::string& json_msg_array, const std::string& user_data) :json_msg_array(json_msg_array), user_data(user_data) {}
    };

    struct TIMCommResult :Result
    {
        int32_t code;
        std::string desc;
        std::string json_params;
        std::string user_data;
        TIMCommResult(int32_t code, const std::string& desc, const std::string& json_params, const std::string& user_data) :code(code), desc(desc), json_params(json_params), user_data(user_data) {}
    };

    struct ResponseResult :TaskResult
    {
        Poco::Net::HTTPResponse::HTTPStatus statusCode;
        std::string reasonPhrase;
        std::map<std::string, std::string> headers;
        std::string body;
        ResponseResult(int id, Poco::Net::HTTPResponse::HTTPStatus statusCode, const std::string& reasonPhrase, const std::map<std::string, std::string>& headers, const std::string& body) :TaskResult(id), statusCode(statusCode), reasonPhrase(reasonPhrase), headers(headers), body(body) {}
    };

    struct WebSocketOpenResult :TaskResult
    {
        WebSocketOpenResult(int id) :TaskResult(id) {}
    };
    struct WebSocketMessageResult :TaskResult
    {
        std::string message;
        bool isBinary;
        WebSocketMessageResult(int id, int len, const char* message, bool isBinary) :TaskResult(id), message(message, len), isBinary(isBinary) {}
    };
    struct WebSocketClosedResult :TaskResult
    {
        short closeStatus;
        std::string statusDescription;
        WebSocketClosedResult(int id, short closeStatus, const std::string& statusDescription) :TaskResult(id), closeStatus(closeStatus), statusDescription(statusDescription) {}
    };
    struct WebSocketErrorResult :TaskResult
    {
        std::string message;
        WebSocketErrorResult(int id, const std::string& message) :TaskResult(id), message(message) {}
    };
}
