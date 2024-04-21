﻿#pragma once
#include "pch.h"
#include <zlib/zlib.h>

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

    static vector<Byte> ReadFileBinary(const string& filePath) {
        std::filesystem::path path((char8_t*)filePath.c_str());
        std::ifstream file(path, std::ios::in | std::ios::binary);
        return vector<Byte>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    static void WriteFileBinary(const string& filePath, const vector<Byte>& data) {
        std::filesystem::path path((char8_t*)filePath.c_str());
        std::ofstream outputFile(path, std::ios::out | std::ios::binary);
        outputFile.write((const char*)data.data(), data.size());
    }

#pragma warning(disable: 6387)
    static vector<Byte> ReadResBinary(int resId, const char* resType)
    {
        auto hModule = GetModuleHandleA(NULL);
        auto hResInfo = FindResourceA(hModule, MAKEINTRESOURCEA(resId), resType);
        auto hResData = LoadResource(hModule, hResInfo);
        auto pRes = (Byte*)LockResource(hResData);
        auto resSize = SizeofResource(hModule, hResInfo);
        return vector<Byte>(pRes, pRes + resSize);
    }
#pragma warning(default: 6387)

    static vector<Byte> Compress(const vector<Byte>& sourceData) {
        auto destLen = compressBound(sourceData.size());
        vector <Byte> destData(destLen);
        compress2(destData.data(), &destLen, sourceData.data(), sourceData.size(), Z_BEST_COMPRESSION);
        destData.resize(destLen);
        return destData;
    }

    static vector<Byte> Uncompress(const vector<Byte>& sourceData) {
        uLong destLen = sourceData.size() << 2;
        vector <Byte> destData(destLen);
        while (uncompress(destData.data(), &destLen, sourceData.data(), sourceData.size()) == Z_BUF_ERROR)
        {
            destLen <<= 1;
            destData.resize(destLen);
        }
        destData.resize(destLen);
        return destData;
    }

    static void AllocConsole() {
        ::AllocConsole();
        SetConsoleOutputCP(CP_UTF8);
        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout);
    }

    static vector<string> GetCommandArgs() {
        vector <string> args;
        LPWSTR commandLine = GetCommandLineW();
        int argc;
        LPWSTR* argv = CommandLineToArgvW(commandLine, &argc);
        for (int i = 1; i < argc; ++i) {
            args.push_back(U16ToU8(std::wstring(argv[i])));
        }
        LocalFree(argv);
        return args;
    }
}

using utils::mb;
