#pragma once
#include "pch.h"
namespace result {
	struct TaskResult {
		size_t id;
		string result;
	};

	struct TIMRecvNewMsg
	{
		string json_msg_array;
		string user_data;
	};

	struct TIMComm
	{
		int32_t code;
		string desc;
		string json_params;
		string user_data;
	};
}
