#pragma once

#include "module.hpp"

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
static void opengl_check_error(const char* filename, int lineno, const char* expr) {
    GLenum err = glad_glGetError();
    if (err != GL_NO_ERROR) [[unlikely]] {
        if (!GetConsoleWindow()) AllocConsole();
        cw(filename, ":", lineno, ": ", expr, " failed: ", opengl_errno_name(err));
        /* system("pause"); */
        /* std::terminate(); */
    }
}

struct GLStateGuard {
    GLStateGuard() {
        clear_gl_error();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glUseProgram(0);
        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_GEQUAL);
        /* glEnable(GL_BLEND); */
        /* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); */
    }

    ~GLStateGuard() {
        glPopAttrib();
    }

    GLStateGuard(GLStateGuard &&) = delete;
};

static void gl_set_border(float border, const char *stipple = nullptr) {
    // border=0: fill, border>0: stroke
    if (border > 0) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(border);
        if (stipple) {
            GLushort c = 0;
            GLint factor = (int)std::ceil(border);
            for (size_t i = 0; stipple[i] && i < 16; i++) {
                c |= (GLushort)(stipple[i] & 1) << i; // '0' = 48, '1' = 49
            }
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(factor, c);
        }
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (stipple) {
            uint32_t c[32]{};
            for (size_t i = 0; stipple[i] && i < 32 * 32; i++) {
                c[i >> 5] |= (uint32_t)(stipple[i] & 1) << (i & 31);
            }
            glEnable(GL_POLYGON_STIPPLE);
            glPolygonStipple((const GLubyte *)c);
        }
    }
}

static void gl_put_vertex(float x, float y) {
    uint32_t width = local.isaac->window->width;
    uint32_t height = local.isaac->window->height;
    glVertex3f((x + 0.5f) / width * 2.0f - 1.0f, (y + 0.5f) / height * 2.0f - 1.0f, 1.0f);
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
    ARG_DEF(1, number, float, x, 0);
    ARG_DEF(2, number, float, y, 0);
    ARG_DEF(3, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(4, number, float, radius, 1);

    GLStateGuard _;
    glPointSize(radius);
    gl_set_color(color);
    glBegin(GL_POINTS);
    gl_put_vertex(x, y);
    CHECK_GL(glEnd());

    return 0;
}

static int DrawLine(lua_State* L) {
    ARG_DEF(1, number, float, x1, 0);
    ARG_DEF(2, number, float, y1, 0);
    ARG_DEF(3, number, float, x2, 0);
    ARG_DEF(4, number, float, y2, 0);
    ARG_DEF(5, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(6, number, float, border, 1);
    ARG_DEF(7, string, const char *, stipple, nullptr);

    GLStateGuard _;
    gl_set_border(border, stipple);
    gl_set_color(color);
    glBegin(GL_LINES);
    gl_put_vertex(x1, y1);
    gl_put_vertex(x2, y2);
    CHECK_GL(glEnd());

    return 0;
}

static int DrawTriangle(lua_State* L) {
    ARG_DEF(1, number, float, x1, 0);
    ARG_DEF(2, number, float, y1, 0);
    ARG_DEF(3, number, float, x2, 0);
    ARG_DEF(4, number, float, y2, 0);
    ARG_DEF(5, number, float, x3, 0);
    ARG_DEF(6, number, float, y3, 0);
    ARG_DEF(7, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(8, number, float, border, 0);
    ARG_DEF(9, string, const char *, stipple, nullptr);

    GLStateGuard _;
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
    ARG_DEF(1, number, float, x1, 0);
    ARG_DEF(2, number, float, y1, 0);
    ARG_DEF(3, number, float, x2, 0);
    ARG_DEF(4, number, float, y2, 0);
    ARG_DEF(5, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(6, number, float, border, 0);
    ARG_DEF(7, string, const char *, stipple, nullptr);

    /* // 保证 x1 <= x2, y1 <= y2 */
    /* std::tie(x1, x2) = std::minmax(x1, x2); */
    /* std::tie(y1, y2) = std::minmax(y1, y2); */

    GLStateGuard _;
    gl_set_border(border, stipple);
    gl_set_color(color);
    glBegin(GL_QUADS);
    gl_put_vertex(x1, y1);
    gl_put_vertex(x1, y2);
    gl_put_vertex(x2, y2);
    gl_put_vertex(x2, y1);
    CHECK_GL(glEnd());

    return 0;
}

static void Init() {
    DEFMOD(OpenGL);
    DEF(PutPixel);
    DEF(DrawLine);
    DEF(DrawTriangle);
    DEF(DrawRect);
    ENDMOD();
}

}
