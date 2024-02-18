#pragma once
#include "pch.h"
#include "state.hpp"
#include "utils.hpp"

namespace config {

	Json::Value ParseJson(const string& mystr)
	{
		Json::CharReaderBuilder crb;
		std::unique_ptr<Json::CharReader> charread(crb.newCharReader());
		Json::Value root;

		charread->parse(mystr.c_str(), mystr.c_str() + mystr.size(), &root, nullptr);
		return root;
	}

	string Encode(Json::Value& json)
	{
		Json::StreamWriterBuilder swb;
		string str = Json::writeString(swb, json);
		Json::writeString(swb, str);
		return str;
	}

	int GetInt(const vector<const char*>& path) {
		if (path.empty()) {
			return 0;
		}

		string str = utils::ReadFile(local.configName);
		Json::Value json = ParseJson(str);
		Json::Value* p_json = &json;

		for (const auto& p : path) {
			if (!p_json->isMember(p))
			{
				return 0;
			}
			p_json = &(*p_json)[p];
		}

		return (*p_json).asInt();
	}

	void SetInt(const vector<const char*>& path, int value) {
		if (path.empty()) {
			return;
		}

		string str = utils::ReadFile(local.configName);
		Json::Value json = ParseJson(str);
		Json::Value* p_json = &json;

		for (const auto& p : path) {
			if (!p_json->isMember(p) || !(*p_json)[p].isObject()) {
				(*p_json)[p] = Json::Value();
			}
			p_json = &(*p_json)[p];
		}

		*p_json = value;
		utils::WriteFile(local.configName, Encode(json));
	}
}
