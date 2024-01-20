#include "pch.h"
#include "inject.hpp"
#include "utils.hpp"
#include "state.hpp"

namespace inject {

	//注入代码
	static void InjectCode(LPCVOID ModuleBase, size_t offset, LPCVOID fuctionAddress, size_t paddingSize)
	{
		size_t opSize = 1 + 4; //操作码长度为1，操作数长度为4
		uint8_t* injectAddress = (uint8_t*)ModuleBase + offset;

		DWORD oldProtect;
		VirtualProtect(injectAddress, opSize + paddingSize, PAGE_EXECUTE_READWRITE, &oldProtect); //修改页保护

		injectAddress[0] = 0xE9;//操作码：jmp
		*(int32_t*)(injectAddress + 1) = (uint8_t*)fuctionAddress - injectAddress - opSize;//操作数：跳转到的地址

		for (size_t i = 0; i < paddingSize; i++)
		{
			injectAddress[opSize + i] = 0x90;//nop填充
		}

		VirtualProtect(injectAddress, opSize + paddingSize, oldProtect, &oldProtect); //恢复页保护
	}

#ifndef __MINGW32__
	// MinGW 的内联汇编只支持 AT&T 格式，和 MSVC 的 Intel 格式完全不同，因此改为在 gnuinject.S 中实现
	// 以下代码仅在 MSVC 下编译
	static const char* logPreFix = "[LOG(%d)] ";
	static int tmpRetIP;
	static int tmpLogLevel;

	//输出日志函数
	__declspec(naked) void LogPrintf(int level, const char* format, ...) {
		__asm {
			call GetConsoleWindow
			test eax, eax
			je flag
			push[esp + 0x04]
			push logPreFix
			call _cprintf
			add esp, 0x08
			pop tmpRetIP
			pop tmpLogLevel
			call utils::Utf8Cprintf
			push tmpLogLevel
			push tmpRetIP
			flag : push ebp
			mov ebp, esp
			and esp, -0x08
			mov eax, local.isaac
			add eax, 0x55E336
			jmp eax
		}
	}

	// 渲染函数
	__declspec(naked) void Render()
	{
		__asm {
			call local.callbacks.OnRender
			push ebp
			mov ebp, esp
			and esp, -0x08
			mov eax, local.isaac
			add eax, 0x4B0606
			jmp eax
		}
	}

	// 游戏更新函数，每秒30次更新
	__declspec(naked) void FASTCALL GameUpdate(isaac::Game* gamePtr)
	{
		__asm {
			push ecx
			call local.callbacks.OnGameUpdate
			pop ecx
			push ebp
			mov ebp, esp
			and esp, -0x10
			mov eax, local.isaac
			add eax, 0x2CDCF6
			jmp eax
		}
	}

	// 特殊更新函数，用来更新某些需要每秒60次更新的东西，游戏更新函数每秒只触发30次，另外30次在这个函数里处理
	__declspec(naked) void SpecialUpdate()
	{
		__asm {
			call local.callbacks.OnSpecialUpdate
			push ebp
			mov ebp, esp
			sub esp, 0x0C
			mov eax, local.isaac
			add eax, 0x2D0406
			jmp eax
		}
	}

	// 执行控制台指令函数,最后两个参数总是0,如果最后一个参数不是0，游戏就会崩溃
	__declspec(naked) void FASTCALL ExecuteCommand(isaac::Console& console, LPCVOID _, const string& text, int unknow, int unknow_point_guess)
	{
		__asm {
			push ecx
			push[esp + 0x10]
			push[esp + 0x10]
			push[esp + 0x10]
			call local.callbacks.OnExecuteCommand
			add esp, 0x0C
			pop ecx
			push ebp
			mov ebp, esp
			push - 0x01
			mov eax, local.isaac
			add eax, 0x2655C5
			jmp eax
		}
	}

	// 控制台输出函数,最后一个参数总是0x96，只有当控制台顶部的"Repentance Console"这行字输出时，这个参数是0
	__declspec(naked) void FASTCALL ConsoleOutput(isaac::Console& console, LPCVOID _, const string& text, uint32_t color, uint32_t type_guess)
	{
		__asm {
			push ecx
			push[esp + 0x10]
			push[esp + 0x10]
			push[esp + 0x10]
			call local.callbacks.OnConsoleOutput
			add esp, 0x0C
			pop ecx
			push ebp
			mov ebp, esp
			push - 0x01
			mov eax, local.isaac
			add eax, 0x26AEC5
			jmp eax
		}
	}

	// MT19937随机数生成,这个函数的注入点在尾部，因此不会影响正常的随机序列，且可以获取并覆盖原函数的返回值
	__declspec(naked) void MTRandom()
	{

		__asm {
			shr eax, 0x12
			xor eax, ecx
			cmp local.MTRandomLockedValue, 0
			je flag
			mov eax, local.MTRandomLockedValue
			flag : ret
		}
	}

	//窗口过程回调函数
	__declspec(naked) LRESULT WINAPI Wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		__asm {
			call local.callbacks.OnWindowMessage
			test eax, eax
			je flag
			push ebp
			mov ebp, esp
			and esp, -0x40
			mov eax, local.isaac
			add eax, 0X5971D6
			jmp eax
			flag : ret 0x10
		}
	}
#endif

	void Init() {
#ifdef __MINGW32__
		// 以下代码仅在 MinGW 下编译
		extern LPCVOID gnuinjectState[];  // 在gnuinject.S中定义
		gnuinjectState[0] = local.isaac;
		gnuinjectState[1] = &local.MTRandomLockedValue;
		gnuinjectState[2] = (LPCVOID)utils::Utf8Cprintf;
		gnuinjectState[3] = (LPCVOID)GetConsoleWindow;
		gnuinjectState[4] = (LPCVOID)_cprintf;
		memcpy(gnuinjectState + 5, &local.callbacks, sizeof(local.callbacks));
#endif

		/* if (!local.isaac) MessageBoxW(NULL, L"以撒句柄 local.isaac 为空2！", L"错误", MB_OK); */

#define INJECT(offset, name, padding) InjectCode(local.isaac, offset, (LPCVOID)name, padding)
		// 渲染
		INJECT(0x4B0600, Render, 1);
		// 执行控制台指令
		INJECT(0x2655C0, ExecuteCommand, 0);
		// 控制台输出
		INJECT(0x26AEC0, ConsoleOutput, 0);
		// 游戏更新
		INJECT(0x2CDCF0, GameUpdate, 1);
		// 特殊更新
		INJECT(0x2D0400, SpecialUpdate, 1);
		// 日志输出
		INJECT(0x55E330, LogPrintf, 1);
		// MT19937随机数生成
		INJECT(0x2C3EA8, MTRandom, 1);
		// 窗口消息
		INJECT(0x5971D0, Wndproc, 1);
#undef INJECT
	}
}
