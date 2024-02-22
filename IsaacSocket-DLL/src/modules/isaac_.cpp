#pragma once

#include "pch.h"
#include "module.hpp"
#include "isaac.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "utils.hpp"

using isaac::lua_State;

namespace isaac_ {

	static int p_Options__index(lua_State* L) {

		ARG_UDATA(1, p_Options, ::isaac::Options**, pp_options);
		METATABLE_BEGIN(isaac::Options, **pp_options);

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
		METATABLE_INDEX_STRING(OptionsIniFilePath);
		METATABLE_INDEX(boolean, FilterEnabled, bool);
		METATABLE_INDEX(boolean, field6_0x26, bool);
		METATABLE_INDEX(boolean, field7_0x27, bool);
		METATABLE_INDEX(number, Exposure, float);
		METATABLE_INDEX(number, Brightness, float);
		METATABLE_INDEX(number, Contrast, float);
		METATABLE_INDEX(boolean, ControlHotplugEnabled, bool);
		METATABLE_INDEX(boolean, field15_0x3b, bool);
		METATABLE_INDEX(boolean, TryImportSave, bool);
		METATABLE_INDEX(boolean, EnableMods, bool);
		METATABLE_INDEX(boolean, EnableAimLock, bool);
		METATABLE_INDEX(boolean, field25_0x4e, bool);
		METATABLE_INDEX(boolean, field26_0x4f, bool);
		METATABLE_INDEX(integer, TouchMode, int);
		METATABLE_INDEX(boolean, EnableSteamCloud, bool);
		METATABLE_INDEX(boolean, field33_0x59, bool);
		METATABLE_INDEX(boolean, field34_0x5a, bool);
		METATABLE_INDEX(boolean, field35_0x5b, bool);
		METATABLE_INDEX(integer, WindowWidth, int);
		METATABLE_INDEX(integer, WindowHeight, int);
		METATABLE_INDEX(integer, WindowPosX, int);
		METATABLE_INDEX(integer, WindowPosY, int);
		METATABLE_INDEX(boolean, EnableInterpolation, bool);
		METATABLE_INDEX(boolean, EnableColorCorrection, bool);
		METATABLE_INDEX(boolean, EnableLighting, bool);
		METATABLE_INDEX(boolean, EnableShockwave, bool);
		METATABLE_INDEX(boolean, EnableCaustics, bool);
		METATABLE_INDEX(boolean, EnablePixelation, bool);
		METATABLE_INDEX(boolean, EnableBloom, bool);
		METATABLE_INDEX(boolean, EnableWaterSurface, bool);
		METATABLE_INDEX(boolean, GetsSetToEnableWaterSurface, bool);
		METATABLE_INDEX(boolean, EnableColorModifier, bool);
		METATABLE_INDEX(boolean, BossHpOnBottom, bool);
		METATABLE_INDEX(boolean, field58_0x87, bool);

		METATABLE_END();
	}

	static void Init() {

		MODULE_BEGIN(Isaac);
		MODULE_UDATA(Options, isaac::Options, local.isaac->manager->options);
		MODULE_END();
	}
}
