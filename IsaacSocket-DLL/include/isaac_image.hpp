#pragma once
#include "pch.h"
#include "utils.hpp"
#include "lua.hpp"

// 小彭老师专用代码开始
#ifdef __MINGW32__
#include "gnucompat.hpp"
#define string ::gnucompat::string
#define vector ::gnucompat::vector
#endif
// 小彭老师专用代码结束

namespace isaac_image {
#pragma warning(disable: 4624)//禁用警告C4624: 已将析构函数隐式定义为“已删除”

	// Lua虚拟机类
	struct LuaEngine
	{
		char pad_0x18[0x18];
		lua_State* L;
		bool luaDebug;
	};

	// Mod类
	struct ModEntry {
		union
		{
			string dir;
			FIELD(0x18, string, name);
			FIELD(0xFC, string, isEnabled);
			FIELD(0x120, string, version);
			FIELD(0x144, string, id);
		};
	};

	// Mod管理器类
	struct ModManager {
		vector<ModEntry*> mods;
	};

	// 多语言文本类
	struct StringTable {
		uint32_t language;
	};

	//游戏选项
	struct Options {
		string OptionsIniFilePath; // 0x0
		float MusicVolume; // 0x18
		float SFXVolume; // 0x1c
		float MapOpacity; // 0x20
		bool Fullscreen; // 0x24
		bool Filter; // 0x25
		bool field6_0x26; // 0x26
		bool field7_0x27; // 0x27
		float Gamma; // 0x28
		float Exposure; // 0x2c
		float Brightness; // 0x30
		float Contrast; // 0x34
		bool ControllerHotplug; // 0x38
		bool DisplayPopups; // 0x39
		bool FoundHUD; // 0x3a
		bool field15_0x3b; // 0x3b
		int CameraStyle; // 0x3c
		int ExtraHUDStyle; // 0x40
		float HUDOffset; // 0x44
		bool TryImportSave; // 0x48
		bool EnableMods; // 0x49
		bool RumbleEnabled; // 0x4a
		bool ChargeBars; // 0x4b
		bool BulletVisibility; // 0x4c
		bool AimLock; // 0x4d
		bool field25_0x4e; // 0x4e
		bool field26_0x4f; // 0x4f
		int TouchMode; // 0x50
		bool DebugConsoleEnabled; // 0x54
		bool VSync; // 0x55
		bool SteamCloud; // 0x56
		bool PauseOnFocusLost; // 0x57
		bool MouseControl; // 0x58
		bool field33_0x59; // 0x59
		bool field34_0x5a; // 0x5a
		bool field35_0x5b; // 0x5b
		int MaxScale; // 0x5c
		int MaxRenderScale; // 0x60
		int WindowWidth; // 0x64
		int WindowHeight; // 0x68
		int WindowPosX; // 0x6c
		int WindowPosY; // 0x70
		int ConsoleFont; // 0x74
		bool FadedConsoleDisplay; // 0x78
		bool SaveCommandHistory; // 0x79
		bool UseBorderlessFullscreen; // 0x7a
		bool EnableInterpolation; // 0x7b
		bool EnableColorCorrection; // 0x7c
		bool EnableLighting; // 0x7d
		bool EnableShockwave; // 0x7e
		bool EnableCaustics; // 0x7f
		bool EnableFilter; // 0x80
		bool EnablePixelation; // 0x81
		bool EnableBloom; // 0x82
		bool EnableWaterSurface; // 0x83
		bool EnableHeatWaves; // 0x84
		bool EnableColorModifier; // 0x85
		bool BossHpOnBottom; // 0x86
		bool field58_0x87; // 0x87
		int AnnouncerVoiceMode; // 0x88
		char pad0[0x1]; // 0x8c
	}; // 0x8d

	// 存档类
	struct PersistentGameData {
		union
		{
			FIELD(0x38, uint8_t, achievements[638]);
			FIELD(0x308, int32_t, donationCount);
			FIELD(0x30C, uint32_t, edenTokens);
			FIELD(0x484, int32_t, greedDonationCount);
		};
	};

	// 管理器类
	struct Manager
	{
		union
		{
			FIELD(0x14, PersistentGameData, persistentGameData);
			FIELD(0x29DF8, Options, options);
			FIELD(0x29FD8, ModManager, modManager);
			FIELD(0x4A234, StringTable, stringTable);
			FIELD(0x1EA818, bool, needExit);
		};
	};

	// 主菜单
	struct MainMenu
	{
		struct
		{
			char pad_0x38[0x38];
			uint32_t page;
			int32_t offsetX;
			int32_t offsetY;
		};
	};

	// 暂停菜单类
	struct PauseMenu
	{
		//0:关闭 1:开启 2:设置界面 小于0:强制隐藏
		int32_t state;
	};

	// 主动道具类
	struct Active
	{
		int32_t item;
		int32_t charge;
		int32_t batteryCharge;
		int32_t subCharge;
		int32_t timedRechargeCooldown;
		float partialCharge;
		int32_t varData;
	};

	// 武器类，未研究完毕
	struct Weapon
	{
		//// 虚表指针
		//int ptr;
		//int var2;
		//float var3;
		//float fireDelay;
		//float abp_tears;
		//float charge;
		//float var7;
		//float dirX;
		//float dirY;
		//int var10;
		//int var11;
		//int type;
	};

	//种子
	struct Seeds
	{
		uint32_t seedMode;
		uint32_t startSeed;
	};

	//错误道具事件
	struct GlitchedEvent
	{
		uint32_t trigger;
		uint32_t effect;
	};

	//错误道具
	struct GlitchedItem
	{
		char pad_0x2C[0x2C];
		vector<GlitchedEvent*> glitchedEvents;
	};

	//GLFW窗口类
	struct _GLFWwindow
	{
		union
		{
			FIELD(0x14, uint32_t, width);
			FIELD(0x18, uint32_t, height);
			//GLFWcharmodsfun
			FIELD(0x214, LPCVOID, character);
		};
	};

	// 控制台类
	struct Console
	{
		union
		{
			//0:关闭 2:开启 4:正在关闭 小于0:强制暂停
			FIELD(0x20, int32_t, state);
			FIELD(0x30, float, offsetY);
			FIELD(0x3C, string, consoleText);
		};
	};

	// 角色身上的道具(饰品)类
	struct HistoryItem
	{
		uint32_t time;
		bool isTrinket;
		char paddind[3];
		int32_t id;
		uint32_t levelStage;
		uint32_t stageType;
		uint32_t roomType;
		uint32_t itemPoolType;
	};

	// 角色的历史
	struct History {
		vector<HistoryItem> historyItems;
	};

	// 角色类
	struct Player
	{
		union
		{
			FIELD(0x132C, Weapon*, weapon);
			FIELD(0x14C4, Active, actives[4]);
			FIELD(0x1745, uint8_t, canShoot);
			FIELD(0x1D0C, History, history);
		};
	};

	// 游戏类
	struct Game
	{
		union
		{
			FIELD(0x1BA50, vector<Player*>, players);
			FIELD(0x1BB04, Seeds, seeds);
			FIELD(0x1BB60, Console, console);
			FIELD(0x10203C, PauseMenu, pauseMenu);
			FIELD(0x1C3164, uint32_t, debugFlag);
			FIELD(0x283C20, vector<GlitchedItem*>, glitchedItems);
		};
	};

#pragma warning(default: 4624)//重新启用警告C4624

	// 以撒主模块镜像类
	struct IsaacImage
	{
		union
		{
			FIELD(0x76A658, double, FrameInterval);
			FIELD(0x7C7B08, _GLFWwindow*, window);
			FIELD(0x7FD65C, Game*, game);
			FIELD(0x7FD674, LuaEngine*, luaEngine);
			FIELD(0x7FD680, Manager*, manager);
			FIELD(0x7FD688, MainMenu*, mainMenu);
			FIELD(0x7AA920, float, screenPointScale);
		};
	};
}

// 小彭老师专用代码开始
#ifdef __MINGW32__
#undef string
#undef vector
#endif
// 小彭老师专用代码结束
