#pragma once
#include "pch.h"

namespace gnucompat {

#ifdef __MINGW32__
#define IMITATE(func) decltype(auto) func(auto &&...ts) const { return reinterpret_cast<base const *>(this)->func(std::forward<decltype(ts)>(ts)...); }
struct string {
    using base = std::string;
    IMITATE(c_str)
    IMITATE(data)
    IMITATE(operator[])
    IMITATE(size)
    IMITATE(empty)
    IMITATE(begin)
    IMITATE(end)
};
template <class T>
struct vector {
    using base = std::vector<T>;
    IMITATE(data)
    IMITATE(operator[])
    IMITATE(size)
    IMITATE(empty)
    IMITATE(begin)
    IMITATE(end)
};
#undef IMITATE
#else
using std::string;
using std::vector;
#endif

}
