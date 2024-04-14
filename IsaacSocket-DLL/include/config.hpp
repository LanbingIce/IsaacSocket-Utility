#pragma once
#include "pch.h"
#include <Poco/Util/JSONConfiguration.h>

namespace config {
    extern Poco::Util::JSONConfiguration _config;

    void _CheckConfigLoad();

    void _Save();

#define _(type,Type,def) if constexpr (std::is_same_v<T, type>){return (type)_config.get##Type(path,def);}
    template <typename T>
    static T Get(const std::string& path) {
        _CheckConfigLoad();
        _(int, Int, 0);
        _(std::string, String, "");
        _(double, Double, 0.0);
        _(float, Double, 0.0F);
        return 0;
    }
#undef _

#define _(type,Type) if constexpr (std::is_same_v<T, type>) {if (Get<type>(path)==value)return;_config.set##Type(path,value);_Save();return;}
    template <typename T>
    static void Set(const std::string& path, T value) {
        _CheckConfigLoad();
        _(int, Int);
        _(const char*, String);
        _(std::string, String);
        _(float, Double);
        _(double, Double);
    }
#undef _
}
