#include "pch.h"
#include "module.hpp"
#include "isaac.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "function.hpp"

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
		// Language 不在这个类里
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

		// 以上是Options原有的成员

		//MusicEnabled 不在这个类里
		METATABLE_INDEX(number, Exposure, float);
		METATABLE_INDEX(number, Brightness, float);
		METATABLE_INDEX(number, Contrast, float);
		METATABLE_INDEX(boolean, ControllerHotplug, bool);
		METATABLE_INDEX(boolean, TryImportSave, bool);
		METATABLE_INDEX(boolean, EnableMods, bool);
		METATABLE_INDEX(integer, TouchMode, int);
		METATABLE_INDEX(boolean, AimLock, bool);
		METATABLE_INDEX(boolean, SteamCloud, bool);
		METATABLE_INDEX(boolean, BossHpOnBottom, bool);
		METATABLE_INDEX(integer, WindowWidth, int);
		METATABLE_INDEX(integer, WindowHeight, int);
		METATABLE_INDEX(integer, WindowPosX, int);
		METATABLE_INDEX(integer, WindowPosY, int);

		// 以上是剩余成员中，存在于Options.ini中的成员

		METATABLE_INDEX(boolean, EnableColorCorrection, bool);
		METATABLE_INDEX(boolean, EnableCaustics, bool);
		METATABLE_INDEX(boolean, EnableShockwave, bool);
		METATABLE_INDEX(boolean, EnableLighting, bool);
		METATABLE_INDEX(boolean, EnableFilter, bool);
		METATABLE_INDEX(boolean, EnablePixelation, bool);
		METATABLE_INDEX(boolean, EnableBloom, bool);
		METATABLE_INDEX(boolean, EnableWaterSurface, bool);
		METATABLE_INDEX(boolean, EnableInterpolation, bool);
		METATABLE_INDEX(boolean, EnableColorModifier, bool);

		// 以上是config.ini中的成员

		METATABLE_INDEX_STRING(OptionsIniFilePath);

		METATABLE_INDEX(boolean, EnableHeatWaves, bool);

		METATABLE_END();
	}

	static int p_Options__newindex(lua_State* L) {

		ARG_UDATA(1, p_Options, ::isaac::Options**, pp_options);
		METATABLE_BEGIN(isaac::Options, **pp_options);

		METATABLE_NEWINDEX(integer, AnnouncerVoiceMode, int);
		METATABLE_NEWINDEX(boolean, BulletVisibility, bool);
		METATABLE_NEWINDEX(integer, CameraStyle, int);
		METATABLE_NEWINDEX(boolean, ChargeBars, bool);
		METATABLE_NEWINDEX(integer, ConsoleFont, int);
		METATABLE_NEWINDEX(boolean, DebugConsoleEnabled, bool);
		METATABLE_NEWINDEX(boolean, DisplayPopups, bool);
		METATABLE_NEWINDEX(integer, ExtraHUDStyle, int);
		METATABLE_NEWINDEX(boolean, FadedConsoleDisplay, bool);
		METATABLE_NEWINDEX(boolean, Filter, bool);
		METATABLE_NEWINDEX(boolean, FoundHUD, bool);
		METATABLE_NEWINDEX(boolean, Fullscreen, bool, function::FullScreen(_obj.Fullscreen));
		METATABLE_NEWINDEX(number, Gamma, float);
		METATABLE_NEWINDEX(number, HUDOffset, float);
		// Language 不在这个类里
		METATABLE_NEWINDEX(number, MapOpacity, float);
		METATABLE_NEWINDEX(integer, MaxRenderScale, int);
		METATABLE_NEWINDEX(integer, MaxScale, int);
		METATABLE_NEWINDEX(boolean, MouseControl, bool);
		METATABLE_NEWINDEX(number, MusicVolume, float);
		METATABLE_NEWINDEX(boolean, PauseOnFocusLost, bool);
		METATABLE_NEWINDEX(boolean, RumbleEnabled, bool);
		METATABLE_NEWINDEX(boolean, SaveCommandHistory, bool);
		METATABLE_NEWINDEX(number, SFXVolume, float);
		METATABLE_NEWINDEX(boolean, UseBorderlessFullscreen, bool);
		METATABLE_NEWINDEX(boolean, VSync, bool);

		// 以上是Options原有的成员

		//MusicEnabled 不在这个类里
		METATABLE_NEWINDEX(number, Exposure, float);
		METATABLE_NEWINDEX(number, Brightness, float);
		METATABLE_NEWINDEX(number, Contrast, float);
		METATABLE_NEWINDEX(boolean, ControllerHotplug, bool);
		METATABLE_NEWINDEX(boolean, TryImportSave, bool);
		METATABLE_NEWINDEX(boolean, EnableMods, bool);
		METATABLE_NEWINDEX(integer, TouchMode, int);
		METATABLE_NEWINDEX(boolean, AimLock, bool);
		METATABLE_NEWINDEX(boolean, SteamCloud, bool);
		METATABLE_NEWINDEX(boolean, BossHpOnBottom, bool);
		METATABLE_NEWINDEX(integer, WindowWidth, int);
		METATABLE_NEWINDEX(integer, WindowHeight, int);
		METATABLE_NEWINDEX(integer, WindowPosX, int);
		METATABLE_NEWINDEX(integer, WindowPosY, int);

		// 以上是剩余成员中，存在于Options.ini中的成员

		METATABLE_NEWINDEX(boolean, EnableColorCorrection, bool);
		METATABLE_NEWINDEX(boolean, EnableCaustics, bool);
		METATABLE_NEWINDEX(boolean, EnableShockwave, bool);
		METATABLE_NEWINDEX(boolean, EnableLighting, bool);
		METATABLE_NEWINDEX(boolean, EnableFilter, bool);
		METATABLE_NEWINDEX(boolean, EnablePixelation, bool);
		METATABLE_NEWINDEX(boolean, EnableBloom, bool);
		METATABLE_NEWINDEX(boolean, EnableWaterSurface, bool);
		METATABLE_NEWINDEX(boolean, EnableInterpolation, bool);
		METATABLE_NEWINDEX(boolean, EnableColorModifier, bool);
		METATABLE_NEWINDEX(boolean, EnableHeatWaves, bool);		//这个成员在config.ini中与EnableWaterSurface共用一个项目

		// 以上是config.ini中的成员

		//METATABLE_NEWINDEX_STRING(OptionsIniFilePath);
		METATABLE_END();
	}

	static RegisterModule Init = [] {
		MODULE_BEGIN(Isaac);
		MODULE_UDATA(Options, isaac::Options, local.isaac->manager->options);
		MODULE_END();
		};
}
