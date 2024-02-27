#include "module.hpp"
#include "state.hpp"
#include <UserSig/GenerateTestUserSig.h>

namespace imsdk_ {

	static int TIMGetSDKVersion(lua_State* L) {
		RET(string, local.imsdk.TIMGetSDKVersion());
	}

	static int TIMInit(lua_State* L) {
		ARG(1, integer, uint64_t, sdk_app_id);
		Json::Value root;
		root["sdk_config_config_file_path"] = utils::GetDataFilePath("ImSDK");
		root["sdk_config_log_file_path"] = utils::GetDataFilePath("ImSDK");
		Json::StreamWriterBuilder swb;
		string str = Json::writeString(swb, root);
		RET(integer, local.imsdk.TIMInit(sdk_app_id, str.c_str()));
	}

	static int TIMGetServerTime(lua_State* L) {
		RET(integer, local.imsdk.TIMGetServerTime());
	}

	static int TIMLogin(lua_State* L) {
		ARG(1, string, const char*, user_id);
		ARG(2, string, const char*, user_sig);
		RET(integer, local.imsdk.TIMLogin(user_id, user_sig, local.callbacks.TIMCommCallback, nullptr));
	}

	static int TIMMsgSendMessage(lua_State* L) {
		ARG(1, string, const char*, conv_id);
		ARG(2, integer, TIMConvType, conv_type);
		ARG(3, string, const char*, json_msg_param);
		char message_id_buffer[128];
		local.lua.lua_pushinteger(L, local.imsdk.TIMMsgSendMessage(conv_id, conv_type, json_msg_param, message_id_buffer, local.callbacks.TIMCommCallback, nullptr));
		RET(string, message_id_buffer);
	}

	static int GenUserSig(lua_State* L) {
		ARG(1, string, const char*, user_id);
		ARG(2, integer, uint32_t, sdk_app_id);
		ARG(3, string, const char*, secret_key);
		RET(string, GenerateTestUserSig::instance().genTestUserSig(user_id, sdk_app_id, secret_key).c_str());
	}

	static RegisterModule Init = [] {
		MODULE_BEGIN(TIM);
		MODULE_FUNC(TIMGetSDKVersion);
		MODULE_FUNC(TIMInit);
		MODULE_FUNC(TIMGetServerTime);
		MODULE_FUNC(TIMLogin);
		MODULE_FUNC(TIMMsgSendMessage);
		MODULE_FUNC(GenUserSig);
		MODULE_END();
		};
}


