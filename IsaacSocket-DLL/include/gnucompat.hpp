#pragma once
#include "pch.h"

namespace gnucompat { // 兼容 MinGW 的只读 std::string 和 std::vector（防止编译器报错）

#ifdef __MINGW32__
// 如果是 MinGW 编译器，那么使用这些兼容代码
#define IMITATE(func) decltype(auto) func(auto &&...ts) const { return reinterpret_cast<base const *>(this)->func(std::forward<decltype(ts)>(ts)...); }
#define BASEON(type, ...) using base = std::type __VA_ARGS__; type(type &&) = delete; operator base const &() const noexcept { return *reinterpret_cast<base const *>(this); } operator base &() noexcept { return *reinterpret_cast<base *>(this); }
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
#undef BASEON
#undef IMITATE
#else
// 否则是 MSVC 编译器，那么原封不动使用标准库
using std::string;
using std::vector;
#endif

}
