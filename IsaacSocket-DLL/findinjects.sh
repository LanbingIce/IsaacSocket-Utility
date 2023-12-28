#!/bin/bash
(cat inject.hpp; echo 'namespace inject { LPCVOID gnuinjectState[1]; } namespace utils { void Utf8Cprintf(const char* format, ...); }') | sed 's/);$/) {}/' | i686-w64-mingw32-g++ -w -std=c++20 -x c++ -S - -I include -I . -o - | grep -E '^(@|__Z)\S*:$' | grep -E 'utils|inject' | awk -F: '{print ".global "$1"\n"$1":"}'
