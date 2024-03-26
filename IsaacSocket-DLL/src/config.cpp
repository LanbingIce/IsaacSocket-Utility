#include "config.hpp"
#include "state.hpp"

#include <Poco/Util/JSONConfiguration.h>

namespace config {
	static const string path = utils::GetDataFilePath("config.json");

	void Load() {
		utils::ReadFile(path, "{}");
		local._config.load(path);
	}

	void Save() {
		std::ofstream ofs(path);
		if (ofs)
		{
			local._config.save(ofs);
		}
	}
}
