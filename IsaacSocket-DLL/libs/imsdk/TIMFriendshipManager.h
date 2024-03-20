// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_FRIENDSHIP_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_FRIENDSHIP_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
//  - 关系链接口，包含好友的添加、删除，黑名单的添加、删除等功能
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
//                        一. 关系链相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 好友变更类型
enum TIMFriendChangeType {
    // 未知类型
    kTIMFriendChange_None,
    // 新增好友
    kTIMFriendChange_FriendAdd,
    // 删除好友
    kTIMFriendChange_FriendDel,
    // 新增好友申请的未决
    kTIMFriendChange_PendencyAdd,
    // 删除好友申请的未决
    kTIMFriendChange_PendencyDel,
    // 加入黑名单
    kTIMFriendChange_BlackListAdd,
    // 从黑名单移除
    kTIMFriendChange_BlackListDel,
    // 未决已读上报
    kTIMFriendChange_PendencyReadedReport,
    // 好友数据更新
    kTIMFriendChange_FriendProfileUpdate,
    // 分组增加
    kTIMFriendChange_FriendGroupAdd,
    // 分组删除
    kTIMFriendChange_FriendGroupDel,
    // 分组修改
    kTIMFriendChange_FriendGroupModify,
};

// 1.2 好友类型
enum TIMFriendType {
    // 单向好友：用户A的好友表中有用户B，但B的好友表中却没有A
    FriendTypeSingle,
    // 双向好友：用户A的好友表中有用户B，B的好友表中也有A
    FriendTypeBoth,
};

// 1.3 好友申请未决类型
enum TIMFriendPendencyType {
    // 别人发给我的
    FriendPendencyTypeComeIn,
    // 我发给别人的
    FriendPendencyTypeSendOut,
    // 双向的
    FriendPendencyTypeBoth,
};

// 1.4 响应好友申请的动作类型
enum TIMFriendResponseAction {
    // 同意
    ResponseActionAgree,
    // 同意并添加
    ResponseActionAgreeAndAdd,
    // 拒绝
    ResponseActionReject,
};

// 1.5 好友的类型
enum TIMFriendCheckRelation {
    // 无关系
    FriendCheckNoRelation,
    // 仅A中有B
    FriendCheckAWithB,
    // 仅B中有A
    FriendCheckBWithA,
    // 双向
    FriendCheckBothWay,
};

// 1.6 好友搜索的枚举
enum TIMFriendshipSearchFieldKey {
    // 用户 ID
    kTIMFriendshipSearchFieldKey_Identifier = 0x01,
    // 昵称
    kTIMFriendshipSearchFieldKey_NickName = 0x01 << 1,
    // 备注
    kTIMFriendshipSearchFieldKey_Remark = 0x01 << 2,
};

// 1.7 两个用户之间的好友关系
enum TIMFriendshipRelationType {
    // 未知关系
    kTIMFriendshipRelationType_None,
    // 单向好友：对方是我的好友，我不是对方的好友
    kTIMFriendshipRelationType_InMyFriendList,
    // 单向好友：对方不是我的好友，我是对方的好友
    kTIMFriendshipRelationType_InOtherFriendList,
    // 双向好友
    kTIMFriendshipRelationType_BothFriend,
};

// 1.8 关注类型
enum TIMFollowType {
    // 无任何关注关系
    kTIMFollowLTypeNone,
    // 对方在我的关注列表中
    kTIMFollowLTypeInMyFollowingList,
    // 对方在我的粉丝列表中
    kTIMFollowLTypeInMyFollowersList,
    // 对方与我互相关注
    kTIMFollowLTypeInBothFollowersList,
};

/////////////////////////////////////////////////////////////////////////////////
//
//                           二. 关系链事件回调定义
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 添加好友的回调
 *
 * @param json_identifier_array 添加好友列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __json_identifier_array 示例__
 * @code{.json}
 * [ "user15" ]
 * @endcode
 */
typedef void(*TIMOnAddFriendCallback)(const char* json_identifier_array, const void* user_data);

/**
 * 2.2 删除好友的回调
 *
 * @param json_identifier_array 删除好友列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __json_identifier_array 示例__
 * @code{.json}
 * [ "user15" ]
 * @endcode
 */
typedef void(*TIMOnDeleteFriendCallback)(const char* json_identifier_array, const void* user_data);

/**
 * 2.3 更新好友资料的回调
 *
 * @param json_friend_profile_update_array 好友资料更新列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __json_friend_profile_update_array 示例 (Json Key 请参考 @ref FriendProfileItem)__
 * @code{.json}
 * [
 *    {
 *       "friend_profile_update_identifier" : "user4",
 *       "friend_profile_update_item" : {
 *          "friend_profile_item_group_name_array" : [ "group1", "group2" ],
 *          "friend_profile_item_remark" : "New Remark"
 *       }
 *    }
 * ]
 * @endcode
 */
typedef void(*TIMUpdateFriendProfileCallback)(const char* json_friend_profile_update_array, const void* user_data);

/**
 * 2.4 好友添加请求的回调
 *
 * @param json_friend_add_request_pendency_array 好友添加请求未决信息列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __json_friend_add_request_pendency_array 示例 (Json Key 请参考 @ref FriendAddPendency)__
 * @code{.json}
 * [
 *    {
 *       "friend_add_pendency_add_source" : "AddSource_Type_android",
 *       "friend_add_pendency_add_wording" : "aaaa",
 *       "friend_add_pendency_identifier" : "v222",
 *       "friend_add_pendency_nick_name" : ""
 *    }
 * ]
 * @endcode
 */
typedef void(*TIMFriendAddRequestCallback)(const char* json_friend_add_request_pendency_array, const void* user_data);

/**
 * 2.5 好友申请删除通知
 * 
 * @param json_identifier_array 删除好友请求的 userid 列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 * 
 * @note
 *  以下四种情况会收到这个回调:
 *  1. 主动删除好友申请
 *  2. 拒绝好友申请
 *  3. 同意好友申请
 *  4. 申请加别人好友被拒绝
 * 
 * __json_identifier_array 的示例__
 * @code{.json}
 * [ "user15" ]
 * @endcode
 */
typedef void(*TIMFriendApplicationListDeletedCallback)(const char* json_identifier_array, const void* user_data);

/**
 * 2.6 好友申请已读通知
 *
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * @note
 * 如果调用 @ref TIMFriendshipReportPendencyReaded 设置好友申请列表已读，会收到这个回调（主要用于多端同步）
 */
typedef void(*TIMFriendApplicationListReadCallback)(const void* user_data);

/**
 * 2.7 黑名单新增通知
 * 
 * @param json_friend_black_added_array 新增黑名单列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __json_friend_black_added_array 示例 (Json Key 请参考 @ref FriendProfile)__
 * @code{.json}
 * [{
 *   "friend_profile_add_source": "",
 *   "friend_profile_add_time": 0,
 *   "friend_profile_add_wording": "",
 *   "friend_profile_custom_string_array": [{
 *       "friend_profile_custom_string_info_key": "Tag_Profile_Custom_Str",
 *       "friend_profile_custom_string_info_value": "test3-lamar-value"
 *   }],
 *   "friend_profile_group_name_array": [],
 *   "friend_profile_identifier": "98826",
 *   "friend_profile_remark": "",
 *   "friend_profile_user_profile": {
 *       "user_profile_add_permission": 1,
 *       "user_profile_birthday": 2000,
 *       "user_profile_custom_string_array": [{
 *           "user_profile_custom_string_info_key": "Tag_Profile_Custom_Str",
 *           "user_profile_custom_string_info_value": "test3-lamar-value"
 *       }],
 *       "user_profile_face_url": "test1-www.google.com",
 *       "user_profile_gender": 2,
 *       "user_profile_identifier": "98826",
 *       "user_profile_language": 1000,
 *       "user_profile_level": 3000,
 *       "user_profile_location": "shenzhen",
 *       "user_profile_nick_name": "test change8888",
 *       "user_profile_role": 4000,
 *       "user_profile_self_signature": "1111111"
 *   }
 * }]
 * @endcode
 */
typedef void(*TIMFriendBlackListAddedCallback)(const char* json_friend_black_added_array, const void* user_data);

/**
 * 2.8 黑名单删除通知
 *
 * @param json_identifier_array 黑名单列表
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 *
 * __json_identifier_array 示例__
 * @code{.json}
 * [ "user15" ]
 * @endcode
 */
typedef void(*TIMFriendBlackListDeletedCallback)(const char* json_identifier_array, const void* user_data);

/**
 * 2.9 订阅公众号的回调
 *
 * @param json_official_account_info 公众号资料，Json Key 请参考 @ref OfficialAccountInfo
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMOfficialAccountSubscribedCallback)(const char* json_official_account_info, const void* user_data);

/**
 * 2.10 取消订阅公众号的回调
 *
 * @param official_account_id 公众号 ID
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMOfficialAccountUnsubscribedCallback)(const char* official_account_id, const void* user_data);

/**
 * 2.11 订阅的公众号被删除的回调
 *
 * @param official_account_id 公众号 ID
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMOfficialAccountDeletedCallback)(const char* official_account_id, const void* user_data);

/**
 * 2.12 订阅的公众号资料更新的回调
 *
 * @param json_official_account_info 公众号资料，Json Key 请参考 @ref OfficialAccountInfo
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMOfficialAccountInfoChangedCallback)(const char* json_official_account_info, const void* user_data);

/**
 * 2.13 关注列表变更的回调
 *
 * @param json_user_info_list 变更的用户列表，Json Key 请参考 @ref UserInfo
 * @param is_add 变更用户是否为新增
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMMyFollowingListChangedCallback)(const char* json_user_info_list, bool is_add, const void* user_data);

/**
 * 2.14 粉丝列表变更的回调
 *
 * @param json_user_info_list 变更的用户列表，Json Key 请参考 @ref UserInfo
 * @param is_add 变更用户是否为新增
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMMyFollowersListChangedCallback)(const char* json_user_info_list, bool is_add, const void* user_data);

/**
 * 2.15 互关列表变更的回调
 *
 * @param json_user_info_list 变更的用户列表，Json Key 请参考 @ref UserInfo
 * @param is_add 变更用户是否为新增
 * @param user_data ImSDK负责透传的用户自定义数据，未做任何处理
 */
typedef void (*TIMMutualFollowersListChangedCallback)(const char* json_user_info_list, bool is_add, const void* user_data);

/////////////////////////////////////////////////////////////////////////////////
//
//                         三. 注册关系链事件回调 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 3.1 设置添加好友的回调
 * 
 * @param cb 添加好友回调，请参考 @ref TIMOnAddFriendCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 此回调为了多终端同步。例如A设备、B设备都登录了同一账号的ImSDK，A设备添加了好友，B设备ImSDK会收到添加好友的推送，ImSDK通过此回调告知开发者。
 */
TIM_API void TIMSetOnAddFriendCallback(TIMOnAddFriendCallback cb, const void* user_data);

/**
 * 3.2 设置删除好友的回调
 * 
 * @param cb 删除好友回调，请参考 @ref TIMOnDeleteFriendCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 此回调为了多终端同步。例如A设备、B设备都登录了同一账号的ImSDK，A设备删除了好友，B设备ImSDK会收到删除好友的推送，ImSDK通过此回调告知开发者。
 */
TIM_API void TIMSetOnDeleteFriendCallback(TIMOnDeleteFriendCallback cb, const void* user_data);

/**
 * 3.3 设置更新好友资料的回调
 * 
 * @param cb 更新好友资料回调，请参考 @ref TIMUpdateFriendProfileCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 此回调为了多终端同步。例如A设备、B设备都登录了同一账号的ImSDK，A设备更新了好友资料，B设备ImSDK会收到更新好友资料的推送，ImSDK通过此回调告知开发者。
 */
TIM_API void TIMSetUpdateFriendProfileCallback(TIMUpdateFriendProfileCallback cb, const void* user_data);

/**
 * 3.4 设置好友添加请求的回调
 * 
 * @param cb 好友添加请求回调，请参考 @ref TIMFriendAddRequestCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 当前登入用户设置添加好友需要确认时，如果有用户请求加当前登入用户为好友，会收到好友添加请求的回调，ImSDK通过此回调告知开发者。如果多终端登入同一账号，每个终端都会收到这个回调。
 */
TIM_API void TIMSetFriendAddRequestCallback(TIMFriendAddRequestCallback cb, const void* user_data);

/**
 * 3.5 设置好友申请被删除的回调
 * 
 * @param cb 好友申请删除回调，请参考 @ref TIMFriendApplicationListDeletedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 以下四种情况会收到此回调：
 *  1. 主动删除好友申请
 *  2. 拒绝好友申请
 *  3. 同意好友申请
 *  4. 申请加别人好友被拒绝
 */
TIM_API void TIMSetFriendApplicationListDeletedCallback(TIMFriendApplicationListDeletedCallback cb, const void* user_data);

/**
 * 3.6 设置好友申请已读的回调
 * 
 * @param cb 好友申请已读回调，请参考 @ref TIMFriendApplicationListReadCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 *
 * @note
 * 如果调用 @ref TIMFriendshipReportPendencyReaded 设置好友申请列表已读，会收到这个回调（主要用于多端同步）
 */
TIM_API void TIMSetFriendApplicationListReadCallback(TIMFriendApplicationListReadCallback cb, const void* user_data);

/**
 * 3.7 设置黑名单新增的回调
 * 
 * @param cb 黑名单新增的回调，请参考 @ref TIMFriendBlackListAddedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetFriendBlackListAddedCallback(TIMFriendBlackListAddedCallback cb, const void* user_data);

/**
 * 3.8 设置黑名单删除的回调
 * 
 * @param cb 黑名单删除的回调，请参考 @ref TIMFriendBlackListDeletedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetFriendBlackListDeletedCallback(TIMFriendBlackListDeletedCallback cb, const void* user_data);

/**
 * 3.9 设置公众号订阅的回调
 *
 * @param cb 公众号订阅的回调，请参考 @ref TIMOfficialAccountSubscribedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetOfficialAccountSubscribedCallback(TIMOfficialAccountSubscribedCallback cb, const void* user_data);

/**
 * 3.10 设置公众号取消订阅的回调
 *
 * @param cb 公众号取消订阅的回调，请参考 @ref TIMOfficialAccountUnsubscribedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetOfficialAccountUnsubscribedCallback(TIMOfficialAccountUnsubscribedCallback cb, const void *user_data);

/**
 * 3.11 设置订阅的公众号被删除的回调
 *
 * @param cb 订阅的公众号被删除的回调，请参考 @ref TIMOfficialAccountDeletedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetOfficialAccountDeletedCallback(TIMOfficialAccountDeletedCallback cb, const void *user_data);

/**
 * 3.12 设置订阅的公众号资料更新的回调
 *
 * @param cb 订阅的公众号资料更新的回调，请参考 @ref TIMOfficialAccountInfoChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetOfficialAccountInfoChangedCallback(TIMOfficialAccountInfoChangedCallback cb, const void *user_data);

/**
 * 3.13 设置关注列表变更的回调
 *
 * @param cb 关注列表变更的回调，请参考 @ref TIMMyFollowingListChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetMyFollowingListChangedCallback(TIMMyFollowingListChangedCallback cb, const void *user_data);

/**
 * 3.14 设置粉丝列表变更的回调
 *
 * @param cb 关注列表变更的回调，请参考 @ref TIMMyFollowersListChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetMyFollowersListChangedCallback(TIMMyFollowersListChangedCallback cb, const void *user_data);

/**
 * 3.15 设置互关列表变更的回调
 *
 * @param cb 关注列表变更的回调，请参考 @ref TIMMutualFollowersListChangedCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 */
TIM_API void TIMSetMutualFollowersListChangedCallback(TIMMutualFollowersListChangedCallback cb, const void *user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                   四. 好友添加、删除、列表获取、资料设置相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 4.1 获取好友列表
 *
 * @param cb 获取好友列表成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 此接口通过回调返回所有好友资料 @ref FriendProfile
 */
TIM_API int TIMFriendshipGetFriendProfileList(TIMCommCallback cb, const void* user_data);

/**
 * 4.2 获取指定好友资料
 *
 * @param friend_id_list 获取好友的 userid 列表
 * @param cb 获取好友信息的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   json::Array json_array;
 *   json_array.push_back("98826");
 *   TIMFriendshipGetFriendsInfo(json_array.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *       printf("GetFriendsInfo code:%d|desc:%s|json_param %s\r\n", code, desc, json_param);
 *   }, nullptr);
 *
 *   json_array.toStyledString().c_str() 得到 JSON 字符串如下:
 *   ["98826"]
 * @endcode
 *
 * __回调的 json_param 示例 (Json Key 请参考 @ref FriendInfoGetResult)__
 * @code{.json}
 *   [{
 *   "friendship_friend_info_get_result_error_code": 0,
 *   "friendship_friend_info_get_result_error_message": "OK",
 *   "friendship_friend_info_get_result_field_info": {
 *       "friend_profile_add_source": "AddSource_Type_contact",
 *       "friend_profile_add_time": 1620786162,
 *       "friend_profile_add_wording": "work together",
 *       "friend_profile_custom_string_array": [{
 *           "friend_profile_custom_string_info_key": "Tag_Profile_Custom_Str",
 *           "friend_profile_custom_string_info_value": "test3-lamar-value"
 *       }],
 *       "friend_profile_group_name_array": ["friend1"],
 *       "friend_profile_identifier": "98826",
 *       "friend_profile_remark": "shoujihao",
 *       "friend_profile_user_profile": {
 *           "user_profile_add_permission": 1,
 *           "user_profile_birthday": 2000,
 *           "user_profile_custom_string_array": [{
 *               "user_profile_custom_string_info_key": "Tag_Profile_Custom_Str",
 *               "user_profile_custom_string_info_value": "test3-lamar-value"
 *           }],
 *           "user_profile_face_url": "test1-www.google.com",
 *           "user_profile_gender": 2,
 *           "user_profile_identifier": "98826",
 *           "user_profile_language": 1000,
 *           "user_profile_level": 3000,
 *           "user_profile_location": "shenzhen",
 *           "user_profile_nick_name": "test change8888",
 *           "user_profile_role": 4000,
 *           "user_profile_self_signature": "1111111"
 *       }
 *   },
 *   "friendship_friend_info_get_result_relation_type": 3,
 *   "friendship_friend_info_get_result_userid": "98826"
 * }]
 * @endcode
 */
TIM_API int TIMFriendshipGetFriendsInfo(const char *friend_id_list,  TIMCommCallback cb, const void* user_data);

/**
 * 4.3 修改好友资料(备注等)
 *
 * @param json_modify_friend_info_param 更新好友资料接口参数的 Json 字符串, Json Key 请参考 @ref FriendProfileCustomStringInfo
 * @param cb 更新好友资料成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 修改好友资料，目前支持修改的字段请参考 @ref FriendProfileItem, 一次可修改多个字段。修改自定义字段时填入的key值可以添加 Tag_SNS_Custom_ 前缀，也可以不添加 Tag_SNS_Custom_ 前缀，当不添加时，SDK 内部会自动添加该前缀。
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_modify_friend_profile_item;
 * json_modify_friend_profile_item[kTIMFriendProfileItemRemark] = "xxxx yyyy";  // 修改备注
 *
 * json::Array json_group_name_array;
 * json_group_name_array.push_back("group1");
 * json_group_name_array.push_back("group2");
 * json_modify_friend_profile_item[kTIMFriendProfileItemGroupNameArray] = json_group_name_array;  // 修改好友分组名称列表
 *
 * json::Object json_custom_object;
 * json_custom_object[kTIMFriendProfileCustomStringInfoKey] = "Str";  // 修改好友资料自定义字段 " Str " 的值
 * json_custom_object[kTIMFriendProfileCustomStringInfoValue] = "this is changed value";
 *
 * json::Array json_custom_array;
 * json_custom_array.push_back(json_custom_object);
 * json_modify_friend_profile_item[kTIMFriendProfileItemCustomStringArray] = json_custom_array;
 *
 * json::Object json_modify_friend_info_param;
 * json_modify_friend_info_param[kTIMFriendshipModifyFriendProfileParamIdentifier] = "user4";
 * json_modify_friend_info_param[kTIMFriendshipModifyFriendProfileParamItem] = json_modify_friend_profile_item;
 * int ret = TIMFriendshipModifyFriendProfile(json::Serialize(json_modify_friend_info_param).c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipModifyFriendProfile(const char* json_modify_friend_info_param, TIMCommCallback cb, const void* user_data);

/**
 * 4.4 搜索好友（5.4.666 及以上版本支持，需要您购买旗舰版套餐）
 *
 * @param json_search_friends_param 搜索好友的关键字和域, Json Key 请参考 @ref FriendSearchParam
 * @param cb 搜索好友的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *   json::Object json_obj;
 *
 *   json::Array json_keyword_list;
 *   Json_keyword_list.push_back("98826");
 *   json_obj[kTIMFriendshipSearchParamKeywordList] = json_keyword_list;
 *
 *   json::Array json_search_field_list;
 *   json_search_field_list.push_back(kTIMFriendshipSearchFieldKey_Identifier);
 *   json_obj[kTIMFriendshipSearchParamSearchFieldList] = json_search_field_list;
 *   TIMFriendshipSearchFriends(json_obj.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 *   }, nullptr);
 *
 *   json_obj.toStyledString().c_str() 得到 JSON 字符串如下:
 *   {
 *       "friendship_search_param_keyword_list": ["98826"],
 *       "friendship_search_param_search_field_list": [1]
 *   }
 * @endcode
 *
 * __回调的 json_param 示例 (Json Key 请参考 @ref FriendProfile)__
 * @code{.cpp}
 *  [
 *     {
 *         "friend_profile_add_source":"AddSource_Type_contact",
 *         "friend_profile_add_time":1620786162,
 *         "friend_profile_add_wording":"work together",
 *         "friend_profile_custom_string_array":[
 *             {
 *                 "friend_profile_custom_string_info_key":"Tag_Profile_Custom_Str",
 *                 "friend_profile_custom_string_info_value":"test3-lamar-value"
 *             }
 *         ],
 *         "friend_profile_group_name_array":[
 *             "friend1"
 *         ],
 *         "friend_profile_identifier":"98826",
 *         "friend_profile_remark":"shoujihao",
 *         "friend_profile_user_profile":{
 *             "user_profile_add_permission":1,
 *             "user_profile_birthday":2000,
 *             "user_profile_custom_string_array":[
 *                 {
 *                     "user_profile_custom_string_info_key":"Tag_Profile_Custom_Str",
 *                     "user_profile_custom_string_info_value":"test3-lamar-value"
 *                 }
 *             ],
 *             "user_profile_face_url":"test1-www.google.com",
 *             "user_profile_gender":2,
 *             "user_profile_identifier":"98826",
 *             "user_profile_language":1000,
 *             "user_profile_level":3000,
 *             "user_profile_location":"深圳",
 *             "user_profile_nick_name":"test change8888",
 *             "user_profile_role":4000,
 *             "user_profile_self_signature":"1111111"
 *         }
 *     }
 *  ]
 * @endcode
 */
TIM_API int TIMFriendshipSearchFriends(const char *json_search_friends_param, TIMCommCallback cb, const void* user_data);

/**
 * 4.5 添加好友
 *
 * @param json_add_friend_param 添加好友接口参数的 Json 字符串, Json Key 请参考 @ref FriendshipAddFriendParam
 * @param cb 添加好友成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 好友关系有单向和双向好友之分。详情请参考[添加好友](https://cloud.tencent.com/document/product/269/1501#.E6.B7.BB.E5.8A.A0.E5.A5.BD.E5.8F.8B).
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_add_friend_param;
 * json_add_friend_param[kTIMFriendshipAddFriendParamIdentifier] = "user4";
 * json_add_friend_param[kTIMFriendshipAddFriendParamFriendType] = FriendTypeBoth;
 * json_add_friend_param[kTIMFriendshipAddFriendParamAddSource] = "Windows";
 * json_add_friend_param[kTIMFriendshipAddFriendParamAddWording] = "I am Iron Man";
 * int ret = TIMFriendshipAddFriend(json_add_friend_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 添加好友失败
 *         return;
 *     }
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipAddFriend(const char* json_add_friend_param, TIMCommCallback cb, const void* user_data);

/**
 * 4.6 删除好友
 *
 * @param json_delete_friend_param 删除好友接口参数的 Json 字符串, Json Key 请参考 @ref FriendshipDeleteFriendParam
 * @param cb 删除好友成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 删除好友也有删除单向好友还是双向好友之分，[删除好友](https://cloud.tencent.com/document/product/269/1501#.E5.88.A0.E9.99.A4.E5.A5.BD.E5.8F.8B).
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_delete_friend_param;
 * json_delete_friend_param[kTIMFriendshipDeleteFriendParamFriendType] = FriendTypeSingle;
 *
 * json::Array json_friend_array;
 * json_friend_array.push_back("user4");
 * json_delete_friend_param[kTIMFriendshipDeleteFriendParamIdentifierArray] = json_friend_array;
 * int ret = TIMFriendshipDeleteFriend(json_delete_friend_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *     if (ERR_SUCC != code) {
 *         // 删除好友失败
 *         return;
 *     }
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipDeleteFriend(const char* json_delete_friend_param, TIMCommCallback cb, const void* user_data);

/**
 * 4.7 检测好友类型(单向或双向)
 *
 * @param json_check_friend_list_param 检测好友接口参数的 Json 字符串, Json Key 请参考 @ref FriendshipCheckFriendTypeParam
 * @param cb 检测好友成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 开发者可以通过此接口检测给定的 UserID 列表跟当前账户的好友关系，检测好友相关内容请参考 [检测好友](https://cloud.tencent.com/document/product/269/1501#.E6.A0.A1.E9.AA.8C.E5.A5.BD.E5.8F.8B)。
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_check_friend_list_param;
 * json_check_friend_list_param[kTIMFriendshipCheckFriendTypeParamCheckType] = FriendTypeBoth;
 *
 * json::Array json_friend_array;
 * json_friend_array.push_back("user4");
 * json_check_friend_list_param[kTIMFriendshipCheckFriendTypeParamIdentifierArray] = json_friend_array;
 * int ret = TIMFriendshipCheckFriendType(json_check_friend_list_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipCheckFriendType(const char* json_check_friend_list_param, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                          五. 好友申请、删除相关接口
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 5.1 获取好友添加请求未决信息列表
 *
 * @param json_get_pendency_list_param 获取未决列表接口参数的 Json 字符串, Json Key 请参考 @ref FriendshipGetPendencyListParam
 * @param cb 获取未决列表成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 好友添加请求未决信息是指好友添加请求未处理的操作。例如，开发者添加对方为好友，对方还没有处理；或者有人添加开发者为好友，开发者还没有处理，称之为好友添加请求未决信息
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_get_pendency_list_param;
 * json_get_pendency_list_param[kTIMFriendshipGetPendencyListParamType] = FriendPendencyTypeBoth;
 * json_get_pendency_list_param[kTIMFriendshipGetPendencyListParamStartSeq] = 0;
 * int ret = TIMFriendshipGetPendencyList(json_get_pendency_list_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipGetPendencyList(const char* json_get_pendency_list_param, TIMCommCallback cb, const void* user_data);

/**
 * 5.2 处理好友请求
 *
 * @param json_handle_friend_add_param 处理好友请求接口参数的 Json 字符串, Json Key 请参考 @ref FriendResponse
 * @param cb 处理好友请求成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 当自己的个人资料的加好友权限 kTIMUserProfileAddPermission 设置为 kTIMProfileAddPermission_NeedConfirm 时，别人添加自己为好友时会收到一个加好友的请求，可通过此接口处理加好友的请求。
 *
 * __示例__
 * @code{.cpp}
 * Json::Value json_handle_friend_add_param;
 * json_handle_friend_add_param[kTIMFriendResponseIdentifier] = "user1";
 * json_handle_friend_add_param[kTIMFriendResponseAction] = ResponseActionAgreeAndAdd;
 * json_handle_friend_add_param[kTIMFriendResponseRemark] = "I am Captain China";
 * json_handle_friend_add_param[kTIMFriendResponseGroupName] = "schoolmate";
 * int ret = TIMFriendshipHandleFriendAddRequest(json_handle_friend_add_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipHandleFriendAddRequest(const char* json_handle_friend_add_param, TIMCommCallback cb, const void* user_data);

/**
 * 5.3 上报好友添加请求未决信息已读
 *
 * @param time_stamp 上报未决信息已读时间戳(单位秒)，填 0 默认会获取当前的时间戳
 * @param cb 上报未决信息已读用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 *  TIMFriendshipReportPendencyReaded(0, [](int32_t code, const char* desc, const char* json_param, const void* user_data) {
 *
 *  }, nullptr);
 *
 *  json_param 为空字符串，判断 code 确认结果即可
 * @endcode
 */
TIM_API int TIMFriendshipReportPendencyReaded(uint64_t time_stamp, TIMCommCallback cb, const void* user_data);

/**
 * 5.4 删除指定好友添加请求未决信息
 *
 * @param json_delete_pendency_param 删除指定未决信息接口参数的 Json 字符串, Json Key 请参考 @ref FriendshipDeletePendencyParam
 * @param cb 删除指定未决信息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_delete_pendency_param;
 * json_delete_pendency_param[kTIMFriendshipDeletePendencyParamType] = FriendPendencyTypeComeIn;
 *
 * json::Array json_application_array;
 * json_application_array.push_back("user1");
 * json_delete_pendency_param[kTIMFriendshipDeletePendencyParamIdentifierArray] = json_application_array;
 * int ret = TIMFriendshipDeletePendency(json_delete_pendency_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipDeletePendency(const char* json_delete_pendency_param, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                           六. 黑名单相关接口
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 6.1 获取黑名单列表
 *
 * @param cb 获取黑名单列表成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 */
TIM_API int TIMFriendshipGetBlackList(TIMCommCallback cb, const void* user_data);

/**
 * 6.2 添加指定用户到黑名单
 *
 * @param json_add_to_blacklist_param 添加指定用户到黑名单接口参数的 Json 字符串
 * @param cb 添加指定用户到黑名单成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_add_to_blacklist_param;
 * json_add_to_blacklist_param.push_back("user5");
 * json_add_to_blacklist_param.push_back("user10");
 * int ret = TIMFriendshipAddToBlackList(json_add_to_blacklist_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipAddToBlackList(const char* json_add_to_blacklist_param, TIMCommCallback cb, const void* user_data);

/**
 * 6.3 从黑名单中删除指定用户列表
 *
 * @param json_delete_from_blacklist_param 从黑名单中删除指定用户接口参数的 Json 字符串
 * @param cb 从黑名单中删除指定用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_delete_from_blacklist_param;
 * json_delete_from_blacklist_param.push_back("user5");
 * json_delete_from_blacklist_param.push_back("user10");
 * int ret = TIMFriendshipDeleteFromBlackList(json_delete_from_blacklist_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipDeleteFromBlackList(const char* json_delete_from_blacklist_param, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                            七. 好友分组相关接口
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 7.1 创建好友分组
 *
 * @param json_create_friend_group_param 创建好友分组接口参数的 Json 字符串, Json Key 请参考 @ref CreateFriendGroupParam
 * @param cb 创建好友分组成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * @note
 * 不能创建已存在的分组
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_group_name_array;
 * json_group_name_array.push_back("Group123");
 *
 * json::Array json_friend_array;
 * json_friend_array.push_back("user3");
 * json_friend_array.push_back("user4");
 *
 * json::Object json_create_friend_group_param;
 * json_create_friend_group_param[kTIMFriendshipCreateFriendGroupParamNameArray] = json_group_name_array;
 * json_create_friend_group_param[kTIMFriendshipCreateFriendGroupParamIdentifierArray] = json_friend_array;
 * int ret = TIMFriendshipCreateFriendGroup(json_create_friend_group_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipCreateFriendGroup(const char* json_create_friend_group_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.2 获取指定好友分组的分组信息
 *
 * @param json_get_friend_group_list_param 获取好友分组信息接口参数的 Json 字符串
 * @param cb 获取好友分组信息成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_get_friend_group_list_param;
 * json_get_friend_group_list_param.push_back("Group123");
 * int ret = TIMFriendshipGetFriendGroupList(json_get_friend_group_list_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipGetFriendGroupList(const char* json_get_friend_group_list_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.3 删除好友分组
 *
 * @param json_delete_friend_group_param 删除好友分组接口参数的 Json 字符串
 * @param cb 删除好友分组成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * json::Array json_delete_friend_group_param;
 * json_delete_friend_group_param.push_back("GroupNewName");
 * int ret = TIMFriendshipDeleteFriendGroup(json_delete_friend_group_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipDeleteFriendGroup(const char* json_delete_friend_group_param, TIMCommCallback cb, const void* user_data);

/**
 * 7.4 修改好友分组
 *
 * @param json_modify_friend_group_param 修改好友分组接口参数的 Json 字符串, Json Key 请参考 @ref FriendshipModifyFriendGroupParam
 * @param cb 修改好友分组成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __示例__
 * @code{.cpp}
 * json::Object json_modify_friend_group_param;
 * json_modify_friend_group_param[kTIMFriendshipModifyFriendGroupParamName] = "Group123";
 * json_modify_friend_group_param[kTIMFriendshipModifyFriendGroupParamNewName] = "GroupNewName";
 *
 * json::Array json_friend_delete_array;
 * json_friend_delete_array.push_back("user4");
 * json_modify_friend_group_param[kTIMFriendshipModifyFriendGroupParamDeleteIdentifierArray] = json_friend_delete_array;
 *
 * json::Array json_friend_add_array;
 * json_friend_add_array.push_back("user5");
 * json_friend_add_array.push_back("user9");
 * json_modify_friend_group_param[kTIMFriendshipModifyFriendGroupParamAddIdentifierArray] = json_friend_add_array;
 * int ret = TIMFriendshipModifyFriendGroup(json_modify_friend_group_param.toStyledString().c_str(), [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *
 * }, nullptr);
 * @endcode
 */
TIM_API int TIMFriendshipModifyFriendGroup(const char* json_modify_friend_group_param, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                           八. 公众号相关接口
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 8.1 订阅公众号（7.6 及其以上版本支持）
 *
 * @param official_account_id 公众号 ID
 * @param cb 订阅公众号成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 */
TIM_API int TIMSubscribeOfficialAccount(const char* official_account_id, TIMCommCallback cb, const void* user_data);

/**
 * 8.2 取消订阅公众号（7.6 及其以上版本支持）
 *
 * @param unsubscribe_official_account_id 公众号 ID
 * @param cb 取消订阅公众号成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 */
TIM_API int TIMUnsubscribeOfficialAccount(const char* unsubscribe_official_account_id, TIMCommCallback cb, const void* user_data);

/**
 * 8.3 获取公众号列表（7.6 及其以上版本支持）
 *
 * @param json_get_official_accounts_info_param 获取公众号列表的参数Json字符串
 * @param cb 获取公众号列表成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 */
TIM_API int TIMGetOfficialAccountsInfo(const char* json_get_official_accounts_info_param, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                           九. 关注/粉丝功能相关接口
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 9.1 关注用户 (7.8 及其以上版本支持，需要您购买旗舰版套餐)
 *
 * @param json_user_id_list 待关注的用户 ID 列表
 * @param cb 关注用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __回调中返回的 json_params 示例 (Json Key 请参考 @ref FollowOperationResult)__
 * @code{.json}
 * [
 *     {
 *         "follow_operation_result_Info":"",
 *         "follow_operation_result_code":0,
 *         "follow_operation_result_user_id":"user1"
 *     },
 *     {
 *         "follow_operation_result_Info":"",
 *         "follow_operation_result_code":0,
 *         "follow_operation_result_user_id":"user2"
 *     }
 * ]
 * @endcode
 */
TIM_API int TIMFollowUser(const char* json_user_id_list, TIMCommCallback cb, const void* user_data);

/**
 * 9.2 取消关注用户 (7.8 及其以上版本支持，需要您购买旗舰版套餐)
 *
 * @param json_user_id_list 待取消关注的用户 ID 列表
 * @param cb 取消关注用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __回调中返回的 json_params 示例 (Json Key 请参考 @ref FollowOperationResult)__
 * @code{.json}
 * [
 *     {
 *         "follow_operation_result_Info":"",
 *         "follow_operation_result_code":0,
 *         "follow_operation_result_user_id":"user1"
 *     },
 *     {
 *         "follow_operation_result_Info":"",
 *         "follow_operation_result_code":0,
 *         "follow_operation_result_user_id":"user2"
 *     }
 * ]
 * @endcode
 */
TIM_API int TIMUnfollowUser(const char* json_user_id_list, TIMCommCallback cb, const void* user_data);

/**
 * 9.3 获取我的关注列表 (7.8 及其以上版本支持，需要您购买旗舰版套餐)
 *
 * @param next_cursor 分页拉取标志，第一次拉取填 NULL 或者 ""，回调中返回的 next_cursor 不为 ""，则需要分页，可以传入该值再次拉取，直至返回为 ""
 * @param cb 取消关注用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __回调中返回的 json_params 示例 (Json Key 请参考 @ref FollowListResult)__
 * @code{.json}
 * {
 *     "follow_list_result_next_cursor":"",  // 分页拉取的标志
 *     "follow_list_result_user_info_list":[
 *         Object{...},  // 用户资料信息
 *         Object{...}   // 用户资料信息
 *     ]
 * }
 * @endcode
 */
TIM_API int TIMGetMyFollowingList(const char* next_cursor, TIMCommCallback cb, const void* user_data);

/**
 * 9.4 获取我的粉丝列表 (7.8 及其以上版本支持，需要您购买旗舰版套餐)
 *
 * @param next_cursor 分页拉取标志，第一次拉取填 NULL 或者 ""，回调中返回的 next_cursor 不为 ""，则需要分页，可以传入该值再次拉取，直至返回为 ""
 * @param cb 取消关注用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 *
 * __回调中返回的 json_params 示例 (Json Key 请参考 @ref FollowListResult)__
 * @code{.json}
 * {
 *     "follow_list_result_next_cursor":"",  // 分页拉取的标志
 *     "follow_list_result_user_info_list":[
 *         Object{...},  // 用户资料信息
 *         Object{...}   // 用户资料信息
 *     ]
 * }
 * @endcode
 */
TIM_API int TIMGetMyFollowersList(const char* next_cursor, TIMCommCallback cb, const void* user_data);

/**
 * 9.5 获取我的互关列表 (7.8 及其以上版本支持，需要您购买旗舰版套餐)
 *
 * @param next_cursor 分页拉取标志，第一次拉取填 NULL 或者 ""，回调中返回的 next_cursor 不为 ""，则需要分页，可以传入该值再次拉取，直至返回为 ""
 * @param cb 取消关注用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __回调中返回的 json_params 示例 (Json Key 请参考 @ref FollowListResult)__
 * @code{.json}
 * {
 *     "follow_list_result_next_cursor":"",  // 分页拉取的标志
 *     "follow_list_result_user_info_list":[
 *         Object{...},  // 用户资料信息
 *         Object{...}   // 用户资料信息
 *     ]
 * }
 * @endcode
 */
TIM_API int TIMGetMutualFollowersList(const char* next_cursor, TIMCommCallback cb, const void* user_data);

/**
 * 9.6 获取指定用户的 关注/粉丝/互关 数量信息 (7.8 及其以上版本支持，需要您购买旗舰版套餐)
 *
 * @param json_user_id_list 用户 ID 列表
 * @param cb 取消关注用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __回调中返回的 json_params 示例 (Json Key 请参考 @ref FollowInfo)__
 * @code{.json}
 * [
 *     {
 *         "follow_info_followers_count":6,
 *         "follow_info_following_count":6,
 *         "follow_info_mutual_followers_count":2,
 *         "follow_info_result_code":0,
 *         "follow_info_result_info":"",
 *         "follow_info_user_id":"user1"
 *     }
 * ]
 * @endcode
 */
TIM_API int TIMGetUserFollowInfo(const char* json_user_id_list, TIMCommCallback cb, const void* user_data);

/**
 * 9.7 检查指定用户的关注类型 (7.8 及其以上版本支持，需要您购买旗舰版套餐)
 *
 * @param json_user_id_list 用户 ID 列表
 * @param cb 取消关注用户成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回 TIM_SUCC 表示接口调用成功（接口只有返回 TIM_SUCC，回调 cb 才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * __回调中返回的 json_params 示例 (Json Key 请参考 @ref FollowTypeCheckResult)__
 * @code{.json}
 * [
 *     {
 *         "follow_type_check_result_code":0,
 *         "follow_type_check_result_follow_type":1,
 *         "follow_type_check_result_info":"OK",
 *         "follow_type_check_result_user_id":"user1"
 *     }
 * ]
 * @endcode
 */
TIM_API int  TIMCheckFollowType(const char* json_user_id_list, TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                     十. 好友资料 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 10.1 FriendProfileCustomStringInfo (好友自定义资料字段)
// string, 只写, 好友自定义资料字段key，首先要在 [控制台](https://console.cloud.tencent.com/im) (功能配置 -> 好友自定义字段) 配置好友自定义字段，key 可以添加 Tag_SNS_Custom_ 前缀，也可以不添加 Tag_SNS_Custom_ 前缀。
static const char* kTIMFriendProfileCustomStringInfoKey = "friend_profile_custom_string_info_key";
// string, 只写, 好友自定义资料字段value
static const char* kTIMFriendProfileCustomStringInfoValue = "friend_profile_custom_string_info_value";

//------------------------------------------------------------------------------
// 10.2 FriendProfile (好友资料)
// string, 只读, 好友UserID
static const char* kTIMFriendProfileIdentifier = "friend_profile_identifier";
// array string, 只读, 好友分组名称列表
static const char* kTIMFriendProfileGroupNameArray = "friend_profile_group_name_array";
// string, 只读, 好友备注，最大96字节，获取自己资料时，该字段为空
static const char* kTIMFriendProfileRemark = "friend_profile_remark";
// string, 只读, 好友申请时的添加理由
static const char* kTIMFriendProfileAddWording = "friend_profile_add_wording";
// string, 只读, 好友申请时的添加来源
static const char* kTIMFriendProfileAddSource = "friend_profile_add_source";
// uint64, 只读, 添加好友的 UTC 时间戳
static const char* kTIMFriendProfileAddTime = "friend_profile_add_time";
// object @ref UserProfile, 只读, 好友的个人资料
static const char* kTIMFriendProfileUserProfile = "friend_profile_user_profile";
// array @ref FriendProfileCustomStringInfo, 只读, [自定义好友字段](https://cloud.tencent.com/document/product/269/1501#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.A5.BD.E5.8F.8B.E5.AD.97.E6.AE.B5)
static const char* kTIMFriendProfileCustomStringArray = "friend_profile_custom_string_array";

//------------------------------------------------------------------------------
// 10.3 FriendProfileItem (好友资料可修改的各个项)
// string, 只写, 修改好友备注
static const char* kTIMFriendProfileItemRemark = "friend_profile_item_remark";
// array string, 只写, 修改好友分组名称列表
static const char* kTIMFriendProfileItemGroupNameArray = "friend_profile_item_group_name_array";
// array @ref FriendProfileCustomStringInfo, 只写, 修改 [自定义好友字段](https://cloud.tencent.com/document/product/269/1501#.E8.87.AA.E5.AE.9A.E4.B9.89.E5.A5.BD.E5.8F.8B.E5.AD.97.E6.AE.B5)
static const char* kTIMFriendProfileItemCustomStringArray = "friend_profile_item_custom_string_array";

//------------------------------------------------------------------------------
// 10.4 FriendshipModifyFriendProfileParam (修改好友资料接口的参数)
// string, 只写, 被修改的好友的UserID
static const char* kTIMFriendshipModifyFriendProfileParamIdentifier = "friendship_modify_friend_profile_param_identifier";
// object @ref FriendProfileItem, 只写, 修改的好友资料各个选项
static const char* kTIMFriendshipModifyFriendProfileParamItem = "friendship_modify_friend_profile_param_item";

//------------------------------------------------------------------------------
// 10.5 FriendProfileUpdate (好友资料更新信息)
// string, 只写, 资料更新的好友的UserID
static const char* kTIMFriendProfileUpdateIdentifier = "friend_profile_update_identifier";
// object @ref FriendProfileItem, 只写, 资料更新的Item
static const char* kTIMFriendProfileUpdateItem = "friend_profile_update_item";

//------------------------------------------------------------------------------
// 10.6 FriendChangeElem (好友变更通知)
// uint @ref TIMFriendChangeType, 只读, 资料变更类型
static const char* kTIMFriendChangeElemChangeType = "friend_change_elem_change_type";
// array string, 只读, 新增的好友UserID列表，只有当 change_type 为 kTIMFriendChange_FriendAdd 时有效
static const char* kTIMFriendChangeElemFriendAddIdentifierArray = "friend_change_elem_friend_add_identifier_array";
// array string, 只读, 删除的好友UserID列表，只有当 change_type 为 kTIMFriendChange_FriendDel 时有效
static const char* kTIMFriendChangeElemFriendDelIdentifierArray = "friend_change_elem_friend_del_identifier_array";
// array @ref FriendAddPendency, 只读, 好友申请的未决列表， 只有当 change_type 为 kTIMFriendChange_PendencyAdd 时有效
static const char* kTIMFriendChangeElemFriendAddPendencyItemArray = "friend_change_elem_friend_add_pendency_array";
// array string, 只读, 被删除的好友申请的未决列表， 只有当 change_type 为 kTIMFriendChange_PendencyDel 时有效
static const char* kTIMFriendChangeElemPendencyDelIdentifierArray = "friend_change_elem_pendency_del_identifier_array";
// uint64, 只读, 未决已读上报时间戳， 只有当 change_type 为 kTIMFriendChange_PendencyReadedReport 时有效
static const char* kTIMFriendChangeElemPendencyReadedReportTimestamp = "friend_change_elem_pendency_readed_report_timestamp";
// array string, 只读, 新增的黑名单UserID列表，只有当 change_type 为 kTIMFriendChange_BlackListAdd 时有效
static const char* kTIMFriendChangeElemBlackListAddIdentifierArray = "friend_change_elem_blacklist_add_identifier_array";
// array string, 只读, 删除的黑名单UserID列表，只有当 change_type 为 kTIMFriendChange_BlackListDel 时有效
static const char* kTIMFriendChangeElemBlackListDelIdentifierArray = "friend_change_elem_blacklist_del_identifier_array";
// array @ref FriendProfileUpdate, 只读, 好友资料更新列表， 只有当 change_type 为 kTIMFriendChange_FriendProfileUpdate 时有效
static const char* kTIMFriendChangeElemFriendProfileUpdateItemArray = "friend_change_elem_friend_profile_update_item_array";
// array string, 只读, 新增的好友分组名称列表， 只有当 change_type 为 kTIMFriendChange_FriendGroupAdd 时有效
static const char* kTIMFriendChangeElemFriendGroupAddIdentifierArray = "friend_change_elem_friend_group_add_array";
// array string, 只读, 删除的好友分组名称列表， 只有当 change_type 为 kTIMFriendChange_FriendGroupDel 时有效
static const char* kTIMFriendChangeElemFriendGroupDelIdentifierArray = "friend_change_elem_friend_group_del_array";
// array string, 只读, 修改的好友分组名称列表， 只有当 change_type 为 kTIMFriendChange_FriendGroupModify 时有效
static const char* kTIMFriendChangeElemFriendGroupModifyIdentifierArray = "friend_change_elem_friend_group_update_array";


/////////////////////////////////////////////////////////////////////////////////
//
//                       十一. 好友申请 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 11.1 FriendshipAddFriendParam (添加好友接口的参数)
// string, 只写, 请求加好友对应的UserID
static const char* kTIMFriendshipAddFriendParamIdentifier = "friendship_add_friend_param_identifier";
// uint @ref TIMFriendType, 只写, 请求添加好友的好友类型
static const char* kTIMFriendshipAddFriendParamFriendType = "friendship_add_friend_param_friend_type";
// string, 只写, 预备注
static const char* kTIMFriendshipAddFriendParamRemark = "friendship_add_friend_param_remark";
// string, 只写, 预分组名
static const char* kTIMFriendshipAddFriendParamGroupName = "friendship_add_friend_param_group_name";
// string, 只写, 加好友来源描述
static const char* kTIMFriendshipAddFriendParamAddSource = "friendship_add_friend_param_add_source";
// string, 只写, 加好友附言
static const char* kTIMFriendshipAddFriendParamAddWording = "friendship_add_friend_param_add_wording";

//------------------------------------------------------------------------------
// 11.2 FriendshipDeleteFriendParam (删除好友接口的参数)
// uint @ref TIMFriendType, 只写, 删除好友，指定删除的好友类型
static const char* kTIMFriendshipDeleteFriendParamFriendType = "friendship_delete_friend_param_friend_type";
// array string, 只写(选填), 删除好友UserID列表
static const char* kTIMFriendshipDeleteFriendParamIdentifierArray = "friendship_delete_friend_param_identifier_array";

//------------------------------------------------------------------------------
// 11.3 FriendAddPendency (好友申请未决信息)
// string, 只读, 添加好友请求方的UserID
static const char* kTIMFriendAddPendencyIdentifier = "friend_add_pendency_identifier";
// string, 只读, 添加好友请求方的昵称
static const char* kTIMFriendAddPendencyNickName = "friend_add_pendency_nick_name";
// string, 只读, 添加好友请求方的来源
static const char* kTIMFriendAddPendencyAddSource = "friend_add_pendency_add_source";
// string, 只读, 添加好友请求方的附言
static const char* kTIMFriendAddPendencyAddWording = "friend_add_pendency_add_wording";

//------------------------------------------------------------------------------
// 11.4 FriendshipGetPendencyListParam (分页获取好友申请未决信息列表的参数)
// uint @ref TIMFriendPendencyType, 只写, 添加好友的未决请求类型
static const char* kTIMFriendshipGetPendencyListParamType = "friendship_get_pendency_list_param_type";
// uint64, 只写, 分页获取未决请求的起始 seq，返回的结果包含最大 seq，作为获取下一页的起始 seq
static const char* kTIMFriendshipGetPendencyListParamStartSeq = "friendship_get_pendency_list_param_start_seq";
// uint64, 只写, 获取未决信息的开始时间戳
static const char* kTIMFriendshipGetPendencyListParamStartTime = "friendship_get_pendency_list_param_start_time";
// int, 只写, 获取未决信息列表，每页的数量
static const char* kTIMFriendshipGetPendencyListParamLimitedSize = "friendship_get_pendency_list_param_limited_size";

//------------------------------------------------------------------------------
// 11.5 PendencyPage (好友申请未决信息页)
// uint64, 只读, 未决请求信息页的起始时间
static const char* kTIMPendencyPageStartTime = "pendency_page_start_time";
// uint64, 只读, 未决请求信息页的未读数量
static const char* kTIMPendencyPageUnReadNum = "pendency_page_unread_num";
// uint64, 只读, 未决请求信息页的当前Seq
static const char* kTIMPendencyPageCurrentSeq = "pendency_page_current_seq";
// array @ref FriendAddPendencyInfo, 只读, 未决请求信息页的未决信息列表
static const char* kTIMPendencyPagePendencyInfoArray = "pendency_page_pendency_info_array";

//------------------------------------------------------------------------------
// 11.6 FriendAddPendencyInfo (好友申请未决信息)
// uint @ref TIMFriendPendencyType, 只读, 好友添加请求未决类型
static const char* kTIMFriendAddPendencyInfoType = "friend_add_pendency_info_type";
// string, 只读, 好友添加请求未决的 UserID
static const char* kTIMFriendAddPendencyInfoIdentifier = "friend_add_pendency_info_identifier";
// string, 只读, 好友添加请求未决的昵称
static const char* kTIMFriendAddPendencyInfoNickName = "friend_add_pendency_info_nick_name";
// string, 只读, 好友添加请求未决的头像
static const char* kTIMFriendAddPendencyInfoFaceUrl = "friend_add_pendency_info_face_url";
// uint64, 只读, 发起好友申请的时间
static const char* kTIMFriendAddPendencyInfoAddTime = "friend_add_pendency_info_add_time";
// string, 只读, 好友添加请求未决的添加来源
static const char* kTIMFriendAddPendencyInfoAddSource = "friend_add_pendency_info_add_source";
// string, 只读, 好友添加请求未决的添加附言
static const char* kTIMFriendAddPendencyInfoAddWording = "friend_add_pendency_info_add_wording";

//------------------------------------------------------------------------------
// 11.7 FriendResponse (处理好友申请未决信息接口的参数)
// string, 只写(必填), 响应好友添加的UserID
static const char* kTIMFriendResponseIdentifier = "friend_response_identifier";
// uint @ref TIMFriendResponseAction, 只写(必填), 响应好友添加的动作
static const char* kTIMFriendResponseAction = "friend_response_action";
// string, 只写(选填), 好友备注
static const char* kTIMFriendResponseRemark = "friend_response_remark";
// string, 只写(选填), 好友分组列表
static const char* kTIMFriendResponseGroupName = "friend_response_group_name";

//------------------------------------------------------------------------------
// 11.8 FriendshipDeletePendencyParam (删除好友申请未决信息接口的参数)
// uint @ref TIMFriendPendencyType, 只读, 添加好友的未决请求类型
static const char* kTIMFriendshipDeletePendencyParamType = "friendship_delete_pendency_param_type";
// array string, 只读, 删除好友未决请求的 UserID 列表
static const char* kTIMFriendshipDeletePendencyParamIdentifierArray = "friendship_delete_pendency_param_identifier_array";


/////////////////////////////////////////////////////////////////////////////////
//
//                         十二. 检查好友关系 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 12.1 FriendshipCheckFriendTypeParam (检测好友的类型接口的参数)
// uint @ref TIMFriendType, 只写, 要检测的好友类型
static const char* kTIMFriendshipCheckFriendTypeParamCheckType = "friendship_check_friendtype_param_check_type";
// array string, 只写, 要检测的好友UserID列表
static const char* kTIMFriendshipCheckFriendTypeParamIdentifierArray = "friendship_check_friendtype_param_identifier_array";

//------------------------------------------------------------------------------
// 12.2 FriendshipCheckFriendTypeResult (检测好友的类型接口返回)
// string, 只读, 被检测的好友UserID
static const char* kTIMFriendshipCheckFriendTypeResultIdentifier = "friendship_check_friendtype_result_identifier";
// uint @ref TIMFriendCheckRelation, 只读, 检测成功时返回的好友的类型
static const char* kTIMFriendshipCheckFriendTypeResultRelation = "friendship_check_friendtype_result_relation";
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 检测的结果
static const char* kTIMFriendshipCheckFriendTypeResultCode = "friendship_check_friendtype_result_code";
// string, 只读, 检测好友失败的描述信息
static const char* kTIMFriendshipCheckFriendTypeResultDesc = "friendship_check_friendtype_result_desc";


/////////////////////////////////////////////////////////////////////////////////
//
//           十三. 好友操作（添加、删除、加黑名单等） API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 13.1 FriendResult (关系链操作接口的返回结果)
// string, 只读, 关系链操作的用户ID
static const char* kTIMFriendResultIdentifier = "friend_result_identifier";
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 关系链操作的结果
static const char* kTIMFriendResultCode = "friend_result_code";
// string, 只读, 关系链操作失败的详细描述
static const char* kTIMFriendResultDesc = "friend_result_desc";


/////////////////////////////////////////////////////////////////////////////////
//
//                      十四. 好友分组 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 14.1 CreateFriendGroupParam (创建好友分组接口参数)
// array string, 只写, 创建分组的名称列表
static const char* kTIMFriendshipCreateFriendGroupParamNameArray = "friendship_create_friend_group_param_name_array";
// array string, 只写, 要放到创建的分组的好友UserID列表
static const char* kTIMFriendshipCreateFriendGroupParamIdentifierArray = "friendship_create_friend_group_param_identifier_array";

//------------------------------------------------------------------------------
// 14.2 FriendGroupInfo (好友分组信息)
// string, 只读, 分组名称
static const char* kTIMFriendGroupInfoName = "friend_group_info_name";
// uint64, 只读, 当前分组的好友个数
static const char* kTIMFriendGroupInfoCount = "friend_group_info_count";
// array string, 只读, 当前分组内好友UserID列表
static const char* kTIMFriendGroupInfoIdentifierArray = "friend_group_info_identifier_array";

//------------------------------------------------------------------------------
// 14.3 FriendshipModifyFriendGroupParam (修改好友分组信息的接口参数)
// string, 只写, 要修改的分组名称
static const char* kTIMFriendshipModifyFriendGroupParamName = "friendship_modify_friend_group_param_name";
// string, 只写(选填), 修改后的分组名称
static const char* kTIMFriendshipModifyFriendGroupParamNewName = "friendship_modify_friend_group_param_new_name";
// array string, 只写(选填), 要从当前分组删除的好友UserID列表
static const char* kTIMFriendshipModifyFriendGroupParamDeleteIdentifierArray = "friendship_modify_friend_group_param_delete_identifier_array";
// array string, 只写(选填), 当前分组要新增的好友UserID列表
static const char* kTIMFriendshipModifyFriendGroupParamAddIdentifierArray = "friendship_modify_friend_group_param_add_identifier_array";


/////////////////////////////////////////////////////////////////////////////////
//
//                      十五. 好友搜索 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 15.1 FriendSearchParam (搜索好友的参数)
// array string, 只写, 搜索的关键字列表，关键字列表最多支持 5 个
static const char* kTIMFriendshipSearchParamKeywordList = "friendship_search_param_keyword_list";
// array uint @ref TIMFriendshipSearchFieldKey, 只写, 好友搜索类型
static const char* kTIMFriendshipSearchParamSearchFieldList = "friendship_search_param_search_field_list";

//------------------------------------------------------------------------------
// 15.2 FriendInfoGetResult (搜索好友结果)
// string, 只读, 好友 user_id
static const char* kTIMFriendshipFriendInfoGetResultIdentifier = "friendship_friend_info_get_result_identifier";
// uint @ref TIMFriendshipRelationType, 只读， 好友关系
static const char* kTIMFriendshipFriendInfoGetResultRelationType = "friendship_friend_info_get_result_relation_type";
// uint, 只读, 错误码
static const char* kTIMFriendshipFriendInfoGetResultErrorCode = "friendship_friend_info_get_result_error_code";
// string, 只读, 错误描述
static const char* kTIMFriendshipFriendInfoGetResultErrorMessage = "friendship_friend_info_get_result_error_message";
// array uint @ref FriendProfile, 只读, 好友资料
static const char* kTIMFriendshipFriendInfoGetResultFriendInfo = "friendship_friend_info_get_result_field_info";


/////////////////////////////////////////////////////////////////////////////////
//
//                     十六. 公众号管理 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 16.1 OfficialAccountInfo(公众号信息)
// string, 只读, 公众号 ID
static const char* kTIMOfficialAccountID = "official_account_id";
// string, 只读, 公众号名称
static const char* kTIMOfficialAccountName = "official_account_name";
// string, 只读, 公众号头像 URL
static const char* kTIMOfficialAccountFaceUrl = "official_account_face_url";
// string, 只读, 公众号所有者
static const char* kTIMOfficialAccountOwnerUserID = "official_account_owner_user_id";
// string, 只读, 公众号介绍
static const char* kTIMOfficialAccountIntroduction = "official_account_introduction";
// string, 只读, 公众号组织
static const char* kTIMOfficialAccountOrganization = "official_account_organization";
// uint64, 只读, 公众号创建时间，单位：秒
static const char* kTIMOfficialAccountCreateTime = "official_account_create_time";
// uint64, 只读, 公众号订阅者数量
static const char* kTIMOfficialAccountSubscriberCount = "official_account_subscriber_count";
// uint64, 只读, 公众号订阅时间，单位：秒
static const char* kTIMOfficialAccountSubscribeTime = "official_account_subscribe_time";
// string, 只读, 公众号自定义字段
static const char* kTIMOfficialAccountCustomData = "official_account_custom_data";

//------------------------------------------------------------------------------
// 16.2 GetOfficialAccountInfoResult(获取公众号信息列表接口的返回)
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 获取公众号详细资料的结果
static const char* kTIMGetOfficialAccountInfoResultCode = "get_official_accounts_info_result_code";
// string, 只读, 获取公众号详细资料失败的描述信息
static const char* kTIMGetOfficialAccountInfoResultDesc = "get_official_accounts_info_result_desc";
// object @ref OfficialAccountInfo, 只读, 公众号详细信息
static const char* kTIMGetOfficialAccountInfo = "get_official_accounts_info";


/////////////////////////////////////////////////////////////////////////////////
//
//                  十七. 关注/粉丝 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 17.1 FollowOperationResult (关注/取关操作接口的返回结果)
// string, 只读, 关注/取关操作的用户 ID
static const char* kTIMFollowOperationResultUserID = "follow_operation_result_user_id";
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 关注/取关的操作返回码
static const char* kTIMFollowOperationResultCode = "follow_operation_result_code";
// string, 只读, 关注/取关操作的返回结果描述
static const char* kTIMFollowOperationResultInfo = "follow_operation_result_Info";

//------------------------------------------------------------------------------
// 17.2 FollowListResult (用户获取 关注/粉丝/互关 列表的结果)
// string, 只读, 下一次拉要取列表的起始位置
static const char* KTIMFollowListResultNextCursor = "follow_list_result_next_cursor";
// array @ref UserInfo, 只读, 用户资料列表
static const char* KTIMFollowListResultUerInfoList = "follow_list_result_user_info_list";

//------------------------------------------------------------------------------
// 17.3 FollowInfo (用户关注信息)
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 获取用户关注数量信息的返回码
static const char* kTIMFollowInfoResultCode = "follow_info_result_code";
// string, 只读, 获取用户关注数量信息的返回结果描述
static const char* kTIMFollowInfoResultInfo = "follow_info_result_info";
// string, 只读, 用户 ID
static const char* kTIMFollowInfoUserID = "follow_info_user_id";
// uint64, 只读, 用户的关注数量
static const char* kTIMFollowInfoFollowingCount = "follow_info_following_count";
// uint64, 只读, 用户的粉丝数量
static const char* kTIMFollowInfoFollowersCount = "follow_info_followers_count";
// uint64, 只读, 用户的互关数量
static const char* kTIMFollowInfoMutualFollowersCount = "follow_info_mutual_followers_count";

//------------------------------------------------------------------------------
// 17.4 FollowTypeCheckResult (指定用户关注类型的检查结果)
// string, 只读, 用户 ID
static const char* kTIMFollowTypeCheckResultUserID = "follow_type_check_result_user_id";
// int [错误码](https://cloud.tencent.com/document/product/269/1671), 只读, 关注类型的检查的返回码
static const char* kTIMFollowTypeCheckResultCode = "follow_type_check_result_code";
// string, 只读, 关注类型的检查的返回结果描述
static const char* kTIMFollowTypeCheckResultInfo = "follow_type_check_result_info";
// uint @ref TIMFollowType, 只读, 关注类型
static const char* kTIMFollowTypeCheckResultFollowType = "follow_type_check_result_follow_type";


/////////////////////////////////////////////////////////////////////////////////
//
//                              十八. 废弃字段
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 18.1以下为老版本拼写错误，为了兼容老版本而保留的宏定义
// enum TIMFriendType
#define FriendTypeSignle  FriendTypeSingle
// enum TIMFriendshipSearchFieldKey
#define kTIMFriendshipSearchFieldKey_NikeName  kTIMFriendshipSearchFieldKey_NickName
// FriendChangeElem JsonKey
#define kTIMFriendChangeElemFreindProfileUpdateItemArray  kTIMFriendChangeElemFriendProfileUpdateItemArray
// FriendProfileCustomStringInfo JsonKey
#define kTIMFriendProfileCustemStringInfoKey    kTIMFriendProfileCustomStringInfoKey
#define kTIMFriendProfileCustemStringInfoValue  kTIMFriendProfileCustomStringInfoValue
// FriendResponse JsonKey
#define kTIMFriendResponeIdentifier  kTIMFriendResponseIdentifier
#define kTIMFriendResponeAction      kTIMFriendResponseAction
#define kTIMFriendResponeRemark      kTIMFriendResponseRemark
#define kTIMFriendResponeGroupName   kTIMFriendResponseGroupName

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_FRIENDSHIP_MANAGER_H_
