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
    if (err != GL_NO_ERROR) [[unlikely]] {
        AllocConsole();
        cw(filename, ":", lineno, ": ", expr, " failed: ", opengl_errno_name(err));
        system("pause");
        std::terminate();
    }
}

static void gl_clean_state() {
    clear_gl_error();
    glUseProgram(0);
}

static void gl_set_border(uint32_t border, const char *stipple = nullptr) {
    // border=0: fill, border>0: stroke
    if (border) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(border);
        if (stipple) {
            GLushort c = 0;
            GLint factor = border;
            for (size_t i = 0; stipple[i] && i < 16; i++) {
                c |= (stipple[i] & 1) << i; // '0' = 48, '1' = 49
            }
            glLineStipple(factor, c);
        }
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (stipple) {
            uint32_t c[32]{};
            for (size_t i = 0; stipple[i] && i < 32 * 32; i++) {
                c[i >> 5] |= (stipple[i] & 1) << (i & 31);
            }
            glPolygonStipple((const GLubyte *)c);
        }
    }
}

static void gl_put_vertex(uint32_t x, uint32_t y) {
    uint32_t width = local.isaac->window->width;
    uint32_t height = local.isaac->window->height;
    glVertex3f((x + 0.5f) / width * 2.0f - 1.0f, (y + 0.5f) / height * 2.0f - 1.0f, 1.0);
}

static void gl_set_color(uint32_t rgba) {
    // 直接提取RGBA分量
    float r = ((rgba >> 24) & 0xFF) / 255.0f;
    float g = ((rgba >> 16) & 0xFF) / 255.0f;
    float b = ((rgba >> 8) & 0xFF) / 255.0f;
    float a = (rgba & 0xFF) / 255.0f;
    glColor4f(r, g, b, a);
}

static int PutPixel(lua_State* L) {
    ARG_DEF(1, integer, uint32_t, x, 0);
    ARG_DEF(2, integer, uint32_t, y, 0);
    ARG_DEF(3, integer, uint32_t, color, 0xFFFFFFFF);

    gl_clean_state();
    gl_set_color(color);
    glBegin(GL_POINTS);
    gl_put_vertex(x, y);
    CHECK_GL(glEnd());

    return 0;
}

static int DrawTriangle(lua_State* L) {
    ARG_DEF(1, integer, uint32_t, x1, 0);
    ARG_DEF(2, integer, uint32_t, y1, 0);
    ARG_DEF(2, integer, uint32_t, x2, 0);
    ARG_DEF(2, integer, uint32_t, y2, 0);
    ARG_DEF(2, integer, uint32_t, x3, 0);
    ARG_DEF(2, integer, uint32_t, y3, 0);
    ARG_DEF(3, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(3, integer, uint32_t, border, 0);
    ARG_DEF(3, string, const char *, stipple, nullptr);

    gl_clean_state();
    gl_set_border(border, stipple);
    gl_set_color(color);
    glBegin(GL_TRIANGLES);
    gl_put_vertex(x1, y1);
    gl_put_vertex(x2, y2);
    gl_put_vertex(x3, y3);
    CHECK_GL(glEnd());

    return 0;
}

static int DrawRect(lua_State* L) {
    ARG_DEF(1, integer, uint32_t, x1, 0);
    ARG_DEF(2, integer, uint32_t, y1, 0);
    ARG_DEF(2, integer, uint32_t, x2, 0);
    ARG_DEF(2, integer, uint32_t, y2, 0);
    ARG_DEF(3, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(3, integer, uint32_t, border, 0);
    ARG_DEF(3, string, const char *, stipple, nullptr);

    /* // 保证 x1 <= x2, y1 <= y2 */
    /* std::tie(x1, x2) = std::minmax(x1, x2); */
    /* std::tie(y1, y2) = std::minmax(y1, y2); */

    gl_clean_state();
    gl_set_border(border, stipple);
    gl_set_color(color);
    glBegin(GL_POLYGON);
    gl_put_vertex(x1, y1);
    gl_put_vertex(x1, y2);
    gl_put_vertex(x2, y2);
    gl_put_vertex(x2, y1);
    CHECK_GL(glEnd());

    return 0;
}

static void Init() {
    lua_State* L = local.isaac->luaVM->L;
    size_t top = local.lua.lua_gettop(L);
    local.lua.lua_getglobal(L, "_ISAAC_SOCKET");
    local.lua.lua_pushstring(L, "IsaacSocket");
    local.lua.lua_gettable(L, -2);
    local.lua.lua_pushstring(L, "OpenGL");
    local.lua.lua_newtable(L);

#define _(name) local.lua.lua_pushstring(L, #name);local.lua.lua_pushcfunction(L, name); local.lua.lua_settable(L, -3)

    _(PutPixel);

    #undef _

    local.lua.lua_settable(L, -3);
    local.lua.lua_settop(L, top);
}

}
