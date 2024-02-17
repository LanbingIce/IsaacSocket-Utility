#pragma once

#include "pch.h"
#include "module.hpp"
#include "isaac.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "utils.hpp"

using isaac::lua_State;

namespace isaac_ {

#define _(luaType,name)if(strcmp(key, #name) == 0){RET(luaType,local.isaac->manager->options.name);}
	static int OptionsGet(lua_State* L) {
		const char* key = local.lua.lua_tostring(L, 2);
		_(integer, AnnouncerVoiceMode);
		_(boolean, BulletVisibility);
		_(integer, CameraStyle);
		_(boolean, ChargeBars);
		_(integer, ConsoleFont);
		_(boolean, DebugConsoleEnabled);
		_(boolean, DisplayPopups);
		_(integer, ExtraHUDStyle);
		_(boolean, FadedConsoleDisplay);
		_(boolean, Filter);
		_(boolean, FoundHUD);
		_(boolean, Fullscreen);
		_(number, Gamma);
		_(number, HUDOffset);
		//_(string, Language);
		_(number, MapOpacity);
		_(integer, MaxRenderScale);
		_(integer, MaxScale);
		_(boolean, MouseControl);
		_(number, MusicVolume);
		_(boolean, PauseOnFocusLost);
		_(boolean, RumbleEnabled);
		_(boolean, SaveCommandHistory);
		_(number, SFXVolume);
		_(boolean, UseBorderlessFullscreen);
		_(boolean, VSync);


		_(integer, TouchMode);

		return local.lua.luaL_error(L, "Invalid member access.");
	}
#undef _
#define _(luaType,name,type)if(strcmp(key, #name) == 0){ARG(3, luaType, type, name);local.isaac->manager->options.name = name;return 0;}
	static int OptionsSet(lua_State* L) {
		const char* key = local.lua.lua_tostring(L, 2);

		_(integer, AnnouncerVoiceMode, int);
		_(boolean, BulletVisibility, bool);
		_(integer, CameraStyle, int);
		_(boolean, ChargeBars, bool);
		_(integer, ConsoleFont, int);
		_(boolean, DebugConsoleEnabled, bool);
		_(boolean, DisplayPopups, bool);
		_(integer, ExtraHUDStyle, int);
		_(boolean, FadedConsoleDisplay, bool);
		_(boolean, Filter, bool);
		_(boolean, FoundHUD, bool);
		_(boolean, Fullscreen, bool);
		_(number, Gamma, float);
		_(number, HUDOffset, float);
		//_(string, Language, const char*);
		_(number, MapOpacity, float);
		_(integer, MaxRenderScale, int);
		_(integer, MaxScale, int);
		_(boolean, MouseControl, bool);
		_(number, MusicVolume, float);
		_(boolean, PauseOnFocusLost, bool);
		_(boolean, RumbleEnabled, bool);
		_(boolean, SaveCommandHistory, bool);
		_(number, SFXVolume, float);
		_(boolean, UseBorderlessFullscreen, bool);
		_(boolean, VSync, bool);


		_(integer, TouchMode, int);
		return local.lua.luaL_error(L, "Invalid member access.");
	}
#undef _

#define MODULE_USERDATA(name)local.lua.lua_pushstring(L, #name);local.lua.lua_newuserdata(L, 0);local.lua.luaL_newmetatable(L, #name);luaL_Reg mt_##name[] = {{"__index", name##Get},{"__newindex", name##Set},{ NULL, NULL }};local.lua.luaL_setfuncs(L, mt_##name, 0);local.lua.lua_setmetatable(L, -2);local.lua.lua_settable(L, -3)

	static void Init() {

		DEFMOD(Isaac);
		MODULE_USERDATA(Options);
		ENDMOD();
	}
}
