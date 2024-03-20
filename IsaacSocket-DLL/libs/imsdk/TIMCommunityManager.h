// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_COMMUNITY_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_COMMUNITY_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 社群接口，包含获取加入的社群列表、创建话题、删除话题、修改话题，获取话题列表等功能
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
//                        一. 社群功能相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 设置(修改)话题信息的类型
enum TIMCommunityTopicModifyInfoFlag {
    // 未定义
    kTIMCommunityTopicModifyInfoFlag_None = 0x00,
    // 修改话题名称
    kTIMCommunityTopicModifyInfoFlag_Name = 0x01,
    // 修改话题公告
    kTIMCommunityTopicModifyInfoFlag_Notification = 0x01 << 1,
    // 修改话题简介
    kTIMCommunityTopicModifyInfoFlag_Introduction = 0x01 << 2,
    // 修改话题头像URL
    kTIMCommunityTopicModifyInfoFlag_FaceUrl = 0x01 << 3,
    // 修改话题是否全体禁言
    kTIMCommunityTopicModifyInfoFlag_MuteALl = 0x01 << 8,
    // 话题自定义字段
    kTIMCommunityTopicModifyInfoFlag_CustomString = 0x01 << 11,
    // 修改话题草稿
    kTIMCommunityTopicModifyInfoFlag_Draft = 0x01 << 14,
    // 修改话题默认权限，7.8 版本开始支持
    kTIMCommunityTopicModifyInfoFlag_DefaultPermissions = 0x01 << 15,
};

// 1.2 修改权限组信息的类型
enum TIMPermissionGroupModifyInfoFlag {
    // 未定义
    kTIMPermissionGroupModifyInfoFlag_None = 0x00,
    // 名称
    kTIMPermissionGroupModifyInfoFlag_Name = 0x01,
    // 群权限
    kTIMPermissionGroupModifyInfoFlag_GroupPermission = 0x01 << 1,
    // 自定义字段
    kTIMPermissionGroupModifyInfoFlag_CustomData = 0x01 << 2,
};

// 1.3 社群权限值
enum V2TIMCommunityPermissionValue {
    // 修改群资料权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_GROUP_INFO = 0x01,
    // 群成员管理权限，包含踢人，进群审核、修改成员资料等。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_GROUP_MEMBER = 0x1 << 1,
    // 管理权限组资料权限，包含创建、修改、删除权限组；在权限组中添加、修改、删除话题权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_MANAGE_PERMISSION_GROUP_INFO = 0x1 << 2,
    // 权限组成员管理权限，包含邀请成员进权限组和把成员从权限组踢出等。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_PERMISSION_GROUP_MEMBER = 0x1 << 3,
    // 话题管理权限，包含创建、修改、删除话题等。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_COMMUNITY_PERMISSION_MANAGE_TOPIC_IN_COMMUNITY = 0x1 << 4,
    // 对某群成员在社群下所有话题的禁言权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_MUTE_MEMBER = 0x1 << 5,
    //群成员在社群下所有话题的发消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_SEND_MESSAGE = 0x1 << 6,
    // 在社群下所有话题发 at all 消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_AT_ALL = 0x1 << 7,
    // 在社群下所有话题拉取入群前的历史消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_GET_HISTORY_MESSAGE = 0x1 << 8,
    // 在社群下所有话题撤回他人消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_REVOKE_OTHER_MEMBER_MESSAGE = 0x1 << 9,
    // 封禁社群成员权限。该位设置为0，表示没有该权限；设置为1，表示有该权限。
    V2TIM_COMMUNITY_PERMISSION_BAN_MEMBER = 0x1 << 10,
};

// 1.4 话题权限值
enum V2TIMTopicPermissionValue {
    // 管理当前话题的权限，包括修改当前话题的资料、删除当前话题。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC = 0x1,
    // 在当前话题中管理话题权限，包括添加、修改、移除话题权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC_PERMISSION = 0x1L << 1,
    // 在当前话题中禁言成员权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_MUTE_MEMBER = 0x1L << 2,
    // 在当前话题中发消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_SEND_MESSAGE = 0x1L << 3,
    // 在当前话题中拉取入群前的历史消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_GET_HISTORY_MESSAGE = 0x1L << 4,
    // 在当前话题中撤回他人消息权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_REVOKE_OTHER_MEMBER_MESSAGE = 0x1L << 5,
    // 在当前话题中发消息时有 at all 权限。该位设置为0，表示没有该权限；设置为1，表示有该权限
    V2TIM_TOPIC_PERMISSION_AT_ALL = 0x1L << 6,
};

/////////////////////////////////////////////////////////////////////////////////
//
//                         二. 社群事件回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 话题创建的回调
 *
 * @param group_id 话题所属的社群 ID
 * @param topic_id 话题 ID
 */
typedef void (*TIMCommunityCreateTopicCallback)(const char* group_id, const char* topic_id, const void* user_data);

/**
 * 2.2 话题被删除的回调
 *
 * @param group_id 话题所属的社群 ID
 * @param topic_id_array 话题列表
 */
typedef void (*TIMCommunityDeleteTopicCallback)(const char* group_id, const char* topic_id_array,
                                                const void* user_data);

/**
 * 2.3 话题更新的回调
 *
 * @param topic_info 话题信息，参见 @ref TIMGroupTopicInfo 类型
 */
typedef void (*TIMCommunityChangeTopicInfoCallback)(const char* group_id, const char* topic_info,
                                                    const void* user_data);

/**
 * 2.4 话题自定义系统通知
 */
typedef void (*TIMCommunityReceiveTopicRESTCustomDataCallback)(const char* topic_id, const char* custom_data,
                                                               const void* user_data);

/**
 * 2.5 权限组创建的回调
 */
typedef void (*TIMCommunityCreatePermissionGroupCallback)(const char* group_id, const char* permission_group_info,
                                                          const void* user_data);

/**
 * 2.6 权限组删除的回调
 */
typedef void (*TIMCommunityDeletePermissionGroupCallback)(const char* group_id, const char* permission_group_id_array,
                                                          const void* user_data);

/**
 * 2.7 权限组更新的回调
 */
typedef void (*TIMCommunityChangePermissionGroupInfoCallback)(const char* group_id, const char* permission_group_info,
                                                              const void* user_data);

/**
 * 2.8 添加成员到权限组中
 */
typedef void (*TIMCommunityAddMembersToPermissionGroupCallback)(const char* group_id, const char* json_result,
                                                                const void* user_data);

/**
 * 2.9 从权限组中删除成员
 */
typedef void (*TIMCommunityRemoveMembersFromPermissionGroupCallback)(const char* group_id, const char* json_result,
                                                                     const void* user_data);

/**
 * 2.10 话题权限添加的回调
 */
typedef void (*TIMCommunityAddTopicPermissionCallback)(const char* group_id, const char* json_result,
                                                       const void* user_data);

/**
 * 2.11 话题权限删除的回调
 */
typedef void (*TIMCommunityDeleteTopicPermissionCallback)(const char* group_id, const char* json_result,
                                                          const void* user_data);

/**
 * 2.12 话题权限修改的回调
 */
typedef void (*TIMCommunityModifyTopicPermissionCallback)(const char* group_id, const char* json_result,
                                                          const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                            三. 注册社群事件回调 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 话题创建
 *
 * @param cb 话题创建回调，请参考 @ref TIMCommunityCreateTopicCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityCreateTopicCallback(TIMCommunityCreateTopicCallback cb, const void* user_data);

/**
 * 3.2 话题被删除
 *
 * @param cb 话题被删除回调，请参考 @ref TIMCommunityDeleteTopicCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityDeleteTopicCallback(TIMCommunityDeleteTopicCallback cb, const void* user_data);

/**
 * 3.3 话题更新
 *
 * @param cb 话题更新回调，请参考 @ref TIMCommunityChangeTopicInfoCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityChangeTopicInfoCallback(TIMCommunityChangeTopicInfoCallback cb, const void* user_data);

/**
 * 3.4 RESTAPI 下发的话题自定义系统消息
 * @param cb 回调，请参考 @ref TIMCommunityReceiveTopicRESTCustomDataCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityReceiveTopicRESTCustomDataCallback(TIMCommunityReceiveTopicRESTCustomDataCallback cb,
                                                               const void* user_data);

/**
 * 3.5 权限组创建
 * @param cb 权限组创建回调，请参考 @ref TIMCommunityCreatePermissionGroupCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityCreatePermissionGroupCallback(TIMCommunityCreatePermissionGroupCallback cb,
                                                          const void* user_data);

/**
 * 3.6 权限组删除
 * @param cb 权限组删除回调，请参考 @ref TIMCommunityDeletePermissionGroupCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityDeletePermissionGroupCallback(TIMCommunityDeletePermissionGroupCallback cb,
                                                          const void* user_data);

/**
 * 3.7 权限组更新
 * @param cb 权限组更新回调，请参考 @ref TIMCommunityChangePermissionGroupInfoCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityChangePermissionGroupInfoCallback(TIMCommunityChangePermissionGroupInfoCallback cb,
                                                              const void* user_data);

/**
 * 3.8 添加成员到权限组中
 * @param cb 添加成员回调，请参考 @ref TIMCommunityAddMembersToPermissionGroupCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityAddMembersToPermissionGroupCallback(TIMCommunityAddMembersToPermissionGroupCallback cb,
                                                                const void* user_data);

/**
 * 3.9 从权限组中删除成员
 * @param cb 删除成员回调，请参考 @ref TIMCommunityRemoveMembersFromPermissionGroupCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityRemoveMembersFromPermissionGroupCallback(
    TIMCommunityRemoveMembersFromPermissionGroupCallback cb, const void* user_data);

/**
 * 3.10 增加话题权限到权限组中
 * @param cb
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityAddTopicPermissionCallback(TIMCommunityAddTopicPermissionCallback cb,
                                                       const void* user_data);

/**
 * 3.11 从权限组删除的话题权限
 * @param cb
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityDeleteTopicPermissionCallback(TIMCommunityDeleteTopicPermissionCallback cb,
                                                          const void* user_data);

/**
 * 3.12 权限组中的话题权限修改
 * @param cb
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetCommunityModifyTopicPermissionCallback(TIMCommunityModifyTopicPermissionCallback cb,
                                                          const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                           四. 社群话题功能相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 4.1 创建支持话题的社群
 *
 * @param json_group_create_param 创建群组的参数Json字符串, Json Key 请参考 @ref CreateGroupParam
 * @param cb 创建群组成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 创建社群时可以指定群ID，若未指定时IM通讯云服务器会生成一个唯一的ID，以便后续操作，群组ID通过创建群组时传入的回调返回
 * - 创建支持话题的社群，一定要填写 kTIMCreateGroupIsSupportTopic 字段并设置为 true
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_group_member_array(Json::arrayValue);
 *
 * Json::Value json_value_param;
 * json_value_param[kTIMCreateGroupParamGroupId] = "first group id";
 * json_value_param[kTIMCreateGroupParamGroupType] = kTIMGroup_Public;
 * json_value_param[kTIMCreateGroupParamGroupName] = "first group name";
 * json_value_param[kTIMCreateGroupParamGroupMemberArray] = json_group_member_array;
 *
 * json_value_param[kTIMCreateGroupParamNotification] = "group notification";
 * json_value_param[kTIMCreateGroupParamIntroduction] = "group introduction";
 * json_value_param[kTIMCreateGroupParamFaceUrl] = "group face url";
 * json_value_param[kTIMCreateGroupParamMaxMemberCount] = 2000;
 * json_value_param[kTIMCreateGroupParamAddOption] = kTIMGroupAddOpt_Any;
 * json_value_param[kTIMCreateGroupParamApproveOption] = kTIMGroupAddOpt_Any;
 * json_value_param[kTIMCreateGroupIsSupportTopic] = true;
 *
 * const void* user_data = nullptr; // 回调函数回传
 * int ret = TIMGroupCreate(json_value_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *    if (ERR_SUCC != code) {
 *         // 创建群组失败
 *         return;
 *     }
 *
 *     // 创建群组成功 解析Json获取创建后的GroupID
 * }, user_data);
 * if (TIM_SUCC != ret) {
 *     // TIMGroupCreate 接口调用失败
 * }
 *
 * // json_value_param.toStyledString().c_str() 得到 json_group_create_param JSON 字符串如下
 * {
 *    "create_group_param_add_option" : 2,
 *    "create_group_param_face_url" : "group face url",
 *    "create_group_param_group_id" : "first group id",
 *    "create_group_param_group_member_array" : [],
 *    "create_group_param_group_name" : "first group name",
 *    "create_group_param_group_type" : 0,
 *    "create_group_param_introduction" : "group introduction",
 *    "create_group_param_max_member_num" : 2000,
 *    "create_group_param_notification" : "group notification",
 *    "create_group_param_is_support_topic" : true
 * }
 * @endcode
 */
TIM_API int TIMCommunityCreate(const char* json_group_create_param, TIMCommCallback cb, const void* user_data);
/**
 * 4.2 获取当前用户已经加入的支持话题的社群列表
 *
 * @param cb 获取社群列表的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   TIMCommunityGetJoinedCommunityList([](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityGetJoinedCommunityList code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityGetJoinedCommunityList(TIMCommCallback cb, const void* user_data);

/**
 * 4.3 创建话题
 *
 * @param group_id 群 ID
 * @param json_topic_info 话题信息，Json Key 请参考 @ref TIMCommunityTopicInfo
 * @param cb 创建话题的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = GetCommunityID();
 *
 *   json::Object topic_info;
 *   topic_info[kTIMCommunityTopicInfoTopicID] = GetTopicID();
 *   topic_info[kTIMCommunityTopicInfoTopicName] = "topic name";
 *
 *   TIMCommunityCreateTopicInCommunity(group_id.c_str(), json::Serialize(topic_info).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityCreateTopicInCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityCreateTopicInCommunity(const char* group_id, const char* json_topic_info, TIMCommCallback cb,
                                               const void* user_data);

/**
 * 4.4 删除话题
 *
 * @param group_id 群 ID
 * @param json_topic_id_array 话题 ID 列表
 * @param cb 删除话题的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = GetCommunityID();
 *
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityDeleteTopicFromCommunity(group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityDeleteTopicFromCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityDeleteTopicFromCommunity(const char* group_id, const char* json_topic_id_array,
                                                 TIMCommCallback cb, const void* user_data);

/**
 * 4.5 修改话题信息
 *
 * @param json_topic_info 话题信息， Json Key 请参考 @ref TIMGroupTopicInfo
 * @param cb 修改话题信息的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   json::Object topic_info;
 *   topic_info[kTIMCommunityTopicInfoTopicID] = GetTopicID();
 *   topic_info[kTIMCommunityTopicInfoTopicName] = "topic name";
 *   topic_info[kTIMCommunityTopicInfoNotification] = "topic notification";
 *   topic_info[kTIMCommunityTopicInfoModifyFlag] = kTIMCommunityTopicModifyInfoFlag_Name |
 *       kTIMCommunityTopicModifyInfoFlag_Notification;
 *
 *   TIMCommunitySetTopicInfo(json::Serialize(topic_info).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunitySetTopicInfo code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunitySetTopicInfo(const char* json_topic_info, TIMCommCallback cb, const void* user_data);

/**
 * 4.6 获取话题列表
 *
 * @param group_id 群 ID
 * @param json_topic_id_array 话题 ID 列表
 * @param cb 获取话题的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note: json_topic_id_array 传空时，获取此社群下的所有话题列表
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = GetCommunityID();
 *
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityGetTopicInfoList(group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityGetTopicInfoList code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityGetTopicInfoList(const char* group_id, const char* json_topic_id_array, TIMCommCallback cb,
                                         const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                       五. 权限组 API
//
/////////////////////////////////////////////////////////////////////////////////

/**
 * 5.1 创建权限组（7.8 及其以上版本支持）
 * @param json_permission_group_info 权限组信息，Json Key 请参考 @ref PermissionGroupInfo
 * @param cb 创建权限组的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   json::Object permission_group_info;
 *   permission_group_info[kTIMCommunityGroupID] = "xxx";
 *   permission_group_info[kTIMPermissionGroupName] = "permission group name";
 *
 *   TIMCommunityCreatePermissionGroupInCommunity(json::Serialize(permission_group_info).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityCreatePermissionGroupInCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityCreatePermissionGroupInCommunity(const char* json_permission_group_info, TIMCommCallback cb,
                                                         const void* user_data);

/**
 * 5.2 删除权限组（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param json_permission_group_id_array 权限组 ID 列表
 * @param cb 删除权限组的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = GetCommunityID();
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityDeletePermissionGroupFromCommunity(group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityDeletePermissionGroupFromCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityDeletePermissionGroupFromCommunity(const char* group_id,
                                                           const char* json_permission_group_id_array,
                                                           TIMCommCallback cb, const void* user_data);

/**
 * 5.3 修改权限组信息（7.8 及其以上版本支持）
 * @param json_permission_group_info 权限组信息，Json Key 请参考 @ref PermissionGroupInfo
 * @param cb 修改权限组的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐
 *
 * __示例__
 * @code{.cpp}
 *   json::Object permission_group_info;
 *   permission_group_info[kTIMCommunityGroupID] = "xxx";
 *   permission_group_info[kTIMPermissionGroupID] = "xxx";
 *   permission_group_info[kTIMPermissionGroupName] = "permission group name";
 *   permission_group_info[kTIMGroupPermission] = V2TIMCommunityPermissionValue::V2TIM_COMMUNITY_PERMISSION_MANAGE_GROUP_INFO | V2TIMCommunityPermissionValue::V2TIM_COMMUNITY_PERMISSION_MANAGE_GROUP_MEMBER;
 *
 *   TIMCommunityModifyPermissionGroupInfoInCommunity(json::Serialize(permission_group_info).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityModifyPermissionGroupInfoInCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityModifyPermissionGroupInfoInCommunity(const char* json_permission_group_info, TIMCommCallback cb,
                                                             const void* user_data);

/**
 * 5.4 获取已加入的权限组列表（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param cb 获取已加入的权限组列表的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   TIMCommunityGetJoinedPermissionGroupListInCommunity([](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityGetJoinedPermissionGroupListInCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityGetJoinedPermissionGroupListInCommunity(const char* group_id,
                                                                TIMCommCallback cb, const void* user_data);

/**
 * 5.5 获取权限组列表（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param json_permission_group_id_array 权限组 ID 列表
 * @param cb 获取权限组列表的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note:
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 * - json_permission_group_id_array 为空时，获取所有的权限组列表；不为空时，获取指定的权限组列表。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityGetPermissionGroupListInCommunity(group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityGetPermissionGroupListInCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityGetPermissionGroupListInCommunity(const char* group_id,
                                                          const char* json_permission_group_id_array,
                                                          TIMCommCallback cb, const void* user_data);

/**
 * 5.6 向社群权限组添加成员（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param permission_group_id 权限组 ID
 * @param json_member_id_array 群成员 ID 列表
 * @param cb 添加成员的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *   const std::string permission_group_id = "xxx";
 *
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityAddCommunityMembersToPermissionGroup(group_id.c_str(), permission_group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityAddCommunityMembersToPermissionGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityAddCommunityMembersToPermissionGroup(const char* group_id, const char* permission_group_id,
                                                             const char* json_member_id_array, TIMCommCallback cb,
                                                             const void* user_data);

/**
 * 5.7 从社群权限组删除成员（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param permission_group_id 权限组 ID
 * @param json_member_id_array 群成员 ID 列表
 * @param cb 删除成员的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *   const std::string permission_group_id = "xxx";
 *
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityRemoveCommunityMembersFromPermissionGroup(group_id.c_str(), permission_group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityRemoveCommunityMembersFromPermissionGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityRemoveCommunityMembersFromPermissionGroup(const char* group_id, const char* permission_group_id,
                                                                  const char* json_member_id_array, TIMCommCallback cb,
                                                                  const void* user_data);

/**
 * 5.8 获取社群权限组成员列表（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param permission_group_id 权限组 ID
 * @param json_member_id_array 群成员 ID 列表
 * @param cb 获取社群权限组成员列表的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *   const std::string permission_group_id = "xxx";
 *   const std::string next_cursor = "";
 *
 *   TIMCommunityGetCommunityMemberListInPermissionGroup(group_id.c_str(), permission_group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityGetCommunityMemberListInPermissionGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityGetCommunityMemberListInPermissionGroup(const char* group_id, const char* permission_group_id,
                                                                const char* next_cursor, TIMCommCallback cb,
                                                                const void* user_data);

/**
 * 5.9 向权限组添加话题权限（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param permission_group_id 权限组 ID
 * @param json_topic_permission_map 话题权限
 * @param cb 添加话题权限的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *   const std::string permission_group_id = "xxx";
 *
 *   json::Array json_array;
 *   json::Object json_obj;
 *   json_obj[kTIMTopicPermissionKey] = "topic id";
 *   json_obj[kTIMTopicPermissionValue] = V2TIMTopicPermissionValue::V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC | V2TIMTopicPermissionValue::V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC_PERMISSION;
 *   json_array.push_back(json_obj);
 *
 *   TIMCommunityAddTopicPermissionToPermissionGroup(group_id.c_str(), permission_group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityAddTopicPermissionToPermissionGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityAddTopicPermissionToPermissionGroup(const char* group_id, const char* permission_group_id,
                                                            const char* json_topic_permission_map, TIMCommCallback cb,
                                                            const void* user_data);

/**
 * 5.10 从权限组中删除话题权限（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param permission_group_id 权限组 ID
 * @param json_topic_id_array 话题 ID 列表
 * @param cb 删除话题权限的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *   const std::string permission_group_id = "xxx";
 *
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityDeleteTopicPermissionFromPermissionGroup(group_id.c_str(), permission_group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityDeleteTopicPermissionFromPermissionGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityDeleteTopicPermissionFromPermissionGroup(const char* group_id, const char* permission_group_id,
                                                                 const char* json_topic_id_array, TIMCommCallback cb,
                                                                 const void* user_data);

/**
 * 5.11 修改权限组中的话题权限（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param permission_group_id 权限组 ID
 * @param json_topic_permission_map 话题权限
 * @param cb 修改权限组中的话题权限的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *   const std::string permission_group_id = "xxx";
 *
 *   json::Array json_array;
 *   json::Object json_obj;
 *   json_obj[kTIMTopicPermissionKey] = "topic id";
 *   json_obj[kTIMTopicPermissionValue] = V2TIMTopicPermissionValue::V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC | V2TIMTopicPermissionValue::V2TIM_TOPIC_PERMISSION_MANAGE_TOPIC_PERMISSION;
 *   json_array.push_back(json_obj);
 *
 *   TIMCommunityModifyTopicPermissionInPermissionGroup(group_id.c_str(), permission_group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityModifyTopicPermissionInPermissionGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityModifyTopicPermissionInPermissionGroup(const char* group_id, const char* permission_group_id,
                                                               const char* json_topic_permission_map,
                                                               TIMCommCallback cb, const void* user_data);

/**
 * 5.12 获取权限组中的话题权限（7.8 及其以上版本支持）
 * @param group_id 社群 ID
 * @param permission_group_id 权限组 ID
 * @param json_topic_id_array 话题 ID 列表
 * @param cb 获取权限组中的话题权限的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return  int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = "xxx";
 *   const std::string permission_group_id = "xxx";
 *
 *   json::Array json_array;
 *   json_array.push_back("id1");
 *   json_array.push_back("id2");
 *
 *   TIMCommunityGetTopicPermissionInPermissionGroup(group_id.c_str(), permission_group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMCommunityGetTopicPermissionInPermissionGroup code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMCommunityGetTopicPermissionInPermissionGroup(const char* group_id, const char* permission_group_id,
                                                            const char* json_topic_id_array, TIMCommCallback cb,
                                                            const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                       六. 社群 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 6.1 TopicInfo(话题信息)
// string, 读写, 话题 ID, 只能在创建话题或者修改话题信息的时候设置。组成方式为：社群 ID + @TOPIC#_xxx，例如社群 ID 为 @TGS#_123，则话题 ID 为 @TGS#_123@TOPIC#_xxx
static const char* kTIMCommunityTopicInfoTopicID = "group_topic_info_topic_id";
// string, 读写, 话题名称
static const char* kTIMCommunityTopicInfoTopicName = "group_topic_info_topic_name";
// string, 读写, 话题介绍
static const char* kTIMCommunityTopicInfoIntroduction = "group_topic_info_introduction";
// string, 读写, 话题公告
static const char* kTIMCommunityTopicInfoNotification = "group_topic_info_notification";
// string, 读写, 话题头像
static const char* kTIMCommunityTopicInfoFaceURL = "group_topic_info_topic_face_url";
// bool, 读写, 话题全员禁言
static const char* kTIMCommunityTopicInfoIsAllMuted = "group_topic_info_is_all_muted";
// uint32, 只读, 当前用户在话题中的禁言时间
static const char* kTIMCommunityTopicInfoSelfMuteTime = "group_topic_info_self_mute_time";
// string, 读写, 话题自定义字段
static const char* kTIMCommunityTopicInfoCustomString = "group_topic_info_custom_string";
// uint @ref TIMReceiveMessageOpt, 只读, 话题消息接收选项，修改话题消息接收选项请调用 @ref TIMMsgSetGroupReceiveMessageOpt 接口
static const char* kTIMCommunityTopicInfoRecvOpt = "group_topic_info_recv_opt";
// string, 读写, 话题草稿
static const char* kTIMCommunityTopicInfoDraftText = "group_topic_info_draft_text";
// uint64, 只读, 话题消息未读数量
static const char* kTIMCommunityTopicInfoUnreadCount = "group_topic_info_unread_count";
// object @ref Message, 只读, 话题 lastMessage
static const char* kTIMCommunityTopicInfoLastMessage = "group_topic_info_last_message";
// uin64, 只读, 话题已读消息的 sequence，从 7.8 版本开始支持
static const char* kTIMCommunityTopicInfoReadSequence = "topic_info_read_sequence";
// array @ref GroupAtInfo, 只读, 话题 at 信息列表
static const char* kTIMCommunityTopicInfoGroupAtInfoArray = "group_topic_info_group_at_info_array";
// uint @ref TIMGroupModifyInfoFlag, 只写(必填), 修改标识,可设置多个值按位或
static const char* kTIMCommunityTopicInfoModifyFlag = "group_modify_info_param_modify_flag";
// uint32, 只读, 话题创建时间
static const char* kTIMCommunityTopicCreateTime = "topic_create_time";
// uint64, 读写, 话题默认权限, 7.8 版本开始支持。群成员在没有加入任何权限组时的默认权限，仅在社群资料 V2TIMGroupInfo 中 enablePermissionGroup = true 打开权限组之后生效
static const char* kTIMCommunityTopicInfoDefaultPermissions = "default_permissions";

//------------------------------------------------------------------------------
// 6.2 TopicOperationResult(话题操作结果)
// int, 只读, 结果 0：成功；非0：失败
static const char* kTIMCommunityTopicOperationResultErrorCode = "group_topic_operation_result_error_code";
// string, 只读, 如果删除失败，会返回错误信息
static const char* kTIMCommunityTopicOperationResultErrorMessage = "group_topic_operation_result_error_message";
// string, 只读, 如果删除成功，会返回对应的 topicID
static const char* kTIMCommunityTopicOperationResultTopicID = "group_topic_operation_result_topic_id";

//------------------------------------------------------------------------------
// 6.3 TopicInfoResult(获取话题信息的结果)
// int, 只读, 结果 0：成功；非0：失败
static const char* kTIMCommunityTopicInfoResultErrorCode = "group_topic_info_result_error_code";
// string, 只读, 如果删除失败，会返回错误信息
static const char* kTIMCommunityTopicInfoResultErrorMessage = "group_topic_info_result_error_message";
// object @ref TIMGroupTopicInfo, 只读, 如果获取成功，会返回对应的 @ref TIMGroupTopicInfo 信息
static const char* kTIMCommunityTopicInfoResultTopicInfo = "group_topic_info_result_topic_info";

//------------------------------------------------------------------------------
// 6.4 PermissionGroupInfo(权限组信息)
// string, 读写, 社群 ID。
static const char* kTIMCommunityGroupID = "community_group_id";
// string, 读写, 权限组 ID, 只能在创建话题或者修改话题信息的时候设置。
static const char* kTIMPermissionGroupID = "permission_group_id";
// string, 读写, 权限组名称。
static const char* kTIMPermissionGroupName = "permission_group_name";
// string, 读写, 权限组自定义数据。
static const char* kTIMPermissionCustomData = "permission_custom_data";
// uint64, 读写, 社群权限。
static const char* kTIMGroupPermission = "group_permission";
// uint64, 只读, 权限组人数。
static const char* kTIMPermissionGroupMemberCount = "permission_group_member_count";
// uint @ref TIMPermissionGroupModifyInfoFlag, 只写(必填), 修改标识,可设置多个值按位或
static const char* kTIMPermissionGroupModifyInfoFlag = "permission_group_modify_info_flag";

//------------------------------------------------------------------------------
// 6.5 TopicPermissionMap(话题权限 map)
// string, 读写, 自定义字段的 key
static const char* kTIMTopicPermissionKey = "topic_permission_key";
// uint64, 读写, 自定义字段的 value
static const char* kTIMTopicPermissionValue = "topic_permission_value";

//------------------------------------------------------------------------------
// 6.6 PermissionGroupInfoResult(获取权限组信息的结果)
// int, 只读, 结果 0：成功；非0：失败
static const char* kTIMPermissionGroupInfoResultErrorCode = "permission_group_info_result_error_code";
// string, 只读, 如果删除失败，会返回错误信息
static const char* kTIMPermissionGroupInfoResultErrorMessage = "permission_group_info_result_error_message";
// object @ref TIMGroupTopicInfo, 只读, 如果获取成功，会返回对应的 @ref TIMGroupTopicInfo 信息
static const char* kTIMPermissionGroupInfoResult = "permission_group_info_result";

//------------------------------------------------------------------------------
// 6.7 PermissionGroupOperationResult(权限组操作结果)
// int, 只读, 结果 0：成功；非0：失败
static const char* kTIMPermissionGroupOperationResultErrorCode = "permission_group_operation_result_error_code";
// string, 只读, 如果删除失败，会返回错误信息
static const char* kTIMPermissionGroupOperationResultErrorMessage = "permission_group_operation_result_error_message";
// string, 只读, 如果删除成功，会返回对应的 permissionGroupID
static const char* kTIMPermissionGroupOperationResultID = "permission_group_operation_result_id";

//------------------------------------------------------------------------------
// 6.8 PermissionGroupMemberOperationResult(权限组成员处理结果)
// string, 只读, 被邀请加入权限组的用户 ID
static const char* kTIMPermissionGroupMemberOperationResultIdentifier = "permission_group_member_operation_result_identifier";
// uint @ref TIMPermissionGroupMemberOperationResult, 只读, 处理结果
static const char* kTIMPermissionGroupMemberOperationResultErrorCode = "permission_group_member_operation_result_error_code";

//------------------------------------------------------------------------------
// 6.9 PermissionGroupMemberInfoResult(获取权限组成员列表接口的返回)
// string, 只读, 下一次拉取的标志, server返回空表示没有更多的数据,否则在下次获取数据时填入这个标志
static const char* kTIMPermissionGroupMemberInfoResultNextCursor = "permission_group_member_info_result_next_cursor";
// array @ref GroupMemberInfo, 只读, 成员信息列表
static const char* kTIMPermissionGroupMemberInfoResultArray = "permission_group_member_info_result_array";

//------------------------------------------------------------------------------
// 6.10 TopicPermissionResult(获取话题权限列表接口的返回)
// int, 只读, 结果 0：成功；非0：失败
static const char* kTIMTopicPermissionResultErrorCode = "topic_permission_result_error_code";
// string, 只读, 如果获取失败，会返回错误信息
static const char* kTIMTopicPermissionResultErrorMessage = "topic_permission_result_error_message";
// string, 只读, 话题 ID。
static const char* kTIMTopicPermissionResultTopicID = "topic_permission_result_topic_id";
// uint64, 只读, 话题 权限。
static const char* kTIMTopicPermissionResultTopicPermission = "topic_permission_result_topic_permission";
// string, 只读, 社群 ID。
static const char* kTIMTopicPermissionResultGroupID = "topic_permission_result_group_id";
// string, 只读, 权限组 ID。
static const char* kTIMTopicPermissionResultPermissionGroupID = "topic_permission_result_permission_group_id";

//------------------------------------------------------------------------------
// 6.11 PermissionGroupCallback(权限组相关监听回调)
// array, 只读, 话题权限 map
static const char* kTIMTopicPermissionMap = "topic_permission_map";
// array, 只读, 删除话题权限的话题 id 列表
static const char* kTIMTopicIDList = "topic_id_list";
// array, 只读，权限组中添加或者删除成员的 id 列表
static const char* kTIMMemberIDList = "member_id_list";

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_COMMUNITY_MANAGER_H_
