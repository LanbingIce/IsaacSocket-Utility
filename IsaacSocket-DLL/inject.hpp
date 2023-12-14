#pragma once
#include "pch.h"
#include "utils.hpp"

namespace inject {
	struct Callbacks
	{
		LPCVOID OnRender;
		LPCVOID OnGameUpdate;
		LPCVOID OnSpecialUpdate;
		LPCVOID OnExecuteCommand;
		LPCVOID OnConsoleOutput;
		uint32_t(__fastcall* OnMTRandom)(uint32_t);
	};

	static const char* logPreFix = "[LOG(%d)] ";
	static HANDLE hProcess;
	static isaac::IsaacImage* isaac;
	static Callbacks callbacks;
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
			mov eax, isaac
			add eax, 0x55E336
			jmp eax
		}
	}

	// 渲染函数
	__declspec(naked) void Render()
	{
		__asm {
			call callbacks.OnRender
			push ebp
			mov ebp, esp
			and esp, -0x08
			mov eax, isaac
			add eax, 0x4B0606
			jmp eax
		}
	}

	// 游戏更新函数，每秒30次更新
	__declspec(naked) void __fastcall GameUpdate(isaac::Game* gamePtr)
	{
		__asm {
			push ecx
			call callbacks.OnGameUpdate
			pop ecx
			push ebp
			mov ebp, esp
			and esp, -0x10
			mov eax, isaac
			add eax, 0x2CDCF6
			jmp eax
		}
	}

	// 特殊更新函数，用来更新某些需要每秒60次更新的东西，游戏更新函数每秒只触发30次，另外30次在这个函数里处理
	__declspec(naked) void SpecialUpdate()
	{
		__asm {
			call callbacks.OnSpecialUpdate
			push ebp
			mov ebp, esp
			sub esp, 0x0C
			mov eax, isaac
			add eax, 0x2D0406
			jmp eax
		}
	}

	// 执行控制台指令函数,最后两个参数总是0,如果最后一个参数不是0，游戏就会崩溃
	__declspec(naked) void __fastcall ExecuteCommand(isaac::Console& console, LPCVOID _, const string& text, int unknow, int unknow_point_guess)
	{
		__asm {
			push ecx
			push[esp + 0x10]
			push[esp + 0x10]
			push[esp + 0x10]
			call callbacks.OnExecuteCommand
			add esp, 0x0C
			pop ecx
			push ebp
			mov ebp, esp
			push - 0x01
			mov eax, isaac
			add eax, 0x2655C5
			jmp eax
		}
	}

	// 控制台输出函数,最后一个参数总是0x96，只有当控制台顶部的"Repentance Console"这行字输出时，这个参数是0
	__declspec(naked) void __fastcall ConsoleOutput(isaac::Console& console, LPCVOID _, const string& text, uint32_t color, uint32_t type_guess)
	{
		__asm {
			push ecx
			push[esp + 0x10]
			push[esp + 0x10]
			push[esp + 0x10]
			call callbacks.OnConsoleOutput
			add esp, 0x0C
			pop ecx
			push ebp
			mov ebp, esp
			push - 0x01
			mov eax, isaac
			add eax, 0x26AEC5
			jmp eax
		}
	}

	// MT19937随机数生成,这个函数的注入点在尾部，因此不会影响正常的随机序列，且可以获取并覆盖原函数的返回值
	// 这个函数对原代码做了优化,节省了部分代码，回调函数的调用约定为fastcall
	__declspec(naked) void MTRandom()
	{
		__asm {
			shr eax, 0x12
			xor ecx, eax
			call callbacks.OnMTRandom
			ret
		}
	}

	//注入代码
	static void InjectCode(size_t offset, LPCVOID fuctionAddress, size_t paddingSize)
	{
		char* injectAddress = (char*)isaac + offset;
		//操作码长度为1，操作数长度为4，两者加起来是5
		uint8_t opcode = 0xE9;//jmp
		WriteProcessMemory(hProcess, injectAddress, &opcode, 1, nullptr);
		int32_t operand = (char*)fuctionAddress - injectAddress - 5;
		WriteProcessMemory(hProcess, injectAddress + 1, &operand, 4, nullptr);
		for (size_t i = 0; i < paddingSize; i++)
		{
			opcode = 0x90;//nop
			WriteProcessMemory(hProcess, injectAddress + 5 + i, &opcode, 1, nullptr);
		}
	}

	void Init(HANDLE hProcess, isaac::IsaacImage* isaac, Callbacks callbacks) {
		inject::hProcess = hProcess;
		inject::isaac = isaac;
		inject::callbacks = callbacks;
		// 渲染
		InjectCode(0x4B0600, Render, 1);
		// 执行控制台指令
		InjectCode(0x2655C0, ExecuteCommand, 0);
		// 控制台输出
		InjectCode(0x26AEC0, ConsoleOutput, 0);
		// 游戏更新
		InjectCode(0x2CDCF0, GameUpdate, 1);
		// 特殊更新
		InjectCode(0x2D0400, SpecialUpdate, 1);
		// 日志输出
		InjectCode(0x55E330, LogPrintf, 1);
		// MT19937随机数生成
		InjectCode(0x2C3EA8, MTRandom, 1);
	}
}
