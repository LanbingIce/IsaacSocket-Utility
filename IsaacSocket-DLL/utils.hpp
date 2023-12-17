#pragma once
#include "pch.h"

namespace utils {
	static std::string ToHexString(uint32_t num)
	{
		std::ostringstream oss;
		oss << std::hex << std::setiosflags(std::ios::uppercase) << num;
		return oss.str();
	}

	// 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
	static size_t U8ToU16(const char* u8, wchar_t* u16 = nullptr, size_t len = 0) {
		return MultiByteToWideChar(CP_UTF8, 0, u8, -1, u16, len);
	}

	// 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
	static size_t U16ToU8(const wchar_t* u16, char* u8 = nullptr, size_t len = 0) {
		return WideCharToMultiByte(CP_UTF8, 0, u16, -1, u8, len, nullptr, nullptr);
	}

	static void Utf8Cprintf(const char* format, ...) {
		va_list v;
		va_start(v, format);
		size_t len = vsnprintf(nullptr, 0, format, v) + 1;
		char* u8 = new char[len];
		vsnprintf(u8, len, format, v);
		va_end(v);
		len = U8ToU16(u8);
		wchar_t* u16 = new wchar_t[len];
		U8ToU16(u8, u16, len);
		_cwprintf(u16);
		delete[] u8, u16;
	}

	// 折叠表达式打印可变参数列表
	template <typename... Args>
	void cw(const Args&... args) {
		if (GetConsoleWindow())
		{
			std::ostringstream oss;
			((oss << args << " "), ...);
			oss << '\n';
			Utf8Cprintf(oss.str().c_str());
		}
	}
}

#define FUNC(offset,ret,convention,...) auto f_##offset=(ret(convention*)(__VA_ARGS__))((char*)isaac+offset)