#pragma once
#include "pch.h"

namespace utils {
	static std::string ToHexString(uint32_t num)
	{
		std::ostringstream oss;
		oss << std::hex << std::setiosflags(std::ios::uppercase) << num;
		return oss.str();
	}

	static void Utf8Cprintf(const char* format, ...) {
		va_list v;
		va_start(v, format);
		size_t size = vsnprintf(nullptr, 0, format, v) + 1;
		char* u8Str = new char[size];
		vsnprintf(u8Str, size, format, v);
		va_end(v);
		size = MultiByteToWideChar(CP_UTF8, 0, u8Str, -1, nullptr, 0);
		wchar_t* u16Str = new wchar_t[size];
		MultiByteToWideChar(CP_UTF8, 0, u8Str, -1, u16Str, size);
		_cwprintf(u16Str);
		delete[] u16Str;
		delete[] u8Str;
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