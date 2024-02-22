﻿#include "module.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stbi/stb_image.h>
#include <glad/glad.h>

#define CHECK_GL(x) do { (x); opengl_check_error(__FILE__, __LINE__, #x); } while (0)


namespace opengl
{

static void clear_gl_error() { while (glGetError() != GL_NO_ERROR); }

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
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) [[unlikely]] {
        if (!GetConsoleWindow()) AllocConsole();
        cw(filename, ":", lineno, ": ", expr, " failed: ", opengl_errno_name(err));
        /* system("pause"); */
        /* std::terminate(); */
    }
}

struct GLStateGuard {
    GLStateGuard() { // 保护游戏状态，直到该对象析构
        clear_gl_error();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glUseProgram(0);
        /* glDrawBuffer(GL_BACK); */
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
        glDepthFunc(GL_GEQUAL);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        // ((x + 0.5f) / width * 2.0f - 1.0f, (y + 0.5f) / height * 2.0f - 1.0f, 0.0f)
        float sx = 1.0f / local.isaac->window->width;
        float sy = 1.0f / local.isaac->window->height;
        glTranslatef(sx - 1.0f, 1.0f - sy, 0.01f);
        glScalef(2.0f * sx, -2.0f * sy, 1.0f);
    }

    ~GLStateGuard() {
        glPopMatrix();
        glPopAttrib();
    }

    GLStateGuard(GLStateGuard&&) = delete;
};

static void gl_set_border(float border, const char* stipple = nullptr) {
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
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (stipple) {
            uint32_t c[32]{};
            for (size_t i = 0; stipple[i] && i < 32 * 32; i++) {
                c[i >> 5] |= (uint32_t)(stipple[i] & 1) << (i & 31);
            }
            glEnable(GL_POLYGON_STIPPLE);
            glPolygonStipple((const GLubyte*)c);
        }
    }
}

static void gl_set_color(uint32_t rgba) {
    // 直接提取RGBA分量
    float r = ((rgba >> 24) & 0xFF) / 255.0f;
    float g = ((rgba >> 16) & 0xFF) / 255.0f;
    float b = ((rgba >> 8) & 0xFF) / 255.0f;
    float a = (rgba & 0xFF) / 255.0f;
    glColor4f(r, g, b, a);
}

struct Image {
    std::vector<uint8_t> data;
    int width = 0, height = 0, channels = 0;

	static int lua_index(lua_State* L) {
		ARG_CPPDATA(1, Image, image);
		METATABLE_BEGIN(Image, *image);
		METATABLE_INDEX(integer, width, int);
		METATABLE_INDEX(integer, height, int);
		METATABLE_INDEX(integer, channels, int);
		METATABLE_END();
	}
};

struct Texture {
    GLuint textureId = 0;

	static int lua_index(lua_State* L) {
		ARG_CPPDATA(1, Texture, texture);
		METATABLE_BEGIN(Texture, *texture);
		METATABLE_INDEX(integer, textureId, GLuint);
		METATABLE_END();
	}

    Texture &operator=(Texture &&) = delete;
    ~Texture() {
        if (textureId) {
            glDeleteTextures(1, &textureId);
            textureId = 0;
        }
    }
};

static void create_image(Image *img, int width, int height, int channels) {
    img->width = width;
    img->height = height;
    img->channels = channels;
    img->data.resize(img->width * img->height * img->channels);
}

static bool load_image(Image *img, const char* filename, int channels = 0, bool flipOnLoad = false) {
    FILE *fp;
    if (_wfopen_s(&fp, std::filesystem::path((const char8_t *)filename).c_str(), L"rb")) [[unlikely]] {
        return false;
    }
    stbi_set_flip_vertically_on_load(flipOnLoad);
    uint8_t* p = stbi_load_from_file(fp, &img->width, &img->height, &img->channels, channels);
    if (!p) [[unlikely]] {
        return false;
    }
    img->data.assign(p, p + img->width * img->height * img->channels);
    stbi_image_free(p);
    return true;
}

static bool load_image_from_memory(Image *img, const char* data, size_t size, int channels = 0, bool flipOnLoad = false) {
    stbi_set_flip_vertically_on_load(flipOnLoad);
    uint8_t* p = stbi_load_from_memory((const stbi_uc *)data, size, &img->width, &img->height, &img->channels, channels);
    if (!p) [[unlikely]] {
        return false;
    }
    img->data.assign(p, p + img->width * img->height * img->channels);
    stbi_image_free(p);
    return true;
}

static void gl_draw_image(const uint8_t* data, int width, int height, int channels) {
    if (channels < 1 || channels > 4) [[unlikely]] {
        return;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    static const GLenum formatTable[] = { GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA };
    glDrawPixels(width, height, formatTable[channels - 1], GL_UNSIGNED_BYTE, data);
}

static int ImageTexture(lua_State* L) {
    ARG_CPPDATA(1, Image, image);

    GLStateGuard _;
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // https://zhuanlan.zhihu.com/p/103881133
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    static const GLenum formatTable[] = { GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA };
    glTexImage2D(GL_TEXTURE_2D, 0, formatTable[image->channels - 1], image->width, image->height, 0, formatTable[image->channels - 1], GL_UNSIGNED_BYTE, image->data.data());

    auto tex = NEW_CPPDATA(Texture);
    tex->textureId = texture;
    return 1;
}

static int CreateEmptyImage(lua_State* L) {
    ARG(1, integer, int, width);
    ARG(2, integer, int, height);
    ARG(3, integer, int, channels);
    auto img = NEW_CPPDATA(Image);
    create_image(img, width, height, channels);
    return 1;
}

static int ReadImage(lua_State* L) {
    ARG(1, string, const char *, path);
    ARG_DEF(2, integer, int, channels, 0);
    ARG_DEF(3, boolean, bool, flipOnLoad, false);
    ARG_DEF(4, boolean, bool, useCached, true);
    auto img = NEW_CPPDATA(Image);
    if (!load_image(img, path, channels, flipOnLoad)) {
        local.lua.lua_pop(L, 1);
        return 0;
    }
    return 1;
}

static int ReadImageFromMemory(lua_State* L) {
    ARG(1, stdstringview, std::string_view, data);
    ARG_DEF(2, integer, int, channels, 0);
    ARG_DEF(3, boolean, bool, flipOnLoad, true);
    auto img = NEW_CPPDATA(Image);
    if (!load_image_from_memory(img, data.data(), data.size(), channels, flipOnLoad)) {
        local.lua.lua_pop(L, 1);
        return 0;
    }
    return 1;
}

static int GetImageSize(lua_State* L) {
    ARG_CPPDATA(1, Image, image);

    RET_TABLE();
    RET_TABLE_KEY(string, "width", integer, image->width);
    RET_TABLE_KEY(string, "height", integer, image->height);
    RET_TABLE_KEY(string, "channels", integer, image->channels);
    RET_TABLE_KEY(string, "data_address", integer, reinterpret_cast<uintptr_t>(image->data.data()));
    RET_TABLE_END();
}

static int ImageDuplicate(lua_State* L) {
    ARG_CPPDATA(1, Image, image);
    *NEW_CPPDATA(Image) = *image;
    return 1;
}

static int ImageResize(lua_State* L) {
    ARG_CPPDATA(1, Image, image);
    ARG_DEF(2, number, uint32_t, width, 0);
    ARG_DEF(3, number, uint32_t, height, 0);

    if (width == 0) width = image->width;
    if (height == 0) height = image->height;
    if (width != image->width || height != image->height) {
        std::vector<uint8_t> newData(width * height * image->channels);
        auto unroll = [image, width, height,
            scaleWidth = (float)image->width / width, scaleHeight = (float)image->height / height,
            oldData = image->data.data(), newData = newData.data()] <int channels> {
                if (image->channels == channels) {
                    for (size_t y = 0; y < height; y++) {
                        uint8_t* oldLine = oldData + (uint32_t)(y * scaleHeight) * image->width * image->channels;
                        uint8_t* newLine = newData + y * width * image->channels;
                        for (size_t x = 0; x < width; x++) {
                            uint32_t oldX = (uint32_t)(x * scaleWidth);
                            uint8_t* oldPixel = oldLine + oldX * image->channels;
                            uint8_t* newPixel = newLine + x * image->channels;
                            memcpy(newPixel, oldPixel, channels * sizeof(uint8_t));
                        }
                    }
                }
            };
        unroll.operator() < 1 > ();
        unroll.operator() < 2 > ();
        unroll.operator() < 3 > ();
        unroll.operator() < 4 > ();
        image->data = std::move(newData);
        image->width = width;
        image->height = height;
    }

    return 0;
}

static int ImagePutPixel(lua_State* L) {
    ARG_CPPDATA(1, Image, image);
    ARG(2, number, uint32_t, x);
    ARG(3, number, uint32_t, y);
    ARG_DEF(4, integer, uint32_t, color, 0xFFFFFFFF);

    uint8_t* pixel = image->data.data() + (y * image->width + x) * image->channels;
    if (image->channels > 0) [[likely]]
        pixel[0] = (color >> 24) & 0xFF;
    if (image->channels > 1) [[likely]]
        pixel[1] = (color >> 16) & 0xFF;
    if (image->channels > 2) [[likely]]
        pixel[2] = (color >> 8) & 0xFF;
    if (image->channels > 3)
        pixel[3] = color & 0xFF;

    return 0;
}

static int ImageGetPixel(lua_State* L) {
    ARG_CPPDATA(1, Image, image);
    ARG(2, number, uint32_t, x);
    ARG(3, number, uint32_t, y);

    uint32_t color = 0;
    uint8_t const* pixel = image->data.data() + (y * image->width + x) * image->channels;
    if (image->channels > 0) [[likely]]
        color |= pixel[0] << 24;
    if (image->channels > 1) [[likely]]
        color |= pixel[1] << 16;
    if (image->channels > 2) [[likely]]
        color |= pixel[2] << 8;
    if (image->channels > 3)
        color |= pixel[3];

    RET(integer, color);
}

static int DrawImage(lua_State* L) {
    ARG(1, number, float, x);
    ARG(2, number, float, y);
    ARG_CPPDATA(3, Image, image);
    ARG_DEF(4, number, float, zoomX, 1);
    ARG_DEF(5, number, float, zoomY, 1);

    GLStateGuard _;
    glPixelZoom(zoomX, zoomY);
    glRasterPos2f(x, y);
    gl_draw_image(image->data.data(), image->width, image->height, image->channels);

    return 0;
}

static int PutPixel(lua_State* L) {
    ARG(1, number, float, x);
    ARG(2, number, float, y);
    ARG_DEF(3, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(4, number, float, radius, 1);

    GLStateGuard _;
    glPointSize(radius);
    gl_set_color(color);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    CHECK_GL(glEnd());

    return 0;
}

static int DrawLine(lua_State* L) {
    ARG(1, number, float, x1);
    ARG(2, number, float, y1);
    ARG(3, number, float, x2);
    ARG(4, number, float, y2);
    ARG_DEF(5, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(6, number, float, border, 1);
    ARG_DEF(7, string, const char*, stipple, nullptr);

    GLStateGuard _;
    gl_set_border(border, stipple);
    gl_set_color(color);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    CHECK_GL(glEnd());

    return 0;
}

static int DrawTriangle(lua_State* L) {
    ARG(1, number, float, x1);
    ARG(2, number, float, y1);
    ARG(3, number, float, x2);
    ARG(4, number, float, y2);
    ARG(5, number, float, x3);
    ARG(6, number, float, y3);
    ARG_DEF(7, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(8, number, float, border, 0);
    ARG_DEF(9, string, const char*, stipple, nullptr);

    GLStateGuard _;
    gl_set_border(border, stipple);
    gl_set_color(color);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    CHECK_GL(glEnd());

    return 0;
}

static int DrawRect(lua_State* L) {
    ARG(1, number, float, x1);
    ARG(2, number, float, y1);
    ARG(3, number, float, x2);
    ARG(4, number, float, y2);
    ARG_DEF(5, integer, uint32_t, color, 0xFFFFFFFF);
    ARG_DEF(6, number, float, border, 0);
    ARG_DEF(7, string, const char*, stipple, nullptr);

    /* // 保证 x1 <= x2, y1 <= y2 */
    /* std::tie(x1, x2) = std::minmax(x1, x2); */
    /* std::tie(y1, y2) = std::minmax(y1, y2); */

    GLStateGuard _;
    gl_set_border(border, stipple);
    gl_set_color(color);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    CHECK_GL(glEnd());

    return 0;
}

static RegisterModule Init = [] {
    MODULE_BEGIN(OpenGL);
    MODULE_FUNC(PutPixel);
    MODULE_FUNC(DrawLine);
    MODULE_FUNC(DrawTriangle);
    MODULE_FUNC(DrawRect);

    MODULE_FUNC(ReadImage);
    MODULE_FUNC(ReadImageFromMemory);
    MODULE_FUNC(CreateEmptyImage);
    MODULE_FUNC(GetImageSize);
    MODULE_FUNC(ImageDuplicate);
    MODULE_FUNC(ImageResize);
    MODULE_FUNC(ImageGetPixel);
    MODULE_FUNC(ImagePutPixel);
    MODULE_FUNC(DrawImage);
    MODULE_FUNC(ImageTexture);

    MODULE_END();
};

}