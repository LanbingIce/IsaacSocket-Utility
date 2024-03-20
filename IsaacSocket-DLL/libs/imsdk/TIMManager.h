// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 基础功能接口，包含 IMSDK 的初始化、反初始化、登录、登出以及用户资料管理等功能
//
// 模块参数说明
//  - API 的参数采用 json 字符串格式，请使用文件中预先定义的 JsonKey 进行参数传递和解析
//  - 如果参数中包含非英文字符，请使用 UTF-8 编码
//
// 模块回调说明
//  1. 回调的类型：
//   - 调用 API 时传入的 TIMCommCallback 回调，用于异步返回 API 的调用结果
//   - 调用 TIMSetXXXCallback 设置的全局回调，用于接收后台推送的通知
//  2. 回调触发的线程：
//   - 对于 Windows 平台，当在主线程中调用 @ref TIMInit 接口时，SDK 会将所有回调抛到主线程，请确保主线程已创建消息循环；否则，回调将在 SDK 内部的逻辑线程触发
//   - 对于 Android 平台，当调用 @ref TIMInit 接口的线程支持消息循环时，SDK 会将所有回调抛到该线程；否则，回调将在 SDK 内部的逻辑线程触发
//   - 对于 iOS 和 MAC 平台，SDK 默认将所有回调抛到主线程
//   - 对于 Linux 平台，暂不支持将回调抛到主线程，回调将在 SDK 内部的逻辑线程触发


/////////////////////////////////////////////////////////////////////////////////
//
//                      一. SDK 基础功能相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 连接事件类型
enum TIMNetworkStatus {
    // 已连接
    kTIMConnected,
    // 失去连接
    kTIMDisconnected,
    // 正在连接
    kTIMConnecting,
    // 连接失败
    kTIMConnectFailed,
};

// 1.2 登陆状态
enum TIMLoginStatus {
    // 已登录
    kTIMLoginStatus_Logined = 1,
    // 登录中
    kTIMLoginStatus_Logining = 2,
    // 未登录
    kTIMLoginStatus_UnLogined = 3,
    // 登出中
    kTIMLoginStatus_Logouting = 4,
};

// 1.3 日志级别
enum TIMLogLevel {
    // 关闭日志输出
    kTIMLog_Off,
    // 全量日志
    kTIMLog_Test,
    // 开发调试过程中一些详细信息日志
    kTIMLog_Verbose,
    // 调试日志
    kTIMLog_Debug,
    // 信息日志
    kTIMLog_Info,
    // 警告日志
    kTIMLog_Warn,
    // 错误日志
    kTIMLog_Error,
    // 断言日志
    kTIMLog_Assert,
};

// 1.4 用户状态类型
enum TIMUserStatusType {
    // 未知状态
    kTIMUserStatusType_Unkown = 0,
    // 在线状态
    kTIMUserStatusType_Online = 1,
    // 离线状态
    kTIMUserStatusType_Offline = 2,
    // 未登录（如主动调用 @ref TIMLogout 接口，或者账号注册后还未登录）
    kTIMUserStatusType_UnLogined = 3,
};

// 1.5 用户性别类型
enum TIMGenderType {
    // 未知性别
    kTIMGenderType_Unknown,
    // 性别男
    kTIMGenderType_Male,
    // 性别女
    kTIMGenderType_Female,
};

// 1.6 用户加好友的选项
enum TIMProfileAddPermission {
    // 未知
    kTIMProfileAddPermission_Unknown,
    // 允许任何人添加好友
    kTIMProfileAddPermission_AllowAny,
    // 添加好友需要验证
    kTIMProfileAddPermission_NeedConfirm,
    // 拒绝任何人添加好友
    kTIMProfileAddPermission_DenyAny,
};

// 1.7 资料变更类型
enum TIMProfileChangeType {
    // 未知类型
    kTIMProfileChange_None,
    // 资料修改
    kTIMProfileChange_Profile,
};


/////////////////////////////////////////////////////////////////////////////////
//
//                         二. SDK 基础事件回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 网络状态回调
 *
 * @param status 网络状态，请参考 @ref TIMNetworkStatus
 * @param code 值为ERR_SUCC表示成功，其他值表示失败。详情请参考 [错误码](https://cloud.tencent.com/document/product/269/1671)
 * @param desc 错误描述字符串
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __感知网络状态的回调处理示例__
 * @code{.json}
 * void NetworkStatusListenerCallback(TIMNetworkStatus status, int32_t code, const char* desc, const void* user_data) {
 *     switch(status) {
 *     case kTIMConnected: {
 *         printf("OnConnected ! user_data:0x%08x", user_data);
 *         break;
 *     }
 *     case kTIMDisconnected:{
 *         printf("OnDisconnected ! user_data:0x%08x", user_data);
 *         break;
 *     }
 *     case kTIMConnecting:{
 *         printf("OnConnecting ! user_data:0x%08x", user_data);
 *         break;
 *     }
 *     case kTIMConnectFailed:{
 *         printf("ConnectFailed code:%u desc:%s ! user_data:0x%08x", code, desc, user_data);
 *         break;
 *     }
 *     }
 * }
 * @endcode
 */
typedef void (*TIMNetworkStatusListenerCallback)(enum TIMNetworkStatus status, int32_t code, const char* desc, const void* user_data);

/**
 * 2.2 被踢下线回调
 *
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMKickedOfflineCallback)(const void* user_data);

/**
 * 2.3 用户票据过期回调
 *
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMUserSigExpiredCallback)(const void* user_data);

/**
 * 2.4 当前用户的资料更新的回调
 *
 * @param json_user_profile 当前用户的资料，请参考 @ref UserProfile
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMSelfInfoUpdatedCallback)(const char* json_user_profile, const void* user_data);

/**
 * 2.5 用户状态变更的回调
 *
 * @param json_user_status_array 用户状态的列表，用户状态请参考 @ref TIMUserStatus
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMUserStatusChangedCallback)(const char* json_user_status_array, const void* user_data);

/**
 * 2.6 订阅用户资料变更的回调
 *
 * @param json_user_info_array 订阅用户资料更新列表，用户资料请参考 @ref UserProfile
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMUserInfoChangedCallback)(const char* json_user_info_array, const void* user_data);

/**
 * 2.7 日志回调
 *
 * @param level 日志级别,请参考 @ref TIMLogLevel
 * @param log 日志字符串
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMLogCallback)(enum TIMLogLevel level, const char* log, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                         三. 注册 SDK 基础事件回调 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 设置网络连接状态监听回调
 * 
 * @param cb 连接事件回调，请参考 @ref TIMNetworkStatusListenerCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 *  - 当调用接口 @ref TIMInit 时，ImSDK会去连接云后台。此接口设置的回调用于监听网络连接的状态。
 *  - 网络连接状态包含四个：正在连接、连接失败、连接成功、已连接。这里的网络事件不表示用户本地网络状态，仅指明ImSDK是否与即时通信IM云Server连接状态。
 *  - 可选设置，如果要用户感知是否已经连接服务器，需要设置此回调，用于通知调用者跟通讯后台链接的连接和断开事件，另外，如果断开网络，等网络恢复后会自动重连，自动拉取消息通知用户，用户无需关心网络状态，仅作通知之用
 *  - 只要用户处于登录状态，ImSDK内部会进行断网重连，用户无需关心。
 */
TIM_API void TIMSetNetworkStatusListenerCallback(TIMNetworkStatusListenerCallback cb, const void* user_data);

/**
 * 3.2 设置被踢下线通知回调
 * 
 * @param cb 踢下线回调，请参考 @ref TIMKickedOfflineCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 用户如果在其他终端登录，会被踢下线，这时会收到用户被踢下线的通知，出现这种情况常规的做法是提示用户进行操作（退出，或者再次把对方踢下线）。
 * 用户如果在离线状态下被踢，下次登录将会失败，可以给用户一个非常强的提醒（登录错误码ERR_IMSDK_KICKED_BY_OTHERS：6208），开发者也可以选择忽略这次错误，再次登录即可。
 * 用户在线情况下的互踢情况:
 *  - 用户在设备1登录，保持在线状态下，该用户又在设备2登录，这时用户会在设备1上强制下线，收到 TIMKickedOfflineCallback 回调。
 *    用户在设备1上收到回调后，提示用户，可继续调用login上线，强制设备2下线。这里是在线情况下互踢过程。
 * 用户离线状态互踢:
 *  - 用户在设备1登录，没有进行logout情况下进程退出。该用户在设备2登录，此时由于用户不在线，无法感知此事件，
 *    为了显式提醒用户，避免无感知的互踢，用户在设备1重新登录时，会返回（ERR_IMSDK_KICKED_BY_OTHERS：6208）错误码，表明之前被踢，是否需要把对方踢下线。
 *    如果需要，则再次调用login强制上线，设备2的登录的实例将会收到 TIMKickedOfflineCallback 回调。
 */
TIM_API void TIMSetKickedOfflineCallback(TIMKickedOfflineCallback cb, const void* user_data);

/**
 * 3.3 设置票据过期回调
 * 
 * @param cb 票据过期回调，请参考 @ref TIMUserSigExpiredCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 用户票据，可能会存在过期的情况，如果用户票据过期，此接口设置的回调会调用。
 * 同时, @ref TIMLogin 也将会返回 70001 错误码。开发者可根据错误码或者票据过期回调进行票据更换
 */
TIM_API void TIMSetUserSigExpiredCallback(TIMUserSigExpiredCallback cb, const void* user_data);

/**
 * 3.4 设置当前用户资料更新回调
 * 
 * @param cb 当前用户的资料更新的回调，请参考 @ref TIMSelfInfoUpdatedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetSelfInfoUpdatedCallback(TIMSelfInfoUpdatedCallback cb, const void* user_data);

/**
 * 3.5 设置用户状态变更回调
 * 
 * @param cb 用户状态变更的回调，请参考 @ref TIMUserStatusChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note 收到通知的情况：
 * 1. 订阅过的用户发生了状态变更（包括在线状态和自定义状态），会触发该回调
 * 2. 在 IM 控制台打开了好友状态通知开关，即使未主动订阅，当好友状态发生变更时，也会触发该回调
 * 3. 同一个账号多设备登录，当其中一台设备修改了自定义状态，所有设备都会收到该回调
 */
TIM_API void TIMSetUserStatusChangedCallback(TIMUserStatusChangedCallback cb, const void* user_data);

/**
 * 3.6 设置用户资料变更回调
 * 
 * @param cb 用户资料更新的回调，请参考 @ref TIMUserInfoChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 仅当通过 @ref TIMSubscribeUserInfo 成功订阅的用户（仅限非好友用户）的资料发生变更时，才会激活此回调函数
 */
TIM_API void TIMSetUserInfoChangedCallback(TIMUserInfoChangedCallback cb, const void *user_data);

/**
 * 3.7 设置日志回调
 * 
 * @param cb 日志回调，请参考 @ref TIMLogCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 *  - 设置日志监听的回调之后，ImSDK内部的日志会回传到此接口设置的回调。
 *  - 开发者可以通过接口 @ref TIMSetConfig 配置哪些日志级别的日志回传到回调函数。
 */
TIM_API void TIMSetLogCallback(TIMLogCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                            四. SDK 初始化相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 4.1 ImSDK初始化
 *
 * @param sdk_app_id 官网申请的SDKAppid
 * @param json_sdk_config ImSDK配置选项 Json 字符串, Json Key请参考 @ref SdkConfig
 * @return int 返回TIM_SUCC表示接口调用成功，其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 在使用ImSDK进一步操作之前，需要先初始化ImSDK
 *  - json_sdk_config 可以为 NULL 空字符串指针或者""空字符串，在此情况下 @ref SdkConfig 均为默认值。
 *  - json_sdk_config 里面的每个Json key都是选填的，详情请参考 @ref SdkConfig
 *  - kTIMSdkConfigLogFilePath 和 kTIMSdkConfigConfigFilePath 的值要求是 UTF-8 编码
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_init;
 * json_value_init[kTIMSdkConfigLogFilePath] = "D:\\";
 * json_value_init[kTIMSdkConfigConfigFilePath] = "D:\\";
 *
 * uint64_t sdk_app_id = 1234567890;
 * if (TIM_SUCC != TIMInit(sdk_app_id, json_value_init.toStyledString().c_str())) {
 *     // TIMInit 接口调用错误，ImSDK初始化失败
 * }
 *
 * // json_value_init.toStyledString() 得到 json_sdk_config JSON 字符串如下
 * {
 *    "sdk_config_config_file_path" : "D:\\",
 *    "sdk_config_log_file_path" : "D:\\"
 * }
 * @endcode
 */
TIM_API int TIMInit(uint64_t sdk_app_id, const char* json_sdk_config);

/**
 * 4.2 ImSDK 反初始化
 *
 * @return int 返回TIM_SUCC表示接口调用成功，其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 卸载DLL或退出进程前需此接口卸载ImSDK，清理ImSDK相关资源
 * 
 * __示例__
 * @code{.cpp}
 * if (TIM_SUCC != TIMUninit()) {
 *     // ImSDK 反初始化失败
 * }
 * @endcode
 */
TIM_API int TIMUninit(void);

/**
 * 4.3 获取 ImSDK 版本号
 *
 * @return const char* 返回 ImSDK 的版本号
 */
TIM_API const char* TIMGetSDKVersion(void);

/**
 * 4.4 获取服务器当前时间
 *
 * @return uint64_t 服务器时间，单位 s
 *
 * @note
 * 可用于信令离线推送场景下超时判断
 */
TIM_API uint64_t TIMGetServerTime();

/**
 * 4.5 设置额外的用户配置
 * 
 * @param json_config 配置选项
 * @param cb 返回设置配置之后所有配置的回调，此回调cb可为空，表示不获取所有配置信息。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK 只负责传回给回调函数 cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 * - 目前支持设置的配置有 http 代理的 IP 和端口、socks5 代理的 IP 和端口、输出日志的级别等。
 * - http 代理的 IP 和端口、socks5 代理的 IP 和端口建议调用 @ref TIMInit 之前配置。
 * - 每项配置可以单独设置，也可以一起配置,详情请参考 @ref SetConfig。
 *
 * __设置 http 代理示例__
 * @code{.cpp}
 * Json::Value json_http_proxy;
 * json_http_proxy[kTIMHttpProxyInfoIp] = "http://http-proxy.xxxxx.com";
 * json_http_proxy[kTIMHttpProxyInfoPort] = 8888;
 * json_http_proxy[kTIMHttpProxyInfoUserName] = "User-01";
 * json_http_proxy[kTIMHttpProxyInfoPassword] = "123456";
 * Json::Value json_config;
 * json_config[kTIMSetConfigHttpProxyInfo] = json_http_proxy;
 *
 * if (TIM_SUCC != TIMSetConfig(json_config.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     // 回调内部
 * }, this)) {
 *     // TIMSetConfig接口调用失败
 * }
 * @endcode
 *
 * __设置 socks5 代理示例__
 * @code{.cpp}
 * Json::Value json_socks5_value;
 * json_socks5_value[kTIMSocks5ProxyInfoIp] = "111.222.333.444";
 * json_socks5_value[kTIMSocks5ProxyInfoPort] = 8888;
 * json_socks5_value[kTIMSocks5ProxyInfoUserName] = "";
 * json_socks5_value[kTIMSocks5ProxyInfoPassword] = "";
 * Json::Value json_config;
 * json_config[kTIMSetConfigSocks5ProxyInfo] = json_socks5_value;
 *
 * if (TIM_SUCC != TIMSetConfig(json_config.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     // 回调内部
 * }, this)) {
 *     //TIMSetConfig接口调用失败
 * }
 * @endcode
 *
 * __设置 pac 代理示例__
 * @code{.cpp}
 * Json::Value json_pac_value;
 * json_pac_value[kTIMPACProxyInfoUserName] = "";
 * json_pac_value[kTIMPACProxyInfoPassword] = "";
 * Json::Value json_config;
 * json_config[kTIMSetConfigPACProxyInfo] = json_pac_value;
 *
 * if (TIM_SUCC != TIMSetConfig(json_config.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     // 回调内部
 * }, this)) {
 *     //TIMSetConfig接口调用失败
 * }
 * @endcode
 */
TIM_API int TIMSetConfig(const char* json_config, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                             五. 登录/登出相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 5.1 登录
 *
 * @param user_id 用户的 UserID
 * @param user_sig 用户的 UserSig
 * @param cb 登录成功与否的回调。票据过期会返回 ERR_USER_SIG_EXPIRED（6206）或者 ERR_SVR_ACCOUNT_USERSIG_EXPIRED（70001） 错误码，此时请您生成新的 userSig 重新登录。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 用户登录腾讯后台服务器后才能正常收发消息，登录需要用户提供 UserID、UserSig 等信息，具体含义请参考 [登录鉴权](https://cloud.tencent.com/document/product/269/31999)
 */
TIM_API int TIMLogin(const char* user_id, const char* user_sig, TIMCommCallback cb, const void* user_data);

/**
 * 5.2 登出
 *
 * @param cb 登出成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 如用户主动登出或需要进行用户的切换，则需要调用登出操作
 */
TIM_API int TIMLogout(TIMCommCallback cb, const void* user_data);

/**
 * 5.3 获取登陆用户的 userID
 *
 * @param user_id_buffer 用户 ID ，出参，分配内存大小不能低于 128 字节，调用接口后，可以读取到以 '\0' 结尾的字符串
 * @return int 返回TIM_SUCC表示接口调用成功，其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * const size_t kUserIDLength = 128;
 * char user_id_buffer[kUserIDLength] = {0};
 * TIMGetLoginUserID(user_id_buffer);
 * @endcode
 */
TIM_API int TIMGetLoginUserID(char* user_id_buffer);

/**
 * 5.4 获取登录状态
 *
 * @return TIMLoginStatus 每个返回值的定义请参考 @ref TIMLoginStatus
 *
 * @note
 * 如果用户已经处于已登录和登录中状态，请勿再频繁调用登录接口登录
 */
TIM_API TIMLoginStatus TIMGetLoginStatus();


/////////////////////////////////////////////////////////////////////////////////
//
//                          六. 用户资料管理相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 6.1 获取指定用户列表的个人资料
 *
 * @param json_get_user_profile_list_param 获取指定用户列表的用户资料接口参数的 Json 字符串, Json Key 请参考 @ref FriendShipGetProfileListParam
 * @param cb 获取指定用户列表的用户资料成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 * 可以通过该接口获取任何人的个人资料，包括自己的个人资料。
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_get_user_profile_list_param;
 * json_get_user_profile_list_param[kTIMFriendShipGetProfileListParamIdentifierArray].append("user1");
 * json_get_user_profile_list_param[kTIMFriendShipGetProfileListParamIdentifierArray].append("user2");
 *
 * int ret = TIMProfileGetUserProfileList(json_get_user_profile_list_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 获取资料列表失败
 *         return;
 *     }
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMProfileGetUserProfileList(const char* json_get_user_profile_list_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.2 修改自己的个人资料
 *
 * @param json_modify_self_user_profile_param 修改自己的资料接口参数的 Json 字符串, Json Key 请参考 @ref UserProfileItem
 * @param cb 修改自己的资料成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 修改自己的资料时，目前支持修改的字段请参考 @ref UserProfileItem, 一次可更新多个字段。修改自定义字段时填入的key值可以添加 Tag_Profile_Custom_ 前缀，也可以不添加 Tag_Profile_Custom_ 前缀，当不添加时，SDK内部会自动添加该前缀。
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value modify_item;
 * modify_item[kTIMUserProfileItemNickName] = "change my nick name"; // 修改昵称
 * modify_item[kTIMUserProfileItemGender] = kTIMGenderType_Female;  // 修改性别
 * modify_item[kTIMUserProfileItemAddPermission] = kTIMProfileAddPermission_NeedConfirm;  // 修改添加好友权限
 *
 * Json::Value json_user_profile_item_custom;
 * json_user_profile_item_custom[kTIMUserProfileCustomStringInfoKey] = "Str";  // 修改个人资料自定义字段 "Str" 的值
 * json_user_profile_item_custom[kTIMUserProfileCustomStringInfoValue] = "my define data";
 * modify_item[kTIMUserProfileItemCustomStringArray].append(json_user_profile_item_custom);
 * int ret = TIMProfileModifySelfUserProfile(modify_item.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 修改自己的个人资料失败
 *         return;
 *     }
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMProfileModifySelfUserProfile(const char* json_modify_self_user_profile_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.3 订阅用户资料（7.4 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_user_id_list 待订阅的用户 ID 列表
 * @param cb 订阅用户资料成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 *  - 该接口用于订阅陌生人的资料变更事件，订阅成功后，当订阅用户资料发生变更，您可以通过监听 @ref TIMSetUserInfoChangedCallback 回调来感知
 *  - 订阅列表最多允许订阅 200 个，超过限制后，会自动淘汰最先订阅的用户
 *  - 自己的资料变更通知不需要订阅，默认会通过  @ref TIMSetSelfInfoUpdatedCallback 回调通知给您
 *  - 好友的资料变更通知不需要订阅，默认会通过  @ref TIMSetUpdateFriendProfileCallback 回调来通知给您
 * 
 * __示例__
 * @code{.cpp}
 * json::Array json_user_id_list;
 * json_user_id_list.push_back("user1");
 * json_user_id_list.push_back("user2");
 * TIMSubscribeUserInfo(json::Serialize(json_user_id_list).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     Printf("TIMSubscribeUserInfo code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMSubscribeUserInfo(const char *json_user_id_list, TIMCommCallback cb, const void* user_data);

/**
 * 6.4 取消订阅用户资料（7.4 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_user_id_list 待取消订阅的用户 ID 列表
 * @param cb 订阅用户资料成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note 请注意：
 * - 当 json_user_id_list 为空 或 nullptr 时，取消当前所有的订阅
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_user_id_list;
 * json_user_id_list.push_back("user1");
 * json_user_id_list.push_back("user2");
 * TIMUnsubscribeUserInfo(json::Serialize(json_user_id_list).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     Printf("TIMUnsubscribeUserInfo code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMUnsubscribeUserInfo(const char *json_user_id_list, TIMCommCallback cb, const void* user_data);

/**
 * 6.5 查询用户状态（6.3 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_identifier_array 用户 ID 列表
 * @param cb 查询用户状态成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 * - 如果您想查询自己的自定义状态，您只需要传入自己的 userID 即可
 * 
 * __示例__
 * @code{.cpp}
 * json::Array json_array;
 * json_array.push_back("user1");
 * json_array.push_back("user2");
 * TIMGetUserStatus(json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     Printf("TIMGetUserStatus code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMGetUserStatus(const char *json_identifier_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.6 设置自己的状态，从 6.3 版本开始支持
 *
 * @param json_current_user_status 待设置的自定义状态，Json Key 请参考 @ref TIMUserStatus
 * @param cb 设置自己的状态成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 * 该接口只支持设置自己的自定义状态，即 kTIMUserStatusCustomStatus 字段，请参考 @ref TIMUserStatus
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_current_user_status;
 * json_current_user_status[kTIMUserStatusCustomStatus] = "custom status";
 * TIMSetSelfStatus(json::Serialize(json_current_user_status).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     Printf("TIMSetSelfStatus code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMSetSelfStatus(const char *json_current_user_status, TIMCommCallback cb, const void* user_data);

/**
 * 6.7 订阅用户状态（6.3 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_identifier_array 待订阅的用户 ID 列表
 * @param cb 订阅用户状态成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 * - 当成功订阅用户状态后，当对方的状态（包含在线状态、自定义状态）发生变更后，您可以监听 @ref TIMSetUserStatusChangedCallback 回调来感知
 * - 如果您需要订阅好友列表的状态，您只需要在控制台上打开开关即可，无需调用该接口
 * - 该接口不支持订阅自己，您可以通过监听 @ref TIMSetUserStatusChangedCallback 回调来感知自身的自定义状态的变更
 * - 订阅列表最多允许订阅 200 个，超过限制后，会自动淘汰最先订阅的用户
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_array;
 * json_array.push_back("user1");
 * json_array.push_back("user2");
 * TIMSubscribeUserStatus(json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     Printf("TIMSubscribeUserStatus code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMSubscribeUserStatus(const char *json_identifier_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.8 取消订阅用户状态，从 6.3 版本开始支持
 *
 * @param json_identifier_array 待取消订阅的用户 ID 列表
 * @param cb 订阅用户状态成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 * - 当 json_identifier_array 为空或 nullptr 时，取消当前所有的订阅
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_array;
 * json_array.push_back("user1");
 * json_array.push_back("user2");
 * TIMUnsubscribeUserStatus(json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     Printf("TIMUnsubscribeUserStatus code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMUnsubscribeUserStatus(const char *json_identifier_array, TIMCommCallback cb, const void* user_data);

// 6.9 更多功能，详见 TIMFriendshipManager.h


/////////////////////////////////////////////////////////////////////////////////
//
//                     七. SDK 基础 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 7.1 SdKConfig(初始化ImSDK的配置)
// string, 只写(选填), 配置文件路径,默认路径为"/"
static const char* kTIMSdkConfigConfigFilePath = "sdk_config_config_file_path";
// string, 只写(选填), 日志文件路径,默认路径为"/"
static const char* kTIMSdkConfigLogFilePath = "sdk_config_log_file_path";

//------------------------------------------------------------------------------
// 7.2 UserConfig(用户配置信息)
// bool, 只写(选填), 是否禁用本地数据库，true表示禁用，false表示不禁用。默认是false
static const char* kTIMUserConfigIsDisableStorage = "user_config_is_is_disable_storage";

//------------------------------------------------------------------------------
// 7.3 HttpProxyInfo (HTTP 代理配置信息)
// string, 只写(必填), 代理的IP
static const char* kTIMHttpProxyInfoIp = "http_proxy_info_ip";
// int, 只写(必填), 代理的端口
static const char* kTIMHttpProxyInfoPort = "http_proxy_info_port";
// string, 只写(选填), 认证的用户名
static const char* kTIMHttpProxyInfoUserName = "http_proxy_info_username";
// string, 只写(选填), 认证的密码
static const char* kTIMHttpProxyInfoPassword = "http_proxy_info_password";

//------------------------------------------------------------------------------
// 7.4 Socks5ProxyInfo (SOCKS5 代理配置信息)
// string, 只写(必填), socks5代理的IP
static const char* kTIMSocks5ProxyInfoIp = "socks5_proxy_info_ip";
// int, 只写(必填), socks5代理的端口
static const char* kTIMSocks5ProxyInfoPort = "socks5_proxy_info_port";
// string, 只写(选填), 认证的用户名
static const char* kTIMSocks5ProxyInfoUserName = "socks5_proxy_info_username";
// string, 只写(选填), 认证的密码
static const char* kTIMSocks5ProxyInfoPassword = "socks5_proxy_info_password";

//------------------------------------------------------------------------------
// 7.5 PACProxyInfo (PAC 代理配置信息)
// string, 只写(选填), 认证的用户名
static const char* kTIMPACProxyInfoUserName = "pac_proxy_info_username";
// string, 只写(选填), 认证的密码
static const char* kTIMPACProxyInfoPassword = "pac_proxy_info_password";

//------------------------------------------------------------------------------
// 7.6 SetConfig (更新配置)
// uint @ref TIMLogLevel, 只写(选填), 输出到日志文件的日志级别
static const char* kTIMSetConfigLogLevel = "set_config_log_level";
// uint @ref TIMLogLevel, 只写(选填), 日志回调的日志级别
static const char* kTIMSetConfigCallbackLogLevel = "set_config_callback_log_level";
// bool, 只写(选填), 是否输出到控制台，默认为 true
static const char* kTIMSetConfigIsLogOutputConsole = "set_config_is_log_output_console";
// object @ref UserConfig, 只写(选填), 用户配置
static const char* kTIMSetConfigUserConfig = "set_config_user_config";
// string, 只写(选填), 自定义数据，如果需要，初始化前设置
// @note
//  - 开发者可以自定义的数据(长度限制为64个字节)，ImSDK只负责透传给即时通信IM后台后，可以通过第三方回调 [状态变更回调](https://cloud.tencent.com/document/product/269/2570)告知开发者业务后台。
static const char* kTIMSetConfigUserDefineData = "set_config_user_define_data";
// object @ref HttpProxyInfo, 只写(选填), 设置HTTP代理，如果需要，在发送图片、文件、语音、视频前设置
// @note
//  - HTTP代理主要用在发送图片、语音、文件、微视频等消息时，将相关文件上传到COS，以及接收到图片、语音、文件、微视频等消息，将相关文件下载到本地时用到
//  - 设置时，设置的IP不能为空，端口不能为0(0端口不可用).如果需要取消HTTP代理，只需将代理的IP设置为空字符串，端口设置为0
static const char* kTIMSetConfigHttpProxyInfo = "set_config_http_proxy_info";
// object @ref Socks5ProxyInfo, 只写(选填), 设置SOCKS5代理，如果需要，初始化前设置
// @note
//  - SOCKS5代理需要在初始化之前设置。设置之后ImSDK发送的所有协议会通过SOCKS5代理服务器发送的即时通信IM后台
static const char* kTIMSetConfigSocks5ProxyInfo = "set_config_socks5_proxy_info";
// object @ref PACProxyInfo, 只写(选填), 设置PAC代理，如果需要，初始化前设置
static const char* kTIMSetConfigPACProxyInfo = "set_config_pac_proxy_info";
// bool, 只写(选填), 如果为true，SDK内部会在选择最优IP时只使用LocalDNS
static const char* kTIMSetConfigIsOnlyLocalDNSSource = "set_config_is_only_local_dns_source";


/////////////////////////////////////////////////////////////////////////////////
//
//                      八. 用户资料 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 8.1 FriendShipGetProfileListParam (获取指定用户列表的个人资料的参数)
// array string, 只写, 想要获取目标用户资料的UserID列表
static const char* kTIMFriendShipGetProfileListParamIdentifierArray = "friendship_getprofilelist_param_identifier_array";

//------------------------------------------------------------------------------
// 8.2 TIMUserStatus (用户状态)
// string, 只读, 用户 ID
static const char* kTIMUserStatusIdentifier = "user_status_identifier";
// uint @ref TIMUserStatusType, 只读, 用户的状态
static const char* kTIMUserStatusStatusType = "user_status_status_type";
// string, 读写, 用户的自定义状态
static const char* kTIMUserStatusCustomStatus = "user_status_custom_status";
// array, 只读， 用户在线终端
static const char* KTIMUserStatusOnlineDevices      = "user_status_online_devices";

//------------------------------------------------------------------------------
// 8.3 UserProfile (用户个人资料)
// string, 只读, 用户ID
static const char* kTIMUserProfileIdentifier = "user_profile_identifier";
// string, 只读, 用户的昵称
static const char* kTIMUserProfileNickName = "user_profile_nick_name";
// uint @ref TIMGenderType, 只读, 性别
static const char* kTIMUserProfileGender = "user_profile_gender";
// string, 只读, 用户头像URL
static const char* kTIMUserProfileFaceUrl = "user_profile_face_url";
// string, 只读, 用户好友备注(请注意，本字段仅在消息的发送者资料中提供)
static const char* kTIMUserProfileFriendRemark = "user_profile_friend_remark";
// string, 只读, 用户个人签名
static const char* kTIMUserProfileSelfSignature = "user_profile_self_signature";
// uint @ref TIMProfileAddPermission, 只读, 用户加好友的选项
static const char* kTIMUserProfileAddPermission = "user_profile_add_permission";
// string, 只读, 用户位置信息
static const char* kTIMUserProfileLocation = "user_profile_location";
// uint, 只读, 语言
static const char* kTIMUserProfileLanguage = "user_profile_language";
// uint, 只读, 生日
static const char* kTIMUserProfileBirthDay = "user_profile_birthday";
// uint, 只读, 等级
static const char* kTIMUserProfileLevel = "user_profile_level";
// uint, 只读, 角色
static const char* kTIMUserProfileRole = "user_profile_role";
// array @ref UserProfileCustomStringInfo, 只读, 请参考 [自定义资料字段](https://cloud.tencent.com/document/product/269/1500#.E8.87.AA.E5.AE.9A.E4.B9.89.E8.B5.84.E6.96.99.E5.AD.97.E6.AE.B5)
static const char* kTIMUserProfileCustomStringArray = "user_profile_custom_string_array";

//------------------------------------------------------------------------------
// 8.4 UserProfileItem (用户自身资料可修改的各个项)
// string, 只写, 修改用户昵称
static const char* kTIMUserProfileItemNickName = "user_profile_item_nick_name";
// uint @ref TIMGenderType, 只写, 修改用户性别
static const char* kTIMUserProfileItemGender = "user_profile_item_gender";
// string, 只写, 修改用户头像
static const char* kTIMUserProfileItemFaceUrl = "user_profile_item_face_url";
// string, 只写, 修改用户签名
static const char* kTIMUserProfileItemSelfSignature = "user_profile_item_self_signature";
// uint @ref TIMProfileAddPermission, 只写, 修改用户加好友的选项
static const char* kTIMUserProfileItemAddPermission = "user_profile_item_add_permission";
// string, 只写, 修改位置
static const char* kTIMUserProfileItemLocation = "user_profile_item_location";
// uint, 只写, 修改语言
static const char* kTIMUserProfileItemLanguage = "user_profile_item_language";
// uint, 只写, 修改生日
static const char* kTIMUserProfileItemBirthDay = "user_profile_item_birthday";
// uint, 只写, 修改等级
static const char* kTIMUserProfileItemLevel = "user_profile_item_level";
// uint, 只写, 修改角色
static const char* kTIMUserProfileItemRole = "user_profile_item_role";
// array @ref UserProfileCustomStringInfo, 只写, 修改 [自定义资料字段](https://cloud.tencent.com/document/product/269/1500#.E8.87.AA.E5.AE.9A.E4.B9.89.E8.B5.84.E6.96.99.E5.AD.97.E6.AE.B5)
static const char* kTIMUserProfileItemCustomStringArray = "user_profile_item_custom_string_array";

//------------------------------------------------------------------------------
// 8.5 UserProfileCustomStringInfo (用户自定义资料字段，字符串)
// string, 只写, 用户自定义资料字段的key值（包含前缀 Tag_Profile_Custom_）
static const char* kTIMUserProfileCustomStringInfoKey = "user_profile_custom_string_info_key";
// string, 只写, 该字段对应的字符串值, 字符串长度不得超过500字节
static const char* kTIMUserProfileCustomStringInfoValue = "user_profile_custom_string_info_value";

//------------------------------------------------------------------------------
// 8.6 ProfileChangeElem (资料变更通知)
// uint @ref TIMProfileChangeType, 只读, 资料变更类型
static const char* kTIMProfileChangeElemChangeType = "profile_change_elem_change_type";
// string, 只读, 资料变更用户的UserID
static const char* kTIMProfileChangeElemFromIdentifier = "profile_change_elem_from_identifier";
// object @ref UserProfileItem, 只读, 具体的变更信息，只有当 kTIMProfileChangeElemChangeType 为 kTIMProfileChange_Profile 时有效
static const char* kTIMProfileChangeElemUserProfileItem = "profile_change_elem_user_profile_item";


/////////////////////////////////////////////////////////////////////////////////
//
//                              九. 废弃字段
//
/////////////////////////////////////////////////////////////////////////////////
// 9.1 群组信息标识
enum TIMGroupGetInfoFlag {
    // 未定义
    kTIMGroupInfoFlag_None = 0x00,
    // 群组名称
    kTIMGroupInfoFlag_Name = 0x01,
    // 群组创建时间
    kTIMGroupInfoFlag_CreateTime = 0x01 << 1,
    // 群组创建者账号
    kTIMGroupInfoFlag_OwnerUin = 0x01 << 2,
    // 消息的 seq
    kTIMGroupInfoFlag_Seq = 0x01 << 3,
    // 群组信息最后修改时间
    kTIMGroupInfoFlag_LastTime = 0x01 << 4,
    // 下一条消息的 seq
    kTIMGroupInfoFlag_NextMsgSeq = 0x01 << 5,
    // 最新群组消息时间
    kTIMGroupInfoFlag_LastMsgTime = 0X01 << 6,
    // SdkAppID
    kTIMGroupInfoFlag_AppId = 0x01 << 7,
    // 群组成员数量
    kTIMGroupInfoFlag_MemberNum = 0x01 << 8,
    // 群组成员最大数量
    kTIMGroupInfoFlag_MaxMemberNum = 0x01 << 9,
    // 群公告内容
    kTIMGroupInfoFlag_Notification = 0x01 << 10,
    // 群简介内容
    kTIMGroupInfoFlag_Introduction = 0x01 << 11,
    // 群头像URL
    kTIMGroupInfoFlag_FaceUrl = 0x01 << 12,
    // 加群选项
    kTIMGroupInfoFlag_AddOption = 0x01 << 13,
    // 群类型
    kTIMGroupInfoFlag_GroupType = 0x01 << 14,
    // 群组内最新一条消息
    kTIMGroupInfoFlag_LastMsg = 0x01 << 15,
    // 群组在线成员数
    kTIMGroupInfoFlag_OnlineNum = 0x01 << 16,
    // 群组是否可见
    kTIMGroupInfoFlag_Visible = 0x01 << 17,
    // 群组是否可以搜索
    kTIMGroupInfoFlag_Searchable = 0x01 << 18,
    // 群组是否全禁言
    kTIMGroupInfoFlag_ShutupAll = 0x01 << 19,
};

// 9.2 群组成员信息标识
enum TIMGroupMemberInfoFlag {
    // 无
    kTIMGroupMemberInfoFlag_None = 0x00,
    // 加入时间
    kTIMGroupMemberInfoFlag_JoinTime = 0x01,
    // 群消息接收选项
    kTIMGroupMemberInfoFlag_MsgFlag = 0x01 << 1,
    // 成员已读消息seq
    kTIMGroupMemberInfoFlag_MsgSeq = 0x01 << 2,
    // 成员角色
    kTIMGroupMemberInfoFlag_MemberRole = 0x01 << 3,
    // 禁言时间。当该值为0时表示没有被禁言
    kTIMGroupMemberInfoFlag_ShutupUntill = 0x01 << 4,
    // 群名片
    kTIMGroupMemberInfoFlag_NameCard = 0x01 << 5,
};

// 9.3 群组成员角色标识
enum TIMGroupMemberRoleFlag {
    // 获取全部角色类型
    kTIMGroupMemberRoleFlag_All = 0x00,
    // 获取所有者(群主)
    kTIMGroupMemberRoleFlag_Owner = 0x01,
    // 获取管理员，不包括群主
    kTIMGroupMemberRoleFlag_Admin = 0x01 << 1,
    // 获取普通群成员，不包括群主和管理员
    kTIMGroupMemberRoleFlag_Member = 0x01 << 2,
};

//------------------------------------------------------------------------------
// 9.4 GroupGetInfoOption(获取群组信息的选项)
// uint64 @ref TIMGroupGetInfoFlag, 读写(选填), 根据想要获取的信息过滤，默认值为0xffffffff(获取全部信息)
static const char* kTIMGroupGetInfoOptionInfoFlag = "group_get_info_option_info_flag";
// array string, 只写(选填), 想要获取的群组自定义字段列表，请参考 [群组自定义字段](https://cloud.tencent.com/document/product/269/1502#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.AD.97.E6.AE.B5)
static const char* kTIMGroupGetInfoOptionCustomArray = "group_get_info_option_custom_array";

//------------------------------------------------------------------------------
// 9.5 GroupMemberGetInfoOption(获取群组成员信息的选项)
// uint64 @ref TIMGroupMemberInfoFlag, 读写(选填), 根据想要获取的信息过滤，默认值为0xffffffff(获取全部信息)
static const char* kTIMGroupMemberGetInfoOptionInfoFlag = "group_member_get_info_option_info_flag";
// uint64 @ref TIMGroupMemberRoleFlag, 读写(选填), 根据成员角色过滤，默认值为kTIMGroupMemberRoleFlag_All，获取所有角色
static const char* kTIMGroupMemberGetInfoOptionRoleFlag = "group_member_get_info_option_role_flag";
// array string, 只写(选填), 请参考 [自定义字段](https://cloud.tencent.com/document/product/269/1502#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.AD.97.E6.AE.B5)
static const char* kTIMGroupMemberGetInfoOptionCustomArray = "group_member_get_info_option_custom_array";

//------------------------------------------------------------------------------
// 9.6 SdKConfig(初始化ImSDK的配置, 已废弃的部分)
// uint64, 只写(选填), 配置Android平台的Java虚拟机指针
static const char* kTIMSdkConfigJavaVM = "sdk_config_java_vm";

//------------------------------------------------------------------------------
// 9.7 UserConfig(用户配置信息，已废弃的部分)
// bool, 只写(选填), true表示要收已读回执事件
static const char* kTIMUserConfigIsReadReceipt = "user_config_is_read_receipt";
// bool, 只写(选填), true表示群tips不计入群消息已读计数
static const char* kTIMUserConfigIsIgnoreGroupTipsUnRead = "user_config_is_ignore_grouptips_unread";
// bool, 只写(选填), true表示服务端要删掉已读状态
static const char* kTIMUserConfigIsSyncReport = "user_config_is_sync_report";
// object @ref GroupGetInfoOption, 只写(选填),获取群组信息默认选项
static const char* kTIMUserConfigGroupGetInfoOption = "user_config_group_getinfo_option";
// object @ref GroupMemberGetInfoOption, 只写(选填),获取群组成员信息默认选项
static const char* kTIMUserConfigGroupMemberGetInfoOption = "user_config_group_member_getinfo_option";

//------------------------------------------------------------------------------
// 9.8 FriendShipGetProfileListParam (获取指定用户列表的个人资料的参数，已废弃的部分)
// bool, 只写, 是否强制更新。false表示优先从本地缓存获取，获取不到则去网络上拉取。true表示直接去网络上拉取资料。默认为false
static const char* kTIMFriendShipGetProfileListParamForceUpdate = "friendship_getprofilelist_param_force_update";

//------------------------------------------------------------------------------
// 9.9 以下为老版本拼写错误，为了兼容老版本而保留的宏定义
// enum TIMGroupGetInfoFlag
#define kTIMGroupInfoFlag_AddOpton  kTIMGroupInfoFlag_AddOption
// enum TIMGenderType
#define kTIMGenderType_Unkown  kTIMGenderType_Unknown
// UserConfig JsonKey
#define kTIMUserConfigIsIngoreGroupTipsUnRead  kTIMUserConfigIsIgnoreGroupTipsUnRead
// SetConfig JsonKey
#define kTIMSetConfigCackBackLogLevel  kTIMSetConfigCallbackLogLevel
// ProfileChangeElem JsonKey
#define kTIMProfileChangeElemFromIndentifier   kTIMProfileChangeElemFromIdentifier
// UserProfileCustomStringInfo JsonKey
#define kTIMUserProfileCustemStringInfoKey    kTIMUserProfileCustomStringInfoKey
#define kTIMUserProfileCustemStringInfoValue  kTIMUserProfileCustomStringInfoValue
// UserProfileItem JsonKey
#define kTIMUserProfileItemLoaction  kTIMUserProfileItemLocation
// GroupMemberInfo JsonKey
#define kTIMGroupMemberInfoRemark  kTIMGroupMemberInfoFriendRemark

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_MANAGER_H_
