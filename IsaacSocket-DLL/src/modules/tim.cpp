#include "module.hpp"
#include "state.hpp"
#include <imsdk/TIMManager.h>
#include <imsdk/GenerateTestUserSig.h>
#include <Poco/JSON/Object.h>

namespace tim {
	static int GenUserSig(lua_State* L) {
		ARG(1, string, const char*, user_id);
		ARG(2, integer, uint32_t, sdk_app_id);
		ARG(3, string, const char*, secret_key);
		RET(string, GenerateTestUserSig::instance().genTestUserSig(user_id, sdk_app_id, secret_key).c_str());
	}

	static int TIMInit(lua_State* L) {
		ARG(1, integer, uint64_t, sdk_app_id);
		Poco::JSON::Object root;
		root.set("sdk_config_config_file_path", utils::GetDataFilePath("ImSDK"));
		root.set("sdk_config_log_file_path", utils::GetDataFilePath("ImSDK"));
		std::ostringstream ostr;
		root.stringify(ostr);
		RET(integer, ::TIMInit(sdk_app_id, ostr.str().c_str()));
	}

	static int TIMUInit(lua_State* L) {
		RET(integer, ::TIMUninit());
	}

	static int TIMGetSDKVersion(lua_State* L) {
		RET(string, ::TIMGetSDKVersion());
	}

	static int TIMGetServerTime(lua_State* L) {
		RET(integer, ::TIMGetServerTime());
	}

	static int TIMSetConfig(lua_State* L) {
		ARG(1, string, const char*, json_config);
		ARG_DEF(2, string, const char*, user_data, "");
		RET(integer, ::TIMSetConfig(json_config, local.callbacks.TIMCommCallback, user_data));
	}

	static int TIMLogin(lua_State* L) {
		ARG(1, string, const char*, user_id);
		ARG(2, string, const char*, user_sig);
		ARG_DEF(3, string, const char*, user_data, "");
		RET(integer, ::TIMLogin(user_id, user_sig, local.callbacks.TIMCommCallback, user_data));
	}

	static int TIMLogout(lua_State* L) {
		ARG(1, string, const char*, user_id);
		ARG(2, string, const char*, user_sig);
		ARG_DEF(3, string, const char*, user_data, "");
		RET(integer, ::TIMLogin(user_id, user_sig, local.callbacks.TIMCommCallback, user_data));
	}

	static int TIMGetLoginUserID(lua_State* L) {
		char user_id_buffer[128]{};
		local.lua.lua_pushinteger(L, ::TIMGetLoginUserID(user_id_buffer));
		local.lua.lua_pushstring(L, user_id_buffer);
		return 2;
	}

	static int TIMGetLoginStatus(lua_State* L) {
		RET(integer, ::TIMGetLoginStatus());
	}

	static int TIMMsgSendMessage(lua_State* L) {
		ARG(1, string, const char*, conv_id);
		ARG(2, integer, TIMConvType, conv_type);
		ARG(3, string, const char*, json_msg_param);
		ARG_DEF(4, string, const char*, user_data, "");
		char message_id_buffer[128]{};
		local.lua.lua_pushinteger(L, ::TIMMsgSendMessage(conv_id, conv_type, json_msg_param, message_id_buffer, local.callbacks.TIMCommCallback, user_data));
		local.lua.lua_pushstring(L, message_id_buffer);
		return 2;
	}

	static RegisterModule Init = [] {
		MODULE_BEGIN(TIM);

		MODULE_FUNC(GenUserSig);

		MODULE_FUNC(TIMInit);
		MODULE_FUNC(TIMUInit);
		MODULE_FUNC(TIMGetSDKVersion);
		MODULE_FUNC(TIMGetServerTime);
		MODULE_FUNC(TIMSetConfig);

		MODULE_FUNC(TIMLogin);
		MODULE_FUNC(TIMLogout);
		MODULE_FUNC(TIMGetLoginUserID);
		MODULE_FUNC(TIMGetLoginStatus);

		MODULE_FUNC(TIMMsgSendMessage);

		MODULE_END();
		};
}