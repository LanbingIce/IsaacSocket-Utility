#pragma once

#include "lua.hpp"
#include "utils.hpp"

using utils::cw;

#define CHECK_GL(x) \
do { \
    (x); \
   opengl_check_error(__FILE__, __LINE__, #x); \
} while (0)


namespace opengl
{

static void clear_gl_error() { while (glad_glGetError() != GL_NO_ERROR); }

static const char* opengl_errno_name(GLenum err) {
    switch (err) {
#define PER_GL_ERROR(x) case GL_##x: return #x;
        PER_GL_ERROR(NO_ERROR)
        PER_GL_ERROR(INVALID_ENUM)
        PER_GL_ERROR(INVALID_VALUE)
        PER_GL_ERROR(INVALID_OPERATION)
        PER_GL_ERROR(STACK_OVERFLOW)
        PER_GL_ERROR(STACK_UNDERFLOW)
        PER_GL_ERROR(OUT_OF_MEMORY)
        #undef PER_GL_ERROR
    }
    return "unknown error";
}
static	void opengl_check_error(const char* filename, int lineno, const char* expr) {
    GLenum err = glad_glGetError();
    if (err != GL_NO_ERROR) {
        AllocConsole();
        cw(filename, ":", lineno, ": ", expr, " failed: ", opengl_errno_name(err));
        system("pause");
        std::terminate();
    }
}

static int PutPixel(lua_State* L) {
    ARG_DEF(1, integer, uint32_t, x, 0);
    ARG_DEF(2, integer, uint32_t, y, 0);
    ARG_DEF(3, integer, uint32_t, rgba, 0);

    // 直接提取RGBA分量
    float r = ((rgba >> 24) & 0xFF) / 255.0f;
    float g = ((rgba >> 16) & 0xFF) / 255.0f;
    float b = ((rgba >> 8) & 0xFF) / 255.0f;
    float a = (rgba & 0xFF) / 255.0f;
    clear_gl_error();
    glUseProgram(0);
    glBegin(GL_POINTS);
    glColor4f(r, g, b, a);
    uint32_t width = local.isaac->window->width;
    uint32_t height = local.isaac->window->height;

    glVertex3f((x + 0.5f) / width * 2.0f - 1.0f, (y + 0.5f) / height * 2.0f - 1.0f, 1.0);

    CHECK_GL(glEnd());

    return 0;
}

static void Init() {
    lua_State* L = local.isaac->luaVM->L;
    size_t top = local.lua->lua_gettop(L);
    local.lua->lua_getglobal(L, "_ISAAC_SOCKET");
    local.lua->lua_pushstring(L, "IsaacSocket");
    local.lua->lua_gettable(L, -2);
    local.lua->lua_pushstring(L, "OpenGL");
    local.lua->lua_newtable(L);

#define _(name) local.lua->lua_pushstring(L, #name);local.lua->lua_pushcfunction(L, name); local.lua->lua_settable(L, -3)

    _(PutPixel);

    #undef _

    local.lua->lua_settable(L, -3);
    local.lua->lua_settop(L, top);
}

}
