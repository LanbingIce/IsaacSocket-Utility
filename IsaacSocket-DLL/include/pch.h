// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <type_traits>
#include <chrono>
#include <utility>
#include <conio.h>
#include <process.h>
#include <stdexcept>
#include <regex>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <cmath>
#include <thread>
#include <mutex>
#include <atomic>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <json/json.h>
#include <fstream>
#include <cwctype>
#include <shellapi.h>
#include <queue>
#include <unordered_map>

#include <imsdk/TIMManager.h>
#include <imsdk/TIMMessageManager.h>

#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "libs/zlib/zlibstatic.lib")
#pragma comment(lib, "libs/imsdk/ImSDK.lib")

#define POCO_STATIC

#ifdef _MSC_VER
#define FASTCALL __fastcall
#endif //_MSC_VER

using std::string;
using std::vector;

#endif //PCH_H
