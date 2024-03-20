// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_SIGNALING_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_SIGNALING_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 信令接口，包含通话邀请相关功能
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
//                      一. 信令相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 信令响应类型
enum TIMSignalingActionType {
    // 未定义
    TIMSignalingActionType_Unknown,
    // 邀请方发起邀请
    TIMSignalingActionType_Invite,
    // 邀请方取消邀请
    TIMSignalingActionType_CancelInvite,
    // 被邀请方接受邀请
    TIMSignalingActionType_AcceptInvite,
    // 被邀请方拒绝邀请
    TIMSignalingActionType_RejectInvite,
    // 邀请超时
    TIMSignalingActionType_InviteTimeout,
};


/////////////////////////////////////////////////////////////////////////////////
//
//                           二. 信令事件回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 收到邀请的回调
 *
 * @param invite_id 邀请 ID
 * @param inviter 邀请者 userID
 * @param group_id 群组 ID
 * @param json_invitee_list 被邀请者 userID 列表，json 字符串类型
 * @param data 自定义字段
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMSignalingReceiveNewInvitationCallback)(const char* invite_id, const char* inviter, const char* group_id,
                                                         const char* json_invitee_list, const char* data, const void* user_data);

/**
 * 2.2 被邀请者接受邀请的回调
 *
 * @param invite_id 邀请 ID
 * @param invitee 被邀请者 userID
 * @param data 自定义字段
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMSignalingInviteeAcceptedCallback)(const char* invite_id, const char* invitee, const char* data, const void* user_data);

/**
 * 2.3 被邀请者拒绝邀请的回调
 *
 * @param invite_id 邀请 ID
 * @param invitee 被邀请者 userID
 * @param data 自定义字段
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMSignalingInviteeRejectedCallback)(const char* invite_id, const char* invitee, const char* data, const void* user_data);

/**
 * 2.4 邀请被取消的回调
 *
 * @param invite_id 邀请 ID
 * @param inviter 邀请者 userID
 * @param data 自定义字段
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMSignalingInvitationCancelledCallback)(const char* invite_id, const char* inviter, const char* data, const void* user_data);

/**
 * 2.5 邀请超时的回调
 *
 * @param invite_id 邀请 ID
 * @param json_invitee_list 被邀请者 userID 列表，json 字符串类型
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMSignalingInvitationTimeoutCallback)(const char* invite_id, const char* json_invitee_list, const void* user_data);

/**
 * 2.6 邀请被修改的回调（6.7 及其以上版本支持）
 *
 * @param invite_id 邀请 ID
 * @param data 自定义字段
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMSignalingInvitationModifiedCallback)(const char* invite_id, const char* data, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                           三. 注册信令事件回调 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 设置收到信令邀请的回调
 * 
 * @param cb 收到信令邀请的回调，请参考 @ref TIMSignalingReceiveNewInvitationCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetSignalingReceiveNewInvitationCallback(TIMSignalingReceiveNewInvitationCallback cb, const void *user_data);

/**
 * 3.2 设置信令邀请被接收者同意的回调
 * 
 * @param cb 同意信令邀请的回调，请参考 @ref TIMSignalingInviteeAcceptedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetSignalingInviteeAcceptedCallback(TIMSignalingInviteeAcceptedCallback cb, const void *user_data);

/**
 * 3.3 设置信令邀请被接收者拒绝的回调
 * 
 * @param cb 拒绝信令邀请的回调，请参考 @ref TIMSignalingInviteeRejectedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetSignalingInviteeRejectedCallback(TIMSignalingInviteeRejectedCallback cb, const void *user_data);

/**
 * 3.4 设置信令邀请被取消的回调
 * 
 * @param cb 信令邀请被取消的回调，请参考 @ref TIMSignalingInvitationCancelledCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetSignalingInvitationCancelledCallback(TIMSignalingInvitationCancelledCallback cb, const void *user_data);

/**
 * 3.5 设置信令邀请超时的回调
 * 
 * @param cb 信令邀请超时的回调，请参考 @ref TIMSignalingInvitationTimeoutCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetSignalingInvitationTimeoutCallback(TIMSignalingInvitationTimeoutCallback cb, const void *user_data);

/**
 * 3.6 设置信令邀请被修改的回调
 * 
 * @param cb 信令邀请被修改的回调，请参考 @ref TIMSignalingInvitationModifiedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetSignalingInvitationModifiedCallback(TIMSignalingInvitationModifiedCallback cb, const void *user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                              四. 信令 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 4.1 邀请某个人
 * 
 * @param invitee 被邀请人的 userID
 * @param data 自定义数据
 * @param online_user_only 是否只有在线用户才能收到邀请，如果设置为 true，只有在线用户才能收到，并且 invite 操作也不会产生历史消息（针对该次 invite 的后续 cancel、accept、reject、timeout 操作也同样不会产生历史消息）
 * @param json_offline_push_info 离线推送时携带的标题和声音，其中 desc 为必填字段，推送的时候会默认展示 desc 信息，Json key 的定义请参考 @ref OfflinePushConfig
 * @param timeout 超时时间，单位 s，如果设置为 0，SDK 不会做超时检测，也不触发 @ref TIMSignalingInvitationTimeoutCallback 回调
 * @param invite_id_buffer 出参，邀请 ID，分配内存大小不能低于 128 字节，如果不需要，可传入 nullptr，调用接口后，可以读取到以 '\0' 结尾的字符串
 * @param cb 回调
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *  Json::Value json_offline_push_info;
 *  json_offline_push_info[kTIMOfflinePushConfigDesc] = "push desc";
 *
 * const size_t kMessageIDLength = 128;
 * char invite_id_buffer[kMessageIDLength] = {0};
 * int ret = TIMSignalingInvite("user", "custom data", true, json_offline_push_info, 30, invite_id_buffer,
 *                      [](int32_t code, const char* desc, const char* json_params, const void* user_data){
 *                      if (ERR_SUCC == code) {
 *                           // 邀请成功
 *                      } else {
 *                           // 邀请失败
 *                       }
 *               }, nullptr);
 * @endcode
 */
TIM_API int TIMSignalingInvite(const char* invitee, const char* data, bool online_user_only, const char* json_offline_push_info, int timeout, char* invite_id_buffer, TIMCommCallback cb, const void* user_data);

/**
 * 4.2 邀请群内的某些人
 * 
 * @param group_id 发起邀请所在群组
 * @param json_invitee_array 被邀请人列表，且被邀请人必须已经在群组内，否则邀请无效
 * @param data 自定义字段
 * @param online_user_only  是否只有在线用户才能收到邀请，如果设置为 true，只有在线用户才能收到，并且 invite 操作也不会产生历史消息（针对该次 invite 的后续 cancel、accept、reject、timeout 操作也同样不会产生历史消息）
 * @param timeout 超时时间，单位 s，如果设置为 0，SDK 不会做超时检测，也不触发 @ref TIMSignalingInvitationTimeoutCallback 回调
 * @param invite_id_buffer 出参，邀请ID，分配内存大小不能低于 128 字节，如果不需要，可传入 nullptr，调用接口后，可以读取到以 '\0' 结尾的字符串
 * @param cb 回调
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_invitee_array(Json::arrayValue);
 * json_invitee_array.append("user1");
 * json_invitee_array.append("user2");
 *
 * const size_t kMessageIDLength = 128;
 * char invite_id_buffer[kMessageIDLength] = {0};
 * int ret = TIMSignalingInviteInGroup("group_id", json_invitee_array, "custom data", true, 30, invite_id_buffer,
 *                      [](int32_t code, const char* desc, const char* json_params, const void* user_data){
 *                      if (ERR_SUCC == code) {
 *                           // 邀请成功
 *                      } else {
 *                           // 邀请失败
 *                       }
 *               }, nullptr);
 * @endcode
 */
TIM_API int TIMSignalingInviteInGroup(const char* group_id, const char* json_invitee_array, const char* data, bool online_user_only, int timeout, char* invite_id_buffer, TIMCommCallback cb, const void* user_data);

/**
 * 4.3 邀请方取消邀请
 * 
 * @param invite_id 邀请 ID
 * @param data 自定义字段
 * @param cb 回调
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 如果所有被邀请人都已经处理了当前邀请（包含超时），不能再取消当前邀请。
 *
 * __示例__
 * @code{.cpp}
 * const char *invite_id = "XXX-XXX-XXX-XXX";
 * int ret = TIMSignalingCancel(invite_id, "",
 *                      [](int32_t code, const char* desc, const char* json_params, const void* user_data){
 *                      if (ERR_SUCC == code) {
 *                           // 取消成功
 *                      } else {
 *                           // 取消失败
 *                       }
 *               }, nullptr);
 * @endcode
 */
TIM_API int TIMSignalingCancel(const char* invite_id, const char* data, TIMCommCallback cb, const void* user_data);

/**
 * 4.4 邀请方接受邀请
 * 
 * @param invite_id 邀请 ID
 * @param data 自定义字段
 * @param cb 回调
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 不能接受不是针对自己的邀请，请在收到 @ref TIMSignalingReceiveNewInvitation 回调的时候先判断 json_invitee_array 有没有自己，如果没有自己，不能 accept 邀请。
 *
 * __示例__
 * @code{.cpp}
 * const char *invite_id = "XXX-XXX-XXX-XXX";
 * int ret = TIMSignalingAccept(invite_id, "",
 *                      [](int32_t code, const char* desc, const char* json_params, const void* user_data){
 *                      if (ERR_SUCC == code) {
 *                           // 接受邀请成功
 *                      } else {
 *                           // 接受邀请失败
 *                       }
 *               }, nullptr);
 * @endcode
 */
TIM_API int TIMSignalingAccept(const char* invite_id, const char* data, TIMCommCallback cb, const void* user_data);

/**
 * 4.5 邀请方拒绝邀请
 * 
 * @param invite_id 邀请 ID
 * @param data 自定义字段
 * @param cb 回调
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 不能拒绝不是针对自己的邀请，请在收到 @ref TIMSignalingReceiveNewInvitation 回调的时候先判断 json_invitee_array 有没有自己，如果没有自己，不能 reject 邀请。
 *
 * __示例__
 * @code{.cpp}
 * const char *invite_id = "XXX-XXX-XXX-XXX";
 * int ret = TIMSignalingReject(invite_id, "",
 *                      [](int32_t code, const char* desc, const char* json_params, const void* user_data){
 *                      if (ERR_SUCC == code) {
 *                           // 拒绝邀请成功
 *                      } else {
 *                           // 拒绝邀请失败
 *                       }
 *               }, nullptr);
 * @endcode
 */
TIM_API int TIMSignalingReject(const char* invite_id, const char* data, TIMCommCallback cb, const void* user_data);

/**
 * 4.6 获取信令信息
 *
 * @param json_msg 消息 json 字符串
 * @param json_signaling_info_cb 获取信令消息的回调，您可以在该回调中根据 code == ERR_SUCC 来确定当前 json_msg 为信令消息
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 
 *  如果 invite 设置 online_user_only 为 false，每次信令操作（包括 invite、cancel、accept、reject、timeout）都会产生一条自定义消息，该消息会通过 @ref TIMRecvNewMsgCallback 抛给用户，用户也可以通过历史消息拉取，如果需要根据信令信息做自定义化文本展示，可以调用下面接口获取信令信息。
 * 
 * __示例__
 * @code{.cpp}
 * const char *json_msg = "";
 * int ret = TIMGetSignalingInfo(json_msg,
 *                      [](int32_t code, const char* desc, const char* json_params, const void* user_data){
 *                      if (ERR_SUCC == code) {
 *                           // 当前消息是信令消息
 *                      } else {
 *                           // 当前消息为普通消息
 *                       }
 *               }, nullptr);
 * @endcode
 */
TIM_API int TIMGetSignalingInfo(const char *json_msg, TIMCommCallback json_signaling_info_cb, const void* user_data);

/**
 * 4.7 修改邀请信令（6.7 及其以上版本支持）
 *
 * @note 仅支持修改邀请信令的自定义字段 data。只有在线用户才能收到的邀请信令不能被修改。
 *
 * __示例__
 * @code{.cpp}
 * const char *invite_id = "XXX-XXX-XXX-XXX";
 * int ret = TIMSignalingModifyInvitation(invite_id, "",
 *                      [](int32_t code, const char* desc, const char* json_params, const void* user_data){
 *                      if (ERR_SUCC == code) {
 *                           // 修改邀请成功
 *                      } else {
 *                           // 修改邀请失败
 *                       }
 *               }, nullptr);
 * @endcode
 */
TIM_API int TIMSignalingModifyInvitation(const char* invite_id, const char* data, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                        五. 信令 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 5.1 SignalingInfo(信令基础信息定义)
// string, 只读, 邀请 ID
static const char* kTIMSignalingInfoInviteID = "signaling_info_invite_id";
// string, 只读, 群组 ID
static const char* kTIMSignalingInfoGroupID = "signaling_info_group_id";
// string, 只读, 邀请方的 ID
static const char* kTIMSignalingInfoInviter = "signaling_info_inviter";
// string, 只读, 被邀请方列表
static const char* kTIMSignalingInfoInviteeList = "signaling_info_invitee_list";
// string, 只读, 信令自定义内容
static const char* kTIMSignalingInfoData = "signaling_info_data";
// int @ref TIMSignalingActionType, 只读, 信令响应类型
static const char* kTIMSignalingInfoActionType = "signaling_info_action_type";
// int, 只读, 超时时间
static const char* kTIMSignalingInfoTimeout = "signaling_info_timeout";

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_SIGNALING_MANAGER_H_
