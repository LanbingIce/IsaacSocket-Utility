// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

using std::endl;
using std::hex;
using std::ios;
using std::ofstream;
using std::ostringstream;
using std::setiosflags;
using std::string;
using std::to_string;
using std::vector;

// 共享内存中与连接程序交互的数据结构
struct Config
{
	int needReload;
	int IsForcePaused;
	int needPrint;
};
// 武器类，未研究完毕
struct Weapon
{
	int ptr;
	// 虚表指针
	int var2;
	float var3;
	float fireDelay;
	float abp_tears;
	float charge;
	float var7;
	float dirX;
	float dirY;
	int var10;
	int var11;
	int type;
};
// 被动道具类
struct PassiveSlot
{
	int pickTime;
	char name_guess[4];
	int item;
	int pickStage;
	int pickStageVariat;
	int pickRoomType;
	int itemPool;
};
// 主动道具类
struct ActiveSlot
{
	int item;
	int charge;
	int batteryCharge;
	int subCharge;
	int timedRechargeCooldown;
	float partialCharge;
	int varData;
};
// 角色类
struct Player
{
	char pad_0x132C[0x132C];
	Weapon* weapon;
	char pad_0x14C4[0x14C4 - 0x132C - 4];
	ActiveSlot activeSlots[4];
	// 4 * 28 bytes
	char pad_0x1745[0x1745 - 0x14C4 - 4 * 28];
	bool canShoot;
	char pad_0x1D0C[0x1D0C - 0x1745 - 1];
	vector<PassiveSlot> passiveSlots;
};
// 控制台类
struct Console
{
	char pad_0x20[0x20];
	int isConsoleOpen;
	char pad_0x30[0x30 - 0x20 - 4];
	float consoleOffsetY;
	char pad_0x3C[0x3C - 0x30 - 4];
	string consoleText;
};

// 游戏类
struct Game
{
	char pad_0x1BA50[0x1BA50];
	vector<Player*> players;
	// 12 bytes
	char pad_0x1BB60[0x1BB60 - 0x1BA50 - 12];
	Console console;
	char pad_0x10203C[0x10203C - 0x1BB60 - sizeof(console)];
	int isMenuPaused;
	char pad_0x1C3164[0x1C3164 - 0x10203C - 4];
	int debugFlag;
};
// 以撒程序类
struct IsaacImage
{
	char pad_0x7FD65C[0x7FD65C];
	Game* game;
	char pad_0x7FD680[0x7FD680 - 0x7FD65C - 4];
	int lua_guess;
};
// 对注入的函数进行声明
static void __fastcall Render_inj();
static void __fastcall GameUpdate_inj(Game* gamePtr);
static void __fastcall ConsoleOutput_inj(Console& console, void*, const string& text, int color, int type_guess);
static void __fastcall ExecuteCommand_inj(Console& console, void*, const string& text, int, int);
static void __fastcall AdditionalUpdate_inj();
static bool __fastcall IsPaused_inj(Game* gamePtr);
// IsaacSocket类，实现具体功能
struct IsaacSocket
{
	static inline IsaacImage* isaac;
	static inline Config* config;
	// int转16进制文本
	static string ToHexString(int num)
	{
		ostringstream os;
		os << hex << setiosflags(ios::uppercase) << num;
		return os.str();
	}
	static void SaveText(string& text) {
		ofstream outfile;
		outfile.open("%temp%/IsaacSocket.txt", ios::app);
		outfile << text << std::endl;
		outfile.close();
	}
	// 重新载入lua环境
	static void ResetLua()
	{
		void* thisPtr = (char*)(isaac->lua_guess) + 0x00029FD8;
		int d_0x7FD674 = *(int*)((unsigned)isaac + 0x7FD674);
		void (*f_0x55E330)(void*, int) = (void (*)(void*, int))((unsigned)isaac + 0x55E330);
		// 输出日志
		f_0x55E330(0, (int)isaac + 0x74F6F4);
		//"Lua is resetting!"
		void(__fastcall * f_0x40AE00)(int) = (void(__fastcall*)(int))((unsigned)isaac + 0x40AE00);
		// 卸载lua环境
		f_0x40AE00(d_0x7FD674);
		void(__fastcall * f_0x3FCB00)(int, int, int) = (void(__fastcall*)(int, int, int))((unsigned)isaac + 0x3FCB00);
		// 加载lua环境
		f_0x3FCB00(d_0x7FD674, NULL, *(char*)(d_0x7FD674 + 0x1C));
		void(__fastcall * f_0x4702F0)(void*) = (void(__fastcall*)(void*))((unsigned)isaac + 0x4702F0);
		// 清除mod列表
		f_0x4702F0(thisPtr);
		void(__fastcall * f_0x470B40)(void*) = (void(__fastcall*)(void*))((unsigned)isaac + 0x470B40);
		// 创建mod列表
		f_0x470B40(thisPtr);
		void(__fastcall * f_0x46F2B0)(void*) = (void(__fastcall*)(void*))((unsigned)isaac + 0x46F2B0);
		// 重新加载着色器
		f_0x46F2B0(thisPtr);
		void (*f_0x4AF200)() = (void (*)())((unsigned)isaac + 0x4AF200);
		// 可能是重新加载精灵
		f_0x4AF200();
		void(__fastcall * f_0x46DAE0)(void*) = (void(__fastcall*)(void*))((unsigned)isaac + 0x46DAE0);
		// 加载lua环境
		f_0x46DAE0(thisPtr);
		int d_0x7FD688 = *(int*)((unsigned)isaac + 0x7FD688);
		if (d_0x7FD688)
		{
			if (isaac->game)
			{
				void(__fastcall * f_0x517F20)(int&) = (void(__fastcall*)(int&))((unsigned)isaac + 0x517F20);
				// 不懂，可能是某种初始化
				f_0x517F20(isaac->game->isMenuPaused);
			}
			void (*f_0x92A0)() = (void (*)())((unsigned)isaac + 0x92A0);
			// 可能是清除什么缓存
			f_0x92A0();
			void (*f_0x4AFA70)() = (void (*)())((unsigned)isaac + 0x4AFA70);
			// 可能是重新加载精灵
			f_0x4AFA70();
			void(__fastcall * f_0x4A3F30)(int) = (void(__fastcall*)(int))((unsigned)isaac + 0x4A3F30);
			// 不懂
			f_0x4A3F30(d_0x7FD688 + 0x101C00);
			void(__fastcall * f_0x4AB4E0)(int) = (void(__fastcall*)(int))((unsigned)isaac + 0x4AB4E0);
			// 不懂
			f_0x4AB4E0(d_0x7FD688 + 0x102E80);
		}
	}
	// 获取“是否强制暂停”的配置，方便注入的汇编函数调用
	static bool IsForcePaused()
	{
		return config->IsForcePaused;
	}
	// 进行一次“获取游戏是否暂停”
	static bool IsPaused()
	{
		return IsPaused_inj(isaac->game);
	}
	// 进行一次“额外更新”，即人物更新之类的每秒额外30次更新
	static void AdditionalUpdate()
	{
		AdditionalUpdate_inj();
	}
	// 进行一次“游戏更新”
	static void GameUpdate()
	{
		GameUpdate_inj(isaac->game);
	}
	// 进行一次“渲染”
	static void Render()
	{
		Render_inj();
	}
	// 进行一次“控制台输出”
	static void ConsoleOutput(const string& text, unsigned int color = 0xFFD3D3D3)
	{
		ConsoleOutput_inj(isaac->game->console, NULL, text, color, 0x96);
	}
	// 进行一次“控制台输出”，并追加换行符
	static void ConsoleOutputLine(const string& text = "", unsigned int color = 0xFFD3D3D3)
	{
		ConsoleOutput_inj(isaac->game->console, NULL, text + "\n", color, 0x96);
	}
	// 进行一次“执行控制台指令”
	static void ExecuteCommand(const string& commandText)
	{
		ExecuteCommand_inj(isaac->game->console, NULL, commandText, 0, 0);
	}
	// 渲染回调，时机在渲染函数的起始位置，只要游戏进程存在就一直触发
	static void OnRender()
	{
		if (config->needReload == 1)
		{
			config->needReload = 0;
			ResetLua();
		}
	}
	// 执行控制台指令回调，时机在执行控制台指令函数的起始位置
	static void OnExecuteCommand(string& str)
	{

	}
	// 额外更新回调，时机在额外更新函数的起始位置
	static void OnAdditionalUpdate()
	{

	}
	// 游戏更新回调，时机在游戏更新函数的起始位置
	static void OnGameUpdate()
	{

	}
	// 控制台输出回调，时机在控制台输出函数的起始位置
	static void OnConsoleOutput(string& str, int color)
	{
		SaveText(str);
	}
};
// 以下为注入的函数
// 渲染函数
__declspec(naked) void __fastcall Render_inj()
{
	__asm {
		call IsaacSocket::OnRender
		push ebp
		mov ebp, esp
		and esp, -0x08
		mov eax, IsaacSocket::isaac
		add eax, 0x4B0606
		jmp eax
	}
}
// 游戏更新函数
__declspec(naked) void __fastcall GameUpdate_inj(Game* gamePtr)
{
	__asm {
		push ecx
		call IsaacSocket::OnGameUpdate
		call IsaacSocket::IsForcePaused
		cmp al, 0x0
		pop ecx
		jne flag
		push ebp
		mov ebp, esp
		and esp, -0x10
		mov eax, IsaacSocket::isaac
		add eax, 0x2CDCF6
		jmp eax
		flag :
		ret
	}
}
// 额外更新函数
__declspec(naked) void __fastcall AdditionalUpdate_inj()
{
	__asm {
		call IsaacSocket::OnAdditionalUpdate
		call IsaacSocket::IsForcePaused
		cmp al, 0x0
		jne flag
		push ebp
		mov ebp, esp
		sub esp, 0x0C
		mov eax, IsaacSocket::isaac
		add eax, 0x2D0406
		jmp eax
		flag :
		ret
	}
}
// 执行控制台指令函数
__declspec(naked) void __fastcall ExecuteCommand_inj(Console& console, void*, const string& text, int, int)
{
	__asm {
		push ecx
		push[esp + 0x8]
		call IsaacSocket::OnExecuteCommand
		add esp, 0x4
		pop ecx
		push ebp
		mov ebp, esp
		push - 0x01
		mov eax, IsaacSocket::isaac
		add eax, 0x2655C5
		jmp eax
	}
}
// 控制台输出函数
__declspec(naked) void __fastcall ConsoleOutput_inj(Console& console, void*, const string& text, int color, int type_guess)
{
	__asm {
		push ecx
		push[esp + 0xC]
		push[esp + 0xC]
		call IsaacSocket::OnConsoleOutput
		add esp, 8
		pop ecx
		push ebp
		mov ebp, esp
		push - 0x1
		mov eax, IsaacSocket::isaac
		add eax, 0x26AEC5
		jmp eax
	}
}
// 游戏是否暂停函数
__declspec(naked) bool __fastcall IsPaused_inj(Game* gamePtr)
{
	__asm {
		push ecx
		call IsaacSocket::IsForcePaused
		cmp al, 00
		pop ecx
		jne flag
		mov eax, IsaacSocket::isaac
		add eax, 0x2D0387
		cmp dword ptr[ecx + 0x1BB80], 0
		jmp eax
		flag :
		mov eax, IsaacSocket::isaac
			add eax, 0x2D03F8
			jmp eax
	}
}
// 以上为注入的函数

//注入函数
static void Inject(int offset, void* fuctionAddress, int paddingSize)
{
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
	int injectAddress = (int)IsaacSocket::isaac + offset;
	unsigned char c = 0xE9;
	WriteProcessMemory(processHandle, (void*)(injectAddress), &c, sizeof(c), nullptr);
	int value = (int)fuctionAddress - (injectAddress + 5);
	WriteProcessMemory(processHandle, (void*)(injectAddress + 1), &value, sizeof(value), nullptr);
	c = 0x90;
	if (paddingSize > 0)
	{
		int pad = 0x90909090;
		WriteProcessMemory(processHandle, (void*)(injectAddress + 5), &pad, paddingSize, nullptr);
	}
	CloseHandle(processHandle);
}

// 初始化，共享内存和注入
static void Init()
{
	HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, L"IsaacSocketSharedMemory");
	if (hMapFile)
	{
		IsaacSocket::config = (Config*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
		IsaacSocket::isaac = (IsaacImage*)GetModuleHandle(NULL);
		// 渲染
		Inject(0x4B0600, &Render_inj, 1);
		// 执行控制台指令
		Inject(0x2655C0, &ExecuteCommand_inj, 0);
		// 控制台输出
		Inject(0x26AEC0, &ConsoleOutput_inj, 0);
		// 是否暂停
		Inject(0x2D0380, &IsPaused_inj, 2);
		// 游戏更新
		Inject(0x2CDCF0, &GameUpdate_inj, 1);
		// 附加更新
		Inject(0x2D0400, &AdditionalUpdate_inj, 1);
	}
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Init();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}