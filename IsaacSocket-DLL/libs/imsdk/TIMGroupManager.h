// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_GROUP_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_GROUP_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 群组接口，包含建群、加群、退群、群成员邀请、非群成员申请进群等功能
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
//                        一. 群组功能相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 群组信息修改的类型
enum TIMGroupTipGroupChangeFlag {
    // 未知的修改
    kTIMGroupTipChangeFlag_Unknown = 0x0,
    // 修改群组名称
    kTIMGroupTipChangeFlag_Name = 0x1,
    // 修改群简介
    kTIMGroupTipChangeFlag_Introduction = 0x2,
    // 修改群公告
    kTIMGroupTipChangeFlag_Notification = 0x3,
    // 修改群头像URL
    kTIMGroupTipChangeFlag_FaceUrl = 0x4,
    // 修改群所有者
    kTIMGroupTipChangeFlag_Owner = 0x5,
    // 修改群自定义信息
    kTIMGroupTipChangeFlag_Custom = 0x6,
    // 群属性变更 (新增)
    kTIMGroupTipChangeFlag_Attribute = 0x7,
    // 全员禁言字段变更
    kTIMGroupTipChangeFlag_ShutupAll = 0x08,
    // 话题自定义字段
    kTIMGroupTipChangeFlag_TopicCustomData = 0x09,
    // 消息接收选项变更
    kTIMGroupTipChangeFlag_MessageReceiveOpt = 0x0A,
    // 申请加群方式下管理员审批选项变更
    kTIMGroupTipChangeFlag_GroupAddOpt = 0x0B,
    // 邀请进群方式下管理员审批选项变更
    kTIMGroupTipChangeFlag_GroupApproveOpt = 0x0C,
    // 开启权限组功能，只支持社群，7.8 版本开始支持
    kTIMGroupTipChangeFlag_EnablePermissionGroup = 0x0D,
    // 群默认权限，只支持社群，7.8 版本开始支持
    kTIMGroupTipChangeFlag_DefaultPermissions = 0x0E,
};

// 1.2 群组系统消息类型
enum TIMGroupTipType {
    // 无效的群提示
    kTIMGroupTip_None,
    // 邀请加群提示
    kTIMGroupTip_Invite,
    // 退群提示
    kTIMGroupTip_Quit,
    // 踢人提示
    kTIMGroupTip_Kick,
    // 设置管理员提示
    kTIMGroupTip_SetAdmin,
    // 取消管理员提示
    kTIMGroupTip_CancelAdmin,
    // 群信息修改提示
    kTIMGroupTip_GroupInfoChange,
    // 群成员信息修改提示
    kTIMGroupTip_MemberInfoChange,
    // 群成员标记修改提示
    kTIMGroupTip_MemberMarkChange,
    // 话题资料修改提示
    kTIMGroupTip_TopicInfoChange,
};

// 1.3 群组类型
enum TIMGroupType {
    // 公开群（Public），成员上限 2000 人，任何人都可以申请加群，但加群需群主或管理员审批，适合用于类似 QQ 中由群主管理的兴趣群。
    kTIMGroup_Public,
    // 工作群（Work），成员上限 200 人，不支持由用户主动加入，需要他人邀请入群，适合用于类似微信中随意组建的工作群（对应老版本的 Private 群）。
    kTIMGroup_Private,
    // 会议群（Meeting），成员上限 6000 人，任何人都可以自由进出，且加群无需被审批，适合用于视频会议和在线培训等场景（对应老版本的 ChatRoom 群）。
    kTIMGroup_ChatRoom,
    // 在线成员广播大群，推荐使用 直播群（AVChatRoom）
    kTIMGroup_BChatRoom,
    // 直播群（AVChatRoom），人数无上限，任何人都可以自由进出，消息吞吐量大，适合用作直播场景中的高并发弹幕聊天室。
    kTIMGroup_AVChatRoom,
    // 社群（Community），成员上限 100000 人，任何人都可以自由进出，且加群无需被审批，适合用于知识分享和游戏交流等超大社区群聊场景。5.8 版本开始支持，需要您购买旗舰版套餐。
    kTIMGroup_Community,
};

// 1.4 群组加群选项
enum TIMGroupAddOption {
    // 禁止加群
    kTIMGroupAddOpt_Forbid = 0,
    // 需要管理员审批
    kTIMGroupAddOpt_Auth = 1,
    // 任何人都可以加群
    kTIMGroupAddOpt_Any = 2,
    // 未定义
    kTIMGroupAddOpt_Unknown = 3,
};

// 1.5 群组成员角色类型
enum TIMGroupMemberRole {
    // 未定义
    kTIMMemberRole_None = 0,
    // 群成员
    kTIMMemberRole_Normal = 200,
    // 管理员
    kTIMMemberRole_Admin = 300,
    // 超级管理员(群主）
    kTIMMemberRole_Owner = 400,
};

// 1.6 群搜索 Field 的枚举
enum TIMGroupSearchFieldKey {
    // 群 ID
    kTIMGroupSearchFieldKey_GroupId = 0x01,
    // 群名称
    kTIMGroupSearchFieldKey_GroupName = 0x01 << 1,
};

// 1.7 设置(修改)群组信息的类型
enum TIMGroupModifyInfoFlag {
    // 未定义
    kTIMGroupModifyInfoFlag_None = 0x00,
    // 修改群组名称
    kTIMGroupModifyInfoFlag_Name = 0x01,
    // 修改群公告
    kTIMGroupModifyInfoFlag_Notification = 0x01 << 1,
    // 修改群简介
    kTIMGroupModifyInfoFlag_Introduction = 0x01 << 2,
    // 修改群头像URL
    kTIMGroupModifyInfoFlag_FaceUrl = 0x01 << 3,
    // 申请加群管理员审批选项
    kTIMGroupModifyInfoFlag_AddOption = 0x01 << 4,
    // 修改群最大成员数
    kTIMGroupModifyInfoFlag_MaxMemberNum = 0x01 << 5,
    // 修改群是否可见
    kTIMGroupModifyInfoFlag_Visible = 0x01 << 6,
    // 修改群是否允许被搜索
    kTIMGroupModifyInfoFlag_Searchable = 0x01 << 7,
    // 修改群是否全体禁言
    kTIMGroupModifyInfoFlag_ShutupAll = 0x01 << 8,
    // 修改群自定义信息
    kTIMGroupModifyInfoFlag_Custom = 0x01 << 9,
    // 话题自定义字段
    kTIMGroupTopicModifyInfoFlag_CustomString = 0x01 << 11,
    // 邀请进群管理员审批选项
    kTIMGroupModifyInfoFlag_ApproveOption = 0x01 << 12,
    // 开启权限组功能，仅支持社群，7.8 版本开始支持
    kTIMGroupModifyInfoFlag_EnablePermissionGroup = 0x1 << 13,
    // 群默认权限，仅支持社群，7.8 版本开始支持
    kTIMGroupModifyInfoFlag_DefaultPermissions = 0x1 << 14,
    // 修改群主
    kTIMGroupModifyInfoFlag_Owner = 0x01 << 31,
};

// 1.8 群成员搜索 Field 的枚举
enum TIMGroupMemberSearchFieldKey {
    // 用户 ID
    kTIMGroupMemberSearchFieldKey_Identifier = 0x01,
    // 昵称
    kTIMGroupMemberSearchFieldKey_NickName = 0x01 << 1,
    // 备注
    kTIMGroupMemberSearchFieldKey_Remark = 0x01 << 2,
    // 名片
    kTIMGroupMemberSearchFieldKey_NameCard = 0x01 << 3,
};

// 1.9 设置(修改)群成员信息的类型
enum TIMGroupMemberModifyInfoFlag {
    // 未定义
    kTIMGroupMemberModifyFlag_None = 0x00,
    // 修改消息接收选项
    kTIMGroupMemberModifyFlag_MsgFlag = 0x01,
    // 修改成员角色
    kTIMGroupMemberModifyFlag_MemberRole = 0x01 << 1,
    // 修改禁言时间
    kTIMGroupMemberModifyFlag_ShutupTime = 0x01 << 2,
    // 修改群名片
    kTIMGroupMemberModifyFlag_NameCard = 0x01 << 3,
    // 修改群成员自定义信息
    kTIMGroupMemberModifyFlag_Custom = 0x01 << 4,
};

// 1.10 群成员操作结果
enum HandleGroupMemberResult {
    // 失败
    kTIMGroupMember_HandledErr,
    // 成功
    kTIMGroupMember_HandledSuc,
    // 已是群成员
    kTIMGroupMember_Included,
    // 已发送邀请
    kTIMGroupMember_Invited,
};

// 1.11 群未决请求类型
enum TIMGroupPendencyType {
    // 需要群主或管理员审批的申请加群请求
    kTIMGroupPendency_GroupJoinNeedApprovedByAdmin = 0,
    // 需要被邀请者同意的邀请入群请求
    kTIMGroupPendency_GroupInviteNeedApprovedByInvitee = 1,
    // 需要群主或管理员审批的邀请入群请求
    kTIMGroupPendency_GroupInviteNeedApprovedByAdmin = 2,
};

// 1.12 群未决处理状态
enum TIMGroupPendencyHandle {
    // 未处理
    kTIMGroupPendency_NotHandle = 0,
    // 他人处理
    kTIMGroupPendency_OtherHandle = 1,
    // 操作方处理
    kTIMGroupPendency_OperatorHandle = 2,
};

// 1.13 群未决处理操作类型
enum TIMGroupPendencyHandleResult {
    // 拒绝
    kTIMGroupPendency_Refuse = 0,
    // 同意
    kTIMGroupPendency_Accept = 1,
};


/////////////////////////////////////////////////////////////////////////////////
//
//                             二. 群组事件回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 群事件回调
 *
 * @param json_group_tip 群提示列表，Json Key 详情请参考 @ref GroupTipsElem
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * @note
 * 群组系统消息事件包括 加入群、退出群、踢出群、设置管理员、取消管理员、群资料变更、群成员资料变更。此消息是针对所有群组成员下发的
 */
typedef void (*TIMGroupTipsEventCallback)(const char* json_group_tip, const void* user_data);

/**
 * 2.2 群属性变更回调
 *
 * @param json_group_attribute_array 变更的群属性列表, Json Key 请参考 @ref GroupAttributes
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __json_group_attribute_array 的示例 (json key 请参考 @ref GroupAttributes)__
 * @code{.cpp}
 * [{"group_attribute_key":"attribute_key1","group_attribute_value":"attribute_value1"}]
 * @endcode
 */
typedef void (*TIMGroupAttributeChangedCallback)(const char *group_id, const char* json_group_attribute_array, const void* user_data);

/**
 * 2.3 群计数器变更的回调
 *
 * @param group_id 群组 ID
 * @param group_counter_key 变更的群计数器的 key
 * @param group_counter_new_value 变更后的群计数器的 value
 */
typedef void (*TIMGroupCounterChangedCallback)(const char *group_id, const char *group_counter_key, int64_t group_counter_new_value, const void *user_data);

/**
 * 2.4 话题创建的回调
 *
 * @param topic_id 话题 ID
 */
typedef void (*TIMGroupTopicCreatedCallback)(const char *group_id, const char *topic_id, const void* user_data);

/**
 * 2.5 话题被删除的回调
 *
 * @param group_id 话题所属的社群 ID
 * @param topic_id_array 话题列表
 */
typedef void (*TIMGroupTopicDeletedCallback)(const char *group_id, const char *topic_id_array, const void* user_data);

/**
 * 2.6 话题更新的回调
 *
 * @param topic_info 话题信息，参见 TIMGroupTopicInfo 类型
 */
typedef void (*TIMGroupTopicChangedCallback)(const char *group_id, const char *topic_info, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                            三. 注册群组事件回调 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 设置群组系统消息回调
 * 
 * @param cb 群消息回调，请参考 @ref TIMGroupTipsEventCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 群组系统消息事件包括 加入群、退出群、踢出群、设置管理员、取消管理员、群资料变更、群成员资料变更。此消息是针对所有群组成员下发的
 */
TIM_API void TIMSetGroupTipsEventCallback(TIMGroupTipsEventCallback cb, const void* user_data);

/**
 * 3.2 设置群组属性变更回调
 * 
 * @param cb 群组属性变更回调，请参考 @ref TIMGroupAttributeChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 某个已加入的群的属性被修改了，会返回所在群组的所有属性（该群所有的成员都能收到）
 */
TIM_API void TIMSetGroupAttributeChangedCallback(TIMGroupAttributeChangedCallback cb, const void* user_data);

/**
 * 3.3 设置群计数器变更回调
 * 
 * @param cb 群计数器变更回调，请参考 @ref TIMGroupCounterChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 某个已加入的群的计数器被修改了，会返回当前变更的群计数器（该群所有的成员都能收到）
 */
TIM_API void TIMSetGroupCounterChangedCallback(TIMGroupCounterChangedCallback cb, const void* user_data);

/**
 * 3.4 话题创建
 * 
 * @param cb 群组属性变更回调，请参考 @ref TIMGroupTopicCreatedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetGroupTopicCreatedCallback(TIMGroupTopicCreatedCallback cb, const void* user_data);

/**
 * 3.5 话题被删除
 * 
 * @param cb 群组属性变更回调，请参考 @ref TIMGroupTopicDeletedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetGroupTopicDeletedCallback(TIMGroupTopicDeletedCallback cb, const void* user_data);

/**
 * 3.6 话题更新
 * 
 * @param cb 群组属性变更回调，请参考 @ref TIMGroupTopicChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetGroupTopicChangedCallback(TIMGroupTopicChangedCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                             四. 群管理相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 4.1 创建群组
 *
 * @param json_group_create_param 创建群组的参数Json字符串, Json Key 请参考 @ref CreateGroupParam
 * @param cb 创建群组成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 创建群组时可以指定群ID，若未指定时IM通讯云服务器会生成一个唯一的ID，以便后续操作，群组ID通过创建群组时传入的回调返回
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
 *    "create_group_param_notification" : "group notification"
 * }
 * @endcode
 */
TIM_API int TIMGroupCreate(const char* json_group_create_param, TIMCommCallback cb, const void* user_data);

/**
 * 4.2 删除(解散)群组
 *
 * @param group_id 要删除的群组ID
 * @param cb 删除群组成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 权限说明：
 *  - 对于私有群，任何人都无法解散群组。
 *  - 对于公开群、聊天室和直播大群，群主可以解散群组。
 * 删除指定群组 group_id 的接口，删除成功与否可根据回调cb的参数判断。
 */
TIM_API int TIMGroupDelete(const char* group_id, TIMCommCallback cb, const void* user_data);

/**
 * 4.3 申请加入群组
 *
 * @param group_id 要加入的群组ID
 * @param hello_msg 申请理由（选填）
 * @param cb 申请加入群组成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 权限说明：
 *  - 私有群不能由用户主动申请入群。
 *  - 公开群和聊天室可以主动申请进入。
 *  - 如果群组设置为需要审核，申请后管理员和群主会受到申请入群系统消息，需要等待管理员或者群主审核，如果群主设置为任何人可加入，则直接入群成功。
 *  - 直播大群可以任意加入群组。
 * 申请加入指定群组 group_id 的接口，申请加入的操作成功与否可根据回调cb的参数判断。
 */
TIM_API int TIMGroupJoin(const char* group_id, const char* hello_msg, TIMCommCallback cb, const void* user_data);

/**
 * 4.4 退出群组
 *
 * @param group_id 要退出的群组ID
 * @param cb 退出群组成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 权限说明：
 *  - 对于私有群，全员可退出群组。
 *  - 对于公开群、聊天室和直播大群，群主不能退出。
 * 退出指定群组group_id的接口，退出成功与否可根据回调cb的参数判断。
 */
TIM_API int TIMGroupQuit(const char* group_id, TIMCommCallback cb, const void* user_data);

/**
 * 4.5 获取当前用户已经加入的群列表
 *
 * @param cb 获取已加入群组列表成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 权限说明：
 *  - 此接口可以获取自己所加入的群列表
 *  - 此接口只能获得加入的部分直播大群的列表。
 * 此接口用于获取当前用户已加入的群组列表，返回群组的基础信息。具体返回的群组信息字段参考[GroupBaseInfo, GroupDetailInfo]()
 */
TIM_API int TIMGroupGetJoinedGroupList(TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                            五. 群资料管理相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 5.1 获取群组信息列表
 *
 * @param json_group_getinfo_param 获取群组信息列表参数的 Json 字符串
 * @param cb 获取群组信息列表成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 此接口用于获取指定群ID列表的群详细信息。具体返回的群组详细信息字段参考 @ref GroupDetailInfo, @ref GroupBaseInfo
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value groupids;
 * groupids.append("third group id");
 * groupids.append("second group id");
 * groupids.append("first group id");
 * int ret = TIMGroupGetGroupInfoList(groupids.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 *
 * // groupids.toStyledString().c_str() 得到json_group_getinfo_param如下
 * [ "third group id", "second group id", "first group id" ]
 * @endcode
 */
TIM_API int TIMGroupGetGroupInfoList(const char* json_group_getinfo_param, TIMCommCallback cb, const void* user_data);

/**
 * 5.2 搜索群组信息列表（5.4.666 及以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_group_search_groups_param  群列表的参数 array ，Json Key 请参考 @ref GroupSearchParam
 * @param cb 搜索群列表回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 *  SDK 会搜索群名称包含于关键字列表 keywordList 的所有群并返回群信息列表。关键字列表最多支持5个。
 * 
 * __示例__
 * @code{.cpp}
 *    Json::Array json_keyword_list;
 *    json_keyword_list.append("lamarzhang_group_public");
 *
 *    Json::Array json_field_list;
 *    json_field_list.append(kTIMGroupSearchFieldKey_GroupId);
 *
 *    Json::Object json_obj;
 *    json_obj[TIMGroupSearchParamKeywordList] = json_keyword_list;
 *    json_obj[TIMGroupSearchParamFieldList] = json_field_list;
 *   TIMGroupSearchGroups(json_array.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 *   }, nullptr);
 * @endcode
 * 
 * __回调的 json_param 示例 (Json Key 请参考 @ref GroupDetailInfo)__
 * @code{.cpp}
 *[{
 *   "group_de tail_info_add_option": 1,
 *   "group_detail_info_create_time": 0,
 *   "group_detail_info_custom_info": [{
 *       "group_info_custom_string_info_key": "custom_public",
 *       "group_info_custom_string_info_value": ""
 *   }, {
 *       "group_info_custom_string_info_key": "custom_public2",
 *       "group_info_custom_string_info_value": ""
 *   }, {
 *       "group_info_custom_string_info_key": "group_info",
 *       "group_info_custom_string_info_value": ""
 *   }, {
 *       "group_info_custom_string_info_key": "group_test",
 *       "group_info_custom_string_info_value": ""
 *   }],
 *   "group_detail_info_face_url": "",
 *   "group_detail_info_group_id": "lamarzhang_group_public",
 *   "group_detail_info_group_name": "lamarzhang_group_public",
 *   "group_detail_info_group_type": 0,
 *   "group_detail_info_info_seq": 9,
 *   "group_detail_info_introduction": "Instroduction",
 *   "group_detail_info_is_shutup_all": false,
 *   "group_detail_info_last_info_time": 1620810613,
 *   "group_detail_info_last_msg_time": 1620810613,
 *   "group_detail_info_max_member_num": 1000,
 *   "group_detail_info_member_num": 2,
 *   "group_detail_info_next_msg_seq": 2,
 *   "group_detail_info_notification": "Notification",
 *   "group_detail_info_online_member_num": 0,
 *   "group_detail_info_owner_identifier": "lamarzhang",
 *   "group_detail_info_searchable": true,
 *   "group_detail_info_visible": true
 *   }]
 * @endcode
 */
TIM_API int TIMGroupSearchGroups(const char *json_group_search_groups_param, TIMCommCallback cb, const void* user_data);

/**
 * 5.3 修改群信息
 *
 * @param json_group_modifyinfo_param 设置群信息参数的 Json 字符串, Json Key 请参考 @ref GroupModifyInfoParam
 * @param cb 设置群信息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 修改群主（群转让）的权限说明：
 *  - 只有群主才有权限进行群转让操作。
 *  - 直播大群不能进行群转让操作。
 * 修改群其他信息的权限说明:
 *  - 对于公开群、聊天室和直播大群，只有群主或者管理员可以修改群简介。
 *  - 对于私有群，任何人可修改群简介。
 * kTIMGroupModifyInfoParamModifyFlag 可以按位或设置多个值。不同的flag设置不同的键,详情请参考 @ref GroupModifyInfoParam
 *
 * __设置群所有者示例__
 * @code{.cpp}
 * Json::Value json_value_modifygroupinfo;
 * json_value_modifygroupinfo[kTIMGroupModifyInfoParamGroupId] = "first group id";
 * json_value_modifygroupinfo[kTIMGroupModifyInfoParamModifyFlag] = kTIMGroupModifyInfoFlag_Owner;
 * json_value_modifygroupinfo[kTIMGroupModifyInfoParamOwner] = "user2";
 *
 * int ret = TIMGroupModifyGroupInfo(json_value_modifygroupinfo.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_value_modifygroupinfo.toStyledString().c_str() 得到json_group_modifyinfo_param JSON 字符串如下
 * {
 *   "group_modify_info_param_group_id" : "first group id",
 *   "group_modify_info_param_modify_flag" : -2147483648,
 *   "group_modify_info_param_owner" : "user2"
 * }
 * @endcode
 *
 * __设置群名称和群通知示例__
 * @code{.cpp}
 * Json::Value json_value_modifygroupinfo;
 * json_value_modifygroupinfo[kTIMGroupModifyInfoParamGroupId] = "first group id";
 * json_value_modifygroupinfo[kTIMGroupModifyInfoParamModifyFlag] = kTIMGroupModifyInfoFlag_Name | kTIMGroupModifyInfoFlag_Notification;
 * json_value_modifygroupinfo[kTIMGroupModifyInfoParamGroupName] = "first group name to other name";
 * json_value_modifygroupinfo[kTIMGroupModifyInfoParamNotification] = "first group notification";
 *
 * int ret = TIMGroupModifyGroupInfo(json_value_modifygroupinfo.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_value_modifygroupinfo.toStyledString().c_str() 得到json_group_modifyinfo_param JSON 字符串如下
 * {
 *    "group_modify_info_param_group_id" : "first group id",
 *    "group_modify_info_param_group_name" : "first group name to other name",
 *    "group_modify_info_param_modify_flag" : 3,
 *    "group_modify_info_param_notification" : "first group notification"
 * }
 * @endcode
 */
TIM_API int TIMGroupModifyGroupInfo(const char* json_group_modifyinfo_param, TIMCommCallback cb, const void* user_data);

/**
 * 5.4 初始化群属性，会清空原有的群属性列表
 *
 * @param group_id  群 ID
 * @param json_group_attributes 群属性的列表, 群属性的 Json Key 请参考 @ref GroupAttributes
 * @param cb  初始化群属性的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note attributes 的使用限制如下:
 *  - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *  - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *  - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型；
 *  - key 最多支持 16 个，长度限制为 32 字节；
 *  - value 长度限制为 4k；
 *  - 总的 attributes（包括 key 和 value）限制为 16k；
 *  - @ref TIMGroupInitGroupAttributes、 @ref TIMGroupSetGroupAttributes @ref TIMGroupDeleteGroupAttributes 接口合并计算， SDK 限制为 5 秒 10 次，超过后回调 8511 错误码；后台限制 1 秒 5 次，超过后返回 10049 错误码；
 *  - @ref TIMGroupGetGroupAttributes 接口 SDK 限制 5 秒 20 次；
 *  - 从 5.6 版本开始，当每次APP启动后初次修改群属性时，请您先调用 @ref TIMGroupGetGroupAttributes 拉取到最新的群属性之后，再发起修改操作；
 *  - 从 5.6 版本开始，当多个用户同时修改同一个群属性时，只有第一个用户可以执行成功，其它用户会收到 10056 错误码；收到这个错误码之后，请您调用 @ref TIMGroupGetGroupAttributes 把本地保存的群属性更新到最新之后，再发起修改操作。
 *
 * __示例__
 * @code{.cpp}
 *    Json::Object json_obj;
 *    json_obj[TIMGroupAttributeKey] = "attribute_key1";
 *    json_obj[TIMGroupAttributeValue] = "attribute_value1";
 *
 *   Json::Array json_array;
 *   json_array.append(json_obj);
 *   TIMGroupInitGroupAttributes("lamarzhang_group_public", json_array.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       // json_param 为空字符串，判断 code 即可
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupInitGroupAttributes(const char *group_id, const char *json_group_attributes, TIMCommCallback cb, const void* user_data);

/**
 * 5.5 设置群属性，已有该群属性则更新其 value 值，没有该群属性则添加该群属性
 *
 * @param group_id 群 ID
 * @param json_group_attributes 群属性的列表, 群属性的 Json Key 请参考 @ref GroupAttributes
 * @param cb 设置群属性的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 *  @note
 *  - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *  - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *  - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型；
 *
 * __示例__
 * @code{.cpp}
 *    Json::Object json_obj;
 *    json_obj[TIMGroupAttributeKey] = "attribute_key1";
 *    json_obj[TIMGroupAttributeValue] = "attribute_value2";
 *
 *    Json::Array json_array;
 *    json_array.append(json_obj);
 *    TIMGroupSetGroupAttributes("lamarzhang_group_public", json_array.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *        // json_param 为空字符串，判断 code 即可
 *    }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupSetGroupAttributes(const char *group_id, const char *json_group_attributes, TIMCommCallback cb, const void* user_data);

/**
 * 5.6 删除群属性
 * @param group_id 群 ID
 * @param json_keys 群属性 key 的列表
 * @param cb 删除群属性的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 *  @note
 *  - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *  - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *  - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型；
 * 
 * __示例__
 * @code{.cpp}
 *    Json::Array json_array;
 *    json_array.append("attribute_key1");
 *
 *    TIMGroupDeleteGroupAttributes("lamarzhang_group_public", json_array.toStyledString().c_str() ,[](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *        // json_param 无 json 字符串带回，判断 code 即可
 *        printf("InitGroupAttributes code:%d|desc:%s|json_param %s\n", code, desc, json_param);
 *    }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupDeleteGroupAttributes(const char *group_id, const char *json_keys, TIMCommCallback cb, const void* user_data);

/**
 * 5.7 获取群指定属性，若传入的 json_keys 为空，则获取所有群属性。
 *
 * @param group_id 群 ID
 * @param json_keys 群属性的 key 列表，若传入为 "", 则获取所有属性列表
 * @param cb 获取群指定属性的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 *  @note
 *  - 6.7 及其以前版本，只支持 AVChatRoom 直播群；
 *  - 从 6.8 版本开始，同时支持 AVChatRoom、Public、Meeting、Work 四种群类型；
 *  - 从 7.0 版本开始，除了话题外，群属性支持所有的群类型；
 * 
 * __示例__
 * @code{.cpp}
 *   Json::Array json_array;
 *   json_array.append("attribute_key1");
 *
 *   TIMGroupGetGroupAttributes("lamarzhang_group_public", json_array.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("InitGroupAttributes code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 *
 *  __回调的 json_param 示例 (Json key 请参考 @ref GroupAttributes)__
 * @code{.json}
 *   [{
 *       "group_attribute_key": "attribute_key1",
 *       "group_attribute_value": "attribute_value1"
 *   }]
 * @endcode
 */
TIM_API int TIMGroupGetGroupAttributes(const char *group_id, const char *json_keys, TIMCommCallback cb, const void* user_data);

/**
 * 5.8 获取指定群在线人数
 *
 * @param group_id 群 ID
 * @param cb 获取指定群在线人数的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意
 * - IMSDK 7.3 以前的版本仅支持直播群（ AVChatRoom）；
 * - IMSDK 7.3 及其以后的版本支持所有群类型。
 *
 * __示例__
 * @code{.cpp}
 * TIMGroupGetOnlineMemberCount("lamarzhang_group_public", [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 *  }, nullptr);
 * @endcode
 *
 * __回调的 json_param 的示例（Json Key 请参考 @ref GroupGetOnlineMemberCountResult)__
 * @code{.json}
 * {"group_get_online_member_count_result":0}
 * @endcode
 */
TIM_API int TIMGroupGetOnlineMemberCount(const char* group_id, TIMCommCallback cb, const void* user_data);

/**
 * 5.9 设置群计数器（7.0 及其以上版本支持）
 *
 * @param group_id 群 ID
 * @param json_group_counter_array 群计数器信息列表，群计数器 Json Key 请参考 @ref TIMGroupCounter
 * @param cb 设置群计数器的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 该计数器的 key 如果存在，则直接更新计数器的 value 值；如果不存在，则添加该计数器的 key-value；
 *  - 当群计数器设置成功后，在回调 cb 中会返回最终成功设置的群计数器信息；
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 * 
 * __示例__
 * @code{.cpp}
 * json::Object json_group_counter;
 * json_group_counter[kTIMGroupCounterKey] = "test_counter";
 * json_group_counter[kTIMGroupCounterValue] = 100;
 *
 * json::Array json_group_counter_array;
 * json_group_counter_array.push_back(json_group_counter);
 *
 * TIMGroupSetGroupCounters(GetGroupID().c_str(),  json::Serialize(json_group_counter_array).c_str(),
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         Printf("SetGroupCounters code:%d|desc:%s|json_param:%s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupSetGroupCounters(const char* group_id, const char* json_group_counter_array, TIMCommCallback cb, const void* user_data);

/**
 * 5.10 获取群计数器（7.0 及其以上版本支持）
 *
 * @param group_id 群 ID
 * @param json_group_counter_key_array 需要获取的群计数器的 key 列表，群计数器 Json Key 请参考 @ref TIMGroupCounter
 * @param cb 获取群计数器的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 如果传入的 json_group_counter_key_array 为空，则表示获取群内的所有计数器；
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 * 
 * __示例__
 * @code{.cpp}
 * json::Array json_group_counter_key_array;
 * json_group_counter_key_array.push_back("test_counter");
 *
 * TIMGroupGetGroupCounters(GetGroupID().c_str(),  json::Serialize(json_group_counter_key_array).c_str(),
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         Printf("GetGroupCounters code:%d|desc:%s|json_param:%s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupGetGroupCounters(const char* group_id, const char* json_group_counter_key_array, TIMCommCallback cb, const void* user_data);

/**
 * 5.11 递增群计数器（7.0 及其以上版本支持）
 *
 * @param group_id 群 ID
 * @param group_counter_key 群计数器的 key
 * @param group_counter_value 群计数器的递增变化量 value
 * @param cb 递增群计数器的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 该计数器的 key 如果存在，则直接在当前值的基础上根据传入的 group_counter_value 作递增操作；反之，添加 key，并在默认值为 0 的基础上根据传入的 group_counter_value 作递增操作；
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 * 
 * __示例__
 * @code{.cpp}
 * TIMGroupIncreaseGroupCounter(GetGroupID().c_str(),  "key1", 2
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         printf("IncreaseGroupCounters code:%d|desc:%s|json_param:%s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupIncreaseGroupCounter(const char* group_id, const char* group_counter_key, int64_t group_counter_value, TIMCommCallback cb, const void* user_data);

/**
 * 5.12 递减群计数器（7.0 及其以上版本支持）
 *
 * @param group_id 群 ID
 * @param group_counter_key 群计数器的 key
 * @param group_counter_value 群计数器的递减变化量 value
 * @param cb 递减群计数器的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 该计数器的 key 如果存在，则直接在当前值的基础上根据传入的 group_counter_value 作递减操作；反之，添加 key，并在默认值为 0 的基础上根据传入的 group_counter_value 作递减操作
 *  - 除了社群和话题，群计数器支持所有的群组类型。
 *
 * __示例__
 * @code{.cpp}
 * TIMGroupDecreaseGroupCounters(GetGroupID().c_str(), "key1", 2,
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         Printf("DecreaseGroupCounters code:%d|desc:%s|json_param:%s\r\n", code, desc, json_param);
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupDecreaseGroupCounter(const char* group_id, const char* group_counter_key, int64_t group_counter_value, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                           六. 社群-话题相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 6.1 获取当前用户已经加入的支持话题的社群列表
 *
 * @param cb 获取社群列表的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   TIMGroupGetJoinedCommunityList([](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMGroupGetJoinedCommunityList code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupGetJoinedCommunityList(TIMCommCallback cb, const void* user_data);

/**
 * 6.2 创建话题
 *
 * @param group_id 群 ID
 * @param json_topic_info 话题信息, Json Key 请参考 @ref TIMGroupTopicInfo
 * @param cb 创建话题的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   const std::string group_id = GetCommunityID();
 *
 *   json::Object topic_info;
 *   topic_info[kTIMGroupTopicInfoTopicID] = GetTopicID();
 *   topic_info[kTIMGroupTopicInfoTopicName] = "topic name";
 *
 *   TIMGroupCreateTopicInCommunity(group_id.c_str(), json::Serialize(topic_info).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMGroupCreateTopicInCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupCreateTopicInCommunity(const char *group_id, const char *json_topic_info, TIMCommCallback cb, const void* user_data);

/**
 * 6.3 删除话题
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
 *   TIMGroupDeleteTopicFromCommunity(group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMGroupDeleteTopicFromCommunity code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupDeleteTopicFromCommunity(const char *group_id, const char *json_topic_id_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.4 修改话题信息
 *
 * @param json_topic_info 话题信息, Json Key 请参考 @ref TIMGroupTopicInfo
 * @param cb 修改话题信息的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   json::Object topic_info;
 *   topic_info[kTIMGroupTopicInfoTopicID] = GetTopicID();
 *   topic_info[kTIMGroupTopicInfoTopicName] = "topic name";
 *   topic_info[kTIMGroupTopicInfoNotification] = "topic notification";
 *   topic_info[kTIMGroupTopicInfoModifyFlag] = kTIMGroupModifyInfoFlag_Name |
 *       kTIMGroupModifyInfoFlag_Notification;
 *
 *   TIMGroupSetTopicInfo(json::Serialize(topic_info).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMGroupSetTopicInfo code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupSetTopicInfo(const char *json_topic_info, TIMCommCallback cb, const void* user_data);

/**
 * 6.5 获取话题列表
 *
 * @param group_id 群 ID
 * @param json_topic_id_array 话题 ID 列表
 * @param cb 删除话题的回调。回调函数定义请参考 @ref TIMCommCallback
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
 *   TIMGroupGetTopicInfoList(group_id.c_str(), json::Serialize(json_array).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("TIMGroupGetTopicInfoList code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupGetTopicInfoList(const char *group_id, const char *json_topic_id_array, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                         七. 群成员管理相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 7.1 获取群成员信息列表
 *
 * @param json_group_getmeminfos_param 获取群成员信息列表参数的 Json 字符串, Json Key 请参考 @ref GroupMemberGetInfoOption
 * @param cb 获取群成员信息列表成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  普通群（工作群、会议群、公开群、社群）的限制：
 *  - kTIMGroupMemberGetInfoOptionRoleFlag 只能设置为 TIMGroupMemberRoleFlag 定义的数值，SDK 会返回指定角色的成员。
 *
 *  直播群（AVChatRoom）的限制：
 *  - 如果设置 kTIMGroupMemberGetInfoOptionRoleFlag 为 TIMGroupMemberRoleFlag 定义的数值，SDK 返回全部成员。返回的人数规则为：拉取最近入群群成员最多 1000 人，新进来的成员排在前面，需要升级旗舰版，并且在 [控制台](https://console.cloud.tencent.com/im) 开启“直播群在线成员列表”开关（6.3 及以上版本支持）。
 *  - 如果设置 kTIMGroupMemberGetInfoOptionRoleFlag 为群成员自定义标记，旗舰版支持拉取指定标记的成员列表。标记群成员的设置请参考 @ref TIMGroupMarkGroupMemberList
 *  - 程序重启后，请重新加入群组，否则拉取群成员会报 10007 错误码。
 *  - 群成员资料信息仅支持 userID | nickName | faceURL | role 字段。
 *
 * __示例__
 * @code{.cpp}
 * Json::Value identifiers(Json::arrayValue);
 * ...
 * Json::Value customs(Json::arrayValue);
 * ...
 * Json::Value option;
 * option[kTIMGroupMemberGetInfoOptionInfoFlag] = kTIMGroupMemberInfoFlag_None;
 * option[kTIMGroupMemberGetInfoOptionRoleFlag] = kTIMGroupMemberRoleFlag_All;
 * option[kTIMGroupMemberGetInfoOptionCustomArray] = customs;
 * Json::Value getmeminfo_opt;
 * getmeminfo_opt[kTIMGroupGetMemberInfoListParamGroupId] = group_id;
 * getmeminfo_opt[kTIMGroupGetMemberInfoListParamIdentifierArray] = identifiers;
 * getmeminfo_opt[kTIMGroupGetMemberInfoListParamOption] = option;
 * getmeminfo_opt[kTIMGroupGetMemberInfoListParamNextSeq] = 0;
 *
 * int ret = TIMGroupGetMemberInfoList(getmeminfo_opt.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 *
 * // getmeminfo_opt.toStyledString().c_str() 得到json_group_getmeminfos_param JSON 字符串如下
 * {
 *    "group_get_members_info_list_param_group_id" : "first group id",
 *    "group_get_members_info_list_param_identifier_array" : [],
 *    "group_get_members_info_list_param_next_seq" : 0,
 *    "group_get_members_info_list_param_option" : {
 *       "group_member_get_info_option_custom_array" : [],
 *       "group_member_get_info_option_info_flag" : 0,
 *       "group_member_get_info_option_role_flag" : 0
 *    }
 * }
 * @endcode
 */
TIM_API int TIMGroupGetMemberInfoList(const char* json_group_getmeminfos_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.2 搜索群成员（5.4.666 及以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_group_search_group_members_param 群成员的列表, Json Key 请参考 @ref GroupMemberSearchParam
 * @param cb 搜索群成员列表的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 * SDK 会在本地搜索指定群 ID 列表中，群成员信息（名片、好友备注、昵称、userID）包含于关键字列表 keywordList 的所有群成员并返回群 ID 和群成员列表的 map，关键字列表最多支持5个。
 * 
 * __示例__
 * @code{.cpp}
 *   Json::Array json_groupid_list;
 *   json_groupid_list.append("lamarzhang_group_public");
 * 
 *   Json::Array json_keyword_list;
 *   json_keyword_list.append("98826");
 *
 *   Json::Array json_field_list;
 *   json_field_list.append(kTIMGroupMemberSearchFieldKey_Identifier);
 * 
 *   Json::Object json_obj;
 *   json_obj[TIMGroupMemberSearchParamGroupidList] = json_groupid_list;
 *   json_obj[TIMGroupMemberSearchParamKeywordList] = json_keyword_list;
 *   json_obj[TIMGroupMemberSearchParamFieldList] = json_field_list;
 *   TIMGroupSearchGroupMembers(json_obj.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 * 
 *   }, nullptr);
 * @endcode
 *
 * __回调的 json_param 示例 (Json Key 请参考 @ref GroupGetOnlineMemberCountResult)__
 * @code{.json}
 * [{
 *   "group_search_member_result_groupid": "lamarzhang_group_public",
 *   "group_search_member_result_member_info_list": [{
 *       "group_member_info_custom_info": [{
 *           "group_info_custom_string_info_key": "group_member_p",
 *           "group_info_custom_string_info_value": ""
 *       }, {
 *           "group_info_custom_string_info_key": "group_member_p2",
 *           "group_info_custom_string_info_value": ""
 *       }],
 *       "group_member_info_identifier": "98826",
 *       "group_member_info_join_time": 1620810613,
 *       "group_member_info_member_role": 4,
 *       "group_member_info_msg_flag": 0,
 *       "group_member_info_msg_seq": 0,
 *       "group_member_info_name_card": "",
 *       "group_member_info_shutup_time": 0
 *   }]
 * }]
 * @endcode
 */
TIM_API int TIMGroupSearchGroupMembers(const char *json_group_search_group_members_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.3 修改群成员信息
 *
 * @param json_group_modifymeminfo_param 设置群信息参数的 Json 字符串, Json Key 请参考 @ref GroupModifyMemberInfoParam
 * @param cb 设置群成员信息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 权限说明：
 *  - 只有群主或者管理员可以进行对群成员的身份进行修改。
 *  - 直播大群不支持修改用户群内身份。
 *  - 只有群主或者管理员可以进行对群成员进行禁言。
 * kTIMGroupModifyMemberInfoParamModifyFlag 可以按位或设置多个值，不同的 flag 设置不同的键, flag 信息请参考 @ref TIMGroupMemberModifyInfoFlag
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_setgroupmeminfo;
 * json_value_setgroupmeminfo[kTIMGroupModifyMemberInfoParamGroupId] = "third group id";
 * json_value_setgroupmeminfo[kTIMGroupModifyMemberInfoParamIdentifier] = "user2";
 * json_value_setgroupmeminfo[kTIMGroupModifyMemberInfoParamModifyFlag] = kTIMGroupMemberModifyFlag_MemberRole | kTIMGroupMemberModifyFlag_NameCard;
 * json_value_setgroupmeminfo[kTIMGroupModifyMemberInfoParamMemberRole] = kTIMMemberRole_Admin;
 * json_value_setgroupmeminfo[kTIMGroupModifyMemberInfoParamNameCard] = "change name card";
 *
 * int ret = TIMGroupModifyMemberInfo(json_value_setgroupmeminfo.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_value_modifygroupmeminfo.toStyledString().c_str() 得到 json_group_modifymeminfo_param JSON 字符串如下
 * {
 *    "group_modify_member_info_group_id" : "third group id",
 *    "group_modify_member_info_identifier" : "user2",
 *    "group_modify_member_info_member_role" : 1,
 *    "group_modify_member_info_modify_flag" : 10,
 *    "group_modify_member_info_name_card" : "change name card"
 * }
 * @endcode
 */
TIM_API int TIMGroupModifyMemberInfo(const char* json_group_modifymeminfo_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.4 邀请加入群组
 *
 * @param json_group_invite_param 邀请加入群组的 Json 字符串, Json Key 请参考 @ref GroupInviteMemberParam
 * @param cb 邀请加入群组成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 权限说明:
 *  - 只有私有群可以拉用户入群
 *  - 公开群、聊天室邀请用户入群
 *  - 需要用户同意；直播大群不能邀请用户入群。
 * 后台限制单次邀请的群成员个数不能超过 20。
 * 此接口支持批量邀请成员加入群组, Json Key详情请参考 @ref GroupInviteMemberParam
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_invite;
 * json_value_invite[kTIMGroupInviteMemberParamGroupId] = group_id;
 * json_value_invite[kTIMGroupInviteMemberParamUserData] = "userdata";
 * json_value_invite[kTIMGroupInviteMemberParamIdentifierArray].append("user1");
 * json_value_invite[kTIMGroupInviteMemberParamIdentifierArray].append("user2");
 *
 * const void* user_data = nullptr; // 回调函数回传;
 * int ret = TIMGroupInviteMember(json_value_invite.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 邀请成员列表失败
 *         return;
 *     }
 *     // 邀请成员列表成功，解析JSON获取每个成员邀请结果
 * }, user_data);
 * if (TIM_SUCC != ret) {
 *     // TIMGroupInviteMember 接口调用失败
 * }
 *
 * // json_value_invite.toStyledString().c_str() 得到 json_group_invite_param JSON 字符串如下
 * {
 *    "group_invite_member_param_group_id" : "first group id",
 *    "group_invite_member_param_identifier_array" : [ "user1", "user2" ],
 *    "group_invite_member_param_user_data" : "userdata"
 * }
 * @endcode
 */
TIM_API int TIMGroupInviteMember(const char* json_group_invite_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.5 删除群组成员（直播群删除群组成员从 6.6 版本开始支持，需要您购买旗舰版套餐）
 *
 * @param json_group_delete_param 删除群组成员的 Json 字符串, Json Key 请参考 @ref GroupDeleteMemberParam
 * @param cb 删除群组成员成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 权限说明：
 *  - 对于私有群：只有创建者可删除群组成员。
 *  - 对于公开群和聊天室：只有管理员和群主可以踢人。
 *  - 对于直播大群：6.6 之前版本只支持禁言（muteGroupMember），不支持踢人。6.6 及以上版本支持禁言和踢人。
 * 此接口支持批量删除群成员, Json Key详情请参考 @ref GroupDeleteMemberParam
 * 该接口其他使用限制请查阅 [官网](https://cloud.tencent.com/document/product/269/75400#.E8.B8.A2.E4.BA.BA)
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_delete;
 * json_value_delete[kTIMGroupDeleteMemberParamGroupId] = group_id;
 * json_value_delete[kTIMGroupDeleteMemberParamUserData] = "reason";
 * json_value_delete[kTIMGroupDeleteMemberParamIdentifierArray].append("user1");
 * json_value_delete[kTIMGroupDeleteMemberParamIdentifierArray].append("user2");
 * json_value_delete[kTIMGroupDeleteMemberParamDuration] = 10;
 *
 * int ret = TIMGroupDeleteMember(json_value_delete.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, this));
 *
 * // json_value_delete.toStyledString().c_str() 得到 json_group_delete_param JSON 字符串如下
 * {
 *   "group_delete_member_param_group_id" : "third group id",
 *   "group_delete_member_param_identifier_array" : [ "user2", "user3" ],
 *   "group_delete_member_param_user_data" : "reason"
 * }
 * @endcode
 */
TIM_API int TIMGroupDeleteMember(const char* json_group_delete_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.6 标记群成员(从 6.6 版本开始支持，需要您购买旗舰版套餐)
 *
 * @param group_id 群 ID。
 * @param member_array 群成员 ID 列表。
 * @param mark_type 标记类型。数字类型，大于等于 1000，您可以自定义，一个直播群里最多允许定义 10 个标记。
 * @param enable_mark true 表示添加标记，false 表示移除标记。
 * @param cb 设置/移除群成员自定义角色成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意
 * - 仅支持直播群。
 * - 只有群主才有权限标记群组中其他人。
 *
 * __示例__
 * @code{.cpp}
 *  std::string group_id = "avchatroom_group_id";
 *  uint32_t mark_type = 30005;
 *  bool enable_mark = true;
 *
 *  json::Array member_array;
 *  member_array.push_back("user1");
 *  member_array.push_back("user2");
 *
 *  TIMGroupMarkGroupMemberList(group_id.c_str(), json::Serialize(member_array).c_str(), mark_type, enable_mark,
 *  [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *      Printf("MarkGroupMemberList code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *  }, nullptr);
 * @endcode
 */
TIM_API int TIMGroupMarkGroupMemberList(const char* group_id, const char* member_array, uint32_t mark_type, bool enable_mark, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                              八. 加群申请相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 8.1 获取群未决信息列表
 *
 * @param json_group_getpendency_list_param 设置群未决信息参数的 Json 字符串, Json Key 请参考 @ref GroupPendencyOption
 * @param cb 获取群未决信息列表成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 此处的群未决消息泛指所有需要审批的群相关的操作。例如：加群待审批，拉人入群待审批等等。即便审核通过或者拒绝后，该条信息也可通过此接口拉回，拉回的信息中有已决标志。
 * - UserA 申请加入群 GroupA，则群管理员可获取此未决相关信息，UserA 因为没有审批权限，不需要获取此未决信息。
 * - 如果 AdminA 拉 UserA 进去 GroupA，则 UserA 可以拉取此未决相关信息，因为该未决信息待 UserA 审批
 * - kTIMGroupPendencyOptionStartTime 设置拉取时间戳,第一次请求填 0,后边根据 server 返回的 @ref GroupPendencyResult 键 kTIMGroupPendencyResultNextStartTime 指定的时间戳进行填写。
 * - kTIMGroupPendencyOptionMaxLimited 拉取的建议数量, server 可根据需要返回或多或少,不能作为完成与否的标志
 * - 权限说明：
 *    - 只有审批人有权限拉取相关未决信息。
 *
 * __示例__
 * @code{.cpp}
 * Json::Value get_pendency_option;
 * get_pendency_option[kTIMGroupPendencyOptionStartTime] = 0;
 * get_pendency_option[kTIMGroupPendencyOptionMaxLimited] = 0;
 * int ret = TIMGroupGetPendencyList(get_pendency_option.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 获取群未决信息失败
 *         return;
 *     }
 * }, nullptr);
 *
 * // get_pendency_option.toStyledString().c_str() 得到json_group_getpendency_list_param JSON 字符串如下
 * {
 *    "group_pendency_option_max_limited" : 0,
 *    "group_pendency_option_start_time" : 0
 * }
 * @endcode
 */
TIM_API int TIMGroupGetPendencyList(const char* json_group_getpendency_list_param, TIMCommCallback cb, const void* user_data);

/**
 * 8.2 处理群未决信息
 *
 * @param json_group_handle_pendency_param 处理群未决信息参数的 Json 字符串, Json Key 请参考 @ref GroupHandlePendencyParam
 * @param cb 处理群未决信息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * - 对于群的未决信息，ImSDK增加了处理接口。审批人可以选择对单条信息进行同意或者拒绝。已处理成功过的未决信息不能再次处理。
 * - 处理未决信息时需要带一个未决信息 @ref GroupPendency, 可以在接口 @ref TIMGroupGetPendencyList 返回的未决信息列表将未决信息保存下来，
 *   在处理未决信息的时候将 @ref GroupPendency 传入键 kTIMGroupHandlePendencyParamPendency 。
 *
 * __示例__
 * @code{.cpp}
 * Json::Value pendency; //构造 GroupPendency
 * ...
 * Json::Value handle_pendency;
 * handle_pendency[kTIMGroupHandlePendencyParamIsAccept] = true;
 * handle_pendency[kTIMGroupHandlePendencyParamHandleMsg] = "I accept this pendency";
 * handle_pendency[kTIMGroupHandlePendencyParamPendency] = pendency;
 * int ret = TIMGroupHandlePendency(handle_pendency.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 上报群未决信息已读失败
 *         return;
 *     }
 * }, nullptr);
 *
 * // handle_pendency.toStyledString().c_str() 得到json_group_handle_pendency_param JSON 字符串如下
 * {
 *    "group_handle_pendency_param_handle_msg" : "I accept this pendency",
 *    "group_handle_pendency_param_is_accept" : true,
 *    "group_handle_pendency_param_pendency" : {
 *       "group_pendency_add_time" : 1551414487947,
 *       "group_pendency_apply_invite_msg" : "Want Join Group, Thank you",
 *       "group_pendency_approval_msg" : "",
 *       "group_pendency_form_identifier" : "user2",
 *       "group_pendency_form_user_defined_data" : "",
 *       "group_pendency_group_id" : "four group id",
 *       "group_pendency_handle_result" : 0,
 *       "group_pendency_handled" : 0,
 *       "group_pendency_pendency_type" : 0,
 *       "group_pendency_to_identifier" : "user1",
 *       "group_pendency_to_user_defined_data" : ""
 *    }
 * }
 * @endcode
 */
TIM_API int TIMGroupHandlePendency(const char* json_group_handle_pendency_param, TIMCommCallback cb, const void* user_data);

/**
 * 8.3 上报群未决信息已读
 *
 * @param time_stamp 已读时间戳(单位秒)。与 @ref GroupPendency 键 kTIMGroupPendencyAddTime 指定的时间比较
 * @param cb 上报群未决信息已读成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 时间戳time_stamp以前的群未决请求都将置为已读。上报已读后，仍然可以拉取到这些未决信息，但可通过对已读时戳的判断判定未决信息是否已读。
 */
TIM_API int TIMGroupReportPendencyReaded(uint64_t time_stamp, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                         九. 群组系统通知相关 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 9.1 GroupTipGroupChangeInfo(群组系统消息-群组信息修改)
// uint @ref TIMGroupTipGroupChangeFlag, 只读, 群消息修改群信息标志
static const char* kTIMGroupTipGroupChangeInfoFlag = "group_tips_group_change_info_flag";
// string, 只读, 修改的后值,不同的 info_flag 字段,具有不同的含义
static const char* kTIMGroupTipGroupChangeInfoValue = "group_tips_group_change_info_value";
// string, 只读, 自定义信息对应的 key 值，只有 info_flag 为 kTIMGroupTipChangeFlag_Custom 时有效
static const char* kTIMGroupTipGroupChangeInfoKey = "group_tips_group_change_info_key";
// bool, 只读, 根据变更类型表示不同的值，当前在 info_flag 为 kTIMGroupTipChangeFlag_ShutupAll 或者 kTIMGroupTipChangeFlag_EnablePermissionGroup 时有效
static const char* kTIMGroupTipGroupChangeInfoBoolValue = "group_tips_group_change_info_bool_value";
// int, 只读, 根据变更类型表示不同的值
// @note 仅针对以下类型有效：
//  - 从 6.5 版本开始，当 info_flag 为 kTIMGroupTipChangeFlag_MessageReceiveOpt 时，该字段标识了群消息接收选项发生了变化，其取值详见 @ref TIMReceiveMessageOpt
//  - 从 6.5 版本开始，当 info_flag 为 kTIMGroupTipChangeFlag_GroupAddOpt 时，该字段标识了申请加群审批选项发生了变化，其取值详见 @ref TIMGroupAddOption
//  - 从 7.1 版本开始，当 info_flag 为 kTIMGroupTipChangeFlag_GroupApproveOpt 时，该字段标识了邀请进群审批选项发生了变化，取值类型详见 @ref TIMGroupAddOption
static const char* kTIMGroupTipGroupChangeInfoIntValue    = "group_tips_group_change_info_int_value";
// uint64, 只读, 根据变更类型表示不同的值，当前只有 info_flag 为 kTIMGroupTipChangeFlag_DefaultPermissions 时有效
static const char* kTIMGroupTipGroupChangeInfoUint64Value    = "group_tips_group_change_info_uint64_value";

//------------------------------------------------------------------------------
// 9.2 GroupTipMemberChangeInfo(群组系统消息-群组成员禁言)
// string, 只读, 群组成员ID
static const char* kTIMGroupTipMemberChangeInfoIdentifier = "group_tips_member_change_info_identifier";
// uint, 只读, 禁言时间
static const char* kTIMGroupTipMemberChangeInfoShutupTime = "group_tips_member_change_info_shutupTime";

//------------------------------------------------------------------------------
// 9.3 GroupTipMemberMarkChangeInfo(群组系统消息-群组成员标记变更)
// bool, 只读, 群成员被标记或取消标记
static const char* kTIMGroupTipMemberChangeInfoEnableMark = "group_tips_member_mark_change_info_enableMark";
// uint, 只读, 标记类型
static const char* kTIMGroupTipMemberMarkChangeInfoMarkType = "group_tips_member_mark_change_info_markType";
// array string, 只读, 群成员 userID 列表
static const char* kTIMGroupTipMemberMarkChangeInfoUserIDList = "group_tips_member_mark_change_info_userIDList";

//------------------------------------------------------------------------------
// 9.4 GroupTipsElem(群组系统消息元素)
// @note 
//  - 针对所有群成员，可以通过监听 @ref TIMSetGroupTipsEventCallback 获取
// uint @ref TIMGroupTipType, 只读, 群消息类型
static const char* kTIMGroupTipsElemTipType = "group_tips_elem_tip_type";
// string, 只读, 操作者ID
static const char* kTIMGroupTipsElemOpUser = "group_tips_elem_op_user";
// string, 只读, 群组ID
static const char* kTIMGroupTipsElemGroupId = "group_tips_elem_group_id";
// array string, 只读, 被操作的账号列表
static const char* kTIMGroupTipsElemUserArray = "group_tips_elem_user_array";
// array @ref GroupTipGroupChangeInfo, 只读, 群资料变更信息列表,仅当 kTIMGroupTipsElemTipType 值为 kTIMGroupTip_GroupInfoChange 时有效
static const char* kTIMGroupTipsElemGroupChangeInfoArray = "group_tips_elem_group_change_info_array";
// array @ref GroupTipMemberChangeInfo, 只读, 群成员变更信息列表,仅当 kTIMGroupTipsElemTipType 值为 kTIMGroupTip_MemberInfoChange 时有效
static const char* kTIMGroupTipsElemMemberChangeInfoArray = "group_tips_elem_member_change_info_array";
// object @ref UserProfile, 只读, 操作者个人资料
static const char* kTIMGroupTipsElemOpUserInfo = "group_tips_elem_op_user_info";
// object @ref GroupMemberInfo, 只读, 群成员信息
static const char* kTIMGroupTipsElemOpGroupMemberInfo = "group_tips_elem_op_group_memberinfo";
// array @ref UserProfile, 只读, 被操作者列表资料
static const char* kTIMGroupTipsElemChangedUserInfoArray = "group_tips_elem_changed_user_info_array";
// array @ref GroupMemberInfo, 只读, 群成员信息列表
static const char* kTIMGroupTipsElemChangedGroupMemberInfoArray = "group_tips_elem_changed_group_memberinfo_array";
// uint, 只读, 当前群成员数,只有当事件消息类型为 kTIMGroupTip_Invite 、 kTIMGroupTip_Quit 、 kTIMGroupTip_Kick 时有效
static const char* kTIMGroupTipsElemMemberNum = "group_tips_elem_member_num";
// string, 只读, 操作方平台信息
static const char* kTIMGroupTipsElemPlatform = "group_tips_elem_platform";
// array @ref GroupTipMemberMarkChangeInfo, 只读, 群成员标记变更信息列表，仅当 kTIMGroupTipsElemTipType 值为 kTIMGroupTip_MemberMarkChange 时有效
static const char* kTIMGroupTipsElemMemberMarkInfoArray = "group_tips_elem_member_mark_info_array";


/////////////////////////////////////////////////////////////////////////////////
//
//                       十. 群组管理 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 10.1 GroupMemberInfo(群成员信息)
// string, 读写(必填), 群组成员ID
static const char* kTIMGroupMemberInfoIdentifier = "group_member_info_identifier";
// string, 只读, 群组 ID
static const char* kTIMGroupMemberInfoGroupId = "group_member_info_group_id";
// uint, 只读, 群组成员加入时间
static const char* kTIMGroupMemberInfoJoinTime = "group_member_info_join_time";
// uint @ref TIMGroupMemberRole, 读写(选填), 群组成员角色
static const char* kTIMGroupMemberInfoMemberRole = "group_member_info_member_role";
// uint @ref TIMReceiveMessageOpt, 只读, 成员接收消息的选项
static const char* kTIMGroupMemberInfoMsgFlag = "group_member_info_msg_flag";
// uint, 只读, 消息序列号
static const char* kTIMGroupMemberInfoMsgSeq = "group_member_info_msg_seq";
// uint, 只读, 成员禁言时间
static const char* kTIMGroupMemberInfoShutupTime = "group_member_info_shutup_time";
// string, 只读, 成员群名片
static const char* kTIMGroupMemberInfoNameCard = "group_member_info_name_card";
// string, 只读, 好友昵称
static const char* kTIMGroupMemberInfoNickName = "group_member_info_nick_name";
// string, 只读, 好友备注
static const char* kTIMGroupMemberInfoFriendRemark = "group_member_info_friend_remark";
// string, 只读, 好友头像
static const char* kTIMGroupMemberInfoFaceUrl = "group_member_info_face_url";
// array @ref GroupMemberInfoCustomString, 只读, 请参考 [自定义字段](https://cloud.tencent.com/document/product/269/1502#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.AD.97.E6.AE.B5)
static const char* kTIMGroupMemberInfoCustomInfo = "group_member_info_custom_info";
// string, 只读，群成员是否在线
static const char* kTIMGroupMemberInfoIsOnline = "group_member_info_is_online";
// array, 只读， 群成员在线终端列表
static const char* KTIMGroupMemberInfoOnlineDevices = "group_member_info_online_devices";

//------------------------------------------------------------------------------
// 10.2 CreateGroupParam(创建群组接口的参数)
// string, 只写(必填), 群组名称
static const char* kTIMCreateGroupParamGroupName = "create_group_param_group_name";
// string, 只写(选填), 群组ID,不填时创建成功回调会返回一个后台分配的群ID，如果创建社群（Community）需要自定义群组 ID ，那必须以 "@TGS#_" 作为前缀。
static const char* kTIMCreateGroupParamGroupId = "create_group_param_group_id";
// uint @ref TIMGroupType, 只写(选填), 群组类型,默认为Public
static const char* kTIMCreateGroupParamGroupType = "create_group_param_group_type";
// bool, 只写(选填), 社群是否支持创建话题, 只在群类型为 Community 时有效
static const char* kTIMCreateGroupIsSupportTopic = "create_group_param_is_support_topic";
// array @ref GroupMemberInfo, 只写(选填), 群组初始成员数组，成员个数不能超过 20（7.1 及其以上版本开始限制）
static const char* kTIMCreateGroupParamGroupMemberArray = "create_group_param_group_member_array";
// string, 只写(选填), 群组公告
static const char* kTIMCreateGroupParamNotification = "create_group_param_notification";
// string, 只写(选填), 群组简介
static const char* kTIMCreateGroupParamIntroduction = "create_group_param_introduction";
// string, 只写(选填), 群组头像URL
static const char* kTIMCreateGroupParamFaceUrl = "create_group_param_face_url";
// uint @ref TIMGroupAddOption, 只写(选填),申请加群审批选项，不同类型的群组支持的申请加群审批选项请参考 [官网]( https://cloud.tencent.com/document/product/269/1502#.E5.8A.A0.E7.BE.A4.E6.96.B9.E5.BC.8F.E5.B7.AE.E5.BC.82)
static const char* kTIMCreateGroupParamAddOption = "create_group_param_add_option";
// uint @ref TIMGroupAddOption, 只写（选填），邀请进群审批选项，不同类型的群组支持的邀请进群审批选项请参考 [官网]( https://cloud.tencent.com/document/product/269/1502#.E5.8A.A0.E7.BE.A4.E6.96.B9.E5.BC.8F.E5.B7.AE.E5.BC.82)
static const char* kTIMCreateGroupParamApproveOption = "create_group_param_approve_option";
// uint, 只写(选填), 群组最大成员数
static const char* kTIMCreateGroupParamMaxMemberCount = "create_group_param_max_member_num";
// array @ref GroupInfoCustomString, 只读(选填), 请参考 [自定义字段](https://cloud.tencent.com/document/product/269/1502#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.AD.97.E6.AE.B5)
static const char* kTIMCreateGroupParamCustomInfo = "create_group_param_custom_info";
// bool, 只写(选填), 开启权限组功能, 仅支持社群, 7.8 版本开始支持。开启后，管理员角色的权限失效，用群权限、话题权限和权限组能力来对社群、话题进行管理。
static const char* kTIMCreateGroupParamEnablePermissionGroup = "create_group_param_enable_permission_group";
// uint64, 只写(选填), 群默认权限, 仅支持社群, 7.8 版本开始支持。群成员在没有加入任何权限组时的默认权限，仅在 enablePermissionGroup = true 打开权限组之后生效
static const char* kTIMCreateGroupParamDefaultPermissions = "create_group_param_default_permissions";

//------------------------------------------------------------------------------
// 10.3 CreateGroupResult(创建群组接口的返回)
// string, 只读, 创建的群ID
static const char* kTIMCreateGroupResultGroupId = "create_group_result_groupid";

//------------------------------------------------------------------------------
// 10.4 GroupSelfInfo(群组内本人的信息)
// uint, 只读, 加入群组时间
static const char* kTIMGroupSelfInfoJoinTime = "group_self_info_join_time";
// uint, 只读, 用户在群组中的角色
static const char* kTIMGroupSelfInfoRole = "group_self_info_role";
// uint, 只读, 消息未读计数
static const char* kTIMGroupSelfInfoUnReadNum = "group_self_info_unread_num";
// uint @ref TIMReceiveMessageOpt, 只读, 消息接收选项
static const char* kTIMGroupSelfInfoMsgFlag = "group_self_info_msg_flag";

//------------------------------------------------------------------------------
// 10.5 GroupBaseInfo(群组基础信息, 获取已加入群组列表接口的返回信息)
// string, 只读, 群组ID
static const char* kTIMGroupBaseInfoGroupId = "group_base_info_group_id";
// string, 只读, 群组名称
static const char* kTIMGroupBaseInfoGroupName = "group_base_info_group_name";
// uint @ref TIMGroupType, 只读, 群组类型
static const char* kTIMGroupBaseInfoGroupType = "group_base_info_group_type";
// string, 只读, 群组头像 URL
static const char* kTIMGroupBaseInfoFaceUrl = "group_base_info_face_url";
// uint, 只读, 群资料的 Seq，群资料的每次变更都会增加这个字段的值
static const char* kTIMGroupBaseInfoInfoSeq = "group_base_info_info_seq";
// uint, 只读, 群最新消息的 Seq。群组内每一条消息都有一条唯一的消息 Seq，且该 Seq 是按照发消息顺序而连续的。从1开始，群内每增加一条消息，LatestSeq 就会增加1
static const char* kTIMGroupBaseInfoLatestSeq = "group_base_info_latest_seq";
// uint, 只读, 用户所在群已读的消息Seq
static const char* kTIMGroupBaseInfoReadedSeq = "group_base_info_readed_seq";
// uint, 只读, 消息接收选项
static const char* kTIMGroupBaseInfoMsgFlag = "group_base_info_msg_flag";
// bool, 只读, 当前群组是否设置了全员禁言
static const char* kTIMGroupBaseInfoIsShutupAll = "group_base_info_is_shutup_all";
// object @ref GroupSelfInfo, 只读, 用户所在群的个人信息
static const char* kTIMGroupBaseInfoSelfInfo = "group_base_info_self_info";

//------------------------------------------------------------------------------
// 10.6 GroupInfoCustomString(群资料自定义字段)
// string, 只写, 自定义字段的 key
static const char* kTIMGroupInfoCustomStringInfoKey = "group_info_custom_string_info_key";
// string, 只写, 自定义字段的 value
static const char* kTIMGroupInfoCustomStringInfoValue = "group_info_custom_string_info_value";

//------------------------------------------------------------------------------
// 10.7 GroupDetailInfo(群组详细信息)
// string, 只读, 群组ID
static const char* kTIMGroupDetailInfoGroupId = "group_detail_info_group_id";
// uint @ref TIMGroupType, 只读, 群组类型
static const char* kTIMGroupDetailInfoGroupType = "group_detail_info_group_type";
// bool, 只读, 社群是否支持创建话题，只在群类型为 Community 时有效
static const char* kTIMGroupDetailInfoIsSupportTopic = "group_detail_info_is_support_topic";
// string, 只读, 群组名称
static const char* kTIMGroupDetailInfoGroupName = "group_detail_info_group_name";
// string, 只读, 群组公告
static const char* kTIMGroupDetailInfoNotification = "group_detail_info_notification";
// string, 只读, 群组简介
static const char* kTIMGroupDetailInfoIntroduction = "group_detail_info_introduction";
// string, 只读, 群组头像URL
static const char* kTIMGroupDetailInfoFaceUrl = "group_detail_info_face_url";
// uint, 只读, 创建群组的 UTC 时间戳
static const char* kTIMGroupDetailInfoCreateTime = "group_detail_info_create_time";
// uint, 只读, 群资料的Seq，群资料的每次变更都会增加这个字段的值
static const char* kTIMGroupDetailInfoInfoSeq = "group_detail_info_info_seq";
// uint, 只读, 上次修改群信息的 UTC 时间戳
static const char* kTIMGroupDetailInfoLastInfoTime = "group_detail_info_last_info_time";
// uint, 只读, 群最新消息的Seq
static const char* kTIMGroupDetailInfoNextMsgSeq = "group_detail_info_next_msg_seq";
// uint, 只读, 最新群组消息时间
static const char* kTIMGroupDetailInfoLastMsgTime = "group_detail_info_last_msg_time";
// uint, 只读, 群组当前成员数量
static const char* kTIMGroupDetailInfoMemberNum = "group_detail_info_member_num";
// uint, 只读, 群组最大成员数量
static const char* kTIMGroupDetailInfoMaxMemberNum = "group_detail_info_max_member_num";
// uint @ref TIMGroupAddOption, 只读, 群组申请加群审批选项
static const char* kTIMGroupDetailInfoAddOption = "group_detail_info_add_option";
// uint @ref TIMGroupAddOption, 只读, 群组邀请进群审批选项
static const char* kTIMGroupDetailInfoApproveOption = "group_detail_info_approve_option";
// uint, 只读, 群组成员是否对外可见
static const char* kTIMGroupDetailInfoVisible = "group_detail_info_visible";
// uint, 只读, 群组是否能被搜索
static const char* kTIMGroupDetailInfoSearchable = "group_detail_info_searchable";
// bool, 只读, 群组是否被设置了全员禁言
static const char* kTIMGroupDetailInfoIsShutupAll = "group_detail_info_is_shutup_all";
// string, 只读, 群组所有者ID
static const char* kTIMGroupDetailInfoOwnerIdentifier = "group_detail_info_owner_identifier";
// array @ref GroupInfoCustomString, 只读, 请参考 [自定义字段](https://cloud.tencent.com/document/product/269/1502#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.AD.97.E6.AE.B5)
static const char* kTIMGroupDetailInfoCustomInfo = "group_detail_info_custom_info";
// bool, 只读, 开启权限组功能，仅在社群生效，7.8 版本开始支持
static const char* kTIMGroupDetailInfoEnablePermissionGroup = "group_detail_info_enable_permission_group";
// uint, 只读, 群组权限，仅在社群生效，7.8 版本开始支持
static const char* kTIMGroupDetailInfoDefaultPermissions = "group_detail_info_default_permissions";

//------------------------------------------------------------------------------
// 10.8 GetGroupInfoResult(获取群组信息列表接口的返回)
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 获取群组详细信息的结果
static const char* kTIMGetGroupInfoResultCode = "get_groups_info_result_code";
// string, 只读, 获取群组详细失败的描述信息
static const char* kTIMGetGroupInfoResultDesc = "get_groups_info_result_desc";
// object @ref GroupDetailInfo, 只读, 群组详细信息
static const char* kTIMGetGroupInfoResultInfo = "get_groups_info_result_info";

//------------------------------------------------------------------------------
// 10.9 GroupSearchParam(群搜索参数)
// array string, 只写(选填), 搜索关键字列表，最多支持5个
static const char* TIMGroupSearchParamKeywordList = "group_search_params_keyword_list";
// array @ref TIMGroupSearchFieldKey, 只写(选填), 搜索域列表
static const char* TIMGroupSearchParamFieldList = "group_search_params_field_list";

//------------------------------------------------------------------------------
// 10.10 GroupModifyInfoParam(设置群信息接口的参数)
// string, 只写(必填), 群组ID
static const char* kTIMGroupModifyInfoParamGroupId = "group_modify_info_param_group_id";
// uint @ref TIMGroupModifyInfoFlag, 只写(必填), 修改标识,可设置多个值按位或
static const char* kTIMGroupModifyInfoParamModifyFlag = "group_modify_info_param_modify_flag";
// string, 只写(选填), 修改群组名称, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_Name 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamGroupName = "group_modify_info_param_group_name";
// string, 只写(选填), 修改群公告, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_Notification 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamNotification = "group_modify_info_param_notification";
// string, 只写(选填), 修改群简介, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_Introduction 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamIntroduction = "group_modify_info_param_introduction";
// string, 只写(选填), 修改群头像URL, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_FaceUrl 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamFaceUrl = "group_modify_info_param_face_url";
// uint, 只写(选填), 申请加群审批选项, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_AddOption 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamAddOption = "group_modify_info_param_add_option";
// uint, 只写(选填), 邀请进群审批选项, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_ApproveOption 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamApproveOption = "group_modify_info_param_approve_option";
// uint, 只写(选填), 修改群最大成员数, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_MaxMemberNum 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamMaxMemberNum = "group_modify_info_param_max_member_num";
// uint, 只写(选填), 修改群是否可见, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_Visible 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamVisible = "group_modify_info_param_visible";
// uint, 只写(选填), 修改群是否允许被搜索, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_Searchable 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamSearchAble = "group_modify_info_param_searchable";
// bool, 只写(选填), 修改群是否全体禁言, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_ShutupAll 时必填,其他情况不用填
static const char* kTIMGroupModifyInfoParamIsShutupAll = "group_modify_info_param_is_shutup_all";
// string, 只写(选填), 修改群主所有者, 当 modify_flag 包含 kTIMGroupModifyInfoFlag_Owner 时必填,其他情况不用填。此时 modify_flag 不能包含其他值，当修改群主时，同时修改其他信息已无意义
static const char* kTIMGroupModifyInfoParamOwner = "group_modify_info_param_owner";
// array @ref GroupInfoCustomString, 只写(选填), 请参考 [自定义字段](https://cloud.tencent.com/document/product/269/1502#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.AD.97.E6.AE.B5)
static const char* kTIMGroupModifyInfoParamCustomInfo = "group_modify_info_param_custom_info";
// bool, 只写(选填), 修改是否开启权限组功能，仅支持社群，7.8 版本开始支持
static const char* kTIMGroupModifyInfoParamEnablePermissionGroup = "group_modify_info_param_enable_permission_group";
// uint, 只写(选填), 修改群权限，仅支持社群，7.8 版本开始支持
static const char* kTIMGroupModifyInfoParamDefaultPermissions = "group_modify_info_param_default_permissions";

//------------------------------------------------------------------------------
// 10.11 GroupAttributes(设置群属性的 map 对象)
// string, 只写, 群属性 map 的 key
static const char* TIMGroupAttributeKey = "group_attribute_key";
// string, 只写, 群属性 map 的 value
static const char* TIMGroupAttributeValue = "group_attribute_value";

//------------------------------------------------------------------------------
// 10.12 GroupCounter(群计数器信息)
// string, 读写, 群计数器的 key 值
static const char* kTIMGroupCounterKey = "group_counter_key";
// int64, 读写, 群计数器的 value 值
static const char* kTIMGroupCounterValue = "group_counter_value";

//------------------------------------------------------------------------------
// 10.12 GroupGetOnlineMemberCountResult(获取指定群在线人数结果)
// int, 只读, 指定群的在线人数
static const char* TIMGroupGetOnlineMemberCountResult = "group_get_online_member_count_result";


/////////////////////////////////////////////////////////////////////////////////
//
//                      十一. 话题 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 11.1 TIMGroupTopicInfo(获取指定群话题信息结果)
// string, 读写, 话题 ID, 只能在创建话题或者修改话题信息的时候设置。组成方式为：社群 ID + @TOPIC#_xxx，例如社群 ID 为 @TGS#_123，则话题 ID 为 @TGS#_123@TOPIC#_xxx
static const char* kTIMGroupTopicInfoTopicID = "group_topic_info_topic_id";
// string, 读写, 话题名称
static const char* kTIMGroupTopicInfoTopicName = "group_topic_info_topic_name";
// string, 读写, 话题介绍
static const char* kTIMGroupTopicInfoIntroduction = "group_topic_info_introduction";
// string, 读写, 话题公告
static const char* kTIMGroupTopicInfoNotification = "group_topic_info_notification";
// string, 读写, 话题头像
static const char* kTIMGroupTopicInfoTopicFaceURL = "group_topic_info_topic_face_url";
// bool, 读写, 话题全员禁言
static const char* kTIMGroupTopicInfoIsAllMuted = "group_topic_info_is_all_muted";
// uint32, 读写, 当前用户在话题中的禁言时间
static const char* kTIMGroupTopicInfoSelfMuteTime = "group_topic_info_self_mute_time";
// string, 读写, 话题自定义字段
static const char* kTIMGroupTopicInfoCustomString = "group_topic_info_custom_string";
// uint @ref TIMReceiveMessageOpt, 只读，话题消息接收选项，修改话题消息接收选项请调用 setGroupReceiveMessageOpt 接口
static const char* kTIMGroupTopicInfoRecvOpt = "group_topic_info_recv_opt";
// string, 读写, 话题草稿
static const char* kTIMGroupTopicInfoDraftText = "group_topic_info_draft_text";
// uint64, 只读, 话题消息未读数量
static const char* kTIMGroupTopicInfoUnreadCount = "group_topic_info_unread_count";
// object @ref Message, 只读, 话题 lastMessage
static const char* kTIMGroupTopicInfoLastMessage = "group_topic_info_last_message";
// array @ref GroupAtInfo, 只读, 话题 at 信息列表
static const char* kTIMGroupTopicInfoGroupAtInfoArray = "group_topic_info_group_at_info_array";
// uint @ref TIMGroupModifyInfoFlag, 只写(必填), 修改标识,可设置多个值按位或
static const char* kTIMGroupTopicInfoModifyFlag = "group_modify_info_param_modify_flag";

//------------------------------------------------------------------------------
// 11.2 TIMGroupTopicOperationResult(话题操作结果)
// int, 只读, 结果 0：成功；非0：失败
static const char* kTIMGroupTopicOperationResultErrorCode = "group_topic_operation_result_error_code";
// string, 只读, 如果删除失败，会返回错误信息
static const char* kTIMGroupTopicOperationResultErrorMessage = "group_topic_operation_result_error_message";
// string, 只读, 如果删除成功，会返回对应的 topicID
static const char* kTIMGroupTopicOperationResultTopicID = "group_topic_operation_result_topic_id";

//------------------------------------------------------------------------------
// 11.3 TIMGroupTopicInfoResult(获取话题信息的结果)
// int, 只读, 结果 0：成功；非0：失败
static const char* kTIMGroupTopicInfoResultErrorCode = "group_topic_info_result_error_code";
// string, 只读, 如果删除失败，会返回错误信息
static const char* kTIMGroupTopicInfoResultErrorMessage = "group_topic_info_result_error_message";
// object @ref TIMGroupTopicInfo, 只读, 如果获取成功，会返回对应的 info
static const char* kTIMGroupTopicInfoResultTopicInfo = "group_topic_info_result_topic_info";

/////////////////////////////////////////////////////////////////////////////////
//
//                     十二. 群成员管理 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 12.1 GroupGetMemberInfoListParam(获取群成员列表接口的参数)
// string, 只写(必填), 群组ID
static const char* kTIMGroupGetMemberInfoListParamGroupId = "group_get_members_info_list_param_group_id";
// array string, 只写(选填), 群成员ID列表
static const char* kTIMGroupGetMemberInfoListParamIdentifierArray = "group_get_members_info_list_param_identifier_array";
// object @ref GroupMemberGetInfoOption, 只写(选填), 获取群成员信息的选项
static const char* kTIMGroupGetMemberInfoListParamOption = "group_get_members_info_list_param_option";
// uint64, 只写(选填), 分页拉取标志,第一次拉取填0,回调成功如果不为零,需要分页,调用接口传入再次拉取,直至为0
static const char* kTIMGroupGetMemberInfoListParamNextSeq = "group_get_members_info_list_param_next_seq";

//------------------------------------------------------------------------------
// 12.2 GroupGetMemberInfoListResult(获取群成员列表接口的返回)
// uint64, 只读, 下一次拉取的标志,server返回0表示没有更多的数据,否则在下次获取数据时填入这个标志
static const char* kTIMGroupGetMemberInfoListResultNexSeq = "group_get_member_info_list_result_next_seq";
// array @ref GroupMemberInfo, 只读, 成员信息列表
static const char* kTIMGroupGetMemberInfoListResultInfoArray = "group_get_member_info_list_result_info_array";

//------------------------------------------------------------------------------
// 12.3 GroupMemberSearchParam(群成员搜索参数)
// array string, 只写(选填), 指定群 ID 列表，若为不填则搜索全部群中的群成员
static const char* TIMGroupMemberSearchParamGroupidList = "group_search_member_params_groupid_list";
// array string, 只写(必填), 搜索关键字列表，最多支持5个
static const char* TIMGroupMemberSearchParamKeywordList = "group_search_member_params_keyword_list";
// array @ref TIMGroupMemberSearchFieldKey, 只写(必填), 搜索域列表
static const char* TIMGroupMemberSearchParamFieldList = "group_search_member_params_field_list";

//------------------------------------------------------------------------------
// 12.4 GroupSearchGroupMembersResult(群成员搜索结果)
// array string, 只读, 群 id 列表
static const char* TIMGroupSearchGroupMembersResultGroupID = "group_search_member_result_groupid";
// array @ref GroupMemberInfo, 只读, 群成员的列表
static const char* TIMGroupSearchGroupMembersResultMemberInfoList = "group_search_member_result_member_info_list";

//------------------------------------------------------------------------------
// 12.5 GroupMemberInfoCustomString(群成员信息自定义字段)
// string, 只写, 自定义字段的key
static const char* kTIMGroupMemberInfoCustomStringInfoKey = "group_member_info_custom_string_info_key";
// string, 只写, 自定义字段的value
static const char* kTIMGroupMemberInfoCustomStringInfoValue = "group_member_info_custom_string_info_value";

//------------------------------------------------------------------------------
// 12.6 GroupModifyMemberInfoParam(设置群成员信息接口的参数)
// string, 只写(必填), 群组ID
static const char* kTIMGroupModifyMemberInfoParamGroupId = "group_modify_member_info_group_id";
// string, 只写(必填), 被设置信息的成员ID
static const char* kTIMGroupModifyMemberInfoParamIdentifier = "group_modify_member_info_identifier";
// uint @ref TIMGroupMemberModifyInfoFlag, 只写(必填), 修改类型,可设置多个值按位或
static const char* kTIMGroupModifyMemberInfoParamModifyFlag = "group_modify_member_info_modify_flag";
// uint @ref TIMReceiveMessageOpt, 只写(选填), 修改消息接收选项, 当 modify_flag 包含 kTIMGroupMemberModifyFlag_MsgFlag 时必填,其他情况不用填
static const char* kTIMGroupModifyMemberInfoParamMsgFlag = "group_modify_member_info_msg_flag";
// uint @ref TIMGroupMemberRole, 只写(选填), 修改成员角色, 当 modify_flag 包含 kTIMGroupMemberModifyFlag_MemberRole 时必填,其他情况不用填
static const char* kTIMGroupModifyMemberInfoParamMemberRole = "group_modify_member_info_member_role";
// uint, 只写(选填), 修改禁言时间, 当 modify_flag 包含 kTIMGroupMemberModifyFlag_ShutupTime 时必填,其他情况不用填
static const char* kTIMGroupModifyMemberInfoParamShutupTime = "group_modify_member_info_shutup_time";
// string, 只写(选填), 修改群名片, 当 modify_flag 包含 kTIMGroupMemberModifyFlag_NameCard 时必填,其他情况不用填
static const char* kTIMGroupModifyMemberInfoParamNameCard = "group_modify_member_info_name_card";
// array @ref GroupMemberInfoCustomString, 只写(选填), 请参考 [自定义字段](https://cloud.tencent.com/document/product/269/1502#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.AD.97.E6.AE.B5)
static const char* kTIMGroupModifyMemberInfoParamCustomInfo = "group_modify_member_info_custom_info";

//------------------------------------------------------------------------------
// 12.7 GroupInviteMemberParam(邀请成员接口的参数)
// string, 只写(必填), 群组ID
static const char* kTIMGroupInviteMemberParamGroupId = "group_invite_member_param_group_id";
// array string, 只写(必填), 被邀请加入群组用户ID数组
static const char* kTIMGroupInviteMemberParamIdentifierArray = "group_invite_member_param_identifier_array";
// string, 只写(选填), 用于自定义数据
static const char* kTIMGroupInviteMemberParamUserData = "group_invite_member_param_user_data";

//------------------------------------------------------------------------------
// 12.8 GroupInviteMemberResult(邀请成员接口的返回)
// string, 只读, 被邀请加入群组的用户ID
static const char* kTIMGroupInviteMemberResultIdentifier = "group_invite_member_result_identifier";
// uint @ref HandleGroupMemberResult, 只读, 邀请结果
static const char* kTIMGroupInviteMemberResultResult = "group_invite_member_result_result";

//------------------------------------------------------------------------------
// 12.9 GroupDeleteMemberParam(删除成员接口的参数)
// string, 只写(必填), 群组ID
static const char* kTIMGroupDeleteMemberParamGroupId = "group_delete_member_param_group_id";
// array string, 只写(必填), 被删除群组成员数组
static const char* kTIMGroupDeleteMemberParamIdentifierArray = "group_delete_member_param_identifier_array";
// string, 只写(选填), 用于自定义数据
static const char* kTIMGroupDeleteMemberParamUserData = "group_delete_member_param_user_data";
// uint32_t，只写(选填)，自被踢出群组开始算起，禁止被踢用户重新申请加群的时间间隔，单位：秒。7.2 版本开始支持
static const char* kTIMGroupDeleteMemberParamDuration = "group_delete_member_param_duration";

//------------------------------------------------------------------------------
// 12.10 GroupDeleteMemberResult(删除成员接口的返回)
// string, 只读, 删除的成员ID
static const char* kTIMGroupDeleteMemberResultIdentifier = "group_delete_member_result_identifier";
// uint @ref HandleGroupMemberResult, 只读, 删除结果
static const char* kTIMGroupDeleteMemberResultResult = "group_delete_member_result_result";

/////////////////////////////////////////////////////////////////////////////////
//
//                     十三. 群未决 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 13.1 GroupPendencyOption(获取群未决信息列表的参数)
// uint64, 只写(必填), 设置拉取时间戳,第一次请求填0,后边根据server返回的 @ref GroupPendencyResult 键kTIMGroupPendencyResultNextStartTime指定的时间戳进行填写
static const char* kTIMGroupPendencyOptionStartTime = "group_pendency_option_start_time";
// uint, 只写(选填), 拉取的建议数量,server可根据需要返回或多或少,不能作为完成与否的标志
static const char* kTIMGroupPendencyOptionMaxLimited = "group_pendency_option_max_limited";

//------------------------------------------------------------------------------
// 13.2 GroupPendency(群未决信息定义)
// string, 读写, 群组ID
static const char* kTIMGroupPendencyGroupId = "group_pendency_group_id";
// string, 读写, 请求者的 ID,例如：请求加群:请求者,邀请加群:邀请人
static const char* kTIMGroupPendencyFromIdentifier = "group_pendency_form_identifier";
// string, 只读, 请求者的昵称
static const char* kTIMGroupPendencyFromNickName = "group_pendency_from_nick_name";
// string, 只读, 请求者的头像
static const char* kTIMGroupPendencyFromFaceUrl = "group_pendency_from_face_url";
// string, 读写, 判决者的 ID，处理此条“加群的未决请求”的管理员ID
static const char* kTIMGroupPendencyToIdentifier = "group_pendency_to_identifier";
// uint64, 只读, 未决信息添加时间
static const char* kTIMGroupPendencyAddTime = "group_pendency_add_time";
// uint @ref TIMGroupPendencyType, 只读, 未决请求类型
static const char* kTIMGroupPendencyPendencyType = "group_pendency_pendency_type";
// uint @ref TIMGroupPendencyHandle, 只读, 群未决处理状态
static const char* kTIMGroupPendencyHandled = "group_pendency_handled";
// uint @ref TIMGroupPendencyHandleResult, 只读, 群未决处理操作类型
static const char* kTIMGroupPendencyHandleResult = "group_pendency_handle_result";
// string, 只读, 申请或邀请附加信息
static const char* kTIMGroupPendencyApplyInviteMsg = "group_pendency_apply_invite_msg";
// string, 只读, 申请或邀请者自定义字段
static const char* kTIMGroupPendencyFromUserDefinedData = "group_pendency_form_user_defined_data";
// string, 只读, 审批信息：同意或拒绝信息
static const char* kTIMGroupPendencyApprovalMsg = "group_pendency_approval_msg";
// string, 只读, 审批者自定义字段
static const char* kTIMGroupPendencyToUserDefinedData = "group_pendency_to_user_defined_data";
// string, 只读, 签名信息，客户不用关心
static const char* kTIMGroupPendencyKey = "group_pendency_key";
// string, 只读, 签名信息，客户不用关心
static const char* kTIMGroupPendencyAuthentication = "group_pendency_authentication";
// string, 只读, 自己的ID
static const char* kTIMGroupPendencySelfIdentifier = "group_pendency_self_identifier";

//------------------------------------------------------------------------------
// 13.3 GroupPendencyResult(获取群未决信息列表的返回)
// uint64, 只读, 下一次拉取的起始时戳,server返回0表示没有更多的数据,否则在下次获取数据时以这个时间戳作为开始时间戳
static const char* kTIMGroupPendencyResultNextStartTime = "group_pendency_result_next_start_time";
// uint64, 只读, 已读上报的时间戳
static const char* kTIMGroupPendencyResultReadTimeSeq = "group_pendency_result_read_time_seq";
// uint, 只读, 未决请求的未读数
static const char* kTIMGroupPendencyResultUnReadNum = "group_pendency_result_unread_num";
// array @ref GroupPendency, 只读, 群未决信息列表
static const char* kTIMGroupPendencyResultPendencyArray = "group_pendency_result_pendency_array";

//------------------------------------------------------------------------------
// 13.4 GroupHandlePendencyParam(处理群未决消息接口的参数)
// bool, 只写(选填), true表示接受，false表示拒绝。默认为false
static const char* kTIMGroupHandlePendencyParamIsAccept = "group_handle_pendency_param_is_accept";
// string, 只写(选填), 同意或拒绝信息,默认为空字符串
static const char* kTIMGroupHandlePendencyParamHandleMsg = "group_handle_pendency_param_handle_msg";
// object @ref GroupPendency, 只写(必填), 未决信息详情
static const char* kTIMGroupHandlePendencyParamPendency = "group_handle_pendency_param_pendency";


/////////////////////////////////////////////////////////////////////////////////
//
//                              十四. 废弃字段
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 14.1 GroupTipsElem(群组系统消息元素, 已废弃字段部分)
// string, 只读, 群组名称
static const char* kTIMGroupTipsElemGroupName = "group_tips_elem_group_name";
// uint, 只读, 群消息时间
static const char* kTIMGroupTipsElemTime = "group_tips_elem_time";

//------------------------------------------------------------------------------
// 14.2 GroupDetailInfo(群组详细信息，已废弃字段部分)
// uint, 只读, 群组在线成员数量,已废弃，请使用 @ref TIMGroupGetOnlineMemberCount 接口获取群在线人数
static const char* kTIMGroupDetailInfoOnlineMemberNum = "group_detail_info_online_member_num";

//------------------------------------------------------------------------------
// 14.3 以下为老版本拼写错误，为了兼容老版本而保留的宏定义
// enum TIMGroupModifyInfoFlag
#define kTIMGroupModifyInfoFlag_MaxMmeberNum  kTIMGroupModifyInfoFlag_MaxMemberNum
// enum TIMGroupMemberSearchFieldKey
#define kTIMGroupMemberSearchFieldKey_NikeName  kTIMGroupMemberSearchFieldKey_NickName
// GroupMemberInfoCustomString JsonKey
#define kTIMGroupMemberInfoCustemStringInfoKey    kTIMGroupMemberInfoCustomStringInfoKey
#define kTIMGroupMemberInfoCustemStringInfoValue  kTIMGroupMemberInfoCustomStringInfoValue
// GroupInfoCustomString JsonKey
#define kTIMGroupInfoCustemStringInfoKey    kTIMGroupInfoCustomStringInfoKey
#define kTIMGroupInfoCustemStringInfoValue  kTIMGroupInfoCustomStringInfoValue
// GroupBaseInfo JsonKey
#define kTIMGroupBaseInfoLastestSeq  kTIMGroupBaseInfoLatestSeq
// GroupDetailInfo JsonKey
#define kTIMGroupDetialInfoGroupId              kTIMGroupDetailInfoGroupId
#define kTIMGroupDetialInfoGroupType            kTIMGroupDetailInfoGroupType
#define kTIMGroupDetialInfoIsSupportTopic       kTIMGroupDetailInfoIsSupportTopic
#define kTIMGroupDetialInfoGroupName            kTIMGroupDetailInfoGroupName
#define kTIMGroupDetialInfoNotification         kTIMGroupDetailInfoNotification
#define kTIMGroupDetialInfoIntroduction         kTIMGroupDetailInfoIntroduction
#define kTIMGroupDetialInfoFaceUrl              kTIMGroupDetailInfoFaceUrl
#define kTIMGroupDetialInfoCreateTime           kTIMGroupDetailInfoCreateTime
#define kTIMGroupDetialInfoInfoSeq              kTIMGroupDetailInfoInfoSeq
#define kTIMGroupDetialInfoLastInfoTime         kTIMGroupDetailInfoLastInfoTime
#define kTIMGroupDetialInfoNextMsgSeq           kTIMGroupDetailInfoNextMsgSeq
#define kTIMGroupDetialInfoLastMsgTime          kTIMGroupDetailInfoLastMsgTime
#define kTIMGroupDetialInfoMemberNum            kTIMGroupDetailInfoMemberNum
#define kTIMGroupDetialInfoMaxMemberNum         kTIMGroupDetailInfoMaxMemberNum
#define kTIMGroupDetialInfoAddOption            kTIMGroupDetailInfoAddOption
#define kTIMGroupDetialInfoApproveOption        kTIMGroupDetailInfoApproveOption
#define kTIMGroupDetialInfoOnlineMemberNum      kTIMGroupDetailInfoOnlineMemberNum
#define kTIMGroupDetialInfoVisible              kTIMGroupDetailInfoVisible
#define kTIMGroupDetialInfoSearchable           kTIMGroupDetailInfoSearchable
#define kTIMGroupDetialInfoIsShutupAll          kTIMGroupDetailInfoIsShutupAll
#define kTIMGroupDetialInfoOwnerIdentifier      kTIMGroupDetailInfoOwnerIdentifier
#define kTIMGroupDetialInfoCustomInfo           kTIMGroupDetailInfoCustomInfo
// GroupGetOnlineMemberCountResult JsonKey
#define TIMGroupGetOnlineMemberCountResulCount  TIMGroupGetOnlineMemberCountResult
// GroupMemberInfo JsonKey
#define kTIMGroupMemberInfoRemark  kTIMGroupMemberInfoFriendRemark
// GroupSearchGroupMembersResult JsonKey
#define TIMGroupSearchGroupMembersdResultGroupID         TIMGroupSearchGroupMembersResultGroupID
#define TIMGroupSearchGroupMembersdResultMemberInfoList  TIMGroupSearchGroupMembersResultMemberInfoList

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_GROUP_MANAGER_H_
