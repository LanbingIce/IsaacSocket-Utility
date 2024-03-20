// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_CLOUD_DEF_H_
#define SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_CLOUD_DEF_H_

#include "TIMCloudComm.h"

// 模块简介
//  - 公共配置选项 和 通用回调 的定义


/////////////////////////////////////////////////////////////////////////////////
//
//                      一. SDK 接口常用配置选项
//
/////////////////////////////////////////////////////////////////////////////////
/// 1.1 调用接口的返回值（若接口参数中有回调，只有当接口返回 TIM_SUCC 时，回调才会被调用）
enum TIMResult {
    /// 接口调用成功
    TIM_SUCC = 0,
    /// 接口调用失败，ImSDK 未初始化
    TIM_ERR_SDKUNINIT = -1,
    /// 接口调用失败，用户未登录
    TIM_ERR_NOTLOGIN = -2,
    /// 接口调用失败，错误的 Json 格式或 Json Key
    TIM_ERR_JSON = -3,
    /// 接口调用失败，参数错误
    TIM_ERR_PARAM = -4,
    /// 接口调用失败，无效的会话
    TIM_ERR_CONV = -5,
    /// 接口调用失败，无效的群组
    TIM_ERR_GROUP = -6,
};

/// 1.2 会话类型
enum TIMConvType {
    /// 无效会话
    kTIMConv_Invalid,
    /// 个人会话
    kTIMConv_C2C,
    /// 群组会话
    kTIMConv_Group,
    /// 系统会话，已废弃
    kTIMConv_System,
};

/// 1.3 消息接收选项
enum TIMReceiveMessageOpt {
    /// 在线正常接收消息，离线时会进行 APNs 推送
    kTIMRecvMsgOpt_Receive = 0,
    /// 不会接收到消息，离线不会有推送通知
    kTIMRecvMsgOpt_Not_Receive,
    /// 在线正常接收消息，离线不会有推送通知
    kTIMRecvMsgOpt_Not_Notify,
};

/////////////////////////////////////////////////////////////////////////////////
//
//                            二. SDK 接口通用回调
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * 接口通用回调的定义
 *
 * @param code 值为 ERR_SUCC 表示成功，其他值表示失败。详情请参考 [错误码](https://cloud.tencent.com/document/product/269/1671)
 * @param desc 错误描述字符串
 * @param json_params Json 字符串，不同的接口，Json 字符串不一样
 * @param user_data ImSDK 负责透传的用户自定义数据，未做任何处理
 *
 * @note
 * 所有回调均需判断 code 是否等于 ERR_SUCC，若不等于说明接口调用失败了，具体原因可以看 code 的值以及 desc 描述。详情请参考 [错误码](https://cloud.tencent.com/document/product/269/1671)
 */
typedef void (*TIMCommCallback)(int32_t code, const char* desc, const char* json_params, const void* user_data);

#endif  // SRC_PLATFORM_CROSS_PLATFORM_INCLUDE_TIM_CLOUD_DEF_H_
