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
	static const char* logPreFix = "[INFO] - \0\0\0\0\0\0\0" "[WARN] - \0\0\0\0\0\0\0""[ERROR] - \0\0\0\0\0\0""[ASSERT] - ";
	static int tmpRetAddr;
	static int tmpLogType;

	//输出日志函数
	__declspec(naked) void LogPrintf(int type, const char* format, ...) {
		__asm {
			call GetConsoleWindow
			test eax, eax
			je flag
			mov eax, [esp + 0x04]
			shl eax, 4
			add eax, logPreFix
			push eax
			call _cprintf
			add esp, 0x04
			pop tmpRetAddr
			pop tmpLogType
			call utils::Utf8Cprintf
			push tmpLogType
			push tmpRetAddr
			flag : push ebp
			mov ebp, esp
			and esp, -0x08
			mov eax, local.isaac
			add eax, 0x55E336
			jmp eax
		}
	}

	//SwapBuffers
	static __declspec(naked) void _SwapBuffers()
	{
		__asm {
			call local.callbacks.PreSwapBuffers
			test eax, eax
			je flag_r0
			add esp, 0x04
			jmp flag_r1
			flag_r0 : call edi
			flag_r1 : pop edi
			pop esi
			mov esp, ebp
			mov eax, local.isaac
			add eax, 0x4B107C
			jmp eax
		}
	}

	// 执行控制台指令函数，用于注入的函数体
	static __declspec(naked) void _ExecuteCommand()
	{
		__asm {
			push ecx
			push[esp + 0x18]
			push[esp + 0x18]
			push[esp + 0x18]
			push ecx
			call local.callbacks.OnExecuteCommand
			add esp, 0x10
			pop ecx
			test eax, eax
			jne flag
			mov eax, local.isaac
			add eax, 0x5F36B0
			push eax
			mov eax, local.isaac
			add eax, 0x2655CA
			jmp eax
			flag : mov esp, ebp
			pop ebp
			ret 0x0C
		}
	}

	// 执行控制台指令函数，最后两个参数总是0,如果最后一个参数不是0，游戏就会崩溃
	__declspec(naked) void FASTCALL ExecuteCommand(const isaac::Console& console, LPCVOID, string& text, int unknow, LPCVOID unknow_point_guess)
	{
		__asm {
			push ebp
			mov ebp, esp
			push - 0x01
			jmp _ExecuteCommand
		}
	}

	// 控制台输出函数，用于注入的函数体
	static __declspec(naked) void _ConsoleOutput()
	{
		__asm {
			push ecx
			push[esp + 0x18]
			push[esp + 0x18]
			push[esp + 0x18]
			push ecx
			call local.callbacks.OnConsoleOutput
			add esp, 0x10
			pop ecx
			test eax, eax
			jne flag
			mov eax, local.isaac
			add eax, 0x5F3735
			push eax
			mov eax, local.isaac
			add eax, 0x26AECA
			jmp eax
			flag : mov esp, ebp
			pop ebp
			ret 0x0C
		}
	}

	// 控制台输出函数，最后一个参数总是0x96，只有当控制台顶部的"Repentance Console"这行字输出时，这个参数是0
	__declspec(naked) void FASTCALL ConsoleOutput(const isaac::Console& console, LPCVOID, string& text, uint32_t color, int type_guess) {
		__asm {
			push ebp
			mov ebp, esp
			push - 0x01
			jmp _ConsoleOutput
		}
	}

	// MT19937随机数生成,这个函数的注入点在尾部，因此不会影响正常的随机序列，且可以获取并覆盖原函数的返回值
	static __declspec(naked) void _MTRandom()
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
	__declspec(naked) LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		__asm {
			push[esp + 0x10]
			push[esp + 0x10]
			push[esp + 0x10]
			push[esp + 0x10]
			call local.callbacks.PreWndProc
			add esp, 0x10
			test eax, eax
			jne flag
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
		// SwapBuffers
		INJECT(0x4B1076, _SwapBuffers, 1);
		// 执行控制台指令
		INJECT(0x2655C5, _ExecuteCommand, 0);
		// 控制台输出
		INJECT(0x26AEC5, _ConsoleOutput, 0);
		// 日志输出
		INJECT(0x55E330, LogPrintf, 1);
		// MT19937随机数生成
		INJECT(0x2C3EA8, _MTRandom, 1);
		// 窗口消息
		INJECT(0x5971D0, WndProc, 1);
#undef INJECT
	}
}
