#pragma once
#include "pch.h"
#include "state.hpp"
#include "utils.hpp"
#include <Poco/Util/JSONConfiguration.h>

namespace config {
	inline const string path = utils::GetDataFilePath("config.json");
	inline Poco::Util::JSONConfiguration _config = Poco::Util::JSONConfiguration(path);

	static void Load() {
		utils::ReadFile(path, "{}");
		_config.load(path);
	}

	static void Save() {
		std::ofstream ofs(path);
		if (ofs)
		{
			_config.save(ofs);
		}
	}

#define _(type,Type,def) if constexpr (std::is_same_v<T, type>){return (type)_config.get##Type(path,def);}
	template <typename T>
	static T Get(const string& path) {
		_(int, Int, 0);
		_(string, String, "");
		_(double, Double, 0.0);
		_(float, Double, 0.0F);
		return 0;
	}
#undef _

#define _(type,Type) if constexpr (std::is_same_v<T, type>) {if (Get<type>(path)==value)return;_config.set##Type(path,value);Save();return;}
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
