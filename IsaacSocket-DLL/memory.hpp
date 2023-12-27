#pragma once

#include "lua.hpp"
#include "isaac.hpp"

namespace memory
{
	enum ValueType
	{
		Memory,
		Int8,
		UInt8,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Float,
		Double
	};

	static int Write(lua_State* L) {

		ARG(1, integer, uint32_t, address);
		ARG(-1, integer, ValueType, type);

		switch (type)
		{

#define _(typeName,type,luaType) case typeName: { ARG(2, luaType, type, value); *(type*)address = value;break;}

			//case:
			_(Int8, int8_t, integer);
			_(UInt8, uint8_t, integer);
			_(Int16, int16_t, integer);
			_(UInt16, uint16_t, integer);
			_(Int32, int32_t, integer);
			_(UInt32, uint32_t, integer);
			_(Int64, int64_t, integer);
			_(UInt64, uint64_t, integer);
			_(Float, float, number);
			_(Double, double, number);

#undef _

		case Memory:
			ARG(2, string, const char*, value);
			local.lua->luaL_len(L, 2);
			ARG(-1, integer, size_t, size);
			std::copy(value, value + size, (char*)address);
			break;
		}
		return 0;
	}

	static int Read(lua_State* L) {
		ARG(1, integer, uint32_t, address);
		ARG(-1, integer, ValueType, type);

		switch (type)
		{

#define _(typeName,type,luaType) case typeName:RET(luaType, *(type*)address);

			//case:
			_(Int8, int8_t, integer);
			_(UInt8, uint8_t, integer);
			_(Int16, int16_t, integer);
			_(UInt16, uint16_t, integer);
			_(Int32, int32_t, integer);
			_(UInt32, uint32_t, integer);
			_(Int64, int64_t, integer);
			_(UInt64, uint64_t, integer);
			_(Float, float, number);
			_(Double, double, number);

#undef _

		case Memory:
			ARG(2, integer, size_t, size);
			local.lua->lua_pushlstring(L, (const char*)address, size);
			break;
		}

		return 1;
	}

#define _(type) static int Read##type(lua_State* L) {local.lua->lua_pushinteger(L,(uint32_t)ValueType::type); return Read(L);}static int Write##type(lua_State* L) {local.lua->lua_pushinteger(L,(uint32_t)ValueType::type); return Write(L);}
	_(Memory);
	_(Int8);
	_(UInt8);
	_(Int16);
	_(UInt16);
	_(Int32);
	_(UInt32);
	_(Int64);
	_(UInt64);
	_(Float);
	_(Double);
#undef _

	static int CalcAddress(lua_State* L) {
		ARG(1, integer, uint32_t, address);
		size_t i = 2;
		while (local.lua->lua_isinteger(L, i))
		{
			ARG(i, integer, uint32_t, offset);
			address = *(uint32_t*)address + offset;
			i++;
		}
		RET(integer, address);
	}

	static int GetImageBase(lua_State* L) {
		RET(integer, (uint32_t)local.isaac);
	}

	void Init() {

		lua_State* L = local.isaac->luaVM->L;
		size_t top = local.lua->lua_gettop(L);

		local.lua->lua_getglobal(L, "_ISAAC_SOCKET");
		local.lua->lua_pushstring(L, "IsaacSocket");
		local.lua->lua_gettable(L, -2);
		local.lua->lua_pushstring(L, "Memory");
		local.lua->lua_newtable(L);

#define _(name) local.lua->lua_pushstring(L, #name);local.lua->lua_pushcfunction(L, name); local.lua->lua_settable(L, -3)

		_(ReadMemory);
		_(ReadInt8);
		_(ReadUInt8);
		_(ReadInt16);
		_(ReadUInt16);
		_(ReadInt32);
		_(ReadUInt32);
		_(ReadInt64);
		_(ReadUInt64);
		_(ReadFloat);
		_(ReadDouble);

		_(WriteMemory);
		_(WriteInt8);
		_(WriteUInt8);
		_(WriteInt16);
		_(WriteUInt16);
		_(WriteInt32);
		_(WriteUInt32);
		_(WriteInt64);
		_(WriteUInt64);
		_(WriteFloat);
		_(WriteDouble);

		_(GetImageBase);
		_(CalcAddress);

#undef _

		local.lua->lua_settable(L, -3);
		local.lua->lua_settop(L, top);
	}
}
