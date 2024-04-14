#include "config.hpp"
#include "state.hpp"

#include <Poco/Util/JSONConfiguration.h>

using std::string;

namespace config {
    static const string path = utils::GetDataFilePath("config.json");
    Poco::Util::JSONConfiguration _config{};

    void _CheckConfigLoad() {
        static bool initialized;
        if (!initialized)
        {
            utils::ReadFile(path, "{}");
            _config.load(path);
        }
    }

    void _Save() {
        std::ofstream ofs(path);
        if (ofs)
        {
            _config.save(ofs);
        }
    }
}
