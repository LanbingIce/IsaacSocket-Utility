#pragma once

#include "pch.h"
#include "module.hpp"
#include "isaac.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "utils.hpp"

using isaac::lua_State;

namespace isaac_ {

	static int Options__index(lua_State* L) {
		METATABLE_BEGIN(isaac::Options, local.isaac->manager->options);

		METATABLE_INDEX(integer, AnnouncerVoiceMode, int);
		METATABLE_INDEX(boolean, BulletVisibility, bool);
		METATABLE_INDEX(integer, CameraStyle, int);
		METATABLE_INDEX(boolean, ChargeBars, bool);
		METATABLE_INDEX(integer, ConsoleFont, int);
		METATABLE_INDEX(boolean, DebugConsoleEnabled, bool);
		METATABLE_INDEX(boolean, DisplayPopups, bool);
		METATABLE_INDEX(integer, ExtraHUDStyle, int);
		METATABLE_INDEX(boolean, FadedConsoleDisplay, bool);
		METATABLE_INDEX(boolean, Filter, bool);
		METATABLE_INDEX(boolean, FoundHUD, bool);
		METATABLE_INDEX(boolean, Fullscreen, bool);
		METATABLE_INDEX(number, Gamma, float);
		METATABLE_INDEX(number, HUDOffset, float);
		//_(string, Language, const char*);这个项目不在这个类里
		METATABLE_INDEX(number, MapOpacity, float);
		METATABLE_INDEX(integer, MaxRenderScale, int);
		METATABLE_INDEX(integer, MaxScale, int);
		METATABLE_INDEX(boolean, MouseControl, bool);
		METATABLE_INDEX(number, MusicVolume, float);
		METATABLE_INDEX(boolean, PauseOnFocusLost, bool);
		METATABLE_INDEX(boolean, RumbleEnabled, bool);
		METATABLE_INDEX(boolean, SaveCommandHistory, bool);
		METATABLE_INDEX(number, SFXVolume, float);
		METATABLE_INDEX(boolean, UseBorderlessFullscreen, bool);
		METATABLE_INDEX(boolean, VSync, bool);
		//以上是官方API现有的项目
		METATABLE_INDEX(integer, TouchMode, int);
		METATABLE_END();
	}

	static void Init() {

		MODULE_BEGIN(Isaac);
		MODULE_UDATA(Options);
		MODULE_END();
	}
}
