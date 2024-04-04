#include "module.hpp"
#include "isaac_socket.hpp"
#include <imsdk/TIMManager.h>
#include <imsdk/TIMMessageManager.h>
#include <imsdk/GenerateTestUserSig.h>
#include <Poco/JSON/Object.h>

namespace tim {
    static void TIMRecvNewMsgCallback(const char* json_msg_array, const void* user_data)
    {
        result::Push(result::TIMRecvNewMsgResult(json_msg_array, (const char*)user_data));
    }

    static void TIMCommCallback(int32_t code, const char* desc, const char* json_params, const void* user_data)
    {
        result::Push(result::TIMCommResult(code, desc, json_params, (const char*)user_data));
    }

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
        TIMAddRecvNewMsgCallback(TIMRecvNewMsgCallback, "");
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
        RET(integer, ::TIMSetConfig(json_config, TIMCommCallback, user_data));
    }

    static int TIMLogin(lua_State* L) {
        ARG(1, string, const char*, user_id);
        ARG(2, string, const char*, user_sig);
        ARG_DEF(3, string, const char*, user_data, "");
        RET(integer, ::TIMLogin(user_id, user_sig, TIMCommCallback, user_data));
    }

    static int TIMLogout(lua_State* L) {
        ARG(1, string, const char*, user_id);
        ARG(2, string, const char*, user_sig);
        ARG_DEF(3, string, const char*, user_data, "");
        RET(integer, ::TIMLogin(user_id, user_sig, TIMCommCallback, user_data));
    }

    static int TIMGetLoginUserID(lua_State* L) {
        char user_id_buffer[128]{};
        lua_pushinteger(L, ::TIMGetLoginUserID(user_id_buffer));
        lua_pushstring(L, user_id_buffer);
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
        lua_pushinteger(L, ::TIMMsgSendMessage(conv_id, conv_type, json_msg_param, message_id_buffer, TIMCommCallback, user_data));
        lua_pushstring(L, message_id_buffer);
        return 2;
    }

    static RegisterModule InitModules = [] {
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

    static result::RegisterResultType HandleResult(
        [](const std::any& aResult, lua_State* L)
        {
            if (aResult.type() == typeid(result::TIMRecvNewMsgResult))
            {
                const auto& result = std::any_cast<result::TIMRecvNewMsgResult>(aResult);
                FAST_MOD_CALLBACK_BEGIN(ISMC_TIM_RECV_NEW_MSG);
                MOD_CALLBACK_ARG(string, result.json_msg_array.c_str());
                MOD_CALLBACK_ARG(string, result.user_data.c_str());
                FAST_MOD_CALLBACK_END();
            }
            else if (aResult.type() == typeid(result::TIMCommResult))
            {
                const auto& result = std::any_cast<result::TIMCommResult>(aResult);
                FAST_MOD_CALLBACK_BEGIN(ISMC_TIM_COMM);
                MOD_CALLBACK_ARG(integer, result.code);
                MOD_CALLBACK_ARG(string, result.desc.c_str());
                MOD_CALLBACK_ARG(string, result.json_params.c_str());
                MOD_CALLBACK_ARG(string, result.user_data.c_str());
                FAST_MOD_CALLBACK_END();
            }
            else
            {
                return false;
            }
            return true;
        });
}