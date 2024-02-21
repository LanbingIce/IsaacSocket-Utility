#pragma once
#include "pch.h"
#include "utils.hpp"

namespace gnucompat { // 兼容 MinGW 的只读 std::string 和 std::vector（防止编译器报错）

#ifdef __MINGW32__
// 如果是 MinGW 编译器，那么使用这些兼容代码
#define IMITATE(func) decltype(auto) func(auto &&...ts) const { return reinterpret_cast<base const *>(this)->func(std::forward<decltype(ts)>(ts)...); }
#define BASEON(type, ...) using base = std::type __VA_ARGS__; operator base const &() const noexcept { return *reinterpret_cast<base const *>(this); } operator base &() noexcept { return *reinterpret_cast<base *>(this); } type(type &&) = delete; type(type const &) = delete; type &operator=(base const &that) { *reinterpret_cast<base *>(this) = that; return *this; } type &operator=(base &&that) { *reinterpret_cast<base *>(this) = std::move(that); return *this; } type &operator=(type const &) = delete; type &operator=(type &&) = delete;
struct string {
    BASEON(string);
    IMITATE(c_str);
    IMITATE(data);
    IMITATE(operator[]);
    IMITATE(size);
    IMITATE(empty);
    IMITATE(begin);
    IMITATE(end);
};
template <class T>
struct vector {
    BASEON(vector, <T>);
    IMITATE(data);
    IMITATE(operator[]);
    IMITATE(size);
    IMITATE(empty);
    IMITATE(begin);
    IMITATE(end);
};
template <class T> struct compatify_type { using type = T; };
template <> struct compatify_type<std::string> { using type = gnucompat::string; };
template <class T> struct compatify_type<std::vector<T>> { using type = gnucompat::vector<T>; };
#undef BASEON
#undef IMITATE
/* #ifdef FIELD */
/* #undef FIELD // 重新定义 utils.hpp 的 FIELD（放弃） */
/* #define FIELD(address,type_,name) struct{char pad_##address[address]; typename ::gnucompat::compatify_type<type_>::type name;} */
/* #endif */
/* static_assert(std::is_trivial_v<gnucompat::string>); */
/* static_assert(std::is_trivial_v<gnucompat::vector<char>>); */
/* struct Test { */
/*     gnucompat::vector<void*> mods; */
/* }; */
/* static_assert(std::is_trivial_v<Test>); */
#else
// 否则是 MSVC 编译器，那么原封不动使用标准库
using std::string;
using std::vector;
#endif

}
