#pragma once
#include "pch.h"
namespace result {
	struct Result
	{
		virtual ~Result() {}
	};

	struct TaskResult :Result {
		size_t id;
		string result;
		TaskResult(size_t id, string result) :id(id), result(result) {}
	};

	struct TIMRecvNewMsg :Result
	{
		string json_msg_array;
		string user_data;
		TIMRecvNewMsg(const char* json_msg_array, const char* user_data) :json_msg_array(json_msg_array), user_data(user_data) {}
	};

	struct TIMComm :Result
	{
		int32_t code;
		string desc;
		string json_params;
		string user_data;
		TIMComm(int32_t code, const char* desc, const char* json_params, const char* user_data) :code(code), desc(desc), json_params(json_params), user_data(user_data) {}
	};
}
