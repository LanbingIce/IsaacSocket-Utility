#pragma once
#include "pch.h"
#include "Poco/Net/HTTPResponse.h"
namespace result {
	struct Result
	{
		virtual ~Result() {}
	};

	struct TaskResult :Result {
		size_t id;
		TaskResult(size_t id) :id(id) {}
	};

	struct ErrorResult :TaskResult
	{
		string error;
		ErrorResult(size_t id, string error) :TaskResult(id), error(error) {};
	};

	struct TIMRecvNewMsgResult :Result
	{
		string json_msg_array;
		string user_data;
		TIMRecvNewMsgResult(const char* json_msg_array, const char* user_data) :json_msg_array(json_msg_array), user_data(user_data) {}
	};

	struct TIMCommResult :Result
	{
		int32_t code;
		string desc;
		string json_params;
		string user_data;
		TIMCommResult(int32_t code, const char* desc, const char* json_params, const char* user_data) :code(code), desc(desc), json_params(json_params), user_data(user_data) {}
	};

	struct ResponseResult :TaskResult
	{
		string body;
		Poco::Net::HTTPResponse response;
		ResponseResult(size_t id, string body, Poco::Net::HTTPResponse response) :TaskResult(id), body(body), response(response) {};
	};
}
