#include "module.hpp"
#include "lua.hpp"
#include "imgui/imgui.h"
#include "udata.hpp"

int udata::LUA_WIN32_FIND_DATAW::lua_index(lua_State* L) {

    auto& data = ARG_UDATA(1, udata::LUA_WIN32_FIND_DATAW);
    METATABLE_BEGIN(WIN32_FIND_DATAW, (data).data);
    METATABLE_INDEX(stdwstring, cFileName);
    METATABLE_END();
}

int udata::LUA_WIN32_FIND_DATAW::lua_newindex(lua_State* L) {
    METATABLE_END();
}

namespace system_
{

    //系统控制台输出
    static int ConsoleOutput(lua_State* L) {
        if (GetConsoleWindow())
        {
            ARG(1, string, const char*, text);
            std::cout << text << std::flush;
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

    static RegisterModule InitModules = [] {
        MODULE_BEGIN(System);
        MODULE_FUNC(ConsoleOutput);
        MODULE_FUNC(GetClipboard);
        MODULE_FUNC(SetClipboard);
        MODULE_END();
        };
};
