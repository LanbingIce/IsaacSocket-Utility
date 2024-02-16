#pragma once
#include "pch.h"
#include "state.hpp"
#include "utils.hpp"

namespace config {

	void WriteFile(const u8string& filePath, const string& body)
	{
		std::ofstream ofs(std::filesystem::path(filePath.c_str()));
		if (!ofs)
		{
			return;
		}
		ofs << body;
		ofs.close();
	}

	std::string ReadFile(const u8string& filePath, string defl = "{}") {

		if (!std::filesystem::exists(filePath))
		{
			WriteFile(filePath, defl);
		}

		std::ifstream ifs(std::filesystem::path(filePath.c_str()));

		if (!ifs)
		{
			return defl;
		}

		std::stringstream ss;
		ss << ifs.rdbuf();
		ifs.close();

		return ss.str();
	}

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

	int GetInt(const char* name) {
		string s = ReadFile(local.configName);
		Json::Value j = ParseJson(s);
		return j[name].asInt();
	}

	void SetInt(const char* name, int value) {
		string s = ReadFile(local.configName);
		Json::Value j = ParseJson(s);
		j[name] = value;
		string str = Encode(j);
		WriteFile(local.configName, str);
	}
}
