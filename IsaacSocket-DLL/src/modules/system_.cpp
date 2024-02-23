#include "module.hpp"

namespace system_
{

	//系统控制台输出
	static int ConsoleOutput(lua_State* L) {
		if (GetConsoleWindow())
		{
			ARG(1, string, const char*, text);
			utils::Utf8Cprintf(text);
		}
		return 0;
	}

	// 获取剪贴板
	static int GetClipboard(lua_State* L) {
		RET(string, ImGui::GetClipboardText());
	}

	// 设置剪贴板
	static int SetClipboard(lua_State* L) {
		ARG_DEF(1, string, const char*, text, "");
		ImGui::SetClipboardText(text);
		return 0;
	}

	static RegisterModule Init = [] {
		MODULE_BEGIN(System);
		MODULE_FUNC(ConsoleOutput);
		MODULE_FUNC(GetClipboard);
		MODULE_FUNC(SetClipboard);
		MODULE_END();
		};
};
