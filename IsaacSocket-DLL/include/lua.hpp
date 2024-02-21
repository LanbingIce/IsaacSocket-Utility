#pragma once
#include "pch.h"
#include "isaac.hpp"

using isaac::lua_State;

//lua类型枚举
#define LUA_TNONE			(-1)
#define LUA_TNIL			0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER			3
#define LUA_TSTRING			4
#define LUA_TTABLE			5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD			8
#define LUA_NUMTAGS			9

//lua类型
#define LUA_INTEGER		long long
#define LUA_NUMBER		double
#define LUA_KCONTEXT	ptrdiff_t

//lua状态码
#define LUA_OK			0
#define LUA_YIELD		1
#define LUA_ERRRUN		2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM		4
#define LUA_ERRGCMM		5
#define LUA_ERRERR		6

#define LUAI_IS32INT	((UINT_MAX >> 30) >= 3)
#if LUAI_IS32INT
#define LUAI_MAXSTACK		1000000
#else
#define LUAI_MAXSTACK		15000
#endif
#define LUA_REGISTRYINDEX	(-LUAI_MAXSTACK - 1000)

//lua类型
typedef LUA_INTEGER lua_Integer;
typedef LUA_NUMBER lua_Number;
typedef int (*lua_CFunction) (lua_State* L);
typedef int ptrdiff_t;
typedef int intptr_t;
typedef LUA_KCONTEXT lua_KContext;
typedef int (*lua_KFunction) (lua_State* L, int status, lua_KContext ctx);
typedef void* (*lua_Alloc) (void* ud, void* ptr, size_t osize, size_t nsize);

typedef struct luaL_Reg {
	const char* name;
	lua_CFunction func;
} luaL_Reg;

namespace lua {

#define _(ret,name,...) ret(*name)(__VA_ARGS__)=(decltype(name))GetProcAddress(hLuaModule, #name)
#pragma warning(disable: 6387)//禁用警告	C6387	“hLuaModule”可能是“0” : 这不符合函数“GetProcAddress”的规范。

	struct Lua
	{
		HMODULE hLuaModule = GetModuleHandleA("Lua5.3.3r.dll");

		_(const char*, lua_pushstring, lua_State* L, const char* s);

		_(const char*, lua_pushlstring, lua_State* L, const char* s, size_t len);

		_(void, lua_pushcclosure, lua_State* L, lua_CFunction fn, int n);

		_(void, lua_pushnumber, lua_State* L, lua_Number n);

		_(void, lua_pushinteger, lua_State* L, lua_Integer n);

		_(void, lua_pushvalue, lua_State* L, int idx);

		_(void, lua_settable, lua_State* L, int idx);

		_(void, lua_gettable, lua_State* L, int idx);

		_(lua_Number, lua_tonumberx, lua_State* L, int idx, int* pisnum);

		_(void, lua_setglobal, lua_State*, const char* name);

		_(void, lua_createtable, lua_State* L, int narray, int nrec);

		_(int, lua_getglobal, lua_State* L, const char* name);

		_(void, lua_settop, lua_State* L, int idx);

		_(int, lua_gettop, lua_State* L);

		_(int, lua_toboolean, lua_State* L, int idx);

		_(void, lua_pushboolean, lua_State* L, int b);

		_(lua_Integer, lua_tointegerx, lua_State* L, int idx, int* pisnum);

		_(int, lua_type, lua_State* L, int idx);

		_(int, lua_isnumber, lua_State* L, int idx);

		_(int, lua_isinteger, lua_State* L, int idx);

		_(int, lua_isstring, lua_State* L, int idx);

		_(const char*, lua_tolstring, lua_State* L, int idx, size_t* len);

		_(int, luaL_error, lua_State* L, const char* fmt, ...);

		_(void, lua_pushnil, lua_State* L);

		_(void, lua_callk, lua_State* L, int nargs, int nresults, lua_KContext ctx, lua_KFunction k);

		_(int, lua_pcallk, lua_State* L, int nargs, int nresults, int errfunc, lua_KContext ctx, lua_KFunction k);

		_(void, lua_rotate, lua_State* L, int idx, int off);

		_(int, luaL_getsubtable, lua_State* L, int idx, const char* fname);

		_(lua_Integer, luaL_len, lua_State* L, int idx);

		_(int, lua_next, lua_State* L, int idx);

		_(void*, lua_newuserdata, lua_State* L, size_t size);

		_(int, luaL_newmetatable, lua_State* L, const char* tname);

		_(void, luaL_setfuncs, lua_State* L, const luaL_Reg* l, int nup);

		_(void, luaL_setmetatable, lua_State* L, const char* tname);

		_(int, lua_isuserdata, lua_State* L, int idx);

		_(void*, lua_touserdata, lua_State* L, int idx);

		_(int, lua_setmetatable, lua_State* L, int objindex);

		_(void*, luaL_testudata, lua_State* L, int ud, const char* tname);

		_(void*, luaL_checkudata, lua_State* L, int ud, const char* tname);

		_(lua_Number, luaL_checknumber, lua_State* L, int arg);

		_(lua_Number, luaL_optnumber, lua_State* L, int arg, lua_Number def);

		_(lua_Integer, luaL_checkinteger, lua_State* L, int arg);

		_(lua_Integer, luaL_optinteger, lua_State* L, int arg, lua_Integer def);

		_(const char*, luaL_checklstring, lua_State* L, int arg, size_t* len);

		_(const char*, luaL_optlstring, lua_State* L, int arg, const char* def, size_t* len);

		void lua_remove(lua_State* L, int index)
		{
			lua_rotate(L, index, -1);
			lua_pop(L, 1);
		}

		int lua_upvalueindex(int i) const
		{
			return LUA_REGISTRYINDEX - i;
		}

		const char* lua_tostring(lua_State* L, int i) const
		{
			return lua_tolstring(L, i, NULL);
		}

		int lua_istable(lua_State* L, int n) const
		{
			return lua_type(L, n) == LUA_TTABLE;
		}

		int lua_isboolean(lua_State* L, int n) const
		{
			return lua_type(L, n) == LUA_TBOOLEAN;
		}

		void lua_newtable(lua_State* L) const
		{
			lua_createtable(L, 0, 0);
		}

		void lua_pushstdstring(lua_State* L, std::string const& s) const
		{
			lua_pushlstring(L, s.data(), s.size());
		}

		void lua_pushstdstringview(lua_State* L, std::string_view s) const
		{
			lua_pushlstring(L, s.data(), s.size());
		}

		void lua_pushcfunction(lua_State* L, lua_CFunction f) const
		{
			lua_pushcclosure(L, f, 0);
		}

		int lua_isstdstring(lua_State* L, int i) const
		{
			return lua_isstring(L, i);
		}

		int lua_isstdstringview(lua_State* L, int i) const
		{
			return lua_isstring(L, i);
		}

		std::string lua_tostdstring(lua_State* L, int i) const
		{
			size_t len = 0;
			const char* str = lua_tolstring(L, i, &len);
			return std::string(str, len);
		}

		std::string_view lua_tostdstringview(lua_State* L, int i) const
		{
			size_t len = 0;
			const char* str = lua_tolstring(L, i, &len);
			return std::string_view(str, len);
		}

		template <class Map = std::map<std::string, std::string>>
		void lua_pushmapstringstring(lua_State* L, std::type_identity_t<Map> const& m) const
		{
			lua_createtable(L, 0, m.size());
			for (const auto& [key, value] : m) {
				lua_pushstdstring(L, key);
				lua_pushstdstring(L, value);
				lua_settable(L, -3);
			}
		}

		void lua_pushvectorstring(lua_State* L, std::vector<std::string> const& v) const
		{
			lua_createtable(L, v.size(), 0);
			for (size_t i = 0; i < v.size(); i++) {
				lua_pushinteger(L, i + 1);
				lua_pushstdstring(L, v[i]);
				lua_settable(L, -3);
			}
		}

		void lua_pushvectorinteger(lua_State* L, std::vector<lua_Integer> const& v) const
		{
			lua_createtable(L, v.size(), 0);
			for (size_t i = 0; i < v.size(); i++) {
				lua_pushinteger(L, i + 1);
				lua_pushinteger(L, v[i]);
				lua_settable(L, -3);
			}
		}

		template <class Map = std::map<std::string, std::string>>
		int lua_ismapstringstring(lua_State* L, int i) const
		{
			return lua_istable(L, i);
		}

		int lua_isvectorstring(lua_State* L, int i) const
		{
			return lua_istable(L, i);
		}

		int lua_isvectorcstring(lua_State* L, int i) const
		{
			return lua_istable(L, i);
		}

		int lua_isvectorinteger(lua_State* L, int i) const
		{
			return lua_istable(L, i);
		}

		template <class Map = std::map<std::string, std::string>>
		Map lua_tomapstringstring(lua_State* L, int i) const
		{
			Map ret;
			lua_pushnil(L); // first key
			while (lua_next(L, i) != 0) {
				// uses 'key' (at index -2) and 'value' (at index -1)
				ret.emplace(lua_tostdstring(L, -2), lua_tostdstring(L, -1));
				// removes 'value'; keeps 'key' for next iteration
				lua_pop(L, 1);
			}
			return ret;
		}

		std::vector<std::string> lua_tovectorstring(lua_State* L, int i) const
		{
			std::vector<std::string> ret;
			lua_pushnil(L); // first key
			while (lua_next(L, i) != 0) {
				// uses 'key' (at index -2) and 'value' (at index -1)
				ret.push_back(lua_tostdstring(L, -1));
				// removes 'value'; keeps 'key' for next iteration
				lua_pop(L, 1);
			}
			return ret;
		}

		std::vector<const char*> lua_tovectorcstring(lua_State* L, int i) const
		{
			std::vector<const char*> ret;
			lua_pushnil(L); // first key
			while (lua_next(L, i) != 0) {
				// uses 'key' (at index -2) and 'value' (at index -1)
				ret.push_back(lua_tostring(L, -1));
				// removes 'value'; keeps 'key' for next iteration
				lua_pop(L, 1);
			}
			return ret;
		}

		std::vector<lua_Integer> lua_tovectorinteger(lua_State* L, int i) const
		{
			std::vector<lua_Integer> ret;
			lua_pushnil(L); // first key
			while (lua_next(L, i) != 0) {
				// uses 'key' (at index -2) and 'value' (at index -1)
				lua_Integer id = lua_tointeger(L, -1);
				ret.push_back(id);
				// removes 'value'; keeps 'key' for next iteration
				lua_pop(L, 1);
			}
			return ret;
		}

		lua_Number lua_tonumber(lua_State* L, int i) const
		{
			return	lua_tonumberx(L, i, NULL);
		}

		void lua_pop(lua_State* L, int n) const
		{
			lua_settop(L, -n - 1);
		}

		lua_Integer lua_tointeger(lua_State* L, int i) const
		{
			return lua_tointegerx(L, i, NULL);
		}

		void lua_call(lua_State* L, int n, int r) const
		{
			return lua_callk(L, n, r, 0, NULL);
		}

		int lua_pcall(lua_State* L, int n, int r, int f) const
		{
			return lua_pcallk(L, n, r, f, 0, NULL);
		}

		int lua_isnone(lua_State* L, int n) const
		{
			return lua_type(L, (n)) == LUA_TNONE;
		}

		int lua_isnoneornil(lua_State* L, int n) const
		{
			return lua_type(L, (n)) <= 0;
		}

		int lua_isnil(lua_State* L, int idx) const {
			return lua_type(L, idx) == LUA_TNIL;
		}

		const char* luaL_checkstring(lua_State* L, int n) const
		{
			return luaL_checklstring(L, n, NULL);
		}

		const char* luaL_optstring(lua_State* L, int n, const char* d) const
		{
			return luaL_optlstring(L, n, d, NULL);
		}

	};
#pragma warning(default: 6387)//重新启用警告C6387
#undef _
}
