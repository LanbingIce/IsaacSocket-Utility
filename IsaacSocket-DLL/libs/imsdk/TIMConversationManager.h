// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_CONVERSATION_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_CONVERSATION_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 会话接口，包含了会话的获取，删除，更新等功能
//  - 会话（Conversation）的类型:
//     (1) C2C 会话，表示单聊情况自己与对方建立的对话，读取消息和发送消息都是通过会话完成
//     (2) Group 会话，表示群聊情况下，群内成员组成的会话，群会话内发送消息群成员都可接收到
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
//                            一. 会话相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 会话事件类型
enum TIMConvEvent {
    // 会话新增,例如收到一条新消息,产生一个新的会话是事件触发
    kTIMConvEvent_Add,
    // 会话删除,例如自己删除某会话时会触发
    kTIMConvEvent_Del,
    // 会话更新,会话内消息的未读计数变化和收到新消息时触发
    kTIMConvEvent_Update,
    // 会话开始
    kTIMConvEvent_Start,
    // 会话结束
    kTIMConvEvent_Finish,
};

// 1.2 会话标记类型
enum TIMConversationMarkType {
    // /< 会话标星
    kTIMConversationMarkTypeStar = 0x1,
    // /< 会话标记未读（重要会话）
    kTIMConversationMarkTypeUnread = 0x1 << 1,
    // /< 会话折叠
    kTIMConversationMarkTypeFold = 0x1 << 2,
    // /< 会话隐藏
    kTIMConversationMarkTypeHide = 0x1 << 3,
};

// 1.3 群 @ 类型
enum TIMGroupAtType {
    // @ 我
    kTIMGroup_At_Me = 1,
    // @ 群里所有人
    kTIMGroup_At_All,
    // @ 群里所有人并且单独 @ 我
    kTIMGroup_At_All_At_ME,
};


/////////////////////////////////////////////////////////////////////////////////
//
//                        二. 会话事件及会话未读数相关回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 会话事件回调
 *
 * @param conv_event 会话事件类型, 请参考 @ref TIMConvEvent
 * @param json_conv_array 会话信息列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __会话事件回调数据解析示例__
 * @code{.cpp}
 * void ConvEventCallback(TIMConvEvent conv_event, const char* json_conv_array, const void* user_data) {
 *     Json::Reader reader;
 *     Json::Value json_value;
 *     if (conv_event == kTIMConvEvent_Start) {
 *         // json_conv_array 为空字符串
 *     } else if(conv_event == kTIMConvEvent_Finish) {
 *         // json_conv_array 为空字符串
 *     }
 *     if (!reader.parse(json_conv_array, json_value)) {
 *         // Json 解析失败
 *         return;
 *     }
 *     for (Json::ArrayIndex i = 0; i < json_value.size(); i++) { // 遍历会话类别
 *         Json::Value& convinfo = json_value[i];
 *         // 区分会话事件类型
 *         if (conv_event == kTIMConvEvent_Add) {
 *
 *         }
 *         else if (conv_event == kTIMConvEvent_Del) {
 *
 *         }
 *     }
 * @endcode
 *
 * __json_conv_array 示例 (Json Key 请参考 @ref ConvInfo)__
 * @code{.json}
 * [{
 *   "conv_active_time": 4611686018427387909,
 *   "conv_id": "98826",
 *   "conv_is_has_draft": false,
 *   "conv_is_has_lastmsg": true,
 *   "conv_is_pinned": true,
 *   "conv_last_msg": {
 *       "message_client_time": 1620877708,
 *       "message_conv_id": "98826",
 *       "message_conv_type": 1,
 *       "message_custom_int": 0,
 *       "message_custom_str": "",
 *       "message_elem_array": [{
 *           "elem_type": 0,
 *           "text_elem_content": "11111"
 *       }],
 *       "message_is_from_self": false,
 *       "message_is_online_msg": false,
 *       "message_is_peer_read": false,
 *       "message_is_read": false,
 *       "message_msg_id": "144115233874815003-1620877708-1038050731",
 *       "message_platform": 0,
 *       "message_priority": 1,
 *       "message_rand": 1038050731,
 *       "message_sender": "98826",
 *       "message_sender_profile": {
 *           "user_profile_add_permission": 1,
 *           "user_profile_birthday": 0,
 *           "user_profile_custom_string_array": [],
 *           "user_profile_face_url": "test1-www.google.com",
 *           "user_profile_gender": 0,
 *           "user_profile_identifier": "98826",
 *           "user_profile_language": 0,
 *           "user_profile_level": 0,
 *           "user_profile_location": "",
 *           "user_profile_nick_name": "test change8888",
 *           "user_profile_role": 0,
 *           "user_profile_self_signature": ""
 *       },
 *       "message_seq": 15840,
 *       "message_server_time": 1620877708,
 *       "message_status": 2,
 *       "message_unique_id": 6961616747713488299
 *   },
 *   "conv_type": 1,
 *   "conv_unread_num": 1
 * }]
 * @endcode
 */
typedef void (*TIMConvEventCallback)(enum TIMConvEvent conv_event, const char* json_conv_array, const void* user_data);

/**
 * 2.2 会话未读消息总数变化
 *
 * @param total_unread_count 未读的消息总数
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMConvTotalUnreadMessageCountChangedCallback)(int total_unread_count, const void* user_data);

/**
 * 2.3 按会话 filter 过滤的未读消息总数变化
 *
 * @param filter 获取未读总数的 filter, Json Key 请参考 @ref TIMConversationListFilter
 * @param total_unread_count 未读的消息总数
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMConvTotalUnreadMessageCountChangedByFilterCallback)(const char* filter, int total_unread_count, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                            三. 会话分组相关回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 会话分组被创建
 *
 * @param group_name 分组名
 * @param conversation_array 会话列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMConvConversationGroupCreatedCallback)(const char* group_name, const char* conversation_array, const void* user_data);

/**
 * 3.2 会话分组被删除
 *
 * @param group_name 分组名
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMConvConversationGroupDeletedCallback)(const char* group_name, const void* user_data);

/**
 * 3.3 会话分组名变更
 *
 * @param old_name 分组名
 * @param new_name 分组名
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMConvConversationGroupNameChangedCallback)(const char* old_name, const char* new_name, const void* user_data);

/**
 * 3.4 会话分组新增会话
 *
 * @param group_name 分组名
 * @param conversation_array 会话列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMConvConversationsAddedToGroupCallback)(const char* group_name, const char* conversation_array, const void* user_data);

/**
 * 3.5 会话分组删除会话
 *
 * @param group_name 分组名
 * @param conversation_array 会话列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMConvConversationsDeletedFromGroupCallback)(const char* group_name, const char* conversation_array, const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                         四. 注册会话事件及未读数相关回调 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 4.1 设置会话事件回调
 * 
 * @param cb 会话事件回调，请参考 @ref TIMConvEventCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 会话事件包括：
 *  - 会话新增
 *  - 会话删除
 *  - 会话更新
 *  - 会话开始
 *  - 会话结束
 * 任何产生一个新会话的操作都会触发会话新增事件，例如调用接口 @ref TIMConvCreate 创建会话，接收到未知会话的第一条消息等。
 * 任何已有会话变化的操作都会触发会话更新事件，例如收到会话新消息，消息撤回，已读上报等。
 * 调用接口 @ref TIMConvDelete 删除会话成功时会触发会话删除事件。
 */
TIM_API void TIMSetConvEventCallback(TIMConvEventCallback cb, const void* user_data);

/**
 * 4.2 设置全部会话未读消息总数变更的回调
 * 
 * @param cb 会话未读消息总数变更的回调，请参考 @ref TIMConvTotalUnreadMessageCountChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 *  - 当您调用 @ref TIMConvGetTotalUnreadMessageCount 获取全部会话未读总数以后，任意会话的未读数发生变化时，SDK 都会通过该回调把最新的未读总数通知给您。
 *  - 未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 kTIMRecvMsgOpt_Not_Receive 或 kTIMRecvMsgOpt_Not_Notify 的会话。
 */
TIM_API void TIMSetConvTotalUnreadMessageCountChangedCallback(TIMConvTotalUnreadMessageCountChangedCallback cb, const void* user_data);

/**
 * 4.3 设置按会话 filter 过滤的未读消息总数变更的回调
 * 
 * @param cb 按会话 filter 过滤的未读消息总数变更的回调，请参考 @ref TIMConvTotalUnreadMessageCountChangedByFilterCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 *  - 您可以调用 @ref TIMConvSubscribeUnreadMessageCountByFilter 注册监听指定 filter 下的未读总数变化，SDK 通过这个回调把最新的未读总数通知给您。
 *  - 您可以注册监听多个不同 filter 下的未读总数变更，这个回调的 filter 参数就是注册监听时指定的 filter，该 filter 携带了 kTIMConversationListFilterConvType、kTIMConversationListFilterMarkType、kTIMConversationListFilterGroupName 三个字段，通过判断这三字段是不是都相同，来区分出不同的 filter。
 *  - 未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 kTIMRecvMsgOpt_Not_Receive 或 kTIMRecvMsgOpt_Not_Notify 的会话。
 */
TIM_API void TIMSetConvUnreadMessageCountChangedByFilterCallback(TIMConvTotalUnreadMessageCountChangedByFilterCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                           五. 注册会话分组相关回调
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 5.1 会话分组被创建
 * 
 * @param cb 会话未读消息总数变更的回调，请参考 @ref TIMConvConversationGroupCreatedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetConvConversationGroupCreatedCallback(TIMConvConversationGroupCreatedCallback cb, const void* user_data);

/**
 * 5.2 会话分组被删除
 * 
 * @param cb 会话未读消息总数变更的回调，请参考 @ref TIMConvConversationGroupDeletedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetConvConversationGroupDeletedCallback(TIMConvConversationGroupDeletedCallback cb, const void* user_data);

/**
 * 5.3 会话分组名变更
 * 
 * @param cb 会话未读消息总数变更的回调，请参考 @ref TIMConvConversationGroupNameChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetConvConversationGroupNameChangedCallback(TIMConvConversationGroupNameChangedCallback cb, const void* user_data);

/**
 * 5.4 会话分组新增会话
 * 
 * @param cb 会话未读消息总数变更的回调，请参考 @ref TIMConvConversationsAddedToGroupCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetConvConversationsAddedToGroupCallback(TIMConvConversationsAddedToGroupCallback cb, const void* user_data);

/**
 * 5.5 会话分组删除会话
 * 
 * @param cb 会话未读消息总数变更的回调，请参考 @ref TIMConvConversationsDeletedFromGroupCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetConvConversationsDeletedFromGroupCallback(TIMConvConversationsDeletedFromGroupCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                             六. 会话基础 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 6.1 获取会话列表
 *
 * @param cb 获取会话列表的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 */
TIM_API int TIMConvGetConvList(TIMCommCallback cb, const void* user_data);

/**
 * 6.2 查询一组会话列表
 *
 * @param json_get_conv_list_param   会话 ID 和会话类型的列表, Json Key 请参考 @ref GetConversationListParam
 * @param cb 会话列表的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功，其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * Json::Object json_obj;
 * json_obj[kTIMGetConversationListParamConvId] = "98826";
 * json_obj[kTIMGetConversationListParamConvType] = kTIMConv_C2C;
 *
 * Json::Array json_array;
 * json_array.append(json_obj);
 *
 * TIMConvGetConvInfo(json_array.toStyledString().c_str(),
 *    [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *    printf("TIMConvGetConvInfo|code:%d|desc:%s\n", code, desc);
 * }, nullptr);
 * @endcode
 *
 * __回调中的 json_param 示例 (Json Key 请参考 @ref ConvInfo)__
 * @code{.json}
 * [{
 *   "conv_active_time": 5,
 *   "conv_id": "98826",
 *   "conv_is_has_draft": false,
 *   "conv_is_has_lastmsg": true,
 *   "conv_is_pinned": false,
 *   "conv_last_msg": {
 *       "message_client_time": 1620877708,
 *       "message_conv_id": "98826",
 *       "message_conv_type": 1,
 *       "message_custom_int": 0,
 *       "message_custom_str": "",
 *       "message_elem_array": [{
 *           "elem_type": 0,
 *           "text_elem_content": "11111"
 *   }],
 *       "message_is_from_self": false,
 *       "message_is_online_msg": false,
 *       "message_is_peer_read": false,
 *       "message_is_read": false,
 *       "message_msg_id": "144115233874815003-1620877708-1038050731",
 *       "message_platform": 0,
 *       "message_priority": 1,
 *       "message_rand": 1038050731,
 *       "message_sender": "98826",
 *       "message_sender_profile": {
 *           "user_profile_add_permission": 1,
 *           "user_profile_birthday": 0,
 *           "user_profile_custom_string_array": [],
 *           "user_profile_face_url": "test1-www.google.com",
 *           "user_profile_gender": 0,
 *           "user_profile_identifier": "98826",
 *           "user_profile_language": 0,
 *           "user_profile_level": 0,
 *           "user_profile_location": "",
 *           "user_profile_nick_name": "test change8888",
 *           "user_profile_role": 0,
 *           "user_profile_self_signature": ""
        },
 *       "message_seq": 15840,
 *       "message_server_time": 1620877708,
 *       "message_status": 2,
 *       "message_unique_id": 6961616747713488299
 *    },
 *    "conv_type": 1,
 *    "conv_unread_num": 1
 * }]
 * @endcode
 */
TIM_API int TIMConvGetConvInfo(const char* json_get_conv_list_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.3 获取会话列表高级接口（从 6.5 版本开始支持）
 *
 * @param filter 获取会话列表高级接口的 filter, Json Key 请参考 @ref TIMConversationListFilter
 * @param next_seq 分页拉取的游标
 * @param count 分页拉取的个数
 * @param cb 获取会话列表高级接口的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   json::Object filter;
 *   filter[kTIMConversationListFilterConvType] = kTIMConv_Group;
 *   filter[kTIMConversationListFilterMarkType] = kTIMConversationMarkTypeStar;
 *   filter[kTIMConversationListFilterConversationGroup] = "my_group_name";
 *   filter[kTIMConversationListFilterHasUnreadCount] = true;
 *   filter[kTIMConversationListFilterHasGroupAtInfo] = true;
 *
 *   TIMConvGetConversationListByFilter(json::Serialize(filter).c_str(), 0, 20, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvGetConversationListByFilter code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 读取 json_param 存放的结果
 *       json::Value json = json::Deserialize(json_param);
 *       // json[TIMConversationListResultConvList] 读取到 ConvInfo 列表
 *       uint64_t next_seq = json[TIMConversationListResultNextSeq].ToUInt64();
 *       bool is_finished = json[TIMConversationListResultIsFinished].ToBool();
 *       if (!is_finished) {
 *           // 继续调用 TIMConvGetConversationListByFilter 获取下一页，filter 参数的字段填写如下所示
 *           // json::Object filter;
 *           // filter[kTIMConversationListFilterConvType] = kTIMConv_Group;
 *           // filter[kTIMConversationListFilterMarkType] = kTIMConversationMarkTypeStar;
 *           // filter[kTIMConversationListFilterConversationGroup] = "my_group_name";
 *           // filter[kTIMConversationListFilterHasUnreadCount] = true;
 *           // filter[kTIMConversationListFilterHasGroupAtInfo] = true;
 *       }
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvGetConversationListByFilter(const char* filter, uint64_t next_seq, uint32_t count, TIMCommCallback cb, const void* user_data);

/**
 * 6.4 删除会话以及该会话中的历史消息
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param cb 删除会话成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 此接口用于删除会话（该会话以及会话中的历史消息，会被 SDK 从本地和服务端一同删除掉，并且不可恢复），删除会话是否成功的结果会通过会话事件回调返回。
 */
TIM_API int TIMConvDelete(const char* conv_id, enum TIMConvType conv_type, TIMCommCallback cb, const void* user_data);

/**
 * 6.5 删除会话列表（从 7.1 版本开始支持）
 *
 * @param conversation_id_array 会话 ID 列表
 * @param clearMessage 是否删除会话中的消息；设置为 false 时，保留会话消息；设置为 true 时，本地和服务器的消息会一起删除，并且不可恢复
 * @param cb 删除会话列表的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK 只负责传回给回调函数 cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意: 每次最多支持删除 100 个会话
 *
 * __示例(回调结果中 json_param 使用的 Json Key 请参考 @ref TIMConversationOperationResult)__
 * @code{.cpp}
 *   json::Array conversation_id_array;
 *   conversation_id_array.push_back("c2c_conversation_id1");
 *   conversation_id_array.push_back("group_conversation_id2");
 *
 *   bool clearMessage = true;
 *
 *   TIMConvDeleteConversationList(json::Serialize(conversation_id_array).c_str(), clearMessage, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvDeleteConversationList code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 遍历读取 json_param 存放的操作结果，参见 TIMConversationOperationResult 的定义
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvDeleteConversationList(const char* conversation_id_array, bool clearMessage, TIMCommCallback cb, const void* user_data);

/**
 * 6.6 设置指定会话的草稿
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_draft_param 被设置的草稿 Json 字符串, Json Key 请参考 @ref Draft
 * @return int 返回TIM_SUCC表示接口调用成功，其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 会话草稿一般用在保存用户当前输入的未发送的消息
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_text;  // 构造消息
 * json_value_text[kTIMElemType] = kTIMElem_Text;
 * json_value_text[kTIMTextElemContent] = "this draft";
 * Json::Value json_value_msg;
 * json_value_msg[kTIMMsgElemArray].append(json_value_text);
 *
 * Json::Value json_value_draft; // 构造草稿
 * json_value_draft[kTIMDraftEditTime] = time(NULL);
 * json_value_draft[kTIMDraftUserDefine] = "this is userdefine";
 * json_value_draft[kTIMDraftMsg] = json_value_msg;
 *
 * if (TIM_SUCC != TIMConvSetDraft(userid.c_str(), TIMConvType::kTIMConv_C2C, json_value_draft.toStyledString().c_str())) {
 *     // TIMConvSetDraft 接口调用失败
 * }
 *
 * // json_value_draft.toStyledString().c_str() 得到 json_draft_param JSON 字符串如下
 * {
 *    "draft_edit_time" : 1551271429,
 *    "draft_msg" : {
 *       "message_elem_array" : [
 *          {
 *             "elem_type" : 0,
 *             "text_elem_content" : "this draft"
 *          }
 *       ]
 *    },
 *    "draft_user_define" : "this is userdefine"
 * }
 * @endcode
 */
TIM_API int TIMConvSetDraft(const char* conv_id, enum TIMConvType conv_type, const char* json_draft_param);

/**
 * 6.7 删除指定会话的草稿
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @return int 返回TIM_SUCC表示接口调用成功，其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 */
TIM_API int TIMConvCancelDraft(const char* conv_id, enum TIMConvType conv_type);

/**
 * 6.8 设置会话自定义数据（从 6.5 版本开始支持）
 *
 * @param conversation_id_array 会话 ID 列表
 * @param custom_data 自定义数据，最大支持 256 bytes
 * @param cb 设置会话自定义字段的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例(回调结果中 json_param 使用的 Json Key 请参考 @ref TIMConversationOperationResult)__
 * @code{.cpp}
 *   json::Array conversation_id_array;
 *   conversation_id_array.push_back("c2c_conversation_id1");
 *   conversation_id_array.push_back("group_conversation_id2");
 *
 *   std::string custom_data = "my_custom_data";
 *
 *   TIMConvSetConversationCustomData(json::Serialize(conversation_id_array).c_str(), custom_data.c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvSetConversationCustomData code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 遍历读取 json_param 存放的操作结果，参见 TIMConversationOperationResult 的定义
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvSetConversationCustomData(const char* conversation_id_array, const char* custom_data, TIMCommCallback cb, const void* user_data);

/**
 * 6.9 设置会话置顶
 *
 * @param conv_id   会话 ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param is_pinned 是否置顶会话
 * @param cb 设置会话置顶回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * // json_param 返回值为空字符串， 直接判断 code 即可
 * TIMConvPinConversation(conv_id, conv_type, true,
 *      [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *      printf("TIMConvPinConversation|code:%d|desc:%s\n", code, desc);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMConvPinConversation(const char* conv_id, TIMConvType conv_type, bool is_pinned, TIMCommCallback cb, const void* user_data);

/**
 * 6.10 标记会话（从 6.5 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param conversation_id_array 会话 ID 列表
 * @param mark_type 会话标记类型，取值详见 @ref TIMConversationMarkType
 * @param enable_mark true：设置标记 false：取消标记
 * @param cb 标记会话的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * 如果已有标记不能满足您的需求，您可以自定义扩展标记，扩展标记需要满足以下两个条件：
 * 1、扩展标记值不能和 @ref TIMConversationMarkType 已有的标记值冲突
 * 2、扩展标记值必须是 0x1LL << n 的位移值（32 <= n < 64，即 n 必须大于等于 32 并且小于 64），比如扩展标记值 0x1LL << 32 表示 "Windows 在线"
 *
 * @note
 * 扩展标记值不能设置为 0x1 << 32，要设置为 0x1LL << 32，明确告诉编译器是 64 位的整型常量。
 *
 * __示例(回调结果中 json_param 使用的 Json Key 请参考 @ref TIMConversationOperationResult)__
 * @code{.cpp}
 *   json::Array conversation_id_array;
 *   conversation_id_array.push_back("c2c_conversation_id1");
 *   conversation_id_array.push_back("group_conversation_id2");
 *
 *   uint64_t mark_type = (uint64_t)kTIMConversationMarkTypeUnread | (0x1LL << 32);
 *   bool enable_mark = true;
 *
 *   TIMConvMarkConversation(json::Serialize(conversation_id_array).c_str(), mark_type, enable_mark, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvMarkConversation code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 遍历读取 json_param 存放的操作结果，参见 TIMConversationOperationResult 的定义
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvMarkConversation(const char* conversation_id_array, uint64_t mark_type, bool enable_mark, TIMCommCallback cb, const void* user_data);

/**
 * 6.11 获取所有会话总的未读消息数
 *
 * @param cb 获取所有会话总的未读消息数回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 调用该接口以后，任意会话的未读数发生变化时，SDK 都会给您抛 @ref TIMSetConvTotalUnreadMessageCountChangedCallback 回调。
 *  - 未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 kTIMRecvMsgOpt_Not_Receive 或 kTIMRecvMsgOpt_Not_Notify 的会话。
 * 
 * __示例 (回调结果中 json_param 使用的 Json Key 请参考 @ref GetTotalUnreadNumberResult)__
 * @code{.cpp}
 *  TIMConvGetTotalUnreadMessageCount(
 *       [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       // json key 请参考 GetTotalUnreadNumberResult
 *       printf("TIMConvGetTotalUnreadMessageCount|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *  }, nullptr);
 * @endcode
 */
TIM_API int TIMConvGetTotalUnreadMessageCount(TIMCommCallback cb, const void* user_data);

/**
 * 6.12 根据 filter 获取未读总数（7.0 及以上版本支持）
 *
 * @param filter 会话 filter, Json Key 请参考 @ref TIMConversationListFilter
 * @param cb 获取未读总数的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 kTIMRecvMsgOpt_Not_Receive 或 kTIMRecvMsgOpt_Not_Notify 的会话。
 *
 * __示例 (回调结果中 json_param 使用的 Json Key 请参考 @ref GetTotalUnreadNumberResult)__
 * @code{.cpp}
 *   json::Object filter;
 *   filter[kTIMConversationListFilterConvType] = kTIMConv_Group;
 *   filter[kTIMConversationListFilterConversationGroup] = "my_group_name";
 *   filter[kTIMConversationListFilterMarkType] = kTIMConversationMarkTypeStar;
 *   filter[kTIMConversationListFilterHasUnreadCount] = true;
 *   filter[kTIMConversationListFilterHasGroupAtInfo] = true;
 *
 *   TIMConvGetUnreadMessageCountByFilter(json::Serialize(filter).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       // json key 请参考 GetTotalUnreadNumberResult
 *       printf("TIMConvGetTotalUnreadMessageCount|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvGetUnreadMessageCountByFilter(const char* filter, TIMCommCallback cb, const void* user_data);

/**
 * 6.13 注册监听指定 filter 的会话未读总数变化（7.0 及以上版本支持）
 *
 * @param filter 会话 filter, Json Key 请参考 @ref TIMConversationListFilter
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 当您调用这个接口以后，该 filter 下的未读数发生变化时，SDK 会给您抛 @ref TIMSetConvUnreadMessageCountChangedByFilterCallback 注册的回调。
 *
 * __示例__
 * @code{.cpp}
 *   json::Object filter;
 *   filter[kTIMConversationListFilterConvType] = kTIMConv_Group;
 *   filter[kTIMConversationListFilterConversationGroup] = "my_group_name";
 *   filter[kTIMConversationListFilterMarkType] = kTIMConversationMarkTypeStar;
 *   filter[kTIMConversationListFilterHasUnreadCount] = true;
 *   filter[kTIMConversationListFilterHasGroupAtInfo] = true;
 *
 *   TIMConvSubscribeUnreadMessageCountByFilter(json::Serialize(filter).c_str());
 * @endcode
 */
TIM_API int TIMConvSubscribeUnreadMessageCountByFilter(const char* filter);

/**
 * 6.14 取消监听指定 filter 的会话未读总数变化（7.0 及以上版本支持）
 *
 * @param filter 会话 filter, Json Key 请参考 @ref TIMConversationListFilter
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   json::Object filter;
 *   filter[kTIMConversationListFilterConvType] = kTIMConv_Group;
 *   filter[kTIMConversationListFilterConversationGroup] = "my_group_name";
 *   filter[kTIMConversationListFilterMarkType] = kTIMConversationMarkTypeStar;
 *   filter[kTIMConversationListFilterHasUnreadCount] = true;
 *   filter[kTIMConversationListFilterHasGroupAtInfo] = true;
 *
 *   TIMConvUnsubscribeUnreadMessageCountByFilter(json::Serialize(filter).c_str());
 * @endcode
 */
TIM_API int TIMConvUnsubscribeUnreadMessageCountByFilter(const char* filter);

/**
 * 6.15 清理会话的未读消息计数（7.1 及以上版本支持）
 *
 * @param conversation_id  会话唯一 ID， C2C 单聊组成方式："c2c_" + userID；群聊组成方式为 "group_" + groupID
 * @param clean_timestamp  清理时间戳，单位为秒，仅对单聊会话生效，指定清理哪一个 timestamp 之前的未读消息计数；当传入为 0 时，对应会话所有的未读消息将被清理，会话的未读数会清 0；
 * @param clean_sequence  清理时 sequence，仅对群聊会话生效，指定清理哪一个 sequence 之前的未读消息计数；当传入为 0 时，对应会话所有的未读消息将被清理，会话的未读数会清 0；
 * @param cb 创建会话分组的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 *  - 当您想清理所有单聊会话的未读消息计数，conversation_id 请传入 "c2c"，即不指定具体的 userID；
 *  - 当您想清理所有群聊会话的未读消息计数，conversation_id 请传入 "group"，即不指定具体的 groupID；
 *  - 当您想清理所有会话的未读消息计数，conversation_id 请传入 "" 或者 nullptr；
 *  - 该接口调用成功后，SDK 会通过 @ref TIMSetConvEventCallback 回调 (@ref TIMConvEvent 为 kTIMConvEvent_Update）将对应会话的最新未读数通知给您。
 *
 * __示例__
 * @code{.cpp}
 *
 *   TIMConvCleanConversationUnreadMessageCount("c2c_user1", 123456, 0, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvCleanConversationUnreadMessageCount code:%d|desc:%s\n", code, desc);
 *
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvCleanConversationUnreadMessageCount(const char* conversation_id, uint64_t clean_timestamp, uint64_t clean_sequence, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//            七. 会话分组相关接口（从 6.5 版本开始支持，需要您购买旗舰版套餐）
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 7.1 创建会话分组（从 6.5 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param group_name 分组名（必填参数，长度要 > 0，最大支持 32 bytes）
 * @param conversation_id_array 会话 ID 列表（必填参数，不能为空）
 * @param cb 创建会话分组的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 会话分组最大支持 20 个，不再使用的分组请及时删除。
 *
 * __示例__
 * @code{.cpp}
 *   std::string group_name = "my_group_name";
 *
 *   json::Array conversation_id_array;
 *   conversation_id_array.push_back("c2c_conversation_id1");
 *   conversation_id_array.push_back("group_conversation_id2");
 *
 *   TIMConvCreateConversationGroup(group_name.c_str(), json::Serialize(conversation_id_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvCreateConversationGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 遍历读取 json_param 存放的操作结果，参见 TIMConversationOperationResult 的定义
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvCreateConversationGroup(const char* group_name, const char* conversation_id_array, TIMCommCallback cb, const void* user_data);

/**
 * 7.2 获取会话分组列表（从 6.5 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param cb 获取会话分组列表的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 该接口获取的是本地缓存的会话分组，建议在 kTIMConvEvent_Finish 之后调用。
 *
 * __示例__
 * @code{.cpp}
 *   TIMConvGetConversationGroupList([](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvGetConversationGroupList code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 读取 json_param 存放的会话分组列表，例如：
 *       // [
 *       //      "my_group_name1",
 *       //      "my_group_name2",
 *       //      "my_group_name3"
 *       // ]
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvGetConversationGroupList(TIMCommCallback cb, const void* user_data);

/**
 * 7.3 删除会话分组（从 6.5 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param group_name 分组名（必填参数，长度要 > 0，最大支持 32 bytes）
 * @param cb 删除会话分组的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   std::string group_name = "my_group_name";
 *
 *   TIMConvDeleteConversationGroup(group_name.c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvDeleteConversationGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvDeleteConversationGroup(const char* group_name, TIMCommCallback cb, const void* user_data);

/**
 * 7.4 重命名会话分组（从 6.5 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param old_name 分组名（必填参数，长度要 > 0，最大支持 32 bytes）
 * @param new_name 分组名（必填参数，长度要 > 0，最大支持 32 bytes）
 * @param cb 重命名会话分组的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   std::string old_name = "old_name";
 *   std::string new_name = "new_name";
 *
 *   TIMConvRenameConversationGroup(old_name.c_str(), new_name.c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvRenameConversationGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvRenameConversationGroup(const char* old_name, const char* new_name, TIMCommCallback cb, const void* user_data);

/**
 * 7.5 添加会话到一个会话分组（从 6.5 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param group_name 分组名（必填参数，长度要 > 0，最大支持 32 bytes）
 * @param conversation_id_array 会话 ID 列表（必填参数，不能为空）
 * @param cb 添加会话到一个会话分组的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例 (回调结果中 json_param 使用的 Json Key 请参考 @ref TIMConversationOperationResult)__
 * @code{.cpp}
 *   std::string group_name = "my_group_name";
 *
 *   json::Array conversation_id_array;
 *   conversation_id_array.push_back("c2c_conversation_id1");
 *   conversation_id_array.push_back("group_conversation_id2");
 *
 *   TIMConvAddConversationsToGroup(group_name.c_str(), json::Serialize(conversation_id_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvAddConversationsToGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 遍历读取 json_param 存放的操作结果，参见 TIMConversationOperationResult 的定义
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvAddConversationsToGroup(const char* group_name, const char* conversation_id_array, TIMCommCallback cb, const void* user_data);

/**
 * 7.6 从会话分组中删除多个会话（从 6.5 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param group_name 分组名（必填参数，长度要 > 0，最大支持 32 bytes）
 * @param conversation_id_array 会话 ID 列表（必填参数，不能为空）
 * @param cb 从会话分组中删除多个会话的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用）。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例 (回调结果中 json_param 使用的 Json Key 请参考 @ref TIMConversationOperationResult)__
 * @code{.cpp}
 *   std::string group_name = "my_group_name";
 *
 *   json::Array conversation_id_array;
 *   conversation_id_array.push_back("c2c_conversation_id1");
 *   conversation_id_array.push_back("group_conversation_id2");
 *
 *   TIMConvDeleteConversationsFromGroup(group_name.c_str(), json::Serialize(conversation_id_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMConvDeleteConversationsFromGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *
 *       // 遍历读取 json_param 存放的操作结果，参见 TIMConversationOperationResult 的定义
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMConvDeleteConversationsFromGroup(const char* group_name, const char* conversation_id_array, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                         八. 会话 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 8.1 Draft(草稿信息)
// object @ref Message, 只读, 草稿内的消息
static const char* kTIMDraftMsg = "draft_msg";
// string, 只读, 用户自定义数据
static const char* kTIMDraftUserDefine = "draft_user_define";
// uint, 只读, 上次设置草稿时的 UTC 时间戳
static const char* kTIMDraftEditTime = "draft_edit_time";

//------------------------------------------------------------------------------
// 8.2 GroupAtInfo(群 @ 信息)
// uint64, 只读, @ 消息序列号，即带有 “@我” 或者 “@所有人” 标记的消息的序列号
static const char* kTIMGroupAtInfoSeq = "conv_group_at_info_seq";
// uint @ref TIMGroupAtType, 只读, @ 提醒类型，分成 “@我” 、“@所有人” 以及 “@我并@所有人” 三类
static const char* kTIMGroupAtInfoAtType = "conv_group_at_info_at_type";

//------------------------------------------------------------------------------
// 8.3 ConvInfo(会话信息)
// string, 只读, 会话ID
static const char* kTIMConvId = "conv_id";
// uint @ref TIMConvType, 只读, 会话类型
static const char* kTIMConvType = "conv_type";
// string, 只读, 会话展示头像（群组：群头像；C2C：对方头像）
static const char* kTIMConvFaceUrl = "conv_face_url";
// uint64, 只读, 会话未读计数
static const char* kTIMConvUnReadNum = "conv_unread_num";
// uint64, 只读, 会话的激活时间
static const char* kTIMConvActiveTime = "conv_active_time";
// bool, 只读, 会话是否有最后一条消息
static const char* kTIMConvIsHasLastMsg = "conv_is_has_lastmsg";
// object @ref Message, 只读, 会话最后一条消息
static const char* kTIMConvLastMsg = "conv_last_msg";
// bool, 只读, 会话是否有草稿
static const char* kTIMConvIsHasDraft = "conv_is_has_draft";
// object @ref Draft, 只读(选填), 会话草稿
static const char* kTIMConvDraft = "conv_draft";
// uint @ref TIMReceiveMessageOpt, 只读(选填), 消息接收选项
static const char* kTIMConvRecvOpt = "conv_recv_opt";
// uint @ref TIMGroupType, 只读(选填), 群组类型, 仅当会话类型为群聊时有效
static const char* kTIMConvGroupType = "conv_group_type";
// array @ref GroupAtInfo, 只读(选填), 群会话 @ 信息列表，用于展示 “有人@我” 或 “@所有人” 这两种提醒状态
static const char* kTIMConvGroupAtInfoArray = "conv_group_at_info_array";
// bool, 只读,是否置顶
static const char* kTIMConvIsPinned = "conv_is_pinned";
// string , 只读, 获取会话展示名称，其展示优先级如下：1、群组，群名称 -> 群 ID;C2C; 2、对方好友备注 -> 对方昵称 -> 对方的 userID
static const char* kTIMConvShowName = "conv_show_name";
// array uint64, 只读, 会话标记列表，取值详见 @TIMConversationMarkType（从 6.5 版本开始支持）
static const char* kTIMConvMarkArray = "conv_mark_array";
// string , 只读, 会话自定义数据（从 6.5 版本开始支持）
static const char* kTIMConvCustomData = "conv_custom_data";
// array string, 只读, 会话所属分组列表（从 6.5 版本开始支持）
static const char* kTIMConvConversationGroupArray = "conv_conversation_group_array";
// uint64, 只读, 最新已读消息的 UTC 时间戳，仅对单聊会话生效（从 7.1 版本开始支持）
static const char* kTIMConvC2CReadTimestamp = "conv_c2c_read_timestamp";
// uint64, 只读, 群消息已读 Sequence（从 7.1 版本开始支持）
static const char* kTIMConvGroupReadSequence = "conv_group_read_sequence";

//------------------------------------------------------------------------------
// 8.4 TIMConversationListFilter(获取会话列表高级接口的 filter)
// uint @ref TIMConvType, 只写, 会话类型
static const char* kTIMConversationListFilterConvType = "conversation_list_filter_conv_type";
// string, 只写, 会话分组名称（不设置表示不过滤此项，设置为 "" 代表过滤不属于任何分组的会话）
static const char* kTIMConversationListFilterConversationGroup = "conversation_list_filter_conversation_group";
// uint @ref TIMConversationMarkType, 只写, 会话标记类型（不设置表示不过滤此项，设置为 0 代表过滤不含任何标记的会话）
static const char* kTIMConversationListFilterMarkType = "conversation_list_filter_mark_type";
// bool, 只写, 会话是否含有未读数（不设置表示不过滤此项，设置为 true 代表过滤含未读数的会话；设置为 false 代表过滤不含未读数的会话）
static const char* kTIMConversationListFilterHasUnreadCount = "conversation_list_filter_has_unread_count";
// bool, 只写, 会话是否含有群 @ 信息（不设置表示不过滤此项，设置为 true 代表过滤含群 @ 消息的会话；设置为 false 代表过滤不含群 @ 消息的会话）
static const char* kTIMConversationListFilterHasGroupAtInfo = "conversation_list_filter_has_group_at_info";

//------------------------------------------------------------------------------
// 8.5 TIMConversationListResult(获取会话列表的结果)
// array @ref ConvInfo, 只读, 会话列表
static const char* TIMConversationListResultConvList = "conversation_list_result_conv_list";
// uint64, 只读, 分页拉取的游标
static const char* TIMConversationListResultNextSeq = "conversation_list_result_next_seq";
// bool, 只读, 分页拉取是否结束
static const char* TIMConversationListResultIsFinished = "conversation_list_result_is_finished";

//------------------------------------------------------------------------------
// 8.6 GetConversationListParam(获取指定的会话列表)
// string, 只写, 会话ID
static const char* kTIMGetConversationListParamConvId = "get_conversation_list_param_conv_id";
// uint @ref TIMConvType, 只写, 会话类型
static const char* kTIMGetConversationListParamConvType = "get_conversation_list_param_conv_type";

//------------------------------------------------------------------------------
// 8.7 GetTotalUnreadNumberResult(获取会话未读消息个数)
// int, 只读，会话未读数
static const char* kTIMConvGetTotalUnreadMessageCountResultUnreadCount = "conv_get_total_unread_message_count_result_unread_count";

//------------------------------------------------------------------------------
// 8.8 TIMConversationOperationResult(会话操作结果)
// string, 只读, 会话 ID
static const char* kTIMConversationOperationResultConversationID = "conversation_operation_result_conversation_id";
// int, 只读, 返回码
static const char* kTIMConversationOperationResultResultCode = "conversation_operation_result_result_code";
// string, 只读, 返回信息
static const char* kTIMConversationOperationResultResultInfo = "conversation_operation_result_result_info";


/////////////////////////////////////////////////////////////////////////////////
//
//                                九. 废弃字段
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 9.1 ConvInfo(会话信息，废弃字段部分)
// string, 只读, 会话所有者
static const char* kTIMConvOwner = "conv_owner";


/////////////////////////////////////////////////////////////////////////////////
//
//                                十. 废弃接口
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 10.1 创建会话（待废弃接口）
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param cb 创建会话的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 会话是指面向一个人或者一个群组的对话，通过与单个人或群组之间会话收发消息
 *  - 此接口创建或者获取会话信息，需要指定会话类型（群组或者单聊），以及会话对方标志（对方账号或者群号）。会话信息通过cb回传。
 *
 * __获取对方 UserID 为 Windows-02 的单聊会话示例__
 * @code{.cpp}
 * const void* user_data = nullptr; // 回调函数回传
 * const char* userid = "Windows-02";
 * int ret = TIMConvCreate(userid, kTIMConv_C2C, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         return;
 *     }
 *     // 回调返回会话的具体信息
 * }, user_data);
 * if (ret != TIM_SUCC) {
 *     // 调用 TIMConvCreate 接口失败
 * }
 * @endcode
 * 
 * __获取群组 ID 为 Windows-Group-01 的群聊会话示例__
 * @code{.cpp}
 * const void* user_data = nullptr; // 回调函数回传
 * const char* userid = "Windows-Group-01";
 * int ret = TIMConvCreate(userid, kTIMConv_Group, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         return;
 *     }
 *     // 回调返回会话的具体信息
 * }, user_data);
 * if (ret != TIM_SUCC) {
 *     // 调用 TIMConvCreate 接口失败
 * }
 * @endcode
 */
TIM_API int TIMConvCreate(const char* conv_id, enum TIMConvType conv_type, TIMCommCallback cb, const void* user_data);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_CONVERSATION_MANAGER_H_
