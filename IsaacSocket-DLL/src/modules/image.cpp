#include "module.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stbi/stb_image.h>

namespace image
{
	struct FileGuard
	{
		FILE* fp;
		FileGuard(const char* filename) {
			_wfopen_s(&fp, std::filesystem::path((const char8_t*)filename).c_str(), L"rb");
		}

		~FileGuard() {
			if (fp)
			{
				fclose(fp);
			}
		}
	};

	static void create_image(Image* img, int width, int height, int channels) {
		img->width = width;
		img->height = height;
		img->channels = channels;
		img->data.resize(img->width * img->height * img->channels);
	}

	static bool load_image(Image* img, const char* filename, int channels = 0, bool flipOnLoad = false) {
		FileGuard fileGuard(filename);
		if (!fileGuard.fp) [[unlikely]] {
			return false;
			}
		stbi_set_flip_vertically_on_load(flipOnLoad);
		uint8_t* p = stbi_load_from_file(fileGuard.fp, &img->width, &img->height, &img->channels, channels);
		if (!p) [[unlikely]] {
			return false;
			}
		img->data.assign(p, p + img->width * img->height * img->channels);
		stbi_image_free(p);
		return true;
	}

	static bool load_image_from_memory(Image* img, const char* data, size_t size, int channels = 0, bool flipOnLoad = false) {
		stbi_set_flip_vertically_on_load(flipOnLoad);
		uint8_t* p = stbi_load_from_memory((const stbi_uc*)data, size, &img->width, &img->height, &img->channels, channels);
		if (!p) [[unlikely]] {
			return false;
			}
		img->data.assign(p, p + img->width * img->height * img->channels);
		stbi_image_free(p);
		return true;
	}

	static int LoadFromFile(lua_State* L) {
		ARG(1, string, const char*, path);
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

	static int Create(lua_State* L) {
		ARG(1, integer, int, width);
		ARG(2, integer, int, height);
		ARG(3, integer, int, channels);
		auto img = NEW_CPPDATA(Image);
		create_image(img, width, height, channels);
		return 1;
	}

	static int LoadFromMemory(lua_State* L) {
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

	static int Duplicate(lua_State* L) {
		ARG_CPPDATA(1, Image, image);
		*NEW_CPPDATA(Image) = *image;
		return 1;
	}

	static int Resize(lua_State* L) {
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


	static int PutPixel(lua_State* L) {
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

	static int GetPixel(lua_State* L) {
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


	static RegisterModule Init = [] {
		MODULE_BEGIN(Image);

		MODULE_FUNC(LoadFromFile);
		MODULE_FUNC(LoadFromMemory);
		MODULE_FUNC(Create);
		MODULE_FUNC(Duplicate);
		MODULE_FUNC(Resize);
		MODULE_FUNC(GetPixel);
		MODULE_FUNC(PutPixel);

		MODULE_END();
		};
};
