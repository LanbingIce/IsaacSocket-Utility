﻿#include "pch.h"
#include "module.hpp"
#include "isaac_image.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "isaac_socket.hpp"
#include "udata.hpp"

namespace isaac_api {
	//是否强制暂停
	static int IsForcePaused(lua_State* L) {
		RET(boolean, isaac.game->console.state < 0);
	}

	//强制暂停
	//正常状态下减5即可变成强制暂停状态
	static int ForcePause(lua_State* L) {
		ARG_DEF(1, boolean, bool, pause, true);
		int32_t& state = isaac.game->console.state;
		state += state < 0 ? 5 : 0;
		state -= pause ? 5 : 0;
		return 0;
	}

	//重新加载lua
	static int ReloadLua(lua_State* L) {
		ARG_DEF(1, boolean, bool, luaDebug, isaac.luaEngine->luaDebug);
		ARG_DEF(2, boolean, bool, exitGame, true);
		isaac.luaEngine->luaDebug = luaDebug;
		local.connectionState = state::RELOAD_LUA;
		local.reloadLuaState = exitGame ? state::EXIT : state::RELOAD;
		return 0;
	}

	//获取debug标志
	static int GetDebugFlag(lua_State* L) {
		RET(integer, isaac.game->debugFlag);
	}

	//获取控制台的输入文本
	static int GetConsoleInput(lua_State* L) {
		RET(string, isaac.game->console.consoleText.c_str());
	}

	//控制台是否打开
	static int IsConsoleOpen(lua_State* L) {
		RET(boolean, isaac.game->console.state != 0 && isaac.game->console.state != -5);
	}

	//设置能否射击
	static int SetCanShoot(lua_State* L) {
		CHECK_PLAYERS();
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, 0, isaac.game->players.size() - 1);
		ARG_DEF(2, boolean, bool, canShoot, true);
		isaac.game->players[playerId]->canShoot = canShoot;
		return 0;
	}

	//获取主动
	static int GetActive(lua_State* L) {
		CHECK_PLAYERS();
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, 0, isaac.game->players.size() - 1);
		ARG_DEF(2, integer, uint32_t, activeId, 0);
		ARG_RANGE(activeId, 0, 3);

		lua_newtable(L);
#define _(type,name) lua_pushstring(L,#name); lua_push##type(L, isaac.game->players[playerId]->actives[activeId].name); lua_settable(L, -3)
		_(integer, item);
		_(integer, charge);
		_(integer, batteryCharge);
		_(integer, subCharge);
		_(integer, timedRechargeCooldown);
		_(number, partialCharge);
		_(integer, varData);
#undef _
		return 1;
	}

	//设置主动
	static int SetActive(lua_State* L) {
		CHECK_PLAYERS();
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, 0, isaac.game->players.size() - 1);
		ARG_DEF(2, integer, uint32_t, activeId, 0);
		ARG_RANGE(activeId, 0, 3);
		if (!lua_istable(L, 3))
		{
			return luaL_error(L, "bad argument #3 :active should be table");
		}
#define _(luaType,type,name) lua_pushstring(L, #name); lua_gettable(L, 3); if (lua_is##luaType(L, -1)){isaac.game->players[playerId]->actives[activeId].name = (type)lua_to##luaType(L, -1);}
		_(integer, int32_t, item);
		_(integer, int32_t, charge);
		_(integer, int32_t, batteryCharge);
		_(integer, int32_t, subCharge);
		_(integer, int32_t, timedRechargeCooldown);
		_(number, float, partialCharge);
		_(integer, int32_t, varData);
#undef _
		return 0;
	}

	//强制隐藏暂停菜单
	static int ForceHidePauseMenu(lua_State* L) {
		ARG_DEF(1, boolean, bool, hide, true);
		int32_t& state = isaac.game->pauseMenu.state;
		state = std::abs(state);
		state = hide ? -state : state;
		return 0;
	}

	//是否强制隐藏菜单
	static int IsPauseMenuForceHidden(lua_State* L) {
		RET(boolean, isaac.game->pauseMenu.state < 0);
	}

	//获取错误道具触发器
	static int GetGlitchedItemTrigger(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, itemId, 0);
		ARG_RANGE(itemId, 0, isaac.game->glitchedItems.size() - 1);
		ARG_DEF(2, integer, uint32_t, eventId, 0);
		ARG_RANGE(eventId, 0, isaac.game->glitchedItems[itemId]->glitchedEvents.size() - 1);
		RET(integer, isaac.game->glitchedItems[itemId]->glitchedEvents[eventId]->trigger);
	}

	//获取错误道具效果
	static int GetGlitchedItemEffect(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, itemId, 0);
		ARG_RANGE(itemId, 0, isaac.game->glitchedItems.size() - 1);
		ARG_DEF(2, integer, uint32_t, eventId, 0);
		ARG_RANGE(eventId, 0, isaac.game->glitchedItems[itemId]->glitchedEvents.size() - 1);
		RET(integer, isaac.game->glitchedItems[itemId]->glitchedEvents[eventId]->trigger);
	}

	//解锁成就
	static int UnlockAchievement(lua_State* L) {
		ARG(1, integer, uint32_t, achievementId);
		ARG_RANGE(achievementId, 0, std::size(isaac.manager->persistentGameData.achievements) - 1);
		ARG_DEF(2, boolean, bool, unlock, true);
		if (achievementId == 0)
		{
			for (size_t i = 1; i < std::size(isaac.manager->persistentGameData.achievements); i++)
			{
				isaac.manager->persistentGameData.achievements[i] = unlock;
			}
		}
		else
		{
			isaac.manager->persistentGameData.achievements[achievementId] = unlock;
		}
		return 0;
	}

	//成就是否已解锁
	static int IsAchievementUnlocked(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, achievementId, 0);
		ARG_RANGE(achievementId, 0, std::size(isaac.manager->persistentGameData.achievements) - 1);
		if (achievementId == 0)
		{
			for (size_t i = 1; i < std::size(isaac.manager->persistentGameData.achievements); i++)
			{
				if (!isaac.manager->persistentGameData.achievements[i])
				{
					RET(boolean, false);
				}
			}
			RET(boolean, true);
		}
		RET(boolean, isaac.manager->persistentGameData.achievements[achievementId]);
	}

	//获取伊甸币
	static int GetEdenTokens(lua_State* L) {
		RET(integer, isaac.manager->persistentGameData.edenTokens);
	}

	//设置伊甸币
	static int SetEdenTokens(lua_State* L) {
		ARG(1, integer, uint32_t, tokens);
		isaac.manager->persistentGameData.edenTokens = tokens;
		return 0;
	}

	//MT随机数是否被锁定
	static int IsMTRandomLocked(lua_State* L) {
		RET(boolean, local.MTRandomLockedValue);
	}

	//锁定MT随机数值
	static int LockMTRandom(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, value, 0);
		local.MTRandomLockedValue = value;
		return 0;
	}

	//获取帧间隔
	static int GetFrameInterval(lua_State* L) {
		RET(number, isaac.FrameInterval);
	}

	//设置帧间隔
	static int SetFrameInterval(lua_State* L) {
		ARG_DEF(1, number, double, interval, 1.0 / 60);
		VAR_WRITE(isaac.FrameInterval, interval);
		return 0;
	}

	//获取捐款机计数
	static int GetDonationCount(lua_State* L) {
		RET(integer, isaac.manager->persistentGameData.donationCount);
	}

	//设置捐款机计数
	static int SetDonationCount(lua_State* L) {
		ARG(1, integer, int32_t, count);
		isaac.manager->persistentGameData.donationCount = count;
		return 0;
	}

	//获取贪婪捐款机计数
	static int GetGreedDonationCount(lua_State* L) {
		RET(integer, isaac.manager->persistentGameData.greedDonationCount);
	}

	//设置贪婪捐款机计数
	static int SetGreedDonationCount(lua_State* L) {
		ARG(1, integer, int32_t, count);
		isaac.manager->persistentGameData.greedDonationCount = count;
		return 0;
	}

	//获取被动道具列表
	static int GetHistoryItems(lua_State* L) {
		CHECK_PLAYERS();
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, 0, isaac.game->players.size() - 1);

		vector<isaac_image::HistoryItem>& historyItems = isaac.game->players[playerId]->history.historyItems;

		RET_TABLE();

		for (size_t i = 0; i < historyItems.size(); i++) {
			lua_pushinteger(L, (LUA_INTEGER)(i + 1));

			auto& item = NEW_UDATA_META(isaac_image::HistoryItem, udata::HistoryItem);
			item = historyItems[i];
			lua_settable(L, -3);
		}

		RET_TABLE_END();
	}

	//获取FPS
	static int GetFPS(lua_State* L) {
		RET(number, ImGui::GetIO().Framerate);
	}

	//日志输出
	static int LogOutput(lua_State* L) {
		ARG(1, string, const char*, text);
		ARG_DEF(2, integer, int, type, 0);
		isaac_socket::LogOutput(text, type);
		return 0;
	}

	//控制台输出
	static int ConsoleOutput(lua_State* L) {
		ARG(1, string, const char*, text);
		ARG_DEF(2, integer, uint32_t, color, 0xFFD3D3D3);
		isaac_socket::ConsoleOutput(text, color);
		return 0;
	}

	static RegisterModule InitModules = [] {
		MODULE_BEGIN(IsaacAPI);

		MODULE_FUNC(IsForcePaused);
		MODULE_FUNC(ForcePause);

		MODULE_FUNC(ReloadLua);
		MODULE_FUNC(GetDebugFlag);

		MODULE_FUNC(GetConsoleInput);
		MODULE_FUNC(IsConsoleOpen);

		MODULE_FUNC(SetCanShoot);

		MODULE_FUNC(IsPauseMenuForceHidden);
		MODULE_FUNC(ForceHidePauseMenu);

		MODULE_FUNC(GetActive);
		MODULE_FUNC(SetActive);

		MODULE_FUNC(GetEdenTokens);
		MODULE_FUNC(SetEdenTokens);

		MODULE_FUNC(IsAchievementUnlocked);
		MODULE_FUNC(UnlockAchievement);

		MODULE_FUNC(IsMTRandomLocked);
		MODULE_FUNC(LockMTRandom);

		MODULE_FUNC(GetGlitchedItemTrigger);
		MODULE_FUNC(GetGlitchedItemEffect);

		MODULE_FUNC(GetFrameInterval);
		MODULE_FUNC(SetFrameInterval);

		MODULE_FUNC(GetDonationCount);
		MODULE_FUNC(SetDonationCount);

		MODULE_FUNC(GetGreedDonationCount);
		MODULE_FUNC(SetGreedDonationCount);

		MODULE_FUNC(GetHistoryItems);

		MODULE_FUNC(GetFPS);

		MODULE_FUNC(ConsoleOutput);
		MODULE_FUNC(LogOutput);

		MODULE_END();
		};
}
