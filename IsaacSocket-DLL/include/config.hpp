#pragma once
#include "pch.h"
#include "state.hpp"

namespace config {
	void Load();

	void Save();

#define _(type,Type,def) if constexpr (std::is_same_v<T, type>){return (type)local._config.get##Type(path,def);}
	template <typename T>
	static T Get(const string& path) {
		_(int, Int, 0);
		_(string, String, "");
		_(double, Double, 0.0);
		_(float, Double, 0.0F);
		return 0;
	}
#undef _

#define _(type,Type) if constexpr (std::is_same_v<T, type>) {if (Get<type>(path)==value)return;local._config.set##Type(path,value);Save();return;}
	template <typename T>
	static void Set(const string& path, T value) {
		_(int, Int);
		_(const char*, String);
		_(string, String);
		_(float, Double);
		_(double, Double);
	}
#undef _
}
