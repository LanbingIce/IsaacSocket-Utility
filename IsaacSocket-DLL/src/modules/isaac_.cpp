#include "pch.h"
#include "module.hpp"
#include "isaac_image.hpp"
#include "lua.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "isaac_socket.hpp"
#include "udata.hpp"

int udata::p_Options::__index(lua_State* L) {
	auto& p_options = ARG_UDATA(1, ::isaac_image::Options*);
	METATABLE_BEGIN(isaac_image::Options, *p_options);

	METATABLE_INDEX(integer, AnnouncerVoiceMode);
	METATABLE_INDEX(boolean, BulletVisibility);
	METATABLE_INDEX(integer, CameraStyle);
	METATABLE_INDEX(boolean, ChargeBars);
	METATABLE_INDEX(integer, ConsoleFont);
	METATABLE_INDEX(boolean, DebugConsoleEnabled);
	METATABLE_INDEX(boolean, DisplayPopups);
	METATABLE_INDEX(integer, ExtraHUDStyle);
	METATABLE_INDEX(boolean, FadedConsoleDisplay);
	METATABLE_INDEX(boolean, Filter);
	METATABLE_INDEX(boolean, FoundHUD);
	METATABLE_INDEX(boolean, Fullscreen);
	METATABLE_INDEX(number, Gamma);
	METATABLE_INDEX(number, HUDOffset);
	// Language 不在这个类里
	METATABLE_INDEX(number, MapOpacity);
	METATABLE_INDEX(integer, MaxRenderScale);
	METATABLE_INDEX(integer, MaxScale);
	METATABLE_INDEX(boolean, MouseControl);
	METATABLE_INDEX(number, MusicVolume);
	METATABLE_INDEX(boolean, PauseOnFocusLost);
	METATABLE_INDEX(boolean, RumbleEnabled);
	METATABLE_INDEX(boolean, SaveCommandHistory);
	METATABLE_INDEX(number, SFXVolume);
	METATABLE_INDEX(boolean, UseBorderlessFullscreen);
	METATABLE_INDEX(boolean, VSync);

	// 以上是Options原有的成员

	//MusicEnabled 不在这个类里
	METATABLE_INDEX(number, Exposure);
	METATABLE_INDEX(number, Brightness);
	METATABLE_INDEX(number, Contrast);
	METATABLE_INDEX(boolean, ControllerHotplug);
	METATABLE_INDEX(boolean, TryImportSave);
	METATABLE_INDEX(boolean, EnableMods);
	METATABLE_INDEX(integer, TouchMode);
	METATABLE_INDEX(boolean, AimLock);
	METATABLE_INDEX(boolean, SteamCloud);
	METATABLE_INDEX(boolean, BossHpOnBottom);
	METATABLE_INDEX(integer, WindowWidth);
	METATABLE_INDEX(integer, WindowHeight);
	METATABLE_INDEX(integer, WindowPosX);
	METATABLE_INDEX(integer, WindowPosY);

	// 以上是剩余成员中，存在于Options.ini中的成员

	METATABLE_INDEX(boolean, EnableColorCorrection);
	METATABLE_INDEX(boolean, EnableCaustics);
	METATABLE_INDEX(boolean, EnableShockwave);
	METATABLE_INDEX(boolean, EnableLighting);
	METATABLE_INDEX(boolean, EnableFilter);
	METATABLE_INDEX(boolean, EnablePixelation);
	METATABLE_INDEX(boolean, EnableBloom);
	METATABLE_INDEX(boolean, EnableWaterSurface);
	METATABLE_INDEX(boolean, EnableInterpolation);
	METATABLE_INDEX(boolean, EnableColorModifier);

	// 以上是config.ini中的成员

	METATABLE_INDEX_STRING(OptionsIniFilePath);

	METATABLE_INDEX(boolean, EnableHeatWaves);

	METATABLE_END();
}

int udata::p_Options::__newindex(lua_State* L) {

	auto& p_options = ARG_UDATA(1, ::isaac_image::Options*);
	METATABLE_BEGIN(isaac_image::Options, *p_options);

	METATABLE_NEWINDEX(integer, AnnouncerVoiceMode);
	METATABLE_NEWINDEX(boolean, BulletVisibility);
	METATABLE_NEWINDEX(integer, CameraStyle);
	METATABLE_NEWINDEX(boolean, ChargeBars);
	METATABLE_NEWINDEX(integer, ConsoleFont);
	METATABLE_NEWINDEX(boolean, DebugConsoleEnabled);
	METATABLE_NEWINDEX(boolean, DisplayPopups);
	METATABLE_NEWINDEX(integer, ExtraHUDStyle);
	METATABLE_NEWINDEX(boolean, FadedConsoleDisplay);
	METATABLE_NEWINDEX(boolean, Filter);
	METATABLE_NEWINDEX(boolean, FoundHUD);
	METATABLE_NEWINDEX(boolean, Fullscreen, isaac_socket::FullScreen(_obj.Fullscreen));
	METATABLE_NEWINDEX(number, Gamma);
	METATABLE_NEWINDEX(number, HUDOffset);
	// Language 不在这个类里
	METATABLE_NEWINDEX(number, MapOpacity);
	METATABLE_NEWINDEX(integer, MaxRenderScale);
	METATABLE_NEWINDEX(integer, MaxScale);
	METATABLE_NEWINDEX(boolean, MouseControl);
	METATABLE_NEWINDEX(number, MusicVolume, isaac_socket::MusicVolume(_obj.MusicVolume));
	METATABLE_NEWINDEX(boolean, PauseOnFocusLost);
	METATABLE_NEWINDEX(boolean, RumbleEnabled);
	METATABLE_NEWINDEX(boolean, SaveCommandHistory);
	METATABLE_NEWINDEX(number, SFXVolume);
	METATABLE_NEWINDEX(boolean, UseBorderlessFullscreen);
	METATABLE_NEWINDEX(boolean, VSync, isaac_socket::VSync(_obj.VSync));

	// 以上是Options原有的成员

	//MusicEnabled 不在这个类里
	METATABLE_NEWINDEX(number, Exposure);
	METATABLE_NEWINDEX(number, Brightness);
	METATABLE_NEWINDEX(number, Contrast);
	METATABLE_NEWINDEX(boolean, ControllerHotplug);
	METATABLE_NEWINDEX(boolean, TryImportSave);
	METATABLE_NEWINDEX(boolean, EnableMods);
	METATABLE_NEWINDEX(integer, TouchMode);
	METATABLE_NEWINDEX(boolean, AimLock);
	METATABLE_NEWINDEX(boolean, SteamCloud);
	METATABLE_NEWINDEX(boolean, BossHpOnBottom);
	METATABLE_NEWINDEX(integer, WindowWidth, if (!_obj.Fullscreen)isaac_socket::FullScreen(false));
	METATABLE_NEWINDEX(integer, WindowHeight, if (!_obj.Fullscreen) isaac_socket::FullScreen(false));
	METATABLE_NEWINDEX(integer, WindowPosX, if (!_obj.Fullscreen) isaac_socket::FullScreen(false));
	METATABLE_NEWINDEX(integer, WindowPosY, if (!_obj.Fullscreen) isaac_socket::FullScreen(false));

	// 以上是剩余成员中，存在于Options.ini中的成员

	METATABLE_NEWINDEX(boolean, EnableColorCorrection);
	METATABLE_NEWINDEX(boolean, EnableCaustics);
	METATABLE_NEWINDEX(boolean, EnableShockwave);
	METATABLE_NEWINDEX(boolean, EnableLighting);
	METATABLE_NEWINDEX(boolean, EnableFilter);
	METATABLE_NEWINDEX(boolean, EnablePixelation);
	METATABLE_NEWINDEX(boolean, EnableBloom);
	METATABLE_NEWINDEX(boolean, EnableWaterSurface);
	METATABLE_NEWINDEX(boolean, EnableInterpolation);
	METATABLE_NEWINDEX(boolean, EnableColorModifier);
	METATABLE_NEWINDEX(boolean, EnableHeatWaves);		//这个成员在config.ini中与EnableWaterSurface共用一个项目

	// 以上是config.ini中的成员

	//METATABLE_NEWINDEX_STRING(OptionsIniFilePath);
	METATABLE_END();
}

namespace isaac_ {
	static RegisterModule InitModules = [] {
		MODULE_BEGIN(Isaac);
		MODULE_UDATA(Options, isaac_image::Options, isaac.manager->options);
		MODULE_END();
		};
}
