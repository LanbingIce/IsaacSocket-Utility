// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_EXPERIMENTAL_API_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_EXPERIMENTAL_API_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 实验性 API, 用于提供一些实验性功能
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
//                         一. ImSDK 实验性通知回调
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 1.1 实验性通知的回调（7.4 及其以上版本支持）
 *
 * @param key 通知 key
 * @param data 通知数据
 */
typedef void (*TIMExperimentalNotifyCallback)(const char* key, const char* data, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                          二. 注册实验性通知回调
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 实验性通知的回调
 * @param cb 实验性通知的回调，请参考 @ref TIMExperimentalNotifyCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetExperimentalNotifyCallback(TIMExperimentalNotifyCallback cb, const void *user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                             三. 实验性 API 
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 实验性 API
 *
 * @note 该接口提供一些实验性功能
 */
TIM_API int callExperimentalAPI(const char* json_param, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                      四. 实验性 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 4.1 TIMInternalOperation(实验性接口的操作类型)
static const char* kTIMInternalOperationSSOData = "internal_operation_sso_data";
static const char* kTIMInternalOperationUserId2TinyId = "internal_operation_userid_tinyid";
static const char* kTIMInternalOperationTinyId2UserId = "internal_operation_tinyid_userid";
static const char* kTIMInternalOperationSetEnv = "internal_operation_set_env";
static const char* kTIMInternalOperationSetIPv6Prior = "internal_operation_set_ipv6_prior";
static const char* kTIMInternalOperationSetMaxRetryCount = "internal_operation_set_max_retry_count";
static const char* kTIMInternalOperationSetPacketRequestTimeout = "internal_operation_set_packet_request_timeout";
static const char* kTIMInternalOperationSetCustomServerInfo = "internal_operation_set_custom_server_info";
static const char* kTIMInternalOperationEnableQuicChannel = "internal_operation_enable_quic_channel";
static const char* kTIMInternalOperationSetSM4GCMCallback = "internal_operation_set_sm4_gcm_callback";
static const char* kTIMInternalOperationInitLocalStorage = "internal_operation_init_local_storage";
static const char* kTIMInternalOperationSetCosSaveRegionForConversation = "internal_operation_set_cos_save_region_for_conversation";
static const char* kTIMInternalOperationSetUIPlatform = "internal_operation_set_ui_platform";
static const char* kTIMInternalOperationSetDatabaseEncryptInfo = "internal_operation_set_database_encrypt_info";
static const char* kTIMInternalOperationIsCommercialAbilityEnabled = "internal_operation_is_commercial_ability_enabled";
static const char* kTIMInternalOperationSetOfflinePushState = "internal_operation_set_offline_push_state";
static const char* kTIMInternalOperationGetOfflinePushState = "internal_operation_get_offline_push_state";
static const char* kTIMInternalOperationGetMessageRevoker = "internal_operation_get_message_revoker";
static const char* kTIMInternalOperationWriteLog = "internal_operation_write_log";
static const char* kTIMInternalOperationClearLocalHistoryMessage = "internal_operation_clear_local_history_message";
static const char* kTIMInternalOperationUpdateProxyInfo = "internal_operation_update_proxy_info";
static const char* kTIMInternalOperationReportTUIComponentUsage = "internal_operation_report_tuicomponent_usage";
static const char* kTIMInternalOperationSendTRTCCustomData = "internal_operation_send_trtc_custom_data";
static const char* kTIMInternalOperationSendRoomCustomData = "internal_operation_send_room_custom_data";
static const char* kTIMInternalOperationSetApplicationID = "internal_operation_set_application_id";
static const char* kTIMInternalOperationGetServerConfig = "internal_operation_get_server_config";
static const char* kTIMInternalOperationSetIgnoreRepeatLogin = "internal_operation_set_ignore_repeat_login";

//------------------------------------------------------------------------------
// 4.2 SSODataParam(发送 sso data 的参数)
// string, 只写(必填), sso请求的命令字
static const char* kTIMSSODataParamCmd = "sso_data_param_cmd";
// string, 只写(必填), sso请求的内容，内容是二进制，需要外部传入base64编码后的字符串，sdk内部回解码成原二进制
static const char* kTIMSSODataParamBody = "sso_data_param_body";
// uint64, 只写(选填), sso请求的超时时间，默认是15秒
static const char* kTIMSSODataParamTimeout = "sso_data_param_timeout";

//------------------------------------------------------------------------------
// 4.3 SSODataRes(发送 sso data 的返回信息)
// string, 只读(必填), sso返回数据对应请求的命令字
static const char* kTIMSSODataResCmd = "sso_data_res_cmd";
// string, 只读(必填), sso返回的内容，内容是二进制，sdk内部使用base64编码了，外部使用前需要base64解码
static const char* kTIMSSODataResBody = "sso_data_res_body";

//------------------------------------------------------------------------------
// 4.4 UserInfo(用户账号信息)
static const char* kTIMUserInfoUserId = "user_info_userid";
static const char* kTIMUserInfoTinyId = "user_info_tinyid";

//------------------------------------------------------------------------------
// 4.5 ServerAddress(服务器地址)
// string, 只写(必填), 服务器 IP
static const char* kTIMServerAddressIp = "server_address_ip";
// int, 只写(必填), 服务器端口
static const char* kTIMServerAddressPort = "server_address_port";
// bool, 只写(选填), 是否 IPv6 地址，默认为 false
static const char* kTIMServerAddressIsIPv6 = "server_address_is_ipv6";
// bool, 只写(选填), 是否 Quic 地址，默认为 false
static const char* kTIMServerAddressIsQuic = "server_address_is_quic";

//------------------------------------------------------------------------------
// 4.6 CustomServerInfo(自定义服务器信息)
// array @ref ServerAddress, 只写(必填), 长连接服务器地址列表
static const char* kTIMCustomServerInfoLongConnectionAddressArray = "longconnection_address_array";
// array @ref ServerAddress, 只写(选填), 短连接服务器地址列表
static const char* kTIMCustomServerInfoShortConnectionAddressArray = "shortconnection_address_array";
// string, 只写(必填), 服务器公钥
static const char* kTIMCustomServerInfoServerPublicKey = "server_public_key";

//------------------------------------------------------------------------------
// 4.7 QuicChannelInfo(Quic 通道信息)
// bool, 只写(必填), 是否启用 Quic 通道，true：打开，false：不打开
static const char* kTIMQuicChannelInfoEnableQuic = "quic_channel_info_enable_quic";

//------------------------------------------------------------------------------
// 4.8 SM4GCMCallbackParam(国密 SM4 GCM 回调函数地址的参数)
// uint64 只写(必填), SM4 GCM 加密回调函数地址
static const char* kTIMSM4GCMCallbackParamEncrypt = "sm4_gcm_callback_param_encrypt";
// uint64, 只写(必填), SM4 GCM 解密回调函数地址
static const char* kTIMSM4GCMCallbackParamDecrypt = "sm4_gcm_callback_param_decrypt";

//------------------------------------------------------------------------------
// 4.9 CosSaveRegionForConversationParam(设置 cos 存储区域)
// string, 只写(必填), 会话 ID
static const char* kTIMCosSaveRegionForConversationParamConversationID = "cos_save_region_for_conversation_param_conversation_id";
// string, 只写(必填), 存储区域
static const char* kTIMCosSaveRegionForConversationParamCosSaveRegion = "cos_save_region_for_conversation_param_cos_save_region";

//------------------------------------------------------------------------------
// 4.10 DatabaseEncryptInfo(数据库加密信息)
// int, 只写(必填), 数据库加密类型，0 不加密（默认），1:按位异或，2:TEA，3:国密，4:AES
static const char* kTIMDatabaseEncryptInfoEncryptType = "database_encrypt_info_encrypt_type";
// string, 只写(选填), 数据库加密类型 key ，除了 按位异或 算法，其他算法的加密 key，必须是长度是 32 base16 字符串，不填写就使用 IMSDK 内部生成的 key，由于数据库加密数据持久化到文件中，因此，一旦 key 被使用过，不能够再更换
static const char* kTIMDatabaseEncryptInfoEncryptKey = "database_encrypt_info_encrypt_key";

//------------------------------------------------------------------------------
// 4.11 CommercialAbilityResult(商业化能力项的查询结果)
// bool, 只读(必填), 查询是否支持指定的商业化能力项的结果，true：支持，false：不支持
static const char* kTIMCommercialAbilityResultEnabled = "commercial_ability_result_enabled";

//------------------------------------------------------------------------------
// 4.12 RequestParam(callExperimentalAPI 接口请求的参数)
// string @ref TIMInternalOperation, 只写(必填), 内部接口的操作类型
static const char* kTIMRequestInternalOperation = "request_internal_operation";
// object @ref SSODataParam, 只写(选填), sso发包请求, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSSOData 时需要设置
static const char* kTIMRequestSSODataParam = "request_sso_data_param";
// array string, 只写(选填), 请求需要转换成tinyid的userid列表, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationUserId2TinyId 时需要设置
static const char* kTIMRequestUserId2TinyIdParam = "request_userid_tinyid_param";
// array uint64, 只写(选填), 请求需要转换成userid的tinyid列表, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationTinyId2UserId 时需要设置
static const char* kTIMRequestTinyId2UserIdParam = "request_tinyid_userid_param";
// bool, 只写(选填), true 表示设置当前环境为测试环境，false表示设置当前环境是正式环境，默认是正式环境, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetEnv 时需要设置
static const char* kTIMRequestSetEnvParam = "request_set_env_param";
// bool, 只写(选填), 在 IPv6 双栈网络下，是否优先使用 IPv6 协议，当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetIPv6Prior 时需要设置
static const char* kTIMRequestSetIPv6PriorParam = "request_set_ipv6_prior_param";
// uint32, 只写(选填), 设置登录、发消息请求的重试次数, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetMaxRetryCount 时需要设置
static const char* kTIMRequestSetMaxRetryCountParam = "request_set_max_retry_count_param";
// int64, 只写(选填), 设置登录、发消息请求的超时时间, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetPacketRequestTimeout 时需要设置
static const char* kTIMRequestSetPacketRequestTimeoutParam = "request_set_packet_request_timeout_param";
// object @ref CustomServerInfo, 只写(选填), 自定义服务器信息, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetCustomServerInfo 时需要设置
static const char* kTIMRequestSetCustomServerInfoParam = "request_set_custom_server_info_param";
// bool, 只写(选填), true 表示设置 Quic 通道信息, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationEnableQuicChannel 时需要设置
static const char* kTIMRequestEnableQuicChannelParam = "request_enable_quic_channel_param";
// object @ref SM4GCMCallbackParam, 只写(选填), 国密 SM4 GCM 回调函数地址的参数, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetSM4GCMCallback 时需要设置
static const char* kTIMRequestSetSM4GCMCallbackParam = "request_set_sm4_gcm_callback_param";
// string, 只写(选填), 初始化 Database 的用户 ID, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationInitLocalStorage 时需要设置
static const char* kTIMRequestInitLocalStorageParam = "request_init_local_storage_user_id_param";
// object @ref CosSaveRegionForConversationParam, 只写(选填), 设置 cos 存储区域的参数, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetCosSaveRegionForConversation 时需要设置
static const char* kTIMRequestSetCosSaveRegionForConversationParam = "request_set_cos_save_region_for_conversation_param";
// uint32, 只写(选填), 设置 UI 平台，当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetUIPlatform 时需要设置
static const char* kTIMRequestSetUIPlatformParam = "request_set_ui_platform_param";
// object @ref DatabaseEncryptInfo, 只写(选填), 设置数据库加密信息, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetDatabaseEncryptInfo 时需要设置
static const char* kTIMRequestSetDatabaseEncryptInfoParam = "request_set_database_encrypt_info_param";
// uint64, 只写(选填), 商业化能力项枚举的组合值, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationIsCommercialAbilityEnabled 时需要设置
static const char* kTIMRequestIsCommercialAbilityEnabledParam = "request_is_commercial_ability_enabled_param";
// uint32, 只写(选填), 设置推送状态：0 - 不设置 1 - 开启推送 2 - 关闭推送, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetOfflinePushState 时需要设置
static const char* kTIMRequestSetOfflinePushStateParam = "request_set_offline_push_state_param";
// array string, 只写(选填), 撤回消息的 id, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationGetMessageRevoker 时需要设置
static const char* kTIMRequestMessageRevokerMessageIdArray = "request_message_revoker_message_id_array";
// int, 只写(选填), 打印日志的级别, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationWriteLog 时需要设置
static const char* kTIMRequestWriteLogLogLevelParam = "request_write_log_log_level_param";
// string, 只写(选填), 打印日志的内容, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationWriteLog 时需要设置
static const char* kTIMRequestWriteLogLogContentParam = "request_write_log_log_content_param";
// string, 只写(选填), 打印日志的文件名, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationWriteLog 时需要设置
static const char* kTIMRequestWriteLogFileNameParam = "request_write_log_file_name_param";
// string, 只写(选填), 打印日志的函数名, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationWriteLog 时需要设置
static const char* kTIMRequestWriteLogFuncNameParam = "request_write_log_func_name_param";
// int, 只写(选填), 打印日志的所在行数, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationWriteLog 时需要设置
static const char* kTIMRequestWriteLogLineNumberParam = "request_write_log_line_number_param";
// string, 只写(选填), 设置要删除消息的会话 ID, 其中单聊格式为 "c2c_userID", 群聊会话格式为 "group_groupID", 当输入为 "c2c" 或者 "group" 时会同时操作所有 单聊 或者 群聊 会话，当输入为 "" 时会同时操纵所有会话，当 kTIMRequestInternalOperation 为 kTIMInternalOperationClearLocalHistoryMessage 时需要设置
static const char* kTIMRequestClearLocalHistoryMessageConversationIDParam = "request_clear_local_history_message_conversation_id_param";
// uint64, 只写(选填), 设置要删除消息时间范围的开始时间, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationClearLocalHistoryMessage 时需要设置
static const char* kTIMRequestClearLocalHistoryMessageBeginTimestampParam = "request_clear_local_history_message_begin_timestamp_param";
// uint64, 只写(选填), 设置要删除消息时间范围的结束时间，删除消息时间范围为 [begin_time, end_time]，若结束时间设置为 0，则删除开始时间之后的所有消息，若开始和结束时间都被设置为 0，则清空指定会话的所有消息，当 kTIMRequestInternalOperation 为 kTIMInternalOperationClearLocalHistoryMessage 时需要设置
static const char* kTIMRequestClearLocalHistoryMessageEndTimestampParam = "request_clear_local_history_message_end_timestamp_param";
static const char* kTIMRequestReportTUIComponentUsageUIComponentTypeParam = "report_tuicomponent_usage_uicomponent_type_param";
static const char* kTIMRequestReportTUIComponentUsageUIStyleTypeParam = "report_tuicomponent_usage_uistyle_type_param";
// string, 只写(必填)，长连接透传发送的数据，当 kTIMRequestInternalOperation 为 kTIMInternalOperationSendTRTCCustomData 时需要设置
static const char* kTIMRequestSendTRTCCustomDataParam = "request_send_trtc_custom_data_param";
// string, 只写(必填)，长连接透传发送的数据，当 kTIMRequestInternalOperation 为 kTIMInternalOperationSendRoomCustomData 时需要设置
static const char* kTIMRequestSendRoomCustomDataServiceCommandParam = "request_send_room_custom_data_service_command_param";
// string, 只写(必填)，长连接透传发送的数据，当 kTIMRequestInternalOperation 为 kTIMInternalOperationSendRoomCustomData 时需要设置
static const char* kTIMRequestSendRoomCustomDataRequestContentParam = "request_send_room_custom_data_request_content_param";
// uint8, 只写(选填), 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetApplicationID 时需要设置
static const char* kTIMRequestSetApplicationIDParam = "request_set_application_id_param";
// string, 只写(必填), 当 kTIMRequestInternalOperation 为 kTIMInternalOperationGetServerConfig 时需要设置
static const char* kTIMRequestGetServerConfigKeyParam = "request_get_server_config_key_param";
// string, 只写(必填), 当 kTIMRequestInternalOperation 为 kTIMInternalOperationGetServerConfig 时需要设置
// 0或不填: 无效， 1:数值类型  2:字符串类型
static const char* kTIMRequestGetServerConfigValueTypeParam = "request_get_server_config_value_type_param";
// bool, 只写(选填), 设置「SDK 是否忽略重复登录请求」, 当 kTIMRequestInternalOperation 为 kTIMInternalOperationSetIgnoreRepeatLogin 时有效
static const char* kTIMRequestSetIgnoreRepeatLoginParam = "request_set_ignore_repeat_login_param";

//------------------------------------------------------------------------------
// 4.13 ResponseInfo(callExperimentalAPI 接口回调返回的数据)
// string @ref TIMInternalOperation, 只读(必填), 响应的内部操作
static const char* kTIMResponseInternalOperation = "response_internal_operation";
// object @ref SSODataRes, 只读(选填), sso发包请求的响应, 当 kTIMResponseInternalOperation 为 kTIMInternalOperationSSOData 时有值
static const char* kTIMResponseSSODataRes = "response_sso_data_res";
// array @ref UserInfo, 只读(选填), 响应的tinyid列表, 当 kTIMResponseInternalOperation 为 kTIMInternalOperationUserId2TinyId 时有值
static const char* kTIMResponseUserId2TinyIdRes = "response_userid_tinyid_res";
// array @ref UserInfo, 只读(选填), 响应的tinyid列表, 当 kTIMResponseInternalOperation 为 kTIMInternalOperationTinyId2UserId 时有值
static const char* kTIMResponseTinyId2UserIdRes = "response_tinyid_userid_res";
// bool, 只读(选填), true 表示当前环境为测试环境，false表示当前环境是正式环境, 当 kTIMResponseInternalOperation 为 kTIMInternalOperationSetEnv 时有值
static const char* kTIMResponseSetEvnRes = "response_set_env_res";
// uint32, 只读(选填), 推送状态：0 - 不设置 1 - 开启推送 2 - 关闭推送, 当 kTIMResponseInternalOperation 为 kTIMInternalOperationGetOfflinePushState 时有值
static const char* kTIMResponseGetOfflinePushStateRes = "response_get_offline_push_state_res";
// string, 只读(选填), 撤回消息的 id, 当 kTIMResponseInternalOperation 为 kTIMInternalOperationGetMessageRevoker 时有值
static const char* kTIMResponseMessageId = "response_message_id";
// string, 只读(选填), 撤回消息的操作者, 当 kTIMResponseInternalOperation 为 kTIMInternalOperationGetMessageRevoker 时有值
static const char* kTIMResponseMessageRevoker = "response_message_revoker";

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_EXPERIMENTAL_API_H_
