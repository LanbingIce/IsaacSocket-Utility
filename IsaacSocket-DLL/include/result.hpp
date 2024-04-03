#pragma once
#include "pch.h"
#include "Poco/Net/HTTPResponse.h"
namespace result {
    struct Result
    {
        virtual ~Result() {}
    };

    void Push(const std::shared_ptr<result::Result>& result);
    std::shared_ptr<result::Result> Pop();
    void Clear();

    struct TaskResult :Result {
        size_t id;
        TaskResult(size_t id) :id(id) {}
        virtual ~TaskResult() {}
    };

    struct ErrorResult :TaskResult
    {
        string error;
        ErrorResult(size_t id, const string& error) :TaskResult(id), error(error) {}
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
        ResponseResult(size_t id, const string& body, const Poco::Net::HTTPResponse& response) :TaskResult(id), body(body), response(response) {}
    };

    struct WebSocketResult :Result {
        size_t id;
        WebSocketResult(size_t id) :id(id) {}
        virtual ~WebSocketResult() {}
    };

    struct WebSocketOpenResult :WebSocketResult
    {
        WebSocketOpenResult(size_t id) :WebSocketResult(id) {}
    };
    struct WebSocketMessageResult :WebSocketResult
    {
        string message;
        bool isBinary;
        WebSocketMessageResult(size_t id, size_t len, const char* message, bool isBinary) :WebSocketResult(id), message(message, len), isBinary(isBinary) {}
    };
    struct WebSocketClosedResult :WebSocketResult
    {
        short closeStatus;
        string statusDescription;
        WebSocketClosedResult(size_t id, short closeStatus, const string& statusDescription) :WebSocketResult(id), closeStatus(closeStatus), statusDescription(statusDescription) {}
    };
    struct WebSocketErrorResult :WebSocketResult
    {
        string message;
        WebSocketErrorResult(size_t id, const string& message) :WebSocketResult(id), message(message) {}
    };
}
