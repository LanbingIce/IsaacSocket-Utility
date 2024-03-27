#pragma once

#include "pch.h"
#include "inject.hpp"

namespace main {
	// 初始化，共享内存和注入
	static void Main() {
		setlocale(LC_ALL, ".UTF8");
		inject::Inject();
	}
}
