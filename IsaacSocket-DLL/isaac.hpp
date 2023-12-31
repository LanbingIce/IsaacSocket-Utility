#pragma once
#include "pch.h"
#include "utils.hpp"
#include "gnucompat.hpp"

namespace isaac {

	struct lua_State;

	//Lua虚拟机类
	struct LuaVM
	{
		char pad_0x18[0x18];
		lua_State* L;
		bool luaDebug;
	};

	//可能的Mod管理器类，还未研究完毕
	struct ModManager {};

	//可能的文件管理器类
	struct FileManager
	{
		union
		{
			FIELD(0x4C, uint8_t, achievements[638]);
			FIELD(0x31C, int32_t, donationMachine);
			FIELD(0x320, uint32_t, edenTokens);
			FIELD(0x498, int32_t, greedDonationMachine);
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

#pragma warning(disable: 4624)//禁用警告C4624: 已将析构函数隐式定义为“已删除”

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
			FIELD(0x7C7B08, _GLFWwindow*, window);
			FIELD(0x7FD65C, Game*, game);
			FIELD(0x7FD674, LuaVM*, luaVM);
			FIELD(0x7FD680, FileManager*, fileManager);
			FIELD(0x7FD688, MainMenu*, mainMenu);
		};
	};
}
