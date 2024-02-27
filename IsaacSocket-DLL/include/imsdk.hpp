#pragma once
#include "pch.h"
#include "utils.hpp"

typedef int (*TIMRecvNewMsgCallback)(const char* json_msg_array, const void* user_data);
typedef int (*TIMCommCallback)(int32_t code, const char* desc, const char* json_params, const void* user_data);

enum TIMResult {
	/// 接口调用成功
	TIM_SUCC = 0,
	/// 接口调用失败，ImSDK 未初始化
	TIM_ERR_SDKUNINIT = -1,
	/// 接口调用失败，用户未登录
	TIM_ERR_NOTLOGIN = -2,
	/// 接口调用失败，错误的 Json 格式或 Json Key
	TIM_ERR_JSON = -3,
	/// 接口调用失败，参数错误
	TIM_ERR_PARAM = -4,
	/// 接口调用失败，无效的会话
	TIM_ERR_CONV = -5,
	/// 接口调用失败，无效的群组
	TIM_ERR_GROUP = -6,
};

/// 1.2 会话类型
enum TIMConvType {
	/// 无效会话
	kTIMConv_Invalid,
	/// 个人会话
	kTIMConv_C2C,
	/// 群组会话
	kTIMConv_Group,
	/// 系统会话，已废弃
	kTIMConv_System,
};

namespace imsdk {

#define _(ret,name,...) ret(*name)(__VA_ARGS__)=(decltype(name))GetProcAddress(hLuaModule, #name)
#pragma warning(disable: 6387)//禁用警告	C6387	“hLuaModule”可能是“0” : 这不符合函数“GetProcAddress”的规范。

	struct ImSDK
	{

		HMODULE hLuaModule = LoadLibraryW(utils::GetDataFilePathW(L"ImSDK.dll").c_str());

		_(int, TIMInit, uint64_t sdk_app_id, const char* json_sdk_config);

		_(const char*, TIMGetSDKVersion, void);

		_(void, TIMAddRecvNewMsgCallback, TIMRecvNewMsgCallback cb, const void* user_data);

		_(int, TIMMsgSendMessage, const char* conv_id, enum TIMConvType conv_type, const char* json_msg_param, char* message_id_buffer, TIMCommCallback cb, const void* user_data);

		_(int, TIMLogin, const char* user_id, const char* user_sig, TIMCommCallback cb, const void* user_data);

		_(uint64_t, TIMGetServerTime);

	};
#pragma warning(default: 6387)//重新启用警告C6387
#undef _
}
