#pragma once
#include "pch.h"

namespace isaac_socket
{
    bool TryInitLua();

    // 进行一次 “日志输出”
    void LogOutput(const char* text, uint32_t type = 0);

    // 进行一次 “控制台输出”
    void ConsoleOutput(std::string text, uint32_t color = 0xFFD3D3D3);

    // 进行一次 “执行控制台指令”
    void ExecuteCommand(std::string commandText);

    // 手动发送一条窗口过程消息
    LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // 重新载入lua环境
    void ReloadLua();

    // 设置GLFW的接收字符回调，使得直接设置控制台state的方式打开控制台也可以输入字符
    void SetGLFWCharacter();

    // 初始化
    void InitByMainThread(HWND hWnd);

    void AllocConsole();

    void FreeConsole();

    // 全屏/取消全屏
    void FullScreen(bool fullScreen);

    // 音乐音量
    void MusicVolume(float musicVolume);

    // 垂直同步
    void VSync(bool vSync);
}
