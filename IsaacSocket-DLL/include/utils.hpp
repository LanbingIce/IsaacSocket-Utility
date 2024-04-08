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
    static size_t AnsiToU16(const char* ansi, wchar_t* u16 = nullptr, size_t len = 0) {
        return MultiByteToWideChar(CP_ACP, 0, ansi, -1, u16, len);
    }

    // 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
    static size_t U8ToU16(const char* u8, wchar_t* u16 = nullptr, size_t len = 0) {
        return MultiByteToWideChar(CP_UTF8, 0, u8, -1, u16, len);
    }

    // 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
    static size_t U16ToAnsi(const wchar_t* u16, char* u8 = nullptr, size_t len = 0) {
        return WideCharToMultiByte(CP_ACP, 0, u16, -1, u8, len, nullptr, nullptr);
    }

    // 只能传入一个或三个参数，若传入一个参数，则返回转换后的长度(包括\0)
    static size_t U16ToU8(const wchar_t* u16, char* u8 = nullptr, size_t len = 0) {
        return WideCharToMultiByte(CP_UTF8, 0, u16, -1, u8, len, nullptr, nullptr);
    }

    static std::string U16ToAnsi(const std::wstring& u16) {
        std::string ansi(utils::U16ToAnsi(u16.c_str()) - 1, '\0');
        utils::U16ToAnsi(u16.c_str(), ansi.data(), ansi.size() + 1);
        return ansi;
    }

    static std::wstring AnsiToU16(const std::string& ansi) {
        std::wstring u16(utils::AnsiToU16(ansi.c_str()) - 1, L'\0');
        utils::AnsiToU16(ansi.c_str(), u16.data(), u16.size() + 1);
        return u16;
    }

    static std::wstring U8ToU16(const std::string& u8) {
        std::wstring u16(utils::U8ToU16(u8.c_str()) - 1, L'\0');
        utils::U8ToU16(u8.c_str(), u16.data(), u16.size() + 1);
        return u16;
    }

    static std::string U16ToU8(const std::wstring& u16) {
        std::string u8(utils::U16ToU8(u16.c_str()) - 1, '\0');
        utils::U16ToU8(u16.c_str(), u8.data(), u8.size() + 1);
        return u8;
    }

    static string GetDataFilePath(const char* fileName) {
        wchar_t c_path[MAX_PATH];
        GetEnvironmentVariableW(L"APPDATA", c_path, MAX_PATH);
        std::filesystem::path path = std::filesystem::path(c_path) / "IsaacSocket" / (char8_t*)fileName;
        return (const char*)path.u8string().c_str();
    }

    static std::wstring GetDataFilePathW(const wchar_t* fileName) {
        wchar_t c_path[MAX_PATH];
        GetEnvironmentVariableW(L"APPDATA", c_path, MAX_PATH);
        std::filesystem::path path = std::filesystem::path(c_path) / "IsaacSocket" / fileName;
        return path.wstring();
    }

    template <typename... Args>
    void mb(const Args... args) {
        std::ostringstream oss;
        ((oss << args << " "), ...);
        size_t len = U8ToU16(oss.str().c_str());
        vector<wchar_t> u16(len);
        U8ToU16(oss.str().c_str(), u16.data(), len);
        MessageBoxW(0, u16.data(), L"", 0);
    }

    // 将文本写入指定文件
    static void WriteFile(const string& filePath, const string& text)
    {
        std::ofstream ofs(std::filesystem::path((const char8_t*)filePath.c_str()));
        if (!ofs)
        {
            return;
        }
        ofs << text;
    }

    // 读取指定文件的文本
    static std::string ReadFile(const string& filePath, const char* defaultText = "") {

        if (!std::filesystem::exists(filePath))
        {
            WriteFile(filePath, defaultText);
        }

        std::ifstream ifs(std::filesystem::path((const char8_t*)filePath.c_str()));

        if (!ifs)
        {
            return defaultText;
        }

        std::ostringstream oss;

        oss << ifs.rdbuf();
        return oss.str();
    }

}

#define FUNC(offset,ret,convention,...) auto f_##offset=(ret(convention*)(__VA_ARGS__))((char*)&isaac+offset)
#define VAR_WRITE(var,value) if(var!=value){DWORD oldProtect;VirtualProtect(&var,sizeof(var),PAGE_READWRITE,&oldProtect);var=value;VirtualProtect(&var,sizeof(var),oldProtect,&oldProtect);}

using utils::mb;
