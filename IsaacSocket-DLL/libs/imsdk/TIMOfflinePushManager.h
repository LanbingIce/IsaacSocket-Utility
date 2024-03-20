// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_OFFLINE_PUSH_MANAGER_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_OFFLINE_PUSH_MANAGER_H_

#include "TIMCloudDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// 模块简介
// *  -离线推送接口，用于支持离线推送功能
//
// 模块参数说明
// *  -API 的参数采用 json 字符串格式，请使用文件中预先定义的 JsonKey 进行参数传递和解析
// *  -如果参数中包含非英文字符，请使用 UTF-8 编码
//
// 模块回调说明
//  1. 回调的类型：
// *  -调用 API 时传入的 TIMCommCallback 回调，用于异步返回 API 的调用结果
// *  -调用 TIMSetXXXCallback 设置的全局回调，用于接收后台推送的通知
//  2. 回调触发的线程：
// *  -对于 Windows 平台，当在主线程中调用 @ref TIMInit 接口时，SDK 会将所有回调抛到主线程，请确保主线程已创建消息循环；否则，回调将在 SDK 内部的逻辑线程触发
// *  -对于 Android 平台，当调用 @ref TIMInit 接口的线程支持消息循环时，SDK 会将所有回调抛到该线程；否则，回调将在 SDK 内部的逻辑线程触发
// *  -对于 iOS 和 MAC 平台，SDK 默认将所有回调抛到主线程
// *  -对于 Linux 平台，暂不支持将回调抛到主线程，回调将在 SDK 内部的逻辑线程触发


/////////////////////////////////////////////////////////////////////////////////
//
//                      一. 离线推送相关配置选项定义
//
/////////////////////////////////////////////////////////////////////////////////
// 1.1 离线推送注册的 token 类型
enum TIMOfflinePushTokenType {
    // 默认厂商 token, 例如 APNS/小米 push/Huawei push 等
    TIMOfflinePushTokenType_Default = 0,
    // TPNS
    TIMOfflinePushTokenType_TPNS = 1,
    // VoIP push
    TIMOfflinePushTokenType_VOIP = 2,
};

// 1.2 iOS 离线推送的类型
enum TIMIOSOfflinePushType {
    // 普通的 APNs 推送
    TIMIOSOfflinePushType_APNS = 0,
    // VoIP 推送
    TIMIOSOfflinePushType_VOIP = 1,
};

// 1.3 Android 离线推送模式
enum TIMAndroidOfflinePushNotifyMode {
    // 普通通知栏消息模式，离线消息下发后，点击通知栏消息直接启动应用，不会给应用进行回调
    kTIMAndroidOfflinePushNotifyMode_Normal,
    // 自定义消息模式，离线消息下发后，点击通知栏消息会给应用进行回调
    kTIMAndroidOfflinePushNotifyMode_Custom,
};

// 1.4 推送规则
enum TIMOfflinePushFlag {
    // 按照默认规则进行推送
    kTIMOfflinePushFlag_Default,
    // 不进行推送
    kTIMOfflinePushFlag_NoPush,
};

/////////////////////////////////////////////////////////////////////////////////
//
//                             二. 离线推送相关 API
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 2.1 设置离线推送配置信息（iOS 和 Android 平台专用）
 *
 * @param json_token 离线推送配置 Json 字符串, Json Key 请参考 @ref OfflinePushToken。注意 kTIMOfflinePushTokenToken 字段要填写为设备 Token 的 hex 字符串（即 base16 编码）。
 * @param cb 成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 *  - 接口成功设置后会开启离线推送功能，如果您需要自定义推送的格式信息，请参考 @ref TIMMsgSendMessage 接口。
 *  - 如果您想关闭离线推送，请把 json_token 设置为 NULL。
 * 
 * __示例__
 * @code{.cpp}
 *   Json::Value json_parameters;
 *   json_parameters[kTIMOfflinePushTokenToken] = "token base16 string";
 *   json_parameters[kTIMOfflinePushTokenBusinessID] = 1234578;
 *   json_parameters[kTIMOfflinePushTokenType] = 0;
 *   TIMMsgSetOfflinePushToken(json_parameters.toStyledString().c_str(),
 *       [](int32_t code, const char* desc, const char* json_params, const void* user_data) {
 *   }, nullptr);
 * @endcode
 */
TIM_API int TIMMsgSetOfflinePushToken(const char *json_token, TIMCommCallback cb, const void* user_data);

/**
 * 2.2 APP 检测到应用退后台时可以调用此接口，可以用作桌面应用角标的初始化未读数量（iOS 和 Android 平台专用）
 *
 * @param unread_count 未读数量
 * @param cb 成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 *  - 从 6.1 版本开始，如果配置了离线推送，会收到厂商或 TPNS 的离线推送通道下发的通知栏消息。
 */
TIM_API int TIMMsgDoBackground(uint32_t unread_count, TIMCommCallback cb, const void* user_data);

/**
 * 2.3 APP 检测到应用进前台时可以调用此接口（iOS 和 Android 平台专用）
 *
 * @param cb 成功与否的回调。回调函数定义请参考 @ref TIMCommCallback
 * @param user_data 用户自定义数据，ImSDK只负责传回给回调函数cb，不做任何处理
 * @return int 返回TIM_SUCC表示接口调用成功（接口只有返回TIM_SUCC，回调cb才会被调用），其他值表示接口调用失败。每个返回值的定义请参考 @ref TIMResult
 * 
 * @note
 *  - 从 6.1 版本开始，调用 TIMMsgDoForeground，会停止离线推送。但如果应用被 kill，仍然可以正常接收离线推送。
 */
TIM_API int TIMMsgDoForeground(TIMCommCallback cb, const void* user_data);


/////////////////////////////////////////////////////////////////////////////////
//
//                      三. 离线推送 API 参数相关的 Json Key 定义
//
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// 3.1 OfflinePushToken(设置离线推送配置信息)
// string, 只写（选填）, 注册应用到厂商平台的 token。注意：填写为设备 Token 的 hex 字符串（即 base16 编码）。
static const char* kTIMOfflinePushTokenToken = "offline_push_token_token";
// uint32, 只写（选填）, IM 控制台证书 ID
static const char* kTIMOfflinePushTokenBusinessID = "offline_push_token_business_id";
// uint @ref TIMOfflinePushTokenType, 只写（选填）, 厂商 token 类型。默认为 TIMOfflinePushTokenType_Default。其中 TIMOfflinePushTokenType_TPNS 为待废弃状态，如果您之前通过 TPNS 接入离线推送，并且在 TPNS 控制台配置推送信息，可以继续按照该方式接入推送功能。如果您从未接入 TPNS，从未在 TPNS 控制台配置推送信息，IM 将不在支持 TPNS 方式接入离线推送功能, 推荐参照 [官网](https://cloud.tencent.com/document/product/269/74284) 接入
static const char* kTIMOfflinePushTokenType = "offline_push_token_type";
 
//------------------------------------------------------------------------------
// 3.2 IOSOfflinePushConfigSoundConfig(iOS 离线推送声音设置选项) 
// string, 选项, 接收时不会播放声音
static const char* kIOSOfflinePushNoSound = "push.no_sound";
// string, 选项, 接收时播放系统声音
static const char* kIOSOfflinePushDefaultSound = "default";

//------------------------------------------------------------------------------
// 3.3 IOSOfflinePushConfig(消息在 iOS 系统上的离线推送配置)
// string, 读写, 通知标题
static const char* kTIMIOSOfflinePushConfigTitle = "ios_offline_push_config_title";
// string, 读写, 离线推送声音设置（仅对 iOS 生效）,可设置的选项请参考 @ref IOSOfflinePushConfigSoundConfig。当 iOSSound = kIOSOfflinePushNoSound，表示接收时不会播放声音；当 iOSSound = kIOSOfflinePushDefaultSound，表示接收时播放系统声音；如果要自定义 iOSSound，需要先把语音文件链接进 Xcode 工程，然后把语音文件名（带后缀）设置给 iOSSound。
static const char* kTIMIOSOfflinePushConfigSound = "ios_offline_push_config_sound";
// bool, 读写, 是否忽略badge计数。若为true，在iOS接收端，这条消息不会使App的应用图标未读计数增加
static const char* kTIMIOSOfflinePushConfigIgnoreBadge = "ios_offline_push_config_ignore_badge";
// uint @ref TIMIOSOfflinePushType, 读写，iOS 离线推送的类型（仅对 iOS 生效），默认值是 TIMIOSOfflinePushType_APNS
static const char* kTIMIOSOfflinePushConfigPushType = "ios_offline_push_config_push_type";

//------------------------------------------------------------------------------
// 3.4 AndroidOfflinePushConfig(消息在 Android 系统上的离线推送配置)
// @note ChannelID 的说明:
//  - Android 8.0系统以上通知栏消息增加了 channelID 的设置，目前 oppo 要求必须填写，否则在 8.0 及以上的 OPPO 手机上会收不到离线推送消息。
//  - 后续可能会增加 xiaomi_channel_id_，huawei_channel_id 等。
// string, 读写, 通知标题
static const char* kTIMAndroidOfflinePushConfigTitle = "android_offline_push_config_title";
// string, 读写, 离线推送声音设置（仅对 Android 生效）。只有华为和谷歌手机支持设置声音提示，小米手机设置声音提示，请您参照 [官网](https://dev.mi.com/console/doc/detail?pId=1278%23_3_0)。另外，谷歌手机 FCM 推送在 Android 8.0 及以上系统设置声音提示，必须调用 setAndroidFCMChannelID 设置好 channelID，才能生效。AndroidSound: Android 工程里 raw 目录中的铃声文件名，不需要后缀名。
static const char* kTIMAndroidOfflinePushConfigSound = "android_offline_push_config_sound";
// uint @ref TIMAndroidOfflinePushNotifyMode, 读写, 当前消息的通知模式
static const char* kTIMAndroidOfflinePushConfigNotifyMode = "android_offline_push_config_notify_mode";
// uint32, 读写，离线推送设置 VIVO 推送消息分类 (待废弃接口，VIVO 推送服务于 2023 年 4 月 3 日优化消息分类规则，推荐使用 kTIMAndroidOfflinePushConfigVIVOCategory 设置消息类别) ，VIVO 手机离线推送消息分类，0：运营消息，1：系统消息。默认取值为 1 。
static const char* kTIMAndroidOfflinePushConfigVIVOClassification = "android_offline_push_config_vivo_classification";
// string, 读写, 离线推送设置 VIVO 推送消息类别，详见 [官网]( https://dev.vivo.com.cn/documentCenter/doc/359)。(VIVO 推送服务于 2023 年 4 月 3 日优化消息分类规则，推荐使用 kTIMAndroidOfflinePushConfigVIVOCategory 设置消息类别，不需要再关注和设置 kTIMAndroidOfflinePushConfigVIVOClassification)
static const char* kTIMAndroidOfflinePushConfigVIVOCategory = "android_offline_push_config_vivo_category";
// string, 读写, 离线推送设置 OPPO 手机 8.0 系统及以上的渠道 ID（仅对 Android 生效）。
static const char* kTIMAndroidOfflinePushConfigOPPOChannelID = "android_offline_push_config_oppo_channel_id";
// string, 读写, 离线推送设置小米手机 8.0 系统及以上的渠道 ID（仅对 Android 生效）。
static const char* kTIMAndroidOfflinePushConfigXiaoMiChannelID = "android_offline_push_config_xiaomi_channel_id";
// string, 读写, 离线推送设置 FCM 通道手机 8.0 系统及以上的渠道 ID（仅对 Android 生效）。
static const char* kTIMAndroidOfflinePushConfigFCMChannelID = "android_offline_push_config_fcm_channel_id";
// string, 读写, 离线推送设置华为推送消息分类，详见 [官网]( https://developer.huawei.com/consumer/cn/doc/development/HMSCore-Guides/message-classification-0000001149358835)
static const char* kTIMAndroidOfflinePushConfigHuaWeiCategory = "android_offline_push_config_huawei_category";

//------------------------------------------------------------------------------
// 3.4 OfflinePushConfig(消息离线推送配置)
// string, 读写, 当前消息在对方收到离线推送时候展示内容
static const char* kTIMOfflinePushConfigDesc = "offline_push_config_desc";
// string, 读写, 当前消息离线推送时的扩展字段
static const char* kTIMOfflinePushConfigExt = "offline_push_config_ext";
// uint @ref TIMOfflinePushFlag, 读写, 当前消息是否允许推送，默认允许推送 kTIMOfflinePushFlag_Default
static const char* kTIMOfflinePushConfigFlag = "offline_push_config_flag";
// object @ref IOSOfflinePushConfig, 读写, iOS离线推送配置
static const char* kTIMOfflinePushConfigIOSConfig = "offline_push_config_ios_config";
// object @ref AndroidOfflinePushConfig, 读写, Android离线推送配置
static const char* kTIMOfflinePushConfigAndroidConfig = "offline_push_config_android_config";
 
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_OFFLINE_PUSH_MANAGER_H_
