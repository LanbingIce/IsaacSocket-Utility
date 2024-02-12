#pragma once
#include "pch.h"
#include "utils.hpp"
#include "gnucompat.hpp"

namespace isaac {

	struct lua_State;

#pragma warning(disable: 4624)//禁用警告C4624: 已将析构函数隐式定义为“已删除”

	//Lua虚拟机类
	struct LuaVM
	{
		char pad_0x18[0x18];
		lua_State* L;
		bool luaDebug;
	};

	//可能的Mod管理器类，还未研究完毕
	struct ModManager {};

	//游戏选项
	struct Options {
		gnucompat::string _optionsIniFilePath; // 0x0
		float _musicVolume; // 0x18
		float _sfxVolume; // 0x1c
		float _mapOpacity; // 0x20
		bool _isFullscreen; // 0x24
		bool _filterEnabled; // 0x25
		bool field6_0x26; // 0x26
		bool field7_0x27; // 0x27
		float _gamma; // 0x28
		float _exposure; // 0x2c
		float _brightness; // 0x30
		float _contrast; // 0x34
		bool _controlHotplugEnabled; // 0x38
		bool _popupsEnabled; // 0x39
		bool _enableFoundHUD; // 0x3a
		bool field15_0x3b; // 0x3b
		int _cameraStyle; // 0x3c
		int _historyHudMode; // 0x40
		float _hudOffset; // 0x44
		bool _tryImportSave; // 0x48
		bool _enableMods; // 0x49
		bool _enableRumble; // 0x4a
		bool _enableChargeBars; // 0x4b
		bool _enableBulletVisibility; // 0x4c
		bool _enableAimLock; // 0x4d
		bool field25_0x4e; // 0x4e
		bool field26_0x4f; // 0x4f
		int _touchMode; // 0x50
		bool _enableDebugConsole; // 0x54
		bool _enableVSync; // 0x55
		bool _enableSteamCloud; // 0x56
		bool _enablePauseOnFocusLost; // 0x57
		bool _enableMouseControl; // 0x58
		bool field33_0x59; // 0x59
		bool field34_0x5a; // 0x5a
		bool field35_0x5b; // 0x5b
		int _maxScale; // 0x5c
		int _maxRenderScale; // 0x60
		int _windowWidth; // 0x64
		int _windowHeight; // 0x68
		int _windowPosX; // 0x6c
		int _windowPosY; // 0x70
		int _consoleFont; // 0x74
		bool _enableFadedConsoleDisplay; // 0x78
		bool _enableSaveCommandHistory; // 0x79
		bool _enableBorderlessFullscreen; // 0x7a
		bool _enableInterpolation; // 0x7b
		bool _enableColorCorrection; // 0x7c
		bool _enableLighting; // 0x7d
		bool _enableShockwave; // 0x7e
		bool _enableCaustics; // 0x7f
		bool _enableFilter; // 0x80
		bool _enablePixelation; // 0x81
		bool _enableBloom; // 0x82
		bool _enableWaterSurface; // 0x83
		bool _getsSetToEnableWaterSurface; // 0x84
		bool _enableColorModifier; // 0x85
		bool _bossHpOnBottom; // 0x86
		bool field58_0x87; // 0x87
		int _announcerVoiceMode; // 0x88
		char pad0[0x1]; // 0x8c
	}; // 0x8d

	//可能的文件管理器类
	struct FileManager
	{
		union
		{
			FIELD(0x4C, uint8_t, achievements[638]);
			FIELD(0x31C, int32_t, donationCount);
			FIELD(0x320, uint32_t, edenTokens);
			FIELD(0x498, int32_t, greedDonationCount);
			FIELD(0x29DF8, Options, options);
			FIELD(0x29FD8, ModManager, modManager);
		};
	};

	//主菜单
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

	// 被动道具类，未研究完毕
	struct Passive
	{
		uint32_t pickTime;
		char name_guess[4];
		int32_t item;
		uint32_t pickStage;
		uint32_t pickStageVariat;
		uint32_t pickRoomType;
		uint32_t itemPool;
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
		gnucompat::vector<GlitchedEvent*> glitchedEvents;
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
			FIELD(0x3C, gnucompat::string, consoleText);
		};
	};

	// 角色类
	struct Player
	{
		union
		{
			FIELD(0x132C, Weapon*, weapon);
			FIELD(0x14C4, Active, actives[4]);
			FIELD(0x1745, uint8_t, canShoot);
			FIELD(0x1D0C, gnucompat::vector<Passive>, passives);
		};
	};

	// 游戏类
	struct Game
	{
		union
		{
			FIELD(0x1BA50, gnucompat::vector<Player*>, players);
			FIELD(0x1BB04, Seeds, seeds);
			FIELD(0x1BB60, Console, console);
			FIELD(0x10203C, PauseMenu, pauseMenu);
			FIELD(0x1C3164, uint32_t, debugFlag);
			FIELD(0x283C20, gnucompat::vector<GlitchedItem*>, glitchedItems);
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
			FIELD(0x7FD674, LuaVM*, luaVM);
			FIELD(0x7FD680, FileManager*, fileManager);
			FIELD(0x7FD688, MainMenu*, mainMenu);
		};
	};
}
