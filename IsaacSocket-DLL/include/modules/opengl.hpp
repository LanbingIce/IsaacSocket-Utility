#pragma once

#include "module.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#include <glad/glad.h>

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

	/* static void glVertex2f(float x, float y) { */
		/* uint32_t width = local.isaac->window->width; */
		/* uint32_t height = local.isaac->window->height; */
		/* glVertex3f((x + 0.5f) / width * 2.0f - 1.0f, (y + 0.5f) / height * 2.0f - 1.0f, 1.0f); */
	/* } */

	static void gl_set_color(uint32_t rgba) {
		// 直接提取RGBA分量
		float r = ((rgba >> 24) & 0xFF) / 255.0f;
		float g = ((rgba >> 16) & 0xFF) / 255.0f;
		float b = ((rgba >> 8) & 0xFF) / 255.0f;
		float a = (rgba & 0xFF) / 255.0f;
		glColor4f(r, g, b, a);
	}
#pragma warning(disable: 26495)//禁用警告C26495: 始终初始化成员变量
	struct Image {
		std::vector<uint8_t> data;
		int width, height, channels;
	};
#pragma warning(default: 26495)//重新启用警告	C26495
	static std::unique_ptr<Image> create_image(const char* filename, int width, int height, int channels) {
		auto img = std::make_unique<Image>();
		img->width = width;
		img->height = height;
		img->channels = channels;
		img->data.resize(img->width * img->height * img->channels);
		return img;
	}

	static std::unique_ptr<Image> load_image(const char* filename, int channels = 0) {
		auto img = std::make_unique<Image>();
		uint8_t* p = stbi_load(filename, &img->width, &img->height, &img->channels, channels);
		if (!p) [[unlikely]] {
			return nullptr;
			}
		img->data.assign(p, p + img->width * img->height * img->channels);
		stbi_image_free(p);
		return img;
	}

	static void gl_draw_image(const uint8_t* data, int width, int height, int channels) {
		if (channels < 1 || channels > 4) [[unlikely]] {
			return;
			}
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		static const GLenum formatTable[] = { GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA };
		glDrawPixels(width, height, formatTable[channels - 1], GL_UNSIGNED_BYTE, data);
	}

	inline auto* image_handles() {
		static HandleTable<Image> table;
		return &table;
	}

	inline auto* image_cache() {
		static KVCache<std::string, Handle> table;
		return &table;
	}

	static int CreateEmptyImage(lua_State* L) {
		ARG_DEF(1, string, const char*, path, nullptr);
		ARG_DEF(2, integer, int, width, 0);
		ARG_DEF(3, integer, int, height, 0);
		ARG_DEF(4, integer, int, channels, 0);
		ARG_DEF(5, boolean, bool, useCached, true);
		if (!path) [[unlikely]] {
			return 0;
			}
			auto gen = [path, width, height, channels] {
				if (auto img = create_image(path, width, height, channels)) {
					return image_handles()->create(std::move(img));
				}
				return NULL_HANDLE;
				};
			Handle imageHandle = useCached ? image_cache()->find(path, gen) : gen();
			RET(integer, imageHandle);
	}

	static int ReadImage(lua_State* L) {
		ARG_DEF(1, string, const char*, path, nullptr);
		ARG_DEF(2, integer, int, channels, 0);
		ARG_DEF(3, boolean, bool, useCached, true);
		if (!path) [[unlikely]] {
			return 0;
			}
			auto gen = [path, channels] {
				if (auto img = load_image(path, channels)) {
					return image_handles()->create(std::move(img));
				}
				return NULL_HANDLE;
				};
			Handle imageHandle = useCached ? image_cache()->find(path, gen) : gen();
			RET(integer, imageHandle);
	}

	static int GetImageSize(lua_State* L) {
		ARG_DEF(3, integer, Handle, imageHandle, NULL_HANDLE);

		if (auto image = image_handles()->find(imageHandle)) {
			RET_TABLE();
			RET_TABLE_KEY(string, "width", integer, image->width);
			RET_TABLE_KEY(string, "height", integer, image->height);
			RET_TABLE_KEY(string, "channels", integer, image->channels);
			RET_TABLE_KEY(string, "data_address", integer, reinterpret_cast<uintptr_t>(image->data.data()));
			RET_TABLE_END();
		}

		return 0;
	}

	static int ImageDuplicate(lua_State* L) {
		ARG_DEF(3, integer, Handle, imageHandle, NULL_HANDLE);

		Handle imageHandle2 = NULL_HANDLE;
		if (auto image = image_handles()->find(imageHandle)) {
			image_handles()->create(std::make_unique<Image>(*image));
		}

		RET(integer, imageHandle2);
	}

	static int ImageResize(lua_State* L) {
		ARG_DEF(1, integer, Handle, imageHandle, NULL_HANDLE);
		ARG_DEF(2, number, uint32_t, width, 0);
		ARG_DEF(3, number, uint32_t, height, 0);

		if (auto image = image_handles()->find(imageHandle)) {
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
		}

		return 0;
	}

	static int ImagePutPixel(lua_State* L) {
		ARG_DEF(3, integer, Handle, imageHandle, NULL_HANDLE);
		ARG_DEF(1, number, uint32_t, x, 0);
		ARG_DEF(2, number, uint32_t, y, 0);
		ARG_DEF(4, integer, uint32_t, color, 0xFFFFFFFF);

		if (auto image = image_handles()->find(imageHandle)) {
			uint8_t* pixel = image->data.data() + (y * image->width + x) * image->channels;
			if (image->channels > 0) [[likely]]
				pixel[0] = (color >> 24) & 0xFF;
				if (image->channels > 1) [[likely]]
					pixel[1] = (color >> 16) & 0xFF;
					if (image->channels > 2) [[likely]]
						pixel[2] = (color >> 8) & 0xFF;
						if (image->channels > 3)
							pixel[3] = color & 0xFF;
		}

		return 0;
	}

	static int ImageGetPixel(lua_State* L) {
		ARG_DEF(3, integer, Handle, imageHandle, NULL_HANDLE);
		ARG_DEF(1, number, uint32_t, x, 0);
		ARG_DEF(2, number, uint32_t, y, 0);

		uint32_t color = 0;
		if (auto image = image_handles()->find(imageHandle)) {
			uint8_t const* pixel = image->data.data() + (y * image->width + x) * image->channels;
			if (image->channels > 0) [[likely]]
				color |= pixel[0] << 24;
				if (image->channels > 1) [[likely]]
					color |= pixel[1] << 16;
					if (image->channels > 2) [[likely]]
						color |= pixel[2] << 8;
						if (image->channels > 3)
							color |= pixel[3];
		}

		RET(integer, color);
	}

	static int DrawImage(lua_State* L) {
		ARG_DEF(1, number, float, x, 0);
		ARG_DEF(2, number, float, y, 0);
		ARG_DEF(3, integer, Handle, imageHandle, NULL_HANDLE);
		ARG_DEF(4, number, float, zoomX, 1);
		ARG_DEF(5, number, float, zoomY, 1);

		GLStateGuard _;
		if (auto image = image_handles()->find(imageHandle)) {
			glPixelZoom(zoomX, zoomY);
			glRasterPos2f(x, y);
			gl_draw_image(image->data.data(), image->width, image->height, image->channels);
		}

		return 0;
	}

	static int FreeImage(lua_State* L) {
		ARG_DEF(1, integer, Handle, imageHandle, NULL_HANDLE);
		image_handles()->destroy(imageHandle);
		return 0;
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
		glVertex2f(x, y);
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
		ARG_DEF(1, number, float, x1, 0);
		ARG_DEF(2, number, float, y1, 0);
		ARG_DEF(3, number, float, x2, 0);
		ARG_DEF(4, number, float, y2, 0);
		ARG_DEF(5, number, float, x3, 0);
		ARG_DEF(6, number, float, y3, 0);
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
		ARG_DEF(1, number, float, x1, 0);
		ARG_DEF(2, number, float, y1, 0);
		ARG_DEF(3, number, float, x2, 0);
		ARG_DEF(4, number, float, y2, 0);
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

	static void Init() {
		DEFMOD(OpenGL);
		DEF(PutPixel);
		DEF(DrawLine);
		DEF(DrawTriangle);
		DEF(DrawRect);

		DEF(ReadImage);
		DEF(CreateEmptyImage);
		DEF(GetImageSize);
		DEF(ImageDuplicate);
		DEF(ImageResize);
		DEF(ImageGetPixel);
		DEF(ImagePutPixel);
		DEF(DrawImage);
		DEF(FreeImage);

		ENDMOD();
	}

}
