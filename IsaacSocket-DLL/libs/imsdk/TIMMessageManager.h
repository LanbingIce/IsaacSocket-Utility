// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_MESSAGE_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_MESSAGE_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 消息接口，包含消息的收发、拉取、搜索、修改、删除、翻译、扩展以及回应等功能
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
//                        一. 消息功能相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 消息当前状态定义
enum TIMMsgStatus {
    // 消息正在发送
    kTIMMsg_Sending = 1,
    // 消息发送成功
    kTIMMsg_SendSucc = 2,
    // 消息发送失败
    kTIMMsg_SendFail = 3,
    // 消息已删除
    kTIMMsg_Deleted = 4,
    // 消息导入状态
    kTIMMsg_LocalImported = 5,
    // 消息撤回状态
    kTIMMsg_Revoked = 6,
    // 消息取消
    kTIMMsg_Cancel = 7,
};

// 1.2 标识消息的优先级，数字越大优先级越低
enum TIMMsgPriority {
    // 优先级最高，一般为红包或者礼物消息
    kTIMMsgPriority_High,
    // 表示优先级次之，建议为普通消息
    kTIMMsgPriority_Normal,
    // 建议为点赞消息等
    kTIMMsgPriority_Low,
    // 优先级最低，一般为成员进退群通知(后台下发)
    kTIMMsgPriority_Lowest,
};

// 1.3 平台信息
enum TIMPlatform {
    // 未知平台
    kTIMPlatform_Other = 0,
    // Windows平台
    kTIMPlatform_Windows,
    // Android平台
    kTIMPlatform_Android,
    // iOS平台
    kTIMPlatform_IOS,
    // MacOS平台
    kTIMPlatform_Mac,
    // iOS模拟器平台
    kTIMPlatform_Simulator,
};

// 1.4 消息元素的类型
enum TIMElemType {
    // 文本元素
    kTIMElem_Text,
    // 图片元素
    kTIMElem_Image,
    // 声音元素
    kTIMElem_Sound,
    // 自定义元素
    kTIMElem_Custom,
    // 文件元素
    kTIMElem_File,
    // 群组系统消息元素
    kTIMElem_GroupTips,
    // 表情元素
    kTIMElem_Face,
    // 位置元素
    kTIMElem_Location,
    // 群组系统通知元素
    kTIMElem_GroupReport,
    // 视频元素
    kTIMElem_Video,
    // 关系链变更消息元素
    kTIMElem_FriendChange,
    // 资料变更消息元素
    kTIMElem_ProfileChange,
    // 合并消息元素
    kTIMElem_Merge,
    // 未知元素类型
    kTIMElem_Invalid = -1,
};

// 1.5 图片质量级别
enum TIMImageLevel {
    // 原图发送
    kTIMImageLevel_Orig,
    // 高压缩率图发送(图片较小,默认值)
    kTIMImageLevel_Compression,
    // 高清图发送(图片较大)
    kTIMImageLevel_HD,
};

// 1.6 群组系统通知类型
enum TIMGroupReportType {
    // 未知类型
    kTIMGroupReport_None,
    // 申请加群(只有管理员会接收到)
    kTIMGroupReport_AddRequest,
    // 申请加群被同意(只有申请人自己接收到)
    kTIMGroupReport_AddAccept,
    // 申请加群被拒绝(只有申请人自己接收到)
    kTIMGroupReport_AddRefuse,
    // 被管理员踢出群(只有被踢者接收到)
    kTIMGroupReport_BeKicked,
    // 群被解散(全员接收)
    kTIMGroupReport_Delete,
    // 创建群(创建者接收, 不展示)
    kTIMGroupReport_Create,
    // 无需被邀请者同意，拉入群中（例如工作群）
    kTIMGroupReport_Invite,
    // 主动退群(主动退出者接收, 不展示)
    kTIMGroupReport_Quit,
    // 设置管理员(被设置者接收)
    kTIMGroupReport_GrantAdmin,
    // 取消管理员(被取消者接收)
    kTIMGroupReport_CancelAdmin,
    // 群已被回收(全员接收, 不展示)
    kTIMGroupReport_GroupRecycle,
    // 需要被邀请者审批的邀请入群请求
    kTIMGroupReport_InviteReqToInvitee,
    // 邀请加群被同意(只有发出邀请者会接收到)
    kTIMGroupReport_InviteAccept,
    // 邀请加群被拒绝(只有发出邀请者会接收到)
    kTIMGroupReport_InviteRefuse,
    // 已读上报多终端同步通知(只有上报人自己收到)
    kTIMGroupReport_ReadReport,
    // 用户自定义通知(默认全员接收)
    kTIMGroupReport_UserDefine,
    // 禁言某些用户(被禁言的用户收到)
    kTIMGroupReport_ShutUpMember,
    // 话题创建
    kTIMGroupReport_TopicCreate,
    // 话题被删除
    kTIMGroupReport_TopicDelete,
    // 群消息已读回执通知
    kTIMGroupReport_GroupMessageRead,
    // 消息接收选项变更通知
    kTIMGroupReport_GroupMessageRecvOption,
    // 被封禁通知
    kTIMGroupReport_BannedFromGroup,
    // 被解封通知
    kTIMGroupReport_UnbannedFromGroup,
    // 需要群主或管理员审批的邀请入群请求
    kTIMGroupReport_InviteReqToAdmin,
};

// 1.7 下载元素的类型
enum TIMDownloadType {
    // 视频缩略图
    kTIMDownload_VideoThumb = 0,
    // 文件
    kTIMDownload_File,
    // 视频
    kTIMDownload_Video,
    // 声音
    kTIMDownload_Sound,
};

// 1.8 消息搜索关键字的组合类型
enum TIMKeywordListMatchType {
    // 包含其中一个搜索关键字即可
    TIMKeywordListMatchType_Or,
    // 需要同时包含所有搜索关键字
    TIMKeywordListMatchType_And
};

// 1.9 群消息已读成员列表过滤
enum TIMGroupMessageReadMembersFilter {
    // 群消息已读成员列表
    TIM_GROUP_MESSAGE_READ_MEMBERS_FILTER_READ = 0,
    // 群消息未读成员列表
    TIM_GROUP_MESSAGE_READ_MEMBERS_FILTER_UNREAD = 1,
};


/////////////////////////////////////////////////////////////////////////////////
//
//                            二. 消息事件回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 新消息回调
 *
 * @param json_msg_array 新消息数组, Json Key 请参考 @ref Message
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * @note
 * 此回调可以获取新接收的消息数组。注意：消息内的元素也是一个数组。数组中每个元素的定义由 elem_type 字段决定
 *
 * __消息数组解析示例__
 * @code{.json}
 * Json::Value json_value_msgs; // 解析消息
 * Json::Reader reader;
 * if (!reader.parse(json_msg_array, json_value_msgs)) {
 *     printf("reader parse failure!%s", reader.getFormattedErrorMessages().c_str());
 *     return;
 * }
 * for (Json::ArrayIndex i = 0; i < json_value_msgs.size(); i++) {  // 遍历Message
 *     Json::Value& json_value_msg = json_value_msgs[i];
 *     Json::Value& elems = json_value_msg[kTIMMsgElemArray];
 *     for (Json::ArrayIndex m = 0; m < elems.size(); m++) {   // 遍历Elem
 *         Json::Value& elem = elems[i];
 *
 *         uint32_t elem_type = elem[kTIMElemType].asUInt();
 *         if (elem_type == TIMElemType::kTIMElem_Text) {  // 文本
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_Sound) {  // 声音
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_File) {  // 文件
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_Image) { // 图片
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_Custom) { // 自定义元素
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_GroupTips) { // 群组系统消息
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_Face) { // 表情
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_Location) { // 位置
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_GroupReport) { // 群组系统通知
 *
 *         } else if (elem_type == TIMElemType::kTIMElem_Video) { // 视频
 *
 *         }
 *     }
 * }
 * @endcode
 *
 * __返回一个文本消息的Json示例 (Json Key 请参考 @ref Message、 @ref TextElem)__
 * @code{.json}
 * [
 *    {
 *       "message_client_time" : 1551080111,
 *       "message_conv_id" : "user2",
 *       "message_conv_type" : 1,
 *       "message_elem_array" : [
 *          {
 *             "elem_type" : 0,
 *             "text_elem_content" : "123213213"
 *          }
 *       ],
 *       "message_is_from_self" : true,
 *       "message_is_read" : true,
 *       "message_rand" : 2130485001,
 *       "message_sender" : "user1",
 *       "message_seq" : 1,
 *       "message_server_time" : 1551080111,
 *       "message_status" : 2
 *    }
 * ]
 * @endcode
 *
 * __返回一个群通知消息的Json示例 (Json Key 请参考 @ref Message、 @ref GroupReportElem)__
 * @code{.json}
 * [
 *    {
 *       "message_client_time" : 1551344977,
 *       "message_conv_id" : "",
 *       "message_conv_type" : 3,
 *       "message_elem_array" : [
 *          {
 *             "elem_type" : 9,
 *             "group_report_elem_group_id" : "first group id",
 *             "group_report_elem_group_name" : "first group name",
 *             "group_report_elem_msg" : "",
 *             "group_report_elem_op_group_memberinfo" : {
 *                "group_member_info_custom_info" : {},
 *                "group_member_info_identifier" : "user1",
 *                "group_member_info_join_time" : 0,
 *                "group_member_info_member_role" : 0,
 *                "group_member_info_msg_flag" : 0,
 *                "group_member_info_msg_seq" : 0,
 *                "group_member_info_name_card" : "",
 *                "group_member_info_shutup_time" : 0
 *             },
 *             "group_report_elem_op_user" : "",
 *             "group_report_elem_platform" : "Windows",
 *             "group_report_elem_report_type" : 6,
 *             "group_report_elem_user_data" : ""
 *          }
 *       ],
 *       "message_is_from_self" : false,
 *       "message_is_read" : true,
 *       "message_rand" : 2207687390,
 *       "message_sender" : "@TIM#SYSTEM",
 *       "message_seq" : 1,
 *       "message_server_time" : 1551344977,
 *       "message_status" : 2
 *    }
 * ]
 * @endcode
 *
 * __返回一个群提示消息的Json示例 (Json Key 请参考 @ref Message、 @ref GroupTipsElem)__
 * @code{.json}
 * [
 *    {
 *       "message_client_time" : 1551412814,
 *       "message_conv_id" : "first group id",
 *       "message_conv_type" : 2,
 *       "message_elem_array" : [
 *          {
 *             "elem_type" : 6,
 *             "group_tips_elem_changed_group_memberinfo_array" : [],
 *             "group_tips_elem_group_change_info_array" : [
 *                {
 *                   "group_tips_group_change_info_flag" : 10,
 *                   "group_tips_group_change_info_value" : "first group name to other name"
 *                }
 *             ],
 *             "group_tips_elem_group_id" : "first group id",
 *             "group_tips_elem_group_name" : "first group name to other name",
 *             "group_tips_elem_member_change_info_array" : [],
 *             "group_tips_elem_member_num" : 0,
 *             "group_tips_elem_op_group_memberinfo" : {
 *                "group_member_info_custom_info" : {},
 *                "group_member_info_identifier" : "user1",
 *                "group_member_info_join_time" : 0,
 *                "group_member_info_member_role" : 0,
 *                "group_member_info_msg_flag" : 0,
 *                "group_member_info_msg_seq" : 0,
 *                "group_member_info_name_card" : "",
 *                "group_member_info_shutup_time" : 0
 *             },
 *             "group_tips_elem_op_user" : "user1",
 *             "group_tips_elem_platform" : "Windows",
 *             "group_tips_elem_time" : 0,
 *             "group_tips_elem_tip_type" : 6,
 *             "group_tips_elem_user_array" : []
 *          }
 *       ],
 *       "message_is_from_self" : false,
 *       "message_is_read" : true,
 *       "message_rand" : 1,
 *       "message_sender" : "@TIM#SYSTEM",
 *       "message_seq" : 1,
 *       "message_server_time" : 1551412814,
 *       "message_status" : 2
 *    },
 * ]
 * @endcode
 */
typedef void (*TIMRecvNewMsgCallback)(const char* json_msg_array, const void* user_data);

/**
 * 2.2 消息内元素相关文件上传进度回调
 *
 * @param json_msg 新消息, Json Key 请参考 @ref Message
 * @param index 上传 Elem 元素在 json_msg 消息的下标
 * @param cur_size 上传当前大小
 * @param total_size 上传总大小
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __示例__
 * @code{.cpp}
 * void MsgElemUploadProgressCallback(const char* json_msg, uint32_t index, uint32_t cur_size, uint32_t total_size, const void* user_data) {
 *     Json::Value json_value_msg;
 *     Json::Reader reader;
 *     if (!reader.parse(json_msg, json_value_msg)) {
 *         // Json 解析失败
 *         return;
 *     }
 *     Json::Value& elems = json_value_msg[kTIMMsgElemArray];
 *     if (index >= elems.size()) {
 *         // index 超过消息元素个数范围
 *         return;
 *     }
 *     uint32_t elem_type = elems[index][kTIMElemType].asUInt();
 *     if (kTIMElem_File ==  elem_type) {
 *
 *     }
 *     else if (kTIMElem_Sound == elem_type) {
 *
 *     }
 *     else if (kTIMElem_Video == elem_type) {
 *
 *     }
 *     else if (kTIMElem_Image == elem_type) {
 *
 *     }
 *     else {
 *         // 其他类型元素不符合上传要求
 *     }
 * }
 * @endcode
 */
typedef void (*TIMMsgElemUploadProgressCallback)(const char* json_msg, uint32_t index, uint32_t cur_size, uint32_t total_size, const void* user_data);

/**
 * 2.3 获取群消息已读群成员列表
 *
 * @param json_group_member_array 群消息已读群成员列表, Json Key 请参考 @ref GroupMemberInfo
 * @param next_seq 下一次分页拉取的游标
 * @param is_finished 群消息已读群成员列表是否已经拉取完毕
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __示例__
 * @code{.cpp}
 * void MsgGroupReadMembersCallback(const char* json_group_member_array, uint64_t next_seq, bool is_finished, const void* user_data) {
 *     Json::Value member_array;
 *     Json::Reader reader;
 *     if (!reader.parse(json_group_member_array, member_array)) {
 *         // Json 解析失败
 *         return;
 *     }
 *
 *     for (Json::ArrayIndex i = 0; i < member_array.size(); i++) {
 *         Json::Value& member = member_array[i];
 *         std::string user_id = member[kTIMGroupMemberInfoIdentifier].asString();
 *         std::string name_card = member[kTIMGroupMemberInfoNameCard].asString();
 *         std::string face_url = member[kTIMGroupMemberInfoFaceUrl].asString();
 *     }
 *
 *     if (false == is_finished) {
 *         TIMMsgGetGroupMessageReadMemberList(json_msg, TIM_GROUP_MESSAGE_READ_MEMBERS_FILTER_READ, next_seq, 100, MsgGroupReadMembersCallback, user_data);
 *     }
 * }
 * @endcode
 */
typedef void (*TIMMsgGroupMessageReadMemberListCallback)(const char* json_group_member_array, uint64_t next_seq, bool is_finished, const void* user_data);

/**
 * 2.4 收到消息已读回执
 *
 * @param json_msg_read_receipt_array 消息已读回执数组, Json Key 请参考 @ref MessageReceipt
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __示例__
 * @code{.cpp}
 * void MsgReadedReceiptCallback(const char* json_msg_read_receipt_array, const void* user_data) {
 *     Json::Value json_value_receipts;
 *     Json::Reader reader;
 *     if (!reader.parse(json_msg_read_receipt_array, json_value_receipts)) {
 *         // Json 解析失败
 *         return;
 *     }
 *
 *     for (Json::ArrayIndex i = 0; i < json_value_receipts.size(); i++) {
 *         Json::Value& json_value_receipt = json_value_receipts[i];
 *         uint32_t conv_type = json_value_receipt[kTIMMsgReceiptConvType].asUInt();
 *         std::string convid = json_value_receipt[kTIMMsgReceiptConvId].asString();
 *
 *         // C2C 消息回执
 *         uint64_t timestamp = json_value_receipt[kTIMMsgReceiptTimeStamp].asUInt64();
 *
 *         // 群消息回执
 *         std::string msg_id = json_value_receipt[kTIMMsgReceiptMsgId].asString();
 *         uint64_t read_count = json_value_receipt[kTIMMsgReceiptReadCount].asUInt64();
 *         uint64_t unread_count = json_value_receipt[kTIMMsgReceiptUnreadCount].asUInt64();
 *
 *         // 消息已读逻辑
 *     }
 * }
 * @endcode
 */
typedef void (*TIMMsgReadedReceiptCallback)(const char* json_msg_read_receipt_array, const void* user_data);

/**
 * 2.5 接收的消息被撤回回调
 *
 * @param json_msg_revoke_info_array 撤回信息数组, Json Key 请参考 @ref Message,  @ref MsgLocator
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * @note 从 7.4 版本开始，该回调支持返回撤回者信息和撤回原因
 *
 * __示例__
 * @code{.cpp}
 * void MsgRevokeCallback(const char* json_msg_revoke_info_array, const void* user_data) {
 *     Json::Value json_value_revoke_info_list;
 *     Json::Reader reader;
 *     if (!reader.parse(json_msg_revoke_info_array, json_value_revoke_info_list)) {
 *         // Json 解析失败
 *         return;
 *     }
 *     for (Json::ArrayIndex i = 0; i < json_value_revoke_info_list.size(); i++) {
 *         Json::Value& json_value_revoke_info = json_value_revoke_info_list[i];
 *
 *         // 撤回的消息标识符
 *         std::string convid = json_value_revoke_info[kTIMMsgLocatorConvId].asString();
 *         uint32_t conv_type = json_value_revoke_info[kTIMMsgLocatorConvType].asUInt();
 *         bool isrevoke      = json_value_revoke_info[kTIMMsgLocatorIsRevoked].asBool();
 *         uint64_t time      = json_value_revoke_info[kTIMMsgLocatorTime].asUInt64();
 *         uint64_t seq       = json_value_revoke_info[kTIMMsgLocatorSeq].asUInt64();
 *         uint64_t rand      = json_value_revoke_info[kTIMMsgLocatorRand].asUInt64();
 *         bool isself        = json_value_revoke_info[kTIMMsgLocatorIsSelf].asBool();
 *
 *         // 撤回者
 *         std::string revoker_id = json_value_revoke_info[kTIMMsgRevokerUserID].asString();
 *         std::string revoker_nick_name = json_value_revoke_info[kTIMMsgRevokerNickName].asString();
 *         std::string revoker_face_url = json_value_revoke_info[kTIMMsgRevokerFaceUrl].asString();
 *
 *         // 撤回原因
 *         std::string revoke_reason = json_value_revoke_info[kTIMMsgRevokeReason].asString();
 *
 *         // 消息撤回逻辑
 *     }
 * }
 * @endcode
 */
typedef void (*TIMMsgRevokeCallback)(const char* json_msg_revoke_info_array, const void* user_data);

/**
 * 2.6 消息更新回调
 *
 * @param json_msg_array 更新的消息数组, Json Key 请参考 @ref Message
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * @note
 * 请参考 @ref TIMRecvNewMsgCallback
 */
typedef void (*TIMMsgUpdateCallback)(const char* json_msg_array, const void* user_data);

/**
 * 2.7 消息扩展信息更新回调
 *
 * @param message_id 消息 ID
 * @param message_extension_array 扩展信息列表, Json Key 请参考 @ref MessageExtension
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __返回的扩展信息列表 json 示例__
 * @code{.json}
 * [
 *    {
 *        "message_extension_key":"extension_key_1",
 *        "message_extension_value":"extension_value_1"
 *    },
 *    {
 *        "message_extension_key":"extension_key_2",
 *        "message_extension_value":"extension_value_2"
 *    }
 * ]
 * @endcode
 */
typedef void (*TIMMsgExtensionsChangedCallback)(const char* message_id, const char* message_extension_array, const void* user_data);

/**
 * 2.8 消息扩展信息删除回调
 *
 * @param message_id 消息 ID
 * @param message_extension_key_array 扩展信息的关键字列表, Json Key 请参考 @ref MessageExtension
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __返回的扩展信息的关键字列表 json 示例__
 * @code{.json}
 * [
 *    {
 *        "message_extension_key":"extension_key_1",
 *    }
 * ]
 * @endcode
 */
typedef void (*TIMMsgExtensionsDeletedCallback)(const char* message_id, const char* message_extension_key_array, const void* user_data);

/**
 * 2.9 消息回应信息更新回调
 *
 * @param message_reaction_change_info_array 回应信息变更列表, Json Key 请参考 @ref MessageReactionChangeInfo
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * @note
 *  - 该回调是消息 Reaction 的增量回调，只会携带变更的 Reaction 信息。
 *  - 当变更的 Reaction 信息里的 message_reaction_total_user_count 字段值为 0 时，表明该 Reaction 已经没有用户在使用，您可以在 UI 上移除该 Reaction 的展示。
 *
 * __返回的回应信息列表 json 示例__
 * @code{.json}
 * [
 *     {
 *         "message_reaction_change_info_msg_id":"12345678910-1689942227-1328217716",
 *         "message_reaction_change_info_reaction_list":[
 *             {
 *                 "message_reaction_id":"emoji1",
 *                 "message_reaction_total_user_count":1,
 *                 "message_reaction_user_info_array":[
 *                     {
 *                         "user_profile_face_url":"www.google.com",
 *                         "user_profile_identifier":"kkkm",
 *                         "user_profile_nick_name":"mizore",
 *                     }
 *                 ]
 *             }
 *         ]
 *     }
 * ]
 * @endcode
 */
typedef void (*TIMMsgReactionsChangedCallback)(const char* message_reaction_change_info_array, const void* user_data);

/**
 * 2.10 登录用户全局消息接收选项变更通知
 *
 * @param json_receive_message_option_info 当前用户全局消息接收选项，请参考 @ref TIMReceiveMessageOptInfo
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMMsgAllMessageReceiveOptionCallback)(const char* json_receive_message_option_info, const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                          三. 注册消息事件回调 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 添加接收新消息回调
 * 
 * @param cb 新消息回调函数，请参考 @ref TIMRecvNewMsgCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 如果用户是登录状态，ImSDK收到新消息会通过此接口设置的回调抛出，另外需要注意，抛出的消息不一定是未读的消息，
 * 只是本地曾经没有过的消息（例如在另外一个终端已读，拉取最近联系人消息时可以获取会话最后一条消息，如果本地没有，会通过此方法抛出）。
 * 在用户登录之后，ImSDK会拉取离线消息，为了不漏掉消息通知，需要在登录之前注册新消息通知。
 */
TIM_API void TIMAddRecvNewMsgCallback(TIMRecvNewMsgCallback cb, const void* user_data);

/**
 * 3.2 删除接收新消息回调
 * 
 * @param cb 新消息回调函数，请参考 @ref TIMRecvNewMsgCallback
 *
 * @note
 * 参数cb需要跟 @ref TIMAddRecvNewMsgCallback 传入的cb一致，否则删除回调失败
 */
TIM_API void TIMRemoveRecvNewMsgCallback(TIMRecvNewMsgCallback cb);

/**
 * 3.3 设置消息内元素相关文件上传进度回调
 *
 * @param cb 文件上传进度回调，请参考 @ref TIMMsgElemUploadProgressCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 设置消息元素上传进度回调。当消息内包含图片、声音、文件、视频元素时，ImSDK会上传这些文件，并触发此接口设置的回调，用户可以根据回调感知上传的进度
 */
TIM_API void TIMSetMsgElemUploadProgressCallback(TIMMsgElemUploadProgressCallback cb, const void* user_data);

/**
 * 3.4 设置消息已读回执回调
 *
 * @param cb  消息已读回执回调，请参考 @ref TIMMsgReadedReceiptCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 发送方发送消息，接收方调用接口 @ref TIMMsgReportReaded 上报 C2C 消息已读，或者调用 @ref TIMMsgSendMessageReadReceipts 发送群消息已读回执，发送方ImSDK会通过此接口设置的回调抛出。
 */
TIM_API void TIMSetMsgReadedReceiptCallback(TIMMsgReadedReceiptCallback cb, const void* user_data);

/**
 * 3.5 设置接收的消息被撤回回调
 *
 * @param cb 消息撤回通知回调,请参考 @ref TIMMsgRevokeCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 发送方发送消息，接收方收到消息。此时发送方调用接口 @ref TIMMsgRevoke 撤回该消息，接收方的ImSDK会通过此接口设置的回调抛出。
 */
TIM_API void TIMSetMsgRevokeCallback(TIMMsgRevokeCallback cb, const void* user_data);

/**
 * 3.6 设置消息更新的回调
 *
 * @param cb 消息更新回调，请参考 @ref TIMMsgUpdateCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 *  - 当您发送的消息在服务端被修改后，ImSDK会通过该回调通知给您
 *  - 您可以在您自己的服务器上拦截所有即时通信IM消息 [发单聊消息之前回调](https://cloud.tencent.com/document/product/269/1632)
 *  - 设置成功之后，即时通信IM服务器会将您的用户发送的每条消息都同步地通知给您的业务服务器。
 *  - 您的业务服务器可以对该条消息进行修改（例如过滤敏感词），如果您的服务器对消息进行了修改，ImSDK就会通过此回调通知您。
 */
TIM_API void TIMSetMsgUpdateCallback(TIMMsgUpdateCallback cb, const void* user_data);

/**
 * 3.7 设置消息扩展信息更新的回调
 *
 * @param cb 消息扩展信息更新回调,请参考 @ref TIMMsgExtensionsChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 */
TIM_API void TIMSetMsgExtensionsChangedCallback(TIMMsgExtensionsChangedCallback cb, const void* user_data);

/**
 * 3.8 设置消息扩展信息删除的回调
 * 
 * @param cb 消息扩展信息删除回调,请参考 @ref TIMMsgExtensionsDeletedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 */
TIM_API void TIMSetMsgExtensionsDeletedCallback(TIMMsgExtensionsDeletedCallback cb, const void* user_data);

/**
 * 3.9 设置消息回应信息更新的回调
 * 
 * @param cb 消息回应信息更新回调,请参考 @ref TIMMsgReactionsChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 */
TIM_API void TIMSetMsgReactionsChangedCallback(TIMMsgReactionsChangedCallback cb, const void* user_data);

/**
 * 3.10 设置全局消息接收选项的回调
 * 
 * @param cb 消息更新回调，请参考 @ref TIMMsgAllMessageReceiveOptionCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 */
TIM_API void TIMSetMsgAllMessageReceiveOptionCallback(TIMMsgAllMessageReceiveOptionCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                            四. 消息收发相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 4.1 发送新消息
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_param  消息 json 字符串, Json Key 请参考 @ref Message
 * @param message_id_buffer 消息 ID ，分配内存大小不能低于 128 字节，如果不需要，可传入 nullptr，调用接口后，可以读取到以 '\0' 结尾的字符串
 * @param cb 发送新消息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数 cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 * 发送新消息，单聊消息和群消息的发送均采用此接口：
 *  - 发送单聊消息时 conv_id 为对方的UserID， conv_type 为 kTIMConv_C2C
 *  - 发送群聊消息时 conv_id 为群ID， conv_type 为 kTIMConv_Group
 * 发送消息时不能发送 kTIMElem_GroupTips、 kTIMElem_GroupReport，他们由后台下发，用于更新(通知)群的信息。可以发送的消息内元素：
 *  - 文本消息元素，请参考 @ref TextElem
 *  - 表情消息元素，请参考 @ref FaceElem
 *  - 位置消息元素，请参考 @ref LocationElem
 *  - 图片消息元素，请参考 @ref ImageElem
 *  - 声音消息元素，请参考 @ref SoundElem
 *  - 自定义消息元素，请参考 @ref CustomElem
 *  - 文件消息元素，请参考 @ref FileElem
 *  - 视频消息元素，请参考 @ref VideoElem
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_text;
 * json_value_text[kTIMElemType] = kTIMElem_Text;
 * json_value_text[kTIMTextElemContent] = "send text";
 * Json::Value json_value_msg;
 * json_value_msg[kTIMMsgElemArray].append(json_value_text);
 *
 * const size_t kMessageIDLength = 128;
 * char message_id_buffer[kMessageIDLength] = {0};
 * int ret = TIMMsgSendMessage(conv_id.c_str(), kTIMConv_C2C, json_value_msg.toStyledString().c_str(), message_id_buffer,
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 消息发送失败
 *         return;
 *     }
 *     // 消息发送成功
 * }, nullptr);
 *
 * // json_value_msg.toStyledString().c_str() 得到 json_msg_param JSON 字符串如下
 * {
 *    "message_id" : "14400111550110000_1551446728_45598731"
 *    "message_client_time" : 1551446728,
 *    "message_elem_array" : [
 *       {
 *          "elem_type" : 0,
 *          "text_elem_content" : "send text"
 *       }
 *    ],
 *    "message_sender" : "user1",
 *    "message_server_time" : 1551446728
 * }
 * @endcode
 */
TIM_API int TIMMsgSendMessage(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_param, char* message_id_buffer, TIMCommCallback cb, const void* user_data);

/**
 * 4.2 根据消息 messageID 取消发送中的消息
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param message_id  消息 ID
 * @param cb 取消结果的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * TIMMsgCancelSend("test_win_03", kTIMConv_C2C, "message_id_1", [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgCancelSend(const char* conv_id, enum TIMConvType conv_type, const char* message_id, TIMCommCallback cb, const void* user_data);

/**
 * 4.3 群发消息，该接口不支持向群组发送消息。
 *
 * @param json_batch_send_param  群发消息 json 字符串, Json Key 请参考 @ref Message
 * @param cb 群发消息成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 * 批量发送消息的接口，每个UserID发送成功与否，通过回调cb返回。
 *
 * __示例__
 * @code{.cpp}
 * //构造消息文本元素
 * Json::Value json_value_elem;
 * json_value_elem[kTIMElemType] = TIMElemType::kTIMElem_Text;
 * json_value_elem[kTIMTextElemContent] = "this is batch send msg";
 * //构造消息
 * Json::Value json_value_msg;
 * json_value_msg[kTIMMsgElemArray].append(json_value_elem);
 *
 * // 构造批量发送ID数组列表
 * Json::Value json_value_ids(Json::arrayValue);
 * json_value_ids.append("user2");
 * json_value_ids.append("user3");
 * // 构造批量发送接口参数
 * Json::Value json_value_batchsend;
 * json_value_batchsend[kTIMMsgBatchSendParamIdentifierArray] = json_value_ids;
 * json_value_batchsend[kTIMMsgBatchSendParamMsg] = json_value_msg;
 * int ret = TIMMsgBatchSend(json_value_batchsend.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 * }, nullptr);
 *
 * // json_value_batchsend.toStyledString().c_str() 得到 json_batch_send_param JSON 字符串如下
 * {
 *    "msg_batch_send_param_identifier_array" : [ "user2", "user3" ],
 *    "msg_batch_send_param_msg" : {
 *       "message_client_time" : 1551340614,
 *       "message_elem_array" : [
 *          {
 *             "elem_type" : 0,
 *             "text_elem_content" : "this is batch send msg"
 *          }
 *       ],
 *       "message_sender" : "user1",
 *       "message_server_time" : 1551340614
 *    }
 * }
 * @endcode
 */
TIM_API int TIMMsgBatchSend(const char* json_batch_send_param, TIMCommCallback cb, const void* user_data);

/**
 * 4.4 下载消息内元素到指定文件路径(图片、视频、音频、文件)
 *
 * @param json_download_elem_param  下载的参数 Json 字符串, Json Key 请参考 @ref DownloadElemParam
 * @param path 下载文件保存路径
 * @param cb 下载成功与否的回调以及下载进度回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 * 此接口用于下载消息内图片、文件、声音、视频等元素。下载的参数 kTIMMsgDownloadElemParamId、kTIMMsgDownloadElemParamBusinessId、kTIMMsgDownloadElemParamUrl 均可以在相应元素内找到。
 * 其中 kTIMMsgDownloadElemParamType 为下载文件类型 @ref TIMDownloadType, 参数 path 要求是 UTF-8 编码
 *
 * __示例__
 * @code{.cpp}
 * Json::Value download_param;
 * download_param[kTIMMsgDownloadElemParamType] = type;
 * download_param[kTIMMsgDownloadElemParamId] = id;
 * download_param[kTIMMsgDownloadElemParamBusinessId] = business_id;
 * download_param[kTIMMsgDownloadElemParamUrl] = url;
 *
 * TIMMsgDownloadElemToPath(download_param.toStyledString().c_str(), (path_ + "\\" + name).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgDownloadElemToPath(const char* json_download_elem_param, const char* path, TIMCommCallback cb, const void* user_data);

/**
 * 4.5 下载合并消息
 *
 * @param json_single_msg  单条消息的 JSON 字符串，接收消息、查找消息或查询历史消息时获取到的消息, Json Key 请参考 @ref Message
 * @param cb 下载成功与否的回调以及下载进度回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * // 接收一条消息 json_single_msg
 * TIMMsgDownloadMergerMessage(json_single_msg, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgDownloadMergerMessage(const char* json_single_msg, TIMCommCallback cb, const void* user_data);

/**
 * 4.6 设置消息自定义数据（本地保存，不会发送到对端，程序卸载重装后失效）
 *
 * @param json_msg_param  消息 json 字符串, Json Key 请参考 @ref Message
 * @param cb 保存自定义消息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __示例__
 * @code{.cpp}
 *   Json::Value json_parameters;
 *   json_parameters[kTIMMsgGetMsgListParamIsRamble] = true;
 *   json_parameters[kTIMMsgGetMsgListParamIsForward] = false;
 *   json_parameters[kTIMMsgGetMsgListParamCount] = 1;
 *   TIMMsgGetMsgList("98826", kTIMConv_C2C, json_parameters.toStyledString().c_str(),
 *      [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *       Json::Reader json_reader;
 *       json::Array json_message_array;
 *       json_reader.parse(json_params, json_message_array);
 *          if (json_message_array.size() > 0) {
 *              Json::Value json_obj_msg = json_message_array[0];
 *              json_obj_msg[kTIMMsgCustomStr] = "custom Str";
 *              json_obj_msg[kTIMMsgCustomInt] = "custom int";
 *              TIMMsgSetLocalCustomData(json_obj_msg.toStyledString().c_str(),
 *                  [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *                      printf("TIMMsgSetLocalCustomData complete|code:%d|desc:%s\n", code, desc);
 *                  }, nullptr);
 *          }
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgSetLocalCustomData(const char* json_msg_param, TIMCommCallback cb, const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                   五. 消息接收选项（接收|接收但不提醒|不接收）相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 5.1 设置针对某个用户的 C2C 消息接收选项（支持批量设置）
 *
 * @param json_identifier_array 用户 ID 列表
 * @param opt 消息接收选项，请参考 @ref TIMReceiveMessageOpt
 * @param cb 设置成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_identifier_array(Json::arrayValue);
 * json_identifier_array.append("user1");
 * json_identifier_array.append("user2");
 *
 * TIMMsgSetC2CReceiveMessageOpt(json_identifier_array.toStyledString().c_str(), kTIMRecvMsgOpt_Receive, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 *
 * @note
 *  - 该接口支持批量设置，您可以通过参数 userIDList 设置一批用户，但一次最大允许设置 30 个用户。
 *  - 该接口调用频率被限制为1秒内最多调用5次。
 * @endcode
 */
TIM_API int TIMMsgSetC2CReceiveMessageOpt(const char* json_identifier_array, TIMReceiveMessageOpt opt, TIMCommCallback cb, const void* user_data);

/**
 * 5.2 查询针对某个用户的 C2C 消息接收选项
 *
 * @param json_identifier_array 用户 ID 列表
 * @param cb 查询结果的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_identifier_array(Json::arrayValue);
 * json_identifier_array.append("user1");
 * json_identifier_array.append("user2");
 *
 * TIMMsgGetC2CReceiveMessageOpt(json_identifier_array.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 *
 * // 回调的 json_param 示例。Json Key请参考 @ref GetC2CRecvMsgOptResult
 * [
 *    {
 *       "msg_recv_msg_opt_result_identifier" : "user1",
 *       "msg_recv_msg_opt_result_opt" : 0,
 *    },
 *    {
 *       "msg_recv_msg_opt_result_identifier" : "user2",
 *       "msg_recv_msg_opt_result_opt" : 1,
 *    }
 * ]
 * @endcode
 */
TIM_API int TIMMsgGetC2CReceiveMessageOpt(const char* json_identifier_array, TIMCommCallback cb, const void* user_data);

/**
 * 5.3 设置群消息的接收选项
 *
 * @param group_id 群 ID
 * @param opt 消息接收选项，请参考 @ref TIMReceiveMessageOpt
 * @param cb 设置成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 查询群消息的接收选项：您可以在群资料（GroupBaseInfo）中获得这个信息
 *
 * __示例__
 * @code{.cpp}
 * TIMMsgSetGroupReceiveMessageOpt("group_id", kTIMRecvMsgOpt_Receive, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgSetGroupReceiveMessageOpt(const char* group_id, TIMReceiveMessageOpt opt, TIMCommCallback cb, const void* user_data);

/**
 * 5.4 设置登录用户全局消息接收选项，从 7.4 版本开始支持
 *
 * @param opt                      全局消息接收选项设置，请参考 @ref TIMReceiveMessageOpt
 * @param start_hour (0 - 23)      免打扰开始时间：小时，取值范围[0 - 23]
 * @param start_minute (0 - 59)    免打扰开始时间：分钟，取值范围[0 - 59]
 * @param start_second (0 - 59)    免打扰开始时间：秒，取值范围[0 - 59]
 * @param duration                 免打扰持续时长：单位：秒，取值范围 [0 - 24*60*60].
 * @param cb 设置成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意
 *  - 当 duration 的取值小于 24*60*60 时，可用于实现重复免打扰，即消息免打扰从每天的 start_hour:start_minute:start_second 表示的时间点开始，持续时长为 duration 秒
 *  - 当 duration 取值不小于 24*60*60 时，可用于实现永久免打扰，即从调用该 API 当天 start_hour:start_minute:start_second 表示的时间点开始永久消息免打扰
 *
 * __示例__
 * @code{.cpp}
 * TIMMsgSetAllReceiveMessageOpt(kTIMRecvMsgOpt_Receive, 12, 0, 0, 60*60*2, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgSetAllReceiveMessageOpt(TIMReceiveMessageOpt opt, int32_t start_hour, int32_t start_minute, int32_t start_second, uint32_t duration, TIMCommCallback cb, const void* user_data);

/**
 * 5.5设置登录用户全局消息接收选项，从 7.4 版本开始支持
 *
 * @param opt                      全局消息接收选项设置，请参考 @ref TIMReceiveMessageOpt
 * @param start_time_stamp           免打扰开始时间，UTC 时间戳，单位：秒
 * @param duration                 免打扰持续时长：单位：秒
 * @param cb 设置成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * TIMMsgSetAllReceiveMessageOpt(kTIMRecvMsgOpt_Receive, 123456, 60*60*2, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgSetAllReceiveMessageOpt2(TIMReceiveMessageOpt opt, uint32_t start_time_stamp, uint32_t duration, TIMCommCallback cb, const void* user_data);

/**
 * 5.6 获取登录用户全局消息接收选项，从 7.4 版本开始支持
 *
 * @param cb 查询结果的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * TIMMsgGetAllReceiveMessageOpt([](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, this);
 * @endcode
 *
 * __回调的 json_param 示例 (Json Key 请参考 @ref TIMReceiveMessageOptInfo)__
 * @code{.cpp}
 * [
 *    {
 *       "kTIMMsgAllRecvMsgOptLevel" : "kTIMRecvMsgOpt_Not_Notify",
 *       "kTIMMsgAllRecvMsgOptStartHour" : 12,    // 免打扰开始时间：小时
 *       "kTIMMsgAllRecvMsgOptStartMinute" : 0,    // 免打扰开始时间：分钟
 *       "kTIMMsgAllRecvMsgOptStartSecond" : 0,    // 免打扰开始时间：秒
 *       "kTIMMsgAllRecvMsgOptStartTimeStamp" : 0,
 *       "kTIMMsgAllRecvMsgDuration" : 7200,
 *    }
 * ]
 *
 * // 或者
 *
 * [
 *    {
 *       "kTIMMsgAllRecvMsgOptLevel" : "kTIMRecvMsgOpt_Not_Notify",
 *       "kTIMMsgAllRecvMsgOptStartHour" : 0,
 *       "kTIMMsgAllRecvMsgOptStartMinute" : 0,
 *       "kTIMMsgAllRecvMsgOptStartSecond" : 0,
 *       "kTIMMsgAllRecvMsgOptStartTimeStamp" : 123456,    // 免打扰开始时间，UTC 时间戳，单位：秒
 *       "kTIMMsgAllRecvMsgDuration" : 7200,
 *    }
 * ]
 * @endcode
 */
TIM_API int TIMMsgGetAllReceiveMessageOpt(TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                   六. 消息拉取、撤回、删除、标记已读等相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 6.1 获取指定会话的历史消息
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_get_msg_param 消息获取参数，Json Key 定义请参考 @ref MsgGetMsgListParam
 * @param cb 获取指定会话的消息列表成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 * 从 kTIMMsgGetMsgListParamLastMsg 指定的消息开始获取本地消息列表，kTIMMsgGetMsgListParamCount 为要获取的消息数目。kTIMMsgGetMsgListParamLastMsg 可以不指定，不指定时表示以会话最新的消息为 LastMsg 。
 * 若指定 kTIMMsgGetMsgListParamIsRamble 为 true 则本地消息获取不够指定数目时，会去获取云端漫游消息。
 * kTIMMsgGetMsgListParamIsForward 为 true 时表示获取比 kTIMMsgGetMsgListParamLastMsg 新的消息，为 false 时表示获取比 kTIMMsgGetMsgListParamLastMsg 旧的消息
 *
 * 拉取 kTIMConv_C2C 消息时，只能使用 kTIMMsgGetMsgListParamLastMsg 作为消息的拉取起点；如果没有指定 kTIMMsgGetMsgListParamLastMsg，默认使用会话的最新消息作为拉取起点
 * 拉取 kTIMConv_Group 消息时，除了可以使用 kTIMMsgGetMsgListParamLastMsg 作为消息的拉取起点外，也可以使用 kTIMMsgGetMsgListParamLastMsgSeq 来指定消息的拉取起点，二者的区别在于：
 *  - 使用 kTIMMsgGetMsgListParamLastMsg 作为消息的拉取起点时，返回的消息列表里不包含 kTIMMsgGetMsgListParamLastMsg；
 *  - 使用 kTIMMsgGetMsgListParamLastMsgSeq 作为消息拉取起点时，返回的消息列表里包含 kTIMMsgGetMsgListParamLastMsgSeq 所表示的消息；
 *
 * 在拉取 kTIMConv_Group 消息时
 *  - 如果同时指定了 kTIMMsgGetMsgListParamLastMsg 和 kTIMMsgGetMsgListParamLastMsgSeq，SDK 优先使用 kTIMMsgGetMsgListParamLastMsg 作为消息的拉取起点
 *  - 如果 kTIMMsgGetMsgListParamLastMsg 和 kTIMMsgGetMsgListParamLastMsgSeq，SDK 都未指定，消息的拉取起点分为如下两种情况：
 *  - 如果设置了拉取的时间范围，SDK 会根据 kTIMMsgGetMsgListParamTimeBegin 所描述的时间点作为拉取起点
 *  - 如果未设置拉取的时间范围，SDK 默认使用会话的最新消息作为拉取起点
 *  - 如果设置了 kTIMMsgGetMsgListParamMessageSequenceArray，则 SDK 优先按照指定的 sequence 返回消息列表
 *
 * 请注意以下特殊逻辑：
 *  - 如果没有触发登录，调用该接口不会返回历史消息
 *  - 如果登录失败，调用该接口会返回本地历史消息
 *  - 如果 SDK 检测到没有网络，调用该接口会返回本地历史消息
 *  - 如果登录成功且网络正常，当 kTIMMsgGetMsgListParamIsRamble 设置为 true 时，调用该接口会先请求云端历史消息，然后再和本地历史消息合并后返回
 *  - 只有会议群（Meeting）才能拉取到进群前的历史消息，直播群（AVChatRoom）消息不存漫游和本地数据库，调用这个接口无效
 *
 * __获取 C2C 会话 Windows-02 消息列表示例__
 * @code{.cpp}
 * Json::Value json_msg(Json::objectValue); // 构造Message
 * Json::Value json_get_msg_param;
 * json_get_msg_param[kTIMMsgGetMsgListParamLastMsg] = json_msg;
 * json_get_msg_param[kTIMMsgGetMsgListParamIsRamble] = false;
 * json_get_msg_param[kTIMMsgGetMsgListParamIsForward] = true;
 * json_get_msg_param[kTIMMsgGetMsgListParamCount] = 100;
 *
 * int ret = TIMMsgGetMsgList("Windows-02", kTIMConv_C2C, json_get_msg_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 * }, this);
 *
 * // json_get_msg_param.toStyledString().c_str() 得到 json_get_msg_param JSON 字符串如下
 * {
 *    "msg_getmsglist_param_count" : 100,
 *    "msg_getmsglist_param_is_forward" : true,
 *    "msg_getmsglist_param_is_ramble" : false,
 *    "msg_getmsglist_param_last_msg" : {}
 * }
 * @endcode
 */
TIM_API int TIMMsgGetMsgList(const char* conv_id, enum TIMConvType conv_type, const char* json_get_msg_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.2 消息撤回
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_param  消息 json 字符串, Json Key 请参考 @ref Message
 * @param cb 消息撤回成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 消息撤回。使用保存的消息Json或者用消息定位符查找到的消息Json，避免重复构造消息Json.
 *  - 撤回消息的时间限制默认 2 minutes，超过 2 minutes 的消息不能撤回，您也可以在 [控制台](https://console.cloud.tencent.com/im)（功能配置 -> 登录与消息 -> 消息撤回设置）自定义撤回时间限制。
 *  - 仅支持单聊和群组中发送的普通消息，无法撤销 kTIMMsgIsOnlineMsg 为 true 即仅在线用户才能收到的消息。
 *  - 如果发送方撤回消息，已经收到消息的一方会收到 TIMMsgRevokeExCallback 回调。
 *  - 从 IMSDK 7.4 版本开始，支持撤回包括直播群（AVChatRoom）、社群在内的所有群类型的消息。
 *  - 在单聊场景中，仅能撤回自己的消息；在群聊场景中，除了可以撤回自己的消息外，管理员或者群主也可以撤回其他群成员的消息。
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_text;
 * json_value_text[kTIMElemType] = kTIMElem_Text;
 * json_value_text[kTIMTextElemContent] = "send text";
 * Json::Value json_value_msg;
 * json_value_msg[kTIMMsgElemArray].append(json_value_text);
 *
 * int ret = TIMMsgSendNewMsg("test_win_03", kTIMConv_C2C, json_value_msg.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 消息发送失败
 *         return;
 *     }
 *     // 消息发送成功 json_param 返回发送后的消息json字符串
 *     TIMMsgRevoke("test_win_03", kTIMConv_C2C, json_param, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         if (ERR_SUCC != code) {
 *             // 消息撤回失败
 *             return;
 *         }
 *         // 消息撤回成功
 *
 *     }, user_data);
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgRevoke(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.3 消息变更
 * 
 * @param json_msg_param  消息 json 字符串, Json Key 请参考 @ref Message
 * @param cb 修改消息内容成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 如果消息修改成功，自己和对端用户（C2C）或群组成员（Group）都会收到 TIMSetMsgUpdateCallback 设置的回调。
 *  - 如果在修改消息过程中，消息已经被其他人修改，cb 会返回 ERR_SDK_MSG_MODIFY_CONFLICT 错误。
 *  - 消息无论修改成功或则失败，cb 都会返回最新的消息对象。
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_text;
 * json_value_text[kTIMElemType] = kTIMElem_Text;
 * json_value_text[kTIMTextElemContent] = "send text";
 * Json::Value json_value_msg;
 * json_value_msg[kTIMMsgElemArray].append(json_value_text);
 *
 * int ret = TIMMsgSendNewMsg("test_win_03", kTIMConv_C2C, json_value_msg.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 消息发送失败
 *         return;
 *     }
 *     // 消息发送成功 json_param 返回发送后的消息json字符串
 *     TIMMsgModifyMessage(json_param, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         if (ERR_SUCC != code) {
 *             // 修改消息内容失败
 *             return;
 *         }
 *         // 修改消息内容成功
 *
 *     }, user_data);
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgModifyMessage(const char* json_msg_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.4 删除指定会话的消息
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msgdel_param 删除消息的参数, Json Key 请参考 @ref MsgDeleteParam
 * @param cb 删除指定会话的消息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_msg(Json::objectValue);
 * Json::Value json_value_msgdelete;
 * json_value_msgdelete[kTIMMsgDeleteParamMsg] = json_value_msg;
 * TIMMsgDelete("user2", kTIMConv_C2C, json_value_msgdelete.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_value_msgdelete.toStyledString().c_str() 得到 json_msgdel_param JSON 字符串如下
 * {
 *   "msg_delete_param_is_ramble" : false,
 *   "msg_delete_param_msg" : {}
 * }
 * @endcode
 */
TIM_API int TIMMsgDelete(const char* conv_id, enum TIMConvType conv_type, const char* json_msgdel_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.5 删除指定会话的本地及漫游消息列表
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_array 消息数组, 消息的 Json Key 请参考 @ref Message
 * @param cb 删除消息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 本接口会在删除本地消息的同时也会删除漫游消息。需要注意以下几点：
 *  - 建议将之前的消息数组Json保存，然后删除的时候直接调用接口，避免构造消息数组。
 *  - 一次最多只能删除 50 条消息。
 *  - 一秒钟最多只能调用一次该接口。
 *  - 如果该账号在其他设备上拉取过这些消息，那么调用该接口删除后，这些消息仍然会保存在那些设备上，即删除消息不支持多端同步。
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_elem; //构造消息文本元素
 * json_value_elem[kTIMElemType] = TIMElemType::kTIMElem_Text;
 * json_value_elem[kTIMTextElemContent] = "this is import msg";
 *
 * Json::Value json_value_msg; //构造消息
 * json_value_msg[kTIMMsgSender] = login_id;
 * json_value_msg[kTIMMsgClientTime] = time(NULL);
 * json_value_msg[kTIMMsgServerTime] = time(NULL);
 * json_value_msg[kTIMMsgElemArray].append(json_value_elem);
 *
 * Json::Value json_value_msgs;  //消息数组
 * json_value_msgs.append(json_value_msg);
 *
 * TIMMsgListDelete("user2", kTIMConv_C2C, json_value_msgs.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_value_msgs.toStyledString().c_str() 得到json_msg_array JSON 字符串如下
 * [
 *    {
 *       "message_client_time" : 1551446728,
 *       "message_elem_array" : [
 *          {
 *             "elem_type" : 0,
 *             "text_elem_content" : "I will be deleted"
 *          }
 *       ],
 *       "message_sender" : "user1",
 *       "message_server_time" : 1551446728
 *    }
 * ]
 * @endcode
 */
TIM_API int TIMMsgListDelete(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.6 清空指定会话的消息
 *
 * @param conv_id 会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param cb 清空成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * TIMMsgClearHistoryMessage("user2", kTIMConv_C2C, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgClearHistoryMessage(const char* conv_id, enum TIMConvType conv_type, TIMCommCallback cb, const void* user_data);

/**
 * 6.7 保存自定义消息
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_param  消息 json 字符串, 消息的 Json Key 请参考 @ref Message
 * @param cb 保存自定义消息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 消息保存接口，一般是自己构造一个消息 Json 字符串，然后保存到指定会话
 */
TIM_API int TIMMsgSaveMsg(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.8 导入消息列表到指定会话
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_array  消息数组, 消息的 Json Key 请参考 @ref Message
 * @param cb 导入消息列表到指定会话成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 批量导入消息，可以自己构造消息去导入。也可以将之前要导入的消息数组 Json 保存，然后导入的时候直接调用接口，避免构造消息数组
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_elem; //构造消息文本元素
 * json_value_elem[kTIMElemType] = TIMElemType::kTIMElem_Text;
 * json_value_elem[kTIMTextElemContent] = "this is import msg";
 *
 * Json::Value json_value_msg; //构造消息
 * json_value_msg[kTIMMsgSender] = login_id;
 * json_value_msg[kTIMMsgClientTime] = time(NULL);
 * json_value_msg[kTIMMsgServerTime] = time(NULL);
 * json_value_msg[kTIMMsgElemArray].append(json_value_elem);
 *
 * Json::Value json_value_msgs;  //消息数组
 * json_value_msgs.append(json_value_msg);
 *
 * TIMMsgImportMsgList("user2", kTIMConv_C2C, json_value_msgs.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_value_msgs.toStyledString().c_str() 得到json_msg_array JSON 字符串如下
 * [
 *    {
 *       "message_client_time" : 1551446728,
 *       "message_elem_array" : [
 *          {
 *             "elem_type" : 0,
 *             "text_elem_content" : "this is import msg"
 *          }
 *       ],
 *       "message_sender" : "user1",
 *       "message_server_time" : 1551446728
 *    }
 * ]
 * @endcode
 */
TIM_API int TIMMsgImportMsgList(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.9 根据消息 messageID 查询本地的消息列表
 *
 * @param json_message_id_array  消息 ID 列表
 * @param cb 根据消息 messageID 查询本地的消息列表成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_message_id_1("id_clienttime_rand_1");
 * Json::Value json_message_id_2("id_clienttime_rand_2");
 *
 * Json::Value json_message_id_array;
 * json_message_id_array.append(json_message_id_1);
 * json_message_id_array.append(json_message_id_2);
 * TIMMsgFindMessages(json_message_id_array.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_message_id_array.toStyledString().c_str() 的到 json_message_id_array JSON 字符串如下
 * [
 *    "id_clienttime_rand_1",
 *    "id_clienttime_rand_2",
 * ]
 * @endcode
 */
TIM_API int TIMMsgFindMessages(const char* json_message_id_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.10 根据消息定位精准查找指定会话的消息
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_Locator_array  消息定位符数组, Json Key 请参考 @ref MsgLocator
 * @param cb 根据消息定位精准查找指定会话的消息成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 *  - 此接口根据消息定位符精准查找指定会话的消息，该功能一般用于消息撤回时查找指定消息等
 *  - 一个消息定位符对应一条消息
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_msg_locator;                      // 一条消息对应一个消息定位符(精准定位)
 * json_msg_locator[kTIMMsgLocatorIsRevoked] = false; // 消息是否被撤回
 * json_msg_locator[kTIMMsgLocatorTime] = 123;        // 填入消息的时间
 * json_msg_locator[kTIMMsgLocatorSeq] = 1;
 * json_msg_locator[kTIMMsgLocatorIsSelf] = false;
 * json_msg_locator[kTIMMsgLocatorRand] = 12345678;
 *
 * Json::Value json_msg_locators;
 * json_msg_locators.append(json_msg_locator);
 * TIMMsgFindByMsgLocatorList("user2", kTIMConv_C2C, json_msg_locators.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 *
 * // json_msg_locators.toStyledString().c_str() 的到 json_msg_Locator_array JSON 字符串如下
 * [
 *    {
 *       "message_locator_is_revoked" : false,
 *       "message_locator_is_self" : false,
 *       "message_locator_rand" : 12345678,
 *       "message_locator_seq" : 1,
 *       "message_locator_time" : 123
 *    }
 * ]
 * @endcode
 */
TIM_API int TIMMsgFindByMsgLocatorList(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_Locator_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.11 搜索本地消息（5.4.666 及以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_search_message_param 消息搜索参数, Json Key 请参考 @ref MessageSearchParam
 * @param cb 搜索成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __搜索本地消息示例__
 * @code{.cpp}
 * Json::Value json_search_message_param;
 * json_search_message_param[kTIMMsgSearchParamKeywordArray].append("keyword1");
 * json_search_message_param[kTIMMsgSearchParamKeywordArray].append("keyword2");
 * json_search_message_param[kTIMMsgSearchParamMessageTypeArray].append(kTIMElem_Text);
 * json_search_message_param[kTIMMsgSearchParamMessageTypeArray].append(kTIMElem_Image);
 * json_search_message_param[kTIMMsgSearchParamConvId] = "xxxxx";
 * json_search_message_param[kTIMMsgSearchParamConvType] = kTIMConv_Group;
 * json_search_message_param[kTIMMsgSearchParamPageIndex] = 0;
 * json_search_message_param[kTIMMsgSearchParamPageSize] = 10;
 *
 * int ret = TIMMsgSearchLocalMessages(json_search_message_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, this);
 *
 * // json_search_message_param.toStyledString().c_str() 得到 json_search_message_param JSON 字符串如下
 * {
 *    "msg_search_param_keyword_array" : ["keyword1", "keyword2"],
 *    "msg_search_param_message_type_array" : [0, 1],
 *    "msg_search_param_page_index" : 0,
 *    "msg_search_param_page_size" : 10
 * }
 * @endcode
 */
TIM_API int TIMMsgSearchLocalMessages(const char* json_search_message_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.12 搜索云端消息（7.3 及以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_search_message_param 消息搜索参数, Json Key 请参考 @ref MessageSearchParam
 * @param cb 搜索成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 该功能为 IM 增值功能，详见[价格说明](https://cloud.tencent.com/document/product/269/11673?from=17176#.E5.9F.BA.E7.A1.80.E6.9C.8D.E5.8A.A1.E8.AF.A6.E6.83.85)
 *  - 如果您没有开通该服务，调用接口会返回 60020 错误码
 *
 * __搜索云端消息示例__
 * @code{.cpp}
 * Json::Value json_search_message_param;
 * json_search_message_param[kTIMMsgSearchParamKeywordArray].append("keyword1");
 * json_search_message_param[kTIMMsgSearchParamKeywordArray].append("keyword2");
 * json_search_message_param[kTIMMsgSearchParamMessageTypeArray].append(kTIMElem_Text);
 * json_search_message_param[kTIMMsgSearchParamMessageTypeArray].append(kTIMElem_Image);
 * json_search_message_param[kTIMMsgSearchParamConvId] = "xxxxx";
 * json_search_message_param[kTIMMsgSearchParamConvType] = kTIMConv_Group;
 * json_search_message_param[kTIMMsgSearchParamSearchCount] = 10;
 * json_search_message_param[kTIMMsgSearchParamSearchCursor] = "xxxxx";
 *
 * int ret = TIMMsgSearchCloudMessages(json_search_message_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, this);
 *
 * // json_search_message_param.toStyledString().c_str() 得到 json_search_message_param JSON 字符串如下
 * {
 *    "msg_search_param_keyword_array" : ["keyword1", "keyword2"],
 *    "msg_search_param_message_type_array" : [0, 1],
 *    "msg_search_param_search_count" : 10,
 *    "msg_search_param_search_cursor" : ""
 * }
 * @endcode
 */
TIM_API int TIMMsgSearchCloudMessages(const char* json_search_message_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.13 发送消息已读回执 （6.1 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg_array  消息列表, 消息的 Json Key 请参考 @ref Message
 * @param cb 成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 *  - 向群消息发送已读回执，需要您先到控制台打开对应的开关，详情参考文档 [群消息已读回执](https://cloud.tencent.com/document/product/269/75343#.E8.AE.BE.E7.BD.AE.E6.94.AF.E6.8C.81.E5.B7.B2.E8.AF.BB.E5.9B.9E.E6.89.A7.E7.9A.84.E7.BE.A4.E7.B1.BB.E5.9E.8B) 。
 *  - 该接口调用成功后，会话未读数不会变化，消息发送者会收到 TIMSetMsgReadedReceiptCallback 注册的回调，回调里面会携带消息的最新已读信息。
 *
 * __发送消息已读回执示例__
 * @code{.cpp}
 * int ret = TIMMsgSendMessageReadReceipts(json_msg_array, [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgSendMessageReadReceipts(const char* json_msg_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.14 获取消息已读回执（6.1 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg_array  消息列表, 消息的 Json Key 请参考 @ref Message
 * @param cb 成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 *  - 获取群消息已读回执，需要您先到控制台打开对应的开关，详情参考文档 [群消息已读回执](https://cloud.tencent.com/document/product/269/75343#.E8.AE.BE.E7.BD.AE.E6.94.AF.E6.8C.81.E5.B7.B2.E8.AF.BB.E5.9B.9E.E6.89.A7.E7.9A.84.E7.BE.A4.E7.B1.BB.E5.9E.8B) 。
 *  - json_msg_array 中的多条消息必须在同一个会话中。
 * 
 * __获取消息已读回执示例__
 * @code{.cpp}
 * int ret = TIMMsgGetMessageReadReceipts(json_msg_array, [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *     Json::Value json_value_receipts;
 *     Json::Reader reader;
 *     if (!reader.parse(json_params, json_value_receipts)) {
 *         // Json 解析失败
 *         return;
 *     }
 *
 *     for (Json::ArrayIndex i = 0; i < json_value_receipts.size(); i++) {
 *         Json::Value& json_value_receipt = json_value_receipts[i];
 *         uint32_t conv_type = json_value_receipt[kTIMMsgReceiptConvType].asUInt();
 *         std::string group_id = json_value_receipt[kTIMMsgReceiptConvId].asString();
 *         std::string msg_id = json_value_receipt[kTIMMsgReceiptMsgId].asString();
 *         uint64_t read_count = json_value_receipt[kTIMMsgReceiptReadCount].asUInt64();
 *         uint64_t unread_count = json_value_receipt[kTIMMsgReceiptUnreadCount].asUInt64();
 *     }
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgGetMessageReadReceipts(const char* json_msg_array, TIMCommCallback cb, const void* user_data);

/**
 * 6.15 获取群消息已读群成员列表（6.1 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg 单条群消息, Json Key 请参考 @ref Message
 * @param filter 指定拉取已读或未读群成员列表。
 * @param next_seq 分页拉取的游标，第一次默认取传 0，后续分页拉取时，传上一次分页拉取成功回调里的 next_seq
 * @param count 分页拉取的个数，最大支持 100 个。
 * @param cb 成功与否的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note 请注意：
 *  - 使用该功能之前，请您先到控制台打开对应的开关，详情参考文档 [群消息已读回执](https://cloud.tencent.com/document/product/269/75343#.E8.AE.BE.E7.BD.AE.E6.94.AF.E6.8C.81.E5.B7.B2.E8.AF.BB.E5.9B.9E.E6.89.A7.E7.9A.84.E7.BE.A4.E7.B1.BB.E5.9E.8B) 。
 * 
 * __发送群消息已读回执示例__
 * @code{.cpp}
 * int ret = TIMMsgGetGroupMessageReadMemberList(json_msg, TIM_GROUP_MESSAGE_READ_MEMBERS_FILTER_READ, next_seq, 100,
 *         [](const char* json_group_member_array, uint64_t next_seq, bool is_finished, const void* user_data) {
 *     Json::Value member_array;
 *     Json::Reader reader;
 *     if (!reader.parse(json_group_member_array, member_array)) {
 *         // Json 解析失败
 *         return;
 *     }
 *
 *     for (Json::ArrayIndex i = 0; i < member_array.size(); i++) {
 *         Json::Value& member = member_array[i];
 *         std::string user_id = member[kTIMGroupMemberInfoIdentifier].asString();
 *         std::string name_card = member[kTIMGroupMemberInfoNameCard].asString();
 *         std::string face_url = member[kTIMGroupMemberInfoFaceUrl].asString();
 *     }
 *
 *     if (false == is_finished) {
 *         TIMMsgGetGroupMessageReadMemberList(json_msg, TIM_GROUP_MESSAGE_READ_MEMBERS_FILTER_READ, next_seq, 100, MsgGroupReadMembersCallback, user_data);
 *     }
 * }, this);
 * @endcode
 */
TIM_API int TIMMsgGetGroupMessageReadMemberList(const char* json_msg, TIMGroupMessageReadMembersFilter filter, uint64_t next_seq, uint32_t count, TIMMsgGroupMessageReadMemberListCallback cb, const void* user_data);

/**
 * 6.16 设置消息扩展 （6.7 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg 消息 json 字符串, Json Key 请参考 @ref Message。消息需满足三个条件：1、消息发送前需设置 kTIMMsgSupportMessageExtension 为 true，2、消息必须是发送成功的状态，3、消息不能是直播群（AVChatRoom）消息。
 * @param json_extension_array 消息扩展信息 json 字符串, Json Key 请参考 @ref MessageExtension。如果扩展的 key 已经存在，则修改扩展的 value 信息，否则新增扩展
 * @param cb 成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 扩展 key 最大支持 100 字节，扩展 value 最大支持 1KB，单次最多支持设置 20 个扩展，单条消息最多可设置 300 个扩展
 *  - 当多个用户同时设置同一个扩展 key 时，只有第一个用户可以执行成功，其它用户会收到 23001 错误码和更新后的扩展信息
 *  - 在收到错误码和最新扩展信息后，请按需重新发起设置操作
 *  - 我们强烈建议不同的用户设置不同的扩展 key，这样大部分场景都不会冲突，比如投票、接龙、问卷调查，都可以把自己的 userID 作为扩展 key
 * 
 * __设置消息扩展示例__
 * @code{.cpp}
 *  json::Array json_element_array;
 *  json::Object json_element;
 *  json_element[kTIMElemType] = kTIMElem_Text;
 *  json_element[kTIMTextElemContent] = "send text";
 *  json_element_array.push_back(json_element);
 *
 *  json::Object json_message;
 *  // 设置此消息支持消息扩展
 *  json_message[kTIMMsgSupportMessageExtension] = true;
 *  json_message[kTIMMsgElemArray] = json_element_array;
 *  std::string json_parameters = json::Serialize(json_message);
 *
 *  const size_t kMessageIDLength = 128;
 *  char message_id_buffer[kMessageIDLength] = {0};
 *  TIMMsgSendMessage(GetGroupID().c_str(), kTIMConv_Group, json_parameters.c_str(), message_id_buffer,
 *      [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *          if (ERR_SUCC != code) {
 *              // 消息发送失败
 *              return;
 *          }
 *
 *           // 设置消息扩展字段参数
 *          json::Object json_extension_item;
 *          json_extension_item[kTIMMsgExtensionKey]   = "extension_key";
 *          json_extension_item[kTIMMsgExtensionValue] = "extension_value";
 *
 *          json::Array json_extension_array;
 *          json_extension_array.push_back(json_extension_item);
 *
 *          // 消息发送成功, json_param 为返回发送后的消息json字符串
 *          TIMMsgSetMessageExtensions(json_param, json::Serialize(json_extension_array).c_str(),
 *              [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *                  if (ERR_SUCC != code) {
 *                      // 设置消息扩展失败
 *                      return;
 *                  }
 *                  // 设置消息扩展成功
 *              }, user_data);
 *  }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgSetMessageExtensions(const char *json_msg, const char *json_extension_array, TIMCommCallback cb, const void *user_data);

/**
 * 6.17 获取消息扩展（6.7 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg 消息 json 字符串, Json Key 请参考 @ref Message
 * @param cb 成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __获取消息扩展示例__
 * @code{.cpp}
 *  json::Object json_parameters;
 *  json_parameters[kTIMMsgGetMsgListParamIsRamble] = true;
 *  json_parameters[kTIMMsgGetMsgListParamIsForward] = false;
 *  json_parameters[kTIMMsgGetMsgListParamCount] = 1;
 *  
 *  TIMMsgGetMsgList(GetGroupID().c_str(), kTIMConv_Group, json::Serialize(json_parameters).c_str(),
 *      [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *          Printf("TIMMsgGetMsgList complete|code:%d|desc:%s|json_params:%s\n", code, desc, json_params);
 * 
 *          json::Array json_message_array = json::Deserialize(json_params).ToArray();
 *          if (json_message_array.size() > 0) {
 *              std::string json_message = json::Serialize(json_message_array[0]);
 * 
 *              TIMMsgGetMessageExtensions(json_message.c_str(),
 *                  [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *                  if (ERR_SUCC != code) {
 *                      // 获取消息扩展失败
 *                      return;
 *                  }
 *                  // 获取消息扩展成功
 *                  Printf("TIMMsgGetMessageExtensions complete|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *                  }, user_data);
 *          }
 *  }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgGetMessageExtensions(const char *json_msg, TIMCommCallback cb, const void *user_data);

/**
 * 6.18 删除消息扩展（6.7 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg 消息 json 字符串, Json Key 请参考 @ref Message
 * @param json_extension_key_array 扩展信息 key 列表，单次最大支持删除 20 个消息扩展，如果设置为空，表示删除消息所有扩展
 * @param cb 成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 *  - 当多个用户同时设置或删除同一个扩展 key 时，只有第一个用户可以执行成功，其它用户会收到 23001 错误码和最新的扩展信息，在收到错误码和扩展信息后，请按需重新发起删除操作。
 * 
 * __删除消息扩展示例__
 * @code{.cpp}
 *  json::Object json_parameters;
 *  json_parameters[kTIMMsgGetMsgListParamIsRamble] = true;
 *  json_parameters[kTIMMsgGetMsgListParamIsForward] = false;
 *  json_parameters[kTIMMsgGetMsgListParamCount] = 1;
 *  
 *  TIMMsgGetMsgList(GetGroupID().c_str(), kTIMConv_Group, json::Serialize(json_parameters).c_str(),
 *      [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *          Printf("TIMMsgGetMsgList complete|code:%d|desc:%s|json_params:%s\n", code, desc, json_params);
 *  
 *          json::Array json_message_array = json::Deserialize(json_params).ToArray();
 *          if (json_message_array.size() > 0) {
 *              std::string json_message = json::Serialize(json_message_array[0]);
 *  
 *              // 设置要删除的消息扩展字段（只需要包含 要删除的 key 值即可，如果传入为空，则将消息扩展字段全部删除）
 *              json::Array json_extension_key_array;
 *              json_extension_key_array.push_back("extension_key");
 *              std::string json_extension_keys = json::Serialize(json_extension_key_array);
 *          
 *              // 删除消息扩展
 *              TIMMsgDeleteMessageExtensions(json_message.c_str(), json_extension_keys.c_str(),
 *                  [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *                      if (ERR_SUCC != code) {
 *                          // 删除消息扩展失败
 *                          return;
 *                      }
 *                      // 删除消息扩展成功
 *                      Printf("TIMMsgDeleteMessageExtensions complete|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *                  }, user_data);
 *          }
 *  }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgDeleteMessageExtensions(const char *json_msg, const char *json_extension_key_array, TIMCommCallback cb, const void *user_data);

/**
 * 6.19 添加消息回应（可以用于实现表情回应，7.4 及其以上版本支持，需要您购买旗舰版套餐）
 *
 *  <p> 表情回应功能是指对某条消息通过表情符号进行互动回应，我们可以看到每种表情的回应人数和回应人列表。
 *  <p> 目前常见的消息回应展示方式会有如下两种风格：
 *  <p> 风格一：
 *  <p>  ----------------------------
 *  <p> |   lucy, happy birthday!    |
 *  <p>  ----------------------------
 *  <p> |   😄 1  💐 2  👍🏻 10        |
 *  <p>  ----------------------------
 *  <p> 风格二：
 *  <p>  ------------------------------------------------
 *  <p> |   lucy, happy birthday!                        |
 *  <p>  ------------------------------------------------
 *  <p> |  😁 bob 💐olivia 🎂david                       |
 *  <p> |  👍🏻 denny、james、lucy、linda、thomas 等10人     |
 *  <p>  ------------------------------------------------
 *  <p>
 *  <p> 当用户点击某个表情后，会跳转到表情回应详情界面：
 *  <p>  |  😄   |   💐    |   👍🏻   |
 *  <p>  |  bob  |  olivia |  lucy   |
 *  <p>  |  ...  |   ...   |  denny  |
 *  <p>  |  ...  |   ...   |  ...    |
 *  <p> 用户可以根据某个表情分页拉取使用该表情的用户信息。
 *  <p>
 *  <p> 您可以基于 SDK API 实现表情回应能力:
 *  <p> 1、调用 @ref TIMMsgAddMessageReaction 接口为一条消息添加一个 emoji，添加成功后，emoji 下就会存储当前操作用户。
 *  <p> 2、调用 @ref TIMMsgRemoveMessageReaction 接口删除已经添加的 emoji，删除成功后，emoji 下就不再存储当前操作用户。
 *  <p> 3、调用 @ref TIMMsgGetMessageReactions 接口批量拉取多条消息的 emoji 列表，其中每个 emoji 都包含了当前使用者总人数以及前 N（默认 10）个使用者用户资料。
 *  <p> 4、调用 @ref TIMMsgGetAllUserListOfMessageReaction 接口分页拉取消息 emoji 的全量使用者用户资料。
 *  <p> 5、监听 @ref TIMMsgReactionsChangedCallback 回调，感知 emoji 的使用者信息变更，该回调会携带 emoji 最新的使用者信息（包含使用者总人数以及前 N 个使用者用户资料）。
 *
 * @param json_msg 消息 json 字符串, Json Key 请参考 @ref Message
 * @param reaction_id 消息回应 ID，在表情回应场景，reaction_id 为表情 ID，单条消息最大支持 10 个 Reaction，单个 Reaction 最大支持 100 个用户。
 *
 * @note
 *  - 该功能为旗舰版功能，需要您购买旗舰版套餐。
 *  - 如果单条消息 Reaction 数量超过最大限制，调用接口会报 ERR_SVR_MSG_REACTION_COUNT_LIMIT 错误。
 *  - 如果单个 Reaction 用户数量超过最大限制，调用接口会报 ERR_SVR_MSG_REACTION_USER_COUNT_LIMIT 错误。
 *  - 如果 Reaction 已经包含当前用户，调用接口会报 ERR_SVR_MSG_REACTION_ALREADY_CONTAIN_USER 错误。
 *
 * __添加消息回应示例__
 * @code{.cpp}
 *  std::string reaction_id = "emoji1";
 *  TIMMsgAddMessageReaction(json_msg, reaction_id.c_str(),
 *      [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *      Printf("TIMMsgAddMessageReaction complete|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *  }, user_data);
 * @endcode
 */
TIM_API int TIMMsgAddMessageReaction(const char *json_msg, const char *reaction_id, TIMCommCallback cb, const void *user_data);

/**
 * 6.20 删除消息回应（7.4 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg 消息 json 字符串, Json Key 请参考 @ref Message
 * @param reaction_id 消息回应 ID，在表情回复场景，reaction_id 为表情 ID。
 *
 * @note
 *  - 如果 Reaction 不存在，调用接口会报 ERR_SVR_MSG_REACTION_NOT_EXISTS 错误。
 *  - 如果 Reaction 不包含当前用户，调用接口会报 ERR_SVR_MSG_REACTION_NOT_CONTAIN_USER 错误。
 *
 * __删除消息回应示例__
 * @code{.cpp}
 *  std::string reaction_id = "emoji1";
 *  TIMMsgRemoveMessageReaction(json_msg, reaction_id.c_str(),
 *      [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         Printf("TIMMsgRemoveMessageReaction complete|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *  }, user_data);
 * @endcode
 */
TIM_API int TIMMsgRemoveMessageReaction(const char *json_msg, const char *reaction_id, TIMCommCallback cb, const void *user_data);

/**
 * 6.21 批量拉取多条消息回应信息（7.4 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg_array 消息列表, Json Key 请参考 @ref Message。一次最大支持 20 条消息，消息必须属于同一个会话。
 * @param max_user_count_per_reaction 取值范围 [0,10]，每个 Reaction 最多只返回前 10 个用户信息，如需更多用户信息，可以按需调用 @ref TIMMsgGetMessageReactionUserList 接口分页拉取。
 *
 * __批量拉取消息回应列表示例__
 * @code{.cpp}
 *  json::Array json_msg_array;
 *  json_msg_array.push_back(json_msg);
 *  std::string json_msg_array_str = json::Serialize(json_msg_array);
 *  TIMMsgGetMessageReactions(json_msg_array_str.c_str(), 10,
 *      [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         Printf("TIMMsgGetMessageReactions complete|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *  }, user_data);
 * @endcode
 */
TIM_API int TIMMsgGetMessageReactions(const char *json_msg_array, uint32_t max_user_count_per_reaction, TIMCommCallback cb, const void *user_data);

/**
 * 6.22 分页拉取使用指定消息回应用户信息（7.4 及其以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_msg 消息 json 字符串, Json Key 请参考 @ref Message
 * @param reaction_id 消息回应 ID，在表情回复场景，reaction_id 为表情 ID。
 * @param next_seq 分页拉取的游标，第一次传 0，后续分页传 succ 返回的 nextSeq。
 * @param count 一次分页最大拉取个数，最大支持 100 个。
 *
 * __拉取消息回应用户列表示例__
 * @code{.cpp}
 *  TIMMsgGetAllUserListOfMessageReaction(json_msg, reaction_id.c_str(), 0, 20,
 *      [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
           Printf("TIMMsgGetAllUserListOfMessageReaction complete|code:%d|desc:%s|json_param:%s\n", code, desc, json_param);
 *  }, user_data);
 * @endcode
 */
TIM_API int TIMMsgGetAllUserListOfMessageReaction(const char *json_msg, const char *reaction_id, uint32_t next_seq, uint32_t count, TIMCommCallback cb, const void *user_data);
/**
 * 6.23 翻译文本消息
 *
 * @param json_source_text_array 待翻译文本数组。
 * @param source_language 源语言。可以设置为特定语言或 ”auto“。“auto“ 表示自动识别源语言。传空默认为 ”auto“。
 * @param target_language 目标语言。支持的目标语言有多种，例如：英语-“en“，简体中文-”zh“，法语-”fr“，德语-”de“等。详情请参考文档 [文本翻译语言支持](https://cloud.tencent.com/document/product/269/85380#.E6.96.87.E6.9C.AC.E7.BF.BB.E8.AF.91.E8.AF.AD.E8.A8.80.E6.94.AF.E6.8C.81)。
 * @param cb 翻译结果的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback。
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult。
 * 
 * __示例__
 * @code{.cpp}
 * json::Array json_source_text_array;
 * json_source_text_array.push_back("send text");
 * json_source_text_array.push_back("translate text test");
 *
 * std::string source_language = "";
 * std::string target_language = "de";
 *
 * TIMMsgTranslateText(json::Serialize(json_source_text_array).c_str(), source_language.c_str(), target_language.c_str(),
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         Printf("\nTIMMsgTranslateText complete|code:%d|desc:%s|json_param:%s\n",
 *             code, desc, json_param);
 *     }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgTranslateText(const char *json_source_text_array, const char *source_language, const char *target_language, TIMCommCallback cb, const void *user_data);

/**
 * 6.24 识别语音消息，将语音转换成文字（7.4 及以上版本支持）
 *
 * @param url 语音消息下载 url，可在消息对象中获取到。
 * @param language 识别的语言。
 * @param cb 识别结果的回调。回调函数定义和参数解析请参考 @ref TIMCommCallback。
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult。
 * 
 * @note
 *  - 语音转文字是增值付费功能，处于内测阶段，您可通过 [即时通信 IM 语音转文字插件交流群](https://zhiliao.qq.com/s/c5GY7HIM62CK/cPSYGIIM62CH) 联系我们为您开通体验完整功能。
 * 
 * __示例__
 * @code{.cpp}
 * std::string language = "en";
 *
 * TIMMsgConvertVoiceToText(language.c_str(),
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         Printf("\nTIMMsgConvertVoiceToText complete|code:%d|desc:%s|json_param:%s\n",
 *             code, desc, json_param);
 *     }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgConvertVoiceToText(const char *url, const char *language, TIMCommCallback cb, const void *user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                      七. 消息收发 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 7.1 Elem (元素的类型)
// uint @ref TIMElemType, 读写(必填), 元素类型
static const char* kTIMElemType = "elem_type";

//------------------------------------------------------------------------------
// 7.2 TextElem (文本元素)
// string, 读写(必填), 文本内容
static const char* kTIMTextElemContent = "text_elem_content";

//------------------------------------------------------------------------------
// 7.3 CustomElem 
// @note
//  - 自定义元素, 自定义消息是指当内置的消息类型无法满足特殊需求，开发者可以自定义消息格式，内容全部由开发者定义，ImSDK只负责透传
// string, 读写(选填), 数据,支持二进制数据
static const char* kTIMCustomElemData = "custom_elem_data";
// string, 读写(选填), 自定义描述
static const char* kTIMCustomElemDesc = "custom_elem_desc";
// string, 读写(选填), 后台推送对应的ext字段
static const char* kTIMCustomElemExt = "custom_elem_ext";
// string, 读写(选填), 自定义声音
static const char* kTIMCustomElemSound = "custom_elem_sound";

//------------------------------------------------------------------------------
// 7.4 ImageElem (图片元素)
// @note
//  图片规格说明：每幅图片有三种规格，分别是 Original（原图）、Large（大图）、Thumb（缩略图）。
//   - 原图：指用户发送的原始图片，尺寸和大小都保持不变。
//   - 大图：是将原图等比压缩，压缩后宽、高中较小的一个等于720像素。
//   - 缩略图：是将原图等比压缩，压缩后宽、高中较小的一个等于198像素
//  如果原图尺寸就小于198像素，则三种规格都保持原始尺寸，不需压缩。
//  如果原图尺寸在198-720之间，则大图和原图一样，不需压缩。
//  在手机上展示图片时，建议优先展示缩略图，用户单击缩略图时再下载大图，单击大图时再下载原图。当然开发者也可以选择跳过大图，单击缩略图时直接下载原图。
//  在 Pad 或 PC 上展示图片时，由于分辨率较大，且基本都是 Wi-Fi 或有线网络，建议直接显示大图，用户单击大图时再下载原图。
// string, 读写(必填), 发送图片的路径
static const char* kTIMImageElemOrigPath = "image_elem_orig_path";
// uint @ref TIMImageLevel, 读写(必填), 发送图片的质量级别
static const char* kTIMImageElemLevel = "image_elem_level";
// int, 读写, 发送图片格式:，0xff:未知格式, 1：JPG, 2:GIF, 3:PNG, 4:BMP
static const char* kTIMImageElemFormat = "image_elem_format";
// string, 只读, 原图 ID
static const char* kTIMImageElemOrigId = "image_elem_orig_id";
// int, 只读, 原图的图片高度
static const char* kTIMImageElemOrigPicHeight = "image_elem_orig_pic_height";
// int, 只读, 原图的图片宽度
static const char* kTIMImageElemOrigPicWidth = "image_elem_orig_pic_width";
// int, 只读, 原图的图片大小
static const char* kTIMImageElemOrigPicSize = "image_elem_orig_pic_size";
// string, 只读, 缩略图 ID
static const char* kTIMImageElemThumbId = "image_elem_thumb_id";
// int, 只读, 缩略图的图片高度
static const char* kTIMImageElemThumbPicHeight = "image_elem_thumb_pic_height";
// int, 只读, 缩略图的图片宽度
static const char* kTIMImageElemThumbPicWidth = "image_elem_thumb_pic_width";
// int, 只读, 缩略图的图片大小
static const char* kTIMImageElemThumbPicSize = "image_elem_thumb_pic_size";
// string, 只读, 大图片uuid
static const char* kTIMImageElemLargeId = "image_elem_large_id";
// int, 只读, 大图片的图片高度
static const char* kTIMImageElemLargePicHeight = "image_elem_large_pic_height";
// int, 只读, 大图片的图片宽度
static const char* kTIMImageElemLargePicWidth = "image_elem_large_pic_width";
// int, 只读, 大图片的图片大小
static const char* kTIMImageElemLargePicSize = "image_elem_large_pic_size";
// string, 只读, 原图URL
static const char* kTIMImageElemOrigUrl = "image_elem_orig_url";
// string, 只读, 缩略图URL
static const char* kTIMImageElemThumbUrl = "image_elem_thumb_url";
// string, 只读, 大图片URL
static const char* kTIMImageElemLargeUrl = "image_elem_large_url";
// int, 只读, 任务ID，已废弃
static const char* kTIMImageElemTaskId = "image_elem_task_id";

//------------------------------------------------------------------------------
// 7.5 SoundElem (音频元素)
// @note
//  - 语音是否已经播放，可使用 消息自定义字段 实现，如定义一个字段值0表示未播放，1表示播放，当用户单击播放后可设置改字段的值为1
//  - 一条消息只能添加一个声音元素，添加多个声音元素时，发送消息可能失败。
// string, 读写(必填), 语音文件路径,需要开发者自己先保存语言然后指定路径
static const char* kTIMSoundElemFilePath = "sound_elem_file_path";
// int, 读写(必填), 语言数据文件大小，以秒为单位
static const char* kTIMSoundElemFileSize = "sound_elem_file_size";
// int, 读写(必填), 语音时长
static const char* kTIMSoundElemFileTime = "sound_elem_file_time";
// string, 只读, 语音 ID
static const char* kTIMSoundElemFileId = "sound_elem_file_id";
// int, 只读, 下载时用到的businessID
static const char* kTIMSoundElemBusinessId = "sound_elem_business_id";
// string, 只读, 下载的URL
static const char* kTIMSoundElemUrl = "sound_elem_url";
// int, 只读, 任务ID，已废弃
static const char* kTIMSoundElemTaskId = "sound_elem_task_id";

//------------------------------------------------------------------------------
// 7.6 VideoElem (视频元素)
// string, 读写(必填), 视频文件类型，发送消息时进行设置
static const char* kTIMVideoElemVideoType = "video_elem_video_type";
// uint, 读写(必填), 视频文件大小
static const char* kTIMVideoElemVideoSize = "video_elem_video_size";
// uint, 读写(必填), 视频时长，发送消息时进行设置
static const char* kTIMVideoElemVideoDuration = "video_elem_video_duration";
// string, 读写(必填), 适配文件路径
static const char* kTIMVideoElemVideoPath = "video_elem_video_path";
// string, 只读, 视频 ID
static const char* kTIMVideoElemVideoId = "video_elem_video_id";
// int, 只读, 下载时用到的businessID
static const char* kTIMVideoElemBusinessId = "video_elem_business_id";
// string, 只读, 视频文件下载的URL
static const char* kTIMVideoElemVideoUrl = "video_elem_video_url";
// string, 读写(必填), 截图文件类型，发送消息时进行设置
static const char* kTIMVideoElemImageType = "video_elem_image_type";
// uint, 读写(必填), 截图文件大小
static const char* kTIMVideoElemImageSize = "video_elem_image_size";
// uint, 读写(必填), 截图高度，发送消息时进行设置
static const char* kTIMVideoElemImageWidth = "video_elem_image_width";
// uint, 读写(必填), 截图宽度，发送消息时进行设置
static const char* kTIMVideoElemImageHeight = "video_elem_image_height";
// string, 读写(必填), 保存截图的路径
static const char* kTIMVideoElemImagePath = "video_elem_image_path";
// string, 只读, 截图 ID
static const char* kTIMVideoElemImageId = "video_elem_image_id";
// string, 只读, 截图文件下载的URL
static const char* kTIMVideoElemImageUrl = "video_elem_image_url";
// uint, 只读, 任务ID，已废弃
static const char* kTIMVideoElemTaskId = "video_elem_task_id";

//------------------------------------------------------------------------------
// 7.7 FileElem (文件元素)
// string, 读写(必填), 文件所在路径（包含文件名）
static const char* kTIMFileElemFilePath = "file_elem_file_path";
// string, 读写(必填), 文件名，显示的名称。不设置该参数时，kTIMFileElemFileName默认为kTIMFileElemFilePath指定的文件路径中的文件名
static const char* kTIMFileElemFileName = "file_elem_file_name";
// int, 读写(必填), 文件大小
static const char* kTIMFileElemFileSize = "file_elem_file_size";
// string, 只读, 文件 ID
static const char* kTIMFileElemFileId = "file_elem_file_id";
// int, 只读, 下载时用到的businessID
static const char* kTIMFileElemBusinessId = "file_elem_business_id";
// string, 只读, 文件下载的URL
static const char* kTIMFileElemUrl = "file_elem_url";
// int, 只读, 任务ID，已废弃
static const char* kTIMFileElemTaskId = "file_elem_task_id";

//------------------------------------------------------------------------------
// 7.8 LocationElem (位置元素)
// string, 读写(选填), 位置描述
static const char* kTIMLocationElemDesc = "location_elem_desc";
// double, 读写(必填), 经度
static const char* kTIMLocationElemLongitude = "location_elem_longitude";
// double, 读写(必填), 纬度
static const char* kTIMLocationElemLatitude = "location_elem_latitude";

//------------------------------------------------------------------------------
// 7.8 FaceElem (表情元素)
// @note
//  - ImSDK 并不提供表情包，如果开发者有表情包，可使用 kTIMFaceElemIndex 存储表情在表情包中的索引，由用户自定义。
//  - 或者直接使用 kTIMFaceElemBuf 存储表情二进制信息(必须转换成String，Json不支持二进制传输)，由用户自定义，ImSDK内部只做透传。
// int, 读写(必填), 表情索引
static const char* kTIMFaceElemIndex = "face_elem_index";
// string, 读写(选填), 其他额外数据,可由用户自定义填写。若要传输二进制，麻烦先转码成字符串。JSON只支持字符串
static const char* kTIMFaceElemBuf = "face_elem_buf";

//------------------------------------------------------------------------------
// 7.8 MergerElem (合并消息元素)
// string, 读写(必填), 合并消息 title
static const char* kTIMMergerElemTitle = "merge_elem_title";
// array string, 读写(必填), 合并消息摘要列表
static const char* kTIMMergerElemAbstractArray = "merge_elem_abstract_array";
// string, 读写(必填), 合并消息兼容文本，低版本 SDK 如果不支持合并消息，默认会收到一条文本消息，文本消息的内容为 compatibleText，该参数不能为空。
static const char* kTIMMergerElemCompatibleText = "merge_elem_compatible_text";
// array @ref Message, 读写(必填), 消息列表（最大支持 300 条，消息对象必须是 kTIMMsg_SendSucc 状态，消息类型不能为 @ref GroupTipsElem 或 @ref GroupReportElem ）
static const char* kTIMMergerElemMsgArray = "merge_elem_message_array";
// bool, 只读, 合并消息里面又包含合并消息我们称之为合并嵌套，合并嵌套层数不能超过 100 层，如果超过限制，layersOverLimit 会返回 YES，kTIMMergerElemTitle 和 kTIMMergerElemAbstractArray 为空，DownloadMergerMessage 会返回 ERR_MERGER_MSG_LAYERS_OVER_LIMIT 错误码。
static const char* kTIMMergerElemLayersOverLimit = "merge_elem_layer_over_limit";
// string, 只读, native 端消息列表下载 key
static const char* kTIMMergerElemRelayPbKey = "merge_elem_relay_pb_key";
// string, 只读, web 端消息列表下载 key
static const char* kTIMMergerElemRelayJsonKey = "merge_elem_relay_json_key";
// string, 只读, 转发消息的 buffer
static const char* kTIMMergerElemRelayBuffer = "merge_elem_relay_buffer";

//------------------------------------------------------------------------------
// 7.9 GroupMessageAtALL(@ 群里所有人的参数)
// string, 只读, 在消息 kTIMMsgGroupAtUserArray 字段中填入 kImSDK_MessageAtALL 表示当前消息需要 @ 群里所有人
static const char* kImSDK_MessageAtALL = "__kImSDK_MessageAtALL__";

//------------------------------------------------------------------------------
// 7.10 GroupTipsElem (群组系统消息元素)
// @note
//  针对所有群成员，可以通过监听 @ref TIMSetGroupTipsEventCallback 获取，Json Key 请参考 @ref GroupTipsElem

//------------------------------------------------------------------------------
// 7.11 GroupReportElem (群组系统通知元素)
// @note
//  针对个人，可以通过监听 @ref TIMAddRecvNewMsgCallback 获取
// uint @ref TIMGroupReportType, 只读, 类型
static const char* kTIMGroupReportElemReportType = "group_report_elem_report_type";
// string, 只读, 群组ID
static const char* kTIMGroupReportElemGroupId = "group_report_elem_group_id";
// string, 只读, 群组名称（已废弃）
static const char* kTIMGroupReportElemGroupName = "group_report_elem_group_name";
// string, 只读, 操作者ID
static const char* kTIMGroupReportElemOpUser = "group_report_elem_op_user";
// string, 只读, 操作理由
static const char* kTIMGroupReportElemMsg = "group_report_elem_msg";
// string, 只读, 操作者填的自定义数据
static const char* kTIMGroupReportElemUserData = "group_report_elem_user_data";
// object @ref UserProfile, 只读, 操作者个人资料
static const char* kTIMGroupReportElemOpUserInfo = "group_report_elem_op_user_info";
// object @ref GroupMemberInfo, 只读,操作者群内资料
static const char* kTIMGroupReportElemOpGroupMemberInfo = "group_report_elem_op_group_memberinfo";
// string, 只读, 操作方平台信息
static const char* kTIMGroupReportElemPlatform = "group_report_elem_platform";
// uint, 只读, 被操作者的禁言时间(禁言某些用户时，被禁言的用户会收到该信息)
static const char* kTIMGroupReportElemShutUpTime = "group_report_elem_shut_up_time";
// uint @ref TIMReceiveMessageOpt, 只读，消息接收选项, 用户修改群消息接收选项时会收到该信息
static const char* kTIMGroupReportElemGroupMessageReceiveOption = "group_report_elem_group_message_receive_option";

//------------------------------------------------------------------------------
// 7.12 Message (消息)
// @note
// 对应 Elem 的顺序:
//   - 目前文件和语音Elem不一定会按照添加顺序传输，其他Elem按照顺序，不过建议不要过于依赖Elem顺序进行处理，应该逐个按照Elem类型处理，防止异常情况下进程Crash。
// 针对群组的红包和点赞消息:
//   - 对于直播场景，会有点赞和发红包功能，点赞相对优先级较低，红包消息优先级较高，具体消息内容可以使用自定义消息 @ref CustomElem 进行定义，发送消息时，可通过 TIMMsgPriority 定义消息优先级。
// 在线消息:
// 开发者通过设置 kTIMMsgIsOnlineMsg 字段为true时，表示发送在线消息,该消息有如下特性:
//   - C2C会话,当此消息发送时，只有对方在线，对方才会收到。如果当时离线，后续再登录也收不到此消息。
//   - 群会话,当此消息发送时，只有群里在线的成员才会收到。如果当时离线，后续再登录也收不到此消息。
//   - 此消息服务器不会保存
//   - 此消息不计入未读计数
//   - 此消息在本地不会存储
// 消息自定义字段:
//     - 开发者可以对消息增加自定义字段，如自定义整数(通过 kTIMMsgCustomInt 指定)、自定义二进制数据(通过 kTIMMsgCustomStr 指定，必须转换成 String，Json 不支持二进制传输)，可以根据这两个字段做出各种不同效果，例如语音消息是否已经播放等等。另外需要注意，此自定义字段仅存储于本地，不会同步到 Server，更换终端获取不到。
// array @ref Elem, 读写(必填), 消息内元素列表
static const char* kTIMMsgElemArray = "message_elem_array";
// string, 读写(选填), 消息所属会话ID
static const char* kTIMMsgConvId = "message_conv_id";
// uint @ref TIMConvType, 读写(选填), 消息所属会话类型
static const char* kTIMMsgConvType = "message_conv_type";
// string, 读写(选填), 消息的发送者
static const char* kTIMMsgSender = "message_sender";
// uint @ref TIMMsgPriority, 读写(选填), 消息优先级
static const char* kTIMMsgPriority = "message_priority";
// uint64, 读写(选填), 客户端时间
static const char* kTIMMsgClientTime = "message_client_time";
// uint64, 读写(选填), 服务端时间
static const char* kTIMMsgServerTime = "message_server_time";
// bool, 读写(选填), 消息是否来自自己
static const char* kTIMMsgIsFormSelf = "message_is_from_self";
// uint @ref TIMPlatform, 读写(选填), 发送消息的平台
static const char* kTIMMsgPlatform = "message_platform";
// bool, 读写(选填), 消息是否已读
static const char* kTIMMsgIsRead = "message_is_read";
// bool, 读写(选填), 消息是否是在线消息，false表示普通消息,true表示在线消息，默认为false
static const char* kTIMMsgIsOnlineMsg = "message_is_online_msg";
// bool, 只读, 对方是否已读（会话维度，已读的条件：msg_time <= 对端标记会话已读的时间），该字段为 true 的条件是消息 timestamp <= 对端标记会话已读的时间
static const char* kTIMMsgIsPeerRead = "message_is_peer_read";
// bool, 只读, 对方是否已读（消息维度，已读的条件：对端针对该消息上报了已读）
static const char* kTIMMsgReceiptPeerRead = "message_receipt_peer_read";
// bool, 读写(选填), 消息是否需要已读回执（6.1 以上版本有效，需要您购买旗舰版套餐），群消息在使用该功能之前，需要先到 IM 控制台设置已读回执支持的群类型
static const char* kTIMMsgNeedReadReceipt = "message_need_read_receipt";
// bool, 读写(选填), 是否支持消息扩展
static const char* kTIMMsgSupportMessageExtension = "message_support_message_extension";
// bool, 只读, 是否是广播消息，仅直播群支持（6.5 及以上版本支持，需要您购买旗舰版套餐）;
static const char* kTIMMsgIsBroadcastMessage = "message_is_broadcast_message";
// bool, 只读, 是否已经发送了已读回执（只有Group 消息有效）
static const char* kTIMMsgHasSentReceipt = "message_has_sent_receipt";
// int32, 只读, 注意：这个字段是内部字段，不推荐使用，推荐调用 TIMMsgGetMessageReadReceipts 获取群消息已读回执
static const char* kTIMMsgGroupReceiptReadCount = "message_group_receipt_read_count";
// int32, 只读, 注意：这个字段是内部字段，不推荐使用，推荐调用 TIMMsgGetMessageReadReceipts 获取群消息已读回执
static const char* kTIMMsgGroupReceiptUnreadCount = "message_group_receipt_unread_count";
// uint64, 只读, 注意：这个字段是内部字段，不推荐使用
static const char* kTIMMsgVersion = "message_version";
// uint @ref TIMMsgStatus, 读写(选填), 消息当前状态
static const char* kTIMMsgStatus = "message_status";
// uint64, 只读, 消息的唯一标识，推荐使用 kTIMMsgMsgId
static const char* kTIMMsgUniqueId = "message_unique_id";
// string, 只读, 消息的唯一标识
static const char* kTIMMsgMsgId = "message_msg_id";
// uint64, 只读, 消息的随机码
static const char* kTIMMsgRand = "message_rand";
// uint64, 只读, 消息序列
static const char* kTIMMsgSeq = "message_seq";
// uint32, 读写(选填), 自定义整数值字段（本地保存，不会发送到对端，程序卸载重装后失效）
static const char* kTIMMsgCustomInt = "message_custom_int";
// string, 读写(选填), 自定义数据字段（本地保存，不会发送到对端，程序卸载重装后失效）
static const char* kTIMMsgCustomStr = "message_custom_str";
// string, 读写(选填), 消息自定义数据（云端保存，会发送到对端，程序卸载重装后还能拉取到）
static const char* kTIMMsgCloudCustomStr = "message_cloud_custom_str";
// bool, 读写(选填), 消息是否不计入未读计数：默认为 NO，表明需要计入未读计数，设置为 YES，表明不需要计入未读计数
static const char* kTIMMsgIsExcludedFromUnreadCount = "message_is_excluded_from_unread_count";
// array string, 读写(选填), 群消息中被 @ 的用户 UserID 列表（即该消息都 @ 了哪些人），如果需要 @ALL ，请传入 kImSDK_MessageAtALL 字段
static const char* kTIMMsgGroupAtUserArray = "message_group_at_user_array";
// bool, 只写(选填), 如果需要转发一条消息，不能直接调用 sendMessage 接口发送原消息，原消息 kTIMMsgIsForwardMessage 设置为 true 再发送。
static const char* kTIMMsgIsForwardMessage = "message_is_forward_message";
// object @ref UserProfile, 读写(选填), 消息的发送者的用户资料
static const char* kTIMMsgSenderProfile = "message_sender_profile";
// object @ref GroupMemberInfo, 读写(选填), 消息发送者在群里面的信息，只有在群会话有效。目前仅能获取字段 kTIMGroupMemberInfoIdentifier、kTIMGroupMemberInfoNameCard 其他的字段建议通过 TIMGroupGetMemberInfoList 接口获取
static const char* kTIMMsgSenderGroupMemberInfo = "message_sender_group_member_info";
// bool, 读写, 是否作为会话的 lastMessage，true: 不作为，false: 作为
static const char* kTIMMsgExcludedFromLastMessage = "message_excluded_from_last_message";
// bool, 读写, 是否不过内容审核（包含【本地审核】和【云端审核】），只有在开通【本地审核】或【云端审核】功能后，该字段设置才有效，设置为 true，表明不过内容审核，设置为 false：表明过内容审核。【本地审核】开通流程请参考 [本地审核功能](https://cloud.tencent.com/document/product/269/83795#.E6.9C.AC.E5.9C.B0.E5.AE.A1.E6.A0.B8.E5.8A.9F.E8.83.BD)。 【云端审核】开通流程请参考 [云端审核功能](https://cloud.tencent.com/document/product/269/83795#.E4.BA.91.E7.AB.AF.E5.AE.A1.E6.A0.B8.E5.8A.9F.E8.83.BD)
static const char* kTIMMsgExcludedFromContentModeration = "message_excluded_from_content_moderation";
// string, 读写, 消息自定义审核配置 ID（从 7.8 版本开始支持）
// 在开通【云端审核】功能后，您可以请前往 [控制台](https://console.cloud.tencent.com/im) (云端审核 -> 审核配置 -> 自定义配置 -> 添加自定义配置) 获取配置 ID。
//【自定义审核】配置流程请参考 [云端审核功能]（https://cloud.tencent.com/document/product/269/78633#a5efc9e8-a7ec-40e3-9b18-8ed1910f589c）
// @note 该字段需要发消息前设置，仅用于控制发消息时的消息审核策略，其值不会存储在漫游和本地
static const char* kTIMMsgCustomModerationConfigurationID= "message_custom_moderation_configuration_id";
// bool, 只读（选填），是否被标记为有安全风险的消息（暂时只支持语音和视频消息），只有在开通【云端审核】功能后才生效，如果您发送的语音或视频消息内容不合规，云端异步审核后会触发 SDK 的 TIMMsgMessageModifiedCallback 回调，回调里的 message 对象该字段值为 true，从 7.4 版本开始支持
static const char* kTIMMsgHasRiskContent = "message_has_risk_content";
static const char* kTIMMsgRiskTypeIdentified = "message_risk_type_identified";
// array string, 只写(选填), 指定群消息接收成员（定向消息）；不支持群 @ 消息设置，不支持社群（Community）和直播群（AVChatRoom）消息设置；该字段设置后，消息会不计入会话未读数。
static const char* kTIMMsgTargetGroupMemberArray = "message_target_group_member_array";
// object @ref OfflinePushConfig, 读写(选填), 消息的离线推送设置
static const char* kTIMMsgOfflinePushConfig = "message_offline_push_config";
// string, 只读(选填), 消息撤回者的 user_id, 仅当消息为撤回状态时有效，从 7.4 版本开始支持
static const char* kTIMMsgRevokerUserId = "message_revoker_user_id";
// string, 只读(选填), 消息撤回者的昵称, 仅当消息为撤回状态时有效，从 7.4 版本开始支持
static const char* kTIMMsgRevokerNickName = "message_revoker_nick_name";
// string, 只读(选填), 消息撤回者的头像地址, 仅当消息为撤回状态时有效，从 7.4 版本开始支持
static const char* kTIMMsgRevokerFaceUrl = "message_revoker_face_url";
// string, 只读(选填), 消息撤回的原因, 仅当消息为撤回状态时有效，从 7.4 版本开始支持
static const char* kTIMMsgRevokeReason = "message_revoke_reason";

//------------------------------------------------------------------------------
// 7.13 MsgBatchSendParam (消息群发接口的参数)
// array string, 只写(必填), 接收群发消息的用户 ID 列表
static const char* kTIMMsgBatchSendParamIdentifierArray = "msg_batch_send_param_identifier_array";
// object @ref Message, 只写(必填), 群发的消息
static const char* kTIMMsgBatchSendParamMsg = "msg_batch_send_param_msg";

//------------------------------------------------------------------------------
// 7.14 MsgBatchSendResult (消息群发接口的返回)
// string, 只读, 接收群发消息的用户 ID
static const char* kTIMMsgBatchSendResultIdentifier = "msg_batch_send_result_identifier";
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 消息发送结果
static const char* kTIMMsgBatchSendResultCode = "msg_batch_send_result_code";
// string, 只读, 消息发送的描述
static const char* kTIMMsgBatchSendResultDesc = "msg_batch_send_result_desc";
// object @ref Message, 只读, 发送的消息
static const char* kTIMMsgBatchSendResultMsg = "msg_batch_send_result_msg";

//------------------------------------------------------------------------------
// 7.15 DownloadElemParam (下载元素接口的参数)
// uint @ref TIMDownloadType, 只写, 从消息元素里面取出来,元素的类型
static const char* kTIMMsgDownloadElemParamType = "msg_download_elem_param_type";
// string, 只写, 从消息元素里面取出来,元素的ID
static const char* kTIMMsgDownloadElemParamId = "msg_download_elem_param_id";
// uint, 只写, 从消息元素里面取出来,元素的BusinessID
static const char* kTIMMsgDownloadElemParamBusinessId = "msg_download_elem_param_business_id";
// string, 只写, 从消息元素里面取出来,元素URL
static const char* kTIMMsgDownloadElemParamUrl = "msg_download_elem_param_url";

//------------------------------------------------------------------------------
// 7.16 MsgDownloadElemResult (下载元素接口的返回)
// uint, 只读, 当前已下载的大小
static const char* kTIMMsgDownloadElemResultCurrentSize = "msg_download_elem_result_current_size";
// uint, 只读, 需要下载的文件总大小
static const char* kTIMMsgDownloadElemResultTotalSize = "msg_download_elem_result_total_size";


/////////////////////////////////////////////////////////////////////////////////
//
//                八. 消息拉取、查找、删除操作 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 8.1 MsgGetMsgListParam (获取历史消息接口的参数)
// object @ref Message, 只写(选填), 指定的消息, 不允许为 null
static const char* kTIMMsgGetMsgListParamLastMsg = "msg_getmsglist_param_last_msg";
// uint, 只写(选填), 从指定消息往后的消息数
static const char* kTIMMsgGetMsgListParamCount = "msg_getmsglist_param_count";
// bool, 只写(选填), 是否漫游消息
static const char* kTIMMsgGetMsgListParamIsRamble = "msg_getmsglist_param_is_ramble";
// array uint32, 只写(选填), 拉取的消息类型集合，kTIMMsgGetMsgListParamIsRamble 为 false 有效，传入空数组表示拉取全部类型消息，取值详见 @ref TIMElemType
static const char* kTIMMsgGetMsgListMessageTypeArray = "msg_getmsglist_param_message_type_array";
// bool, 只写(选填), 是否向前排序
static const char* kTIMMsgGetMsgListParamIsForward = "msg_getmsglist_param_is_forward";
// uint64, 只写(选填), 指定的消息的 seq
static const char* kTIMMsgGetMsgListParamLastMsgSeq = "msg_getmsglist_param_last_msg_seq";
// uint64, 只写(选填), 开始时间；UTC 时间戳， 单位：秒
static const char* kTIMMsgGetMsgListParamTimeBegin = "msg_getmsglist_param_time_begin";
// uint64, 只写(选填), 持续时间；单位：秒
static const char* kTIMMsgGetMsgListParamTimePeriod = "msg_getmsglist_param_time_period";
// array uint64, 只写(选填), 拉取的消息 seq 集合，仅针对 group 有效
static const char* kTIMMsgGetMsgListParamMessageSeqArray = "msg_getmsglist_param_message_seq_array";

//------------------------------------------------------------------------------
// 8.2 MsgLocator (消息定位符)
// bool, 读写, 要查找的消息所属的会话ID
static const char* kTIMMsgLocatorConvId = "message_locator_conv_id";
// bool, 读写, 要查找的消息所属的会话类型
static const char* kTIMMsgLocatorConvType = "message_locator_conv_type";
// bool, 读写(必填), 要查找的消息是否是被撤回。true表示被撤回的，false 表示未撤回的。默认为 false
static const char* kTIMMsgLocatorIsRevoked = "message_locator_is_revoked";
// uint64, 读写(必填), 要查找的消息的时间戳
static const char* kTIMMsgLocatorTime = "message_locator_time";
// uint64, 读写(必填), 要查找的消息的序列号
static const char* kTIMMsgLocatorSeq = "message_locator_seq";
// bool, 读写(必填), 要查找的消息的发送者是否是自己。true 表示发送者是自己，false 表示发送者不是自己。默认为 false
static const char* kTIMMsgLocatorIsSelf = "message_locator_is_self";
// uint64, 读写(必填), 要查找的消息随机码
static const char* kTIMMsgLocatorRand = "message_locator_rand";
// uint64, 读写(必填), 要查找的消息的唯一标识
static const char* kTIMMsgLocatorUniqueId = "message_locator_unique_id";

//------------------------------------------------------------------------------
// 8.3 MessageSearchParam (消息搜索参数)
// array string, 只写(必填)，搜索关键字列表，最多支持5个。
static const char* kTIMMsgSearchParamKeywordArray = "msg_search_param_keyword_array";
// array @ref TIMElemType, 只写(选填), 指定搜索的消息类型集合，传入空数组，表示搜索支持的全部类型消息（ @ref FaceElem 和 @ref GroupTipsElem 暂不支持）取值详见 @ref TIMElemType。
static const char* kTIMMsgSearchParamMessageTypeArray = "msg_search_param_message_type_array";
// string, 只写(选填)，会话唯一 ID，C2C 单聊组成方式为: "c2c_userID"：群聊组成方式为: "group_groupID"
static const char* kTIMMsgSearchParamConvId = "msg_search_param_conv_id";
// uint @ref TIMConvType, 只写(选填), 会话类型，如果设置 kTIMConv_Invalid，代表搜索全部会话。否则，代表搜索指定会话。
static const char* kTIMMsgSearchParamConvType = "msg_search_param_conv_type";
// uint64, 只写(选填), 搜索的起始时间点。默认为0即代表从现在开始搜索。UTC 时间戳，单位：秒
static const char* kTIMMsgSearchParamSearchTimePosition = "msg_search_param_search_time_position";
// uint64, 只写(选填), 从起始时间点开始的过去时间范围，单位秒。默认为0即代表不限制时间范围，传 24x60x60 代表过去一天。
static const char* kTIMMsgSearchParamSearchTimePeriod = "msg_search_param_search_time_period";
// uint, 只写(选填), 分页的页号：用于分页展示查找结果，从零开始起步。首次调用：通过参数 pageSize = 10, pageIndex = 0 调用 searchLocalMessage，从结果回调中的 totalCount 可以获知总共有多少条结果。计算页数：可以获知总页数：totalPage = (totalCount % loadCount == 0) ? (totalCount / pageIndex) : (totalCount / pageIndex + 1) 。再次调用：可以通过指定参数 pageIndex (pageIndex < totalPage) 返回后续页号的结果。
static const char* kTIMMsgSearchParamPageIndex = "msg_search_param_page_index";
// uint, 只写(选填), 每页结果数量：用于分页展示查找结果，如不希望分页可将其设置成 0，但如果结果太多，可能会带来性能问题。
static const char* kTIMMsgSearchParamPageSize = "msg_search_param_page_size";
// uint @ref TIMKeywordListMatchType, 只写(选填), 关键字进行 Or 或者 And 进行搜索(不填写时，默认为 Or)
static const char* kTIMMsgSearchParamKeywordListMatchType = "msg_search_param_keyword_list_match_type";
// array string, 只写(选填), 按照发送者的 userid 进行搜索
static const char* kTIMMsgSearchParamSenderIdentifierArray = "msg_search_param_send_identifier_array";
// uint, 只写(选填), 服务武器搜索结果数量。
static const char* kTIMMsgSearchParamSearchCount = "msg_search_param_search_count";
// string, 只写(选填)，服务武器搜索游标。第一次填空字符串，续拉时填写 @ref MessageSearchResult 中的返回值。
static const char* kTIMMsgSearchParamSearchCursor = "msg_search_param_search_cursor";

//------------------------------------------------------------------------------
// 8.4 MessageSearchResultItem (消息搜索结果项)
// string, 只读，会话 ID
static const char* kTIMMsgSearchResultItemConvId = "msg_search_result_item_conv_id";
// uint @ref TIMConvType, 只读, 会话类型
static const char* kTIMMsgSearchResultItemConvType = "msg_search_result_item_conv_type";
// uint, 只读, 当前会话一共搜索到了多少条符合要求的消息
static const char* kTIMMsgSearchResultItemTotalMessageCount = "msg_search_result_item_total_message_count";
// array @ref Message, 只读, 满足搜索条件的消息列表
static const char* kTIMMsgSearchResultItemMessageArray = "msg_search_result_item_message_array";

//------------------------------------------------------------------------------
// 8.5 MessageSearchResult (消息搜索结果返回)
// uint, 只读, 如果您本次搜索【指定会话】，那么返回满足搜索条件的消息总数量；如果您本次搜索【全部会话】，那么返回满足搜索条件的消息所在的所有会话总数量。
static const char* kTIMMsgSearchResultTotalCount = "msg_search_result_total_count";
// array @ref MessageSearchResultItem, 只读, 如果您本次搜索【指定会话】，那么返回结果列表只包含该会话结果；如果您本次搜索【全部会话】，那么对满足搜索条件的消息根据会话 ID 分组，分页返回分组结果；
static const char* kTIMMsgSearchResultItemArray = "msg_search_result_item_array";
// string, 只写(选填)，服务器搜索游标。
static const char* kTIMMsgSearchResultSearchCursor = "msg_search_result_search_cursor";

//------------------------------------------------------------------------------
// 8.5 MsgDeleteParam (消息删除接口的参数)
// object @ref Message, 只写(选填), 要删除的消息
static const char* kTIMMsgDeleteParamMsg = "msg_delete_param_msg";
// bool, 只写(选填), 是否删除本地/漫游所有消息。true删除漫游消息，false删除本地消息，默认值false
static const char* kTIMMsgDeleteParamIsRamble = "msg_delete_param_is_ramble";


/////////////////////////////////////////////////////////////////////////////////
//
//                    九. 消息接收选项 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 9.1 GetC2CRecvMsgOptResult (查询 C2C 消息接收选项的返回)
// string, 只读，用户 ID
static const char* kTIMMsgGetC2CRecvMsgOptResultIdentifier = "msg_recv_msg_opt_result_identifier";
// uint @ref TIMReceiveMessageOpt, 只读，消息接收选项
static const char* kTIMMsgGetC2CRecvMsgOptResultOpt = "msg_recv_msg_opt_result_opt";

//------------------------------------------------------------------------------
// 9.2 TIMReceiveMessageOptInfo (全局消息消息接收选项)
// uint, 只读, 获取消息免打扰开始时间：小时
static const char* kTIMMsgAllRecvMsgOptStartHour = "msg_all_recv_msg_opt_start_hour";
// uint, 只读, 获取消息免打扰开始时间：分钟
static const char* kTIMMsgAllRecvMsgOptStartMinute = "msg_all_recv_msg_opt_start_minute";
// uint, 只读, 获取消息免打扰开始时间：秒
static const char* kTIMMsgAllRecvMsgOptStartSecond = "msg_all_recv_msg_opt_start_second";
// uint, 只读, 获取消息免打扰开始的 UTC 时间戳，如果返回的 startTimeStamp 大于 0，您可以直接使用；如果返回的 startTimeStamp 等于 0，您需要调用 getStartHour()、getStartMinute()、getStartSecond() 来获取免打扰的相对开始时间
static const char* kTIMMsgAllRecvMsgOptStartTimeStamp = "msg_all_recv_msg_opt_start_time_stamp";
// uint, 只读, 获取免打扰持续时长，单位：秒
static const char* kTIMMsgAllRecvMsgDuration = "msg_all_recv_msg_duration";
// uint @ref TIMReceiveMessageOpt, 只读, 消息接收选项，支持两种类型：kTIMRecvMsgOpt_Receive 和 kTIMRecvMsgOpt_Not_Notify
static const char* kTIMMsgAllRecvMsgOptLevel = "msg_all_recv_msg_opt_level";


/////////////////////////////////////////////////////////////////////////////////
//
//         十. 消息翻译、已读回执、扩展、回应等 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 10.1 MessageTranslateTextResult (文本消息翻译结果)
// string, 只读, 待翻译的文本
static const char* kTIMMsgTranslateTextSourceText = "msg_translate_text_source_text";
// string, 只读, 翻译后的文本
static const char* kTIMMsgTranslateTextTargetText = "msg_translate_text_target_text";

//------------------------------------------------------------------------------
// 10.2 MessageReceipt (消息已读回执)
// string, 只读, 会话ID
static const char* kTIMMsgReceiptConvId = "msg_receipt_conv_id";
// uint @ref TIMConvType, 只读, 会话类型
static const char* kTIMMsgReceiptConvType = "msg_receipt_conv_type";
// string, 只读, 群消息 ID
static const char* kTIMMsgReceiptMsgId = "msg_receipt_msg_id";
// uint64, 只读, 时间戳
static const char* kTIMMsgReceiptTimeStamp = "msg_receipt_time_stamp";
// bool, 只读, C2C 对端消息是否已读
static const char* kTIMMsgReceiptIsPeerRead = "msg_receipt_is_peer_read";
// uint64, 只读, 群消息已读人数
static const char* kTIMMsgReceiptReadCount = "msg_receipt_read_count";
// uint64, 只读, 群消息未读人数
static const char* kTIMMsgReceiptUnreadCount = "msg_receipt_unread_count";

//------------------------------------------------------------------------------
// 10.3 MessageExtension (消息扩展信息)
// string, 读写(选填), 扩展字段的 key
static const char* kTIMMsgExtensionKey = "message_extension_key";
// string, 读写(选填), 扩展字段的 value
static const char* kTIMMsgExtensionValue = "message_extension_value";

//------------------------------------------------------------------------------
// 10.4 MessageExtensionResult (消息扩展操作结果)
// uint32, 只读, 消息扩展操作的返回码
static const char* kTIMMsgExtensionResultCode = "message_extension_result_code";
// string, 只读, 消息扩展操作的返回信息提示
static const char* kTIMMsgExtensionResultInfo = "message_extension_result_info";
// object, 只读, 消息扩展操作返回结果所对应的扩展字段（每一对 key-value 都会自己的操作返回码以及返回信息提示）
static const char* kTIMMsgExtensionItem = "message_extension_item";

//------------------------------------------------------------------------------
// 10.5 MessageReaction (消息回应信息)
// string, 只读, 消息回应 ID
static const char* kTIMMsgReactionID = "message_reaction_id";
// uint32, 只读，消息回应总用户个数
static const char* kTIMMsgReactionTotalUserCount = "message_reaction_total_user_count";
// array @ref UserInfo, 只读, 使用同一个 reaction_id 回应消息的部分用户列表（用户列表数量取决于调用 TIMMsgGetMessageReactions 接口时设置的 max_user_count_per_reaction 值）
static const char* kTIMMsgReactionPartialUserInfoList = "message_reaction_partial_user_info_array";
// bool, 只读，自己是否使用了该 reaction
static const char* kTIMMsgReactionReactedByMyself = "message_reaction_reacted_by_myself";

//------------------------------------------------------------------------------
// 10.6 MessageReactionResult (消息回应列表拉取结果)
// uint32, 只读, 消息扩展操作的返回码
static const char* kTIMMsgReactionResultCode = "message_reaction_result_code";
// string, 只读, 消息扩展操作的返回信息提示
static const char* kTIMMsgReactionResultInfo = "message_reaction_result_info";
// string, 只读, 消息 ID
static const char* kTIMMsgReactionResultMsgId = "message_reaction_result_msg_id";
// array @ref MessageReaction, 只读, 消息回应列表
static const char* kTIMMsgReactionResultReactionList = "message_reaction_result_reaction_list";

//------------------------------------------------------------------------------
// 10.7 MessageReactionUserResult (消息回应用户列表拉取结果)
// array @ref UserInfo, 只读, 消息回应用户列表
static const char* kTIMMsgReactionUserResultUserInfoArray = "message_reaction_user_result_user_info_array";
// uint32, 只读, 消息回应用户列表下次拉取 seq
static const char* kTIMMsgReactionUserResultNextSeq = "message_reaction_user_result_next_seq";
// bool, 只读, true: 已拉取完所有消息回应用户列表，false: 未拉取完所有消息回应用户列表
static const char* kTIMMsgReactionUserResultIsFinished = "message_reaction_user_result_is_finished";

//------------------------------------------------------------------------------
// 10.8 MessageReactionChangeInfo (消息回应列表更新信息)
// string, 只读, 消息 ID
static const char* kTIMMsgReactionChangeInfoMsgId = "message_reaction_change_info_msg_id";
// array @ref MessageReaction, 只读, 变更的消息回应列表
static const char* kTIMMsgReactionChangeInfoReactionList = "message_reaction_change_info_reaction_list";


/////////////////////////////////////////////////////////////////////////////////
//
//                            十一. 废弃字段
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 11.1 以下为老版本拼写错误，为了兼容老版本而保留的宏定义
// 若在消息 kTIMMsgGroupAtUserArray 字段中填入，表示当前消息需要 @ 群里所有人
#define kImSDK_MesssageAtALL  kImSDK_MessageAtALL
// LocationElem (位置元素) JsonKey
#define kTIMLocationElemlatitude  kTIMLocationElemLatitude

/////////////////////////////////////////////////////////////////////////////////
//
//                            十二. 废弃接口
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 12.1 发送新消息（待废弃接口，请使用 TIMMsgSendMessage 接口）
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_param  消息json字符串
 * @param cb 发送新消息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 发送新消息，单聊消息和群消息的发送均采用此接口：
 *  - 发送单聊消息时 conv_id 为对方的UserID， conv_type 为 kTIMConv_C2C
 *  - 发送群聊消息时 conv_id 为群ID， conv_type 为 kTIMConv_Group 。
 * 发送消息时不能发送 kTIMElem_GroupTips、 kTIMElem_GroupReport，他们由后台下发，用于更新(通知)群的信息。可以发送的消息内元素：
 *  - 文本消息元素，请参考 @ref TextElem
 *  - 表情消息元素，请参考 @ref FaceElem
 *  - 位置消息元素，请参考 @ref LocationElem
 *  - 图片消息元素，请参考 @ref ImageElem
 *  - 声音消息元素，请参考 @ref SoundElem
 *  - 自定义消息元素，请参考 @ref CustomElem
 *  - 文件消息元素，请参考 @ref FileElem
 *  - 视频消息元素，请参考 @ref VideoElem
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_text;
 * json_value_text[kTIMElemType] = kTIMElem_Text;
 * json_value_text[kTIMTextElemContent] = "send text";
 * Json::Value json_value_msg;
 * json_value_msg[kTIMMsgElemArray].append(json_value_text);
 * json_value_msg[kTIMMsgSender] = login_id;
 * json_value_msg[kTIMMsgClientTime] = time(NULL);
 * json_value_msg[kTIMMsgServerTime] = time(NULL);
 *
 * int ret = TIMMsgSendNewMsg(conv_id.c_str(), kTIMConv_C2C, json_value_msg.toStyledString().c_str(),
 *     [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 消息发送失败
 *         return;
 *     }
 *     // 消息发送成功
 * }, this);
 *
 * // json_value_msg.toStyledString().c_str() 得到 json_msg_param JSON 字符串如下
 * {
 *    "message_client_time" : 1551446728,
 *    "message_elem_array" : [
 *       {
 *          "elem_type" : 0,
 *          "text_elem_content" : "send text"
 *       }
 *    ],
 *    "message_sender" : "user1",
 *    "message_server_time" : 1551446728
 * }
 * @endcode
 */
TIM_API int TIMMsgSendNewMsg(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_param, TIMCommCallback cb, const void* user_data);

/**
 * 12.2 发送新消息（待废弃接口，请使用 TIMMsgSendMessage 接口）
 *
 * @param conv_id   会话的ID
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_param  消息json字符串
 * @param msgid_cb 返回消息 ID 的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param res_cb 发送新消息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 发送新消息，单聊消息和群消息的发送均采用此接口：
 *  - 发送单聊消息时 conv_id 为对方的UserID， conv_type 为 kTIMConv_C2C
 *  - 发送群聊消息时 conv_id 为群ID， conv_type 为 kTIMConv_Group 。
 * 发送消息时不能发送 kTIMElem_GroupTips、 kTIMElem_GroupReport，他们由后台下发，用于更新(通知)群的信息。可以发送的消息内元素：
 *  - 文本消息元素，请参考 @ref TextElem
 *  - 表情消息元素，请参考 @ref FaceElem
 *  - 位置消息元素，请参考 @ref LocationElem
 *  - 图片消息元素，请参考 @ref ImageElem
 *  - 声音消息元素，请参考 @ref SoundElem
 *  - 自定义消息元素，请参考 @ref CustomElem
 *  - 文件消息元素，请参考 @ref FileElem
 *  - 视频消息元素，请参考 @ref VideoElem
 * 
 * __示例__
 * @code{.cpp}
 * Json::Value json_value_text;
 * json_value_text[kTIMElemType] = kTIMElem_Text;
 * json_value_text[kTIMTextElemContent] = "send text";
 * Json::Value json_value_msg;
 * json_value_msg[kTIMMsgElemArray].append(json_value_text);
 * json_value_msg[kTIMMsgSender] = login_id;
 * json_value_msg[kTIMMsgClientTime] = time(NULL);
 * json_value_msg[kTIMMsgServerTime] = time(NULL);
 *
 * int ret = TIMMsgSendNewMsgEx(conv_id.c_str(), kTIMConv_C2C, json_value_msg.toStyledString().c_str(),
 *    [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         // 从 json_param 读取消息 ID
 *    },
 *    [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *         if (ERR_SUCC != code) {
 *             // 消息发送失败
 *             return;
 *         }
 *         // 消息发送成功
 *     }，
 * }, this);
 *
 * // json_value_msg.toStyledString().c_str() 得到 json_msg_param JSON 字符串如下
 * {
 *    "message_client_time" : 1551446728,
 *    "message_elem_array" : [
 *       {
 *          "elem_type" : 0,
 *          "text_elem_content" : "send text"
 *       }
 *    ],
 *    "message_sender" : "user1",
 *    "message_server_time" : 1551446728
 * }
 * @endcode
 */
TIM_API int TIMMsgSendNewMsgEx(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_param, TIMCommCallback msgid_cb, TIMCommCallback res_cb, const void* user_data);

/**
 * 12.3 消息上报已读（待废弃接口，请使用 TIMConvCleanConversationUnreadMessageCount 接口, 详见 TIMConversationManager.h 文件）
 *
 * @param conv_id   会话的ID，从 5.8 版本开始，当 conv_id 为 NULL 空字符串指针或者 "" 空字符串时，标记 conv_type 表示的所有单聊消息或者群组消息为已读状态
 * @param conv_type 会话类型，请参考 @ref TIMConvType
 * @param json_msg_param  消息json字符串
 * @param cb 消息上报已读成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * json_msg_param 可以填 NULL 空字符串指针或者 "" 空字符串，此时以会话当前最新消息的时间戳（如果会话存在最新消息）或当前时间为已读时间戳上报.当要指定消息时，则以该指定消息的时间戳为已读时间戳上报，最好用接收新消息获取的消息数组里面的消息Json或者用消息定位符查找到的消息Json，避免重复构造消息Json。
 */
TIM_API int TIMMsgReportReaded(const char* conv_id, enum TIMConvType conv_type, const char* json_msg_param, TIMCommCallback cb, const void* user_data);

/**
 * 12.4 标记所有消息为已读（待废弃接口，请使用 TIMConvCleanConversationUnreadMessageCount 接口，详见 TIMConversationManager.h 文件）
 *
 * @param cb 成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 */
TIM_API int TIMMsgMarkAllMessageAsRead(TIMCommCallback cb, const void* user_data);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_MESSAGE_MANAGER_H_
