﻿#include "pch.h"
#include "module.hpp"
#include "isaac.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "function.hpp"

using isaac::lua_State;

namespace isaac_api {

	static int HistoryItem__index(lua_State* L) {
		ARG_UDATA(1, isaac::HistoryItem, item);
		METATABLE_BEGIN(isaac::HistoryItem, item);
		METATABLE_INDEX(integer, time);
		METATABLE_INDEX(boolean, isTrinket);
		METATABLE_INDEX(integer, id);
		METATABLE_INDEX(integer, levelStage);
		METATABLE_INDEX(integer, stageType);
		METATABLE_INDEX(integer, roomType);
		METATABLE_INDEX(integer, itemPoolType);
		METATABLE_END();
	}

	static int HistoryItem__newindex(lua_State* L) {
		ARG_UDATA(1, isaac::HistoryItem, item);
		METATABLE_BEGIN(isaac::HistoryItem, item);
		METATABLE_END();
	}


	//是否强制暂停
	static int IsForcePaused(lua_State* L) {
		RET(boolean, local.isaac->game->console.state < 0);
	}

	//强制暂停
	//正常状态下减5即可变成强制暂停状态
	static int ForcePause(lua_State* L) {
		ARG_DEF(1, boolean, bool, pause, true);
		int32_t& state = local.isaac->game->console.state;
		state += state < 0 ? 5 : 0;
		state -= pause ? 5 : 0;
		return 0;
	}

	//重新加载lua
	static int ReloadLua(lua_State* L) {
		ARG_DEF(1, boolean, bool, luaDebug, local.isaac->luaEngine->luaDebug);
		local.isaac->luaEngine->luaDebug = luaDebug;
		local.needReload = true;
		return 0;
	}

	//获取debug标志
	static int GetDebugFlag(lua_State* L) {
		RET(integer, local.isaac->game->debugFlag);
	}

	//获取控制台的输入文本
	static int GetConsoleInput(lua_State* L) {
		RET(string, local.isaac->game->console.consoleText.c_str());
	}

	//控制台是否打开
	static int IsConsoleOpen(lua_State* L) {
		RET(boolean, local.isaac->game->console.state != 0 && local.isaac->game->console.state != -5);
	}

	//设置能否射击
	static int SetCanShoot(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, local.isaac->game->players.size());
		ARG_DEF(2, boolean, bool, canShoot, true);
		local.isaac->game->players[playerId]->canShoot = canShoot;
		return 0;
	}

	//获取主动
	static int GetActive(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, local.isaac->game->players.size());
		ARG_DEF(2, integer, uint32_t, activeId, 0);
		ARG_RANGE(activeId, 4);

		local.lua.lua_newtable(L);
#define _(type,name) local.lua.lua_pushstring(L,#name); local.lua.lua_push##type(L, local.isaac->game->players[playerId]->actives[activeId].name); local.lua.lua_settable(L, -3)
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
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, local.isaac->game->players.size());
		ARG_DEF(2, integer, uint32_t, activeId, 0);
		ARG_RANGE(activeId, 4);
		if (!local.lua.lua_istable(L, 3))
		{
			return local.lua.luaL_error(L, "bad argument #3 :active should be table");
		}
#define _(luaType,type,name) local.lua.lua_pushstring(L, #name); local.lua.lua_gettable(L, 3); if (local.lua.lua_is##luaType(L, -1)){local.isaac->game->players[playerId]->actives[activeId].name = (type)local.lua.lua_to##luaType(L, -1);}
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
		int32_t& state = local.isaac->game->pauseMenu.state;
		state = std::abs(state);
		state = hide ? -state : state;
		return 0;
	}

	//是否强制隐藏菜单
	static int IsPauseMenuForceHidden(lua_State* L) {
		RET(boolean, local.isaac->game->pauseMenu.state < 0);
	}

	//获取错误道具触发器
	static int GetGlitchedItemTrigger(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, itemId, 0);
		ARG_RANGE(itemId, local.isaac->game->glitchedItems.size());
		ARG_DEF(2, integer, uint32_t, eventId, 0);
		ARG_RANGE(eventId, local.isaac->game->glitchedItems[itemId]->glitchedEvents.size());
		RET(integer, local.isaac->game->glitchedItems[itemId]->glitchedEvents[eventId]->trigger);
	}

	//获取错误道具效果
	static int GetGlitchedItemEffect(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, itemId, 0);
		ARG_RANGE(itemId, local.isaac->game->glitchedItems.size());
		ARG_DEF(2, integer, uint32_t, eventId, 0);
		ARG_RANGE(eventId, local.isaac->game->glitchedItems[itemId]->glitchedEvents.size());
		RET(integer, local.isaac->game->glitchedItems[itemId]->glitchedEvents[eventId]->trigger);
	}

	//解锁成就
	static int UnlockAchievement(lua_State* L) {
		ARG(1, integer, uint32_t, achievementId);
		ARG_RANGE(achievementId, std::size(local.isaac->manager->persistentGameData.achievements));
		ARG_DEF(2, boolean, bool, unlock, true);
		if (achievementId == 0)
		{
			for (size_t i = 1; i < std::size(local.isaac->manager->persistentGameData.achievements); i++)
			{
				local.isaac->manager->persistentGameData.achievements[i] = unlock;
			}
		}
		else
		{
			local.isaac->manager->persistentGameData.achievements[achievementId] = unlock;
		}
		return 0;
	}

	//成就是否已解锁
	static int IsAchievementUnlocked(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, achievementId, 0);
		ARG_RANGE(achievementId, std::size(local.isaac->manager->persistentGameData.achievements));
		if (achievementId == 0)
		{
			for (size_t i = 1; i < std::size(local.isaac->manager->persistentGameData.achievements); i++)
			{
				if (!local.isaac->manager->persistentGameData.achievements[i])
				{
					RET(boolean, false);
				}
			}
			RET(boolean, true);
		}
		RET(boolean, local.isaac->manager->persistentGameData.achievements[achievementId]);
	}

	//获取伊甸币
	static int GetEdenTokens(lua_State* L) {
		RET(integer, local.isaac->manager->persistentGameData.edenTokens);
	}

	//设置伊甸币
	static int SetEdenTokens(lua_State* L) {
		ARG(1, integer, uint32_t, tokens);
		local.isaac->manager->persistentGameData.edenTokens = tokens;
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
		RET(number, local.isaac->FrameInterval);
	}

	//设置帧间隔
	static int SetFrameInterval(lua_State* L) {
		ARG_DEF(1, number, double, interval, 1.0 / 60);
		VAR_WRITE(local.isaac->FrameInterval, interval);
		return 0;
	}

	//获取捐款机计数
	static int GetDonationCount(lua_State* L) {
		RET(integer, local.isaac->manager->persistentGameData.donationCount);
	}

	//设置捐款机计数
	static int SetDonationCount(lua_State* L) {
		ARG(1, integer, int32_t, count);
		local.isaac->manager->persistentGameData.donationCount = count;
		return 0;
	}

	//获取贪婪捐款机计数
	static int GetGreedDonationCount(lua_State* L) {
		RET(integer, local.isaac->manager->persistentGameData.greedDonationCount);
	}

	//设置贪婪捐款机计数
	static int SetGreedDonationCount(lua_State* L) {
		ARG(1, integer, int32_t, count);
		local.isaac->manager->persistentGameData.greedDonationCount = count;
		return 0;
	}

	//获取被动道具列表
	static int GetHistoryItems(lua_State* L) {
		ARG_DEF(1, integer, uint32_t, playerId, 0);
		ARG_RANGE(playerId, local.isaac->game->players.size());

		vector<isaac::HistoryItem>& historyItems = local.isaac->game->players[playerId]->history.historyItems;

		RET_TABLE();

		for (size_t i = 0; i < historyItems.size(); i++) {
			local.lua.lua_pushinteger(L, (LUA_INTEGER)(i + 1));

			NEW_UDATA(isaac::HistoryItem, item, HistoryItem);
			item = historyItems[i];
			local.lua.lua_settable(L, -3);
		}

		RET_TABLE_END();
	}

	//获取FPS
	static int GetFPS(lua_State* L) {
		RET(number, ImGui::GetIO().Framerate);
	}

	//控制台输出
	static int ConsoleOutput(lua_State* L) {
		const char* text;
		size_t len;
		if (local.lua.lua_isstring(L, 1)) {
			text = local.lua.lua_tolstring(L, 1, &len);
		}
		else {
			return local.lua.luaL_error(L, "bad argument #1: text should be string");
		}
		ARG_DEF(2, integer, uint32_t, color, 0xFFD3D3D3);
		string str = string(text, len);
		function::ConsoleOutput(str, color);
		return 0;
	}

	static RegisterModule Init = [] {
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

		MODULE_END();
		};
}
