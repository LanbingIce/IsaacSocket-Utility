#pragma once

#include "lua.hpp"
#include "state.hpp"

namespace lua {
#define NEW_CPPDATA(type) new (local.lua.luaCPP_newuserdata<type>(L, type::lua_index,type::lua_newindex, lua::lua_cppdata_gc<type>)) type
#define ARG_CPPDATA(index,type,name) type *name = local.lua.luaCPP_getuserdata<type>(L, index)

	template <class T>
	static int lua_cppdata_gc(lua_State* L) {
		T* p = local.lua.luaCPP_getuserdata<T>(L, 1);
		p->~T();
		return 0;
	}

	template <int (*fp)(lua_State*)>
	static int (*lua_cppfunction())(lua_State*) {
		return [](lua_State* L) noexcept -> int {
			try {
				return fp(L);
			}
			catch (std::exception const& e) {
				cw("Exception in cpp function:", e.what());
				return local.lua.luaL_error(L, "Exception in cpp function: %s", e.what());
			}
			catch (...) {
				cw("Exception in cpp function: unknown exception");
				return local.lua.luaL_error(L, "Exception in cpp function: unknown exception");
			}
			};
	}

}

#define NEW_UDATA(type,name) type& name = *(type*)local.lua.lua_newuserdata(L, sizeof(type))
#define SET_METATABLE(name) if(local.lua.luaL_newmetatable(L, #name)){luaL_Reg mt_##name[] = { { "__index", name##__index },{ "__newindex", name##__newindex },{ NULL, NULL } };local.lua.luaL_setfuncs(L, mt_##name, 0);}local.lua.lua_setmetatable(L, -2)

#define MODULE_BEGIN(name) lua_State* L = local.isaac->luaEngine->L; int top = local.lua.lua_gettop(L); local.lua.lua_getglobal(L, "_ISAAC_SOCKET"); local.lua.lua_pushstring(L, "IsaacSocket"); local.lua.lua_gettable(L, -2); local.lua.lua_pushstring(L, #name); local.lua.lua_newtable(L)
#define MODULE_FUNC(name) local.lua.lua_pushstring(L, #name);local.lua.lua_pushcfunction(L, lua::lua_cppfunction<name>()); local.lua.lua_settable(L, -3)
#define MODULE_UDATA(name,type,value)local.lua.lua_pushstring(L, #name);type** pp_##name = (type**)local.lua.lua_newuserdata(L, sizeof(type*));SET_METATABLE(p_##name);*pp_##name = &value;local.lua.lua_settable(L, -3)
#define MODULE_END() local.lua.lua_settable(L, -3); local.lua.lua_settop(L, top)

#define _CHECK_ARG(index,luaType,type,name) if(local.lua.lua_is##luaType(L,index)){name = (type)local.lua.lua_to##luaType(L,index);}else{return local.lua.luaL_error(L, "bad argument #"#index": "#name" should be "#luaType);}
#define ARG(index,luaType,type,name) type name; _CHECK_ARG(index,luaType,type,name)
#define ARG_DEF(index,luaType,type,name,def) type name;if(local.lua.lua_isnoneornil(L,index)){name=def;}else _CHECK_ARG(index,luaType,type,name)
#define ARG_RANGE(name,range) if (name >= range){std::ostringstream oss;oss<<"invalid "#name": "<<std::to_string(name); return local.lua.luaL_error(L, oss.str().c_str());}

#define _CHECK_ARG_UDATA(index,udataType,type,name)p_##name = (type*)local.lua.luaL_checkudata(L, index, #udataType);type& name = *p_##name
#define ARG_UDATA(index,udataType,type,name)type* p_##name; _CHECK_ARG_UDATA(index,udataType,type,name)
#define ARG_UDATA_DEF(index,udataType,type,name,def)type* p_##name;if(local.lua.lua_isnoneornil(L,index)){p_##name=&def;}else _CHECK_ARG_UDATA(index,udataType,type,name)

#define _LUA_PCALL(paramNum,resultNum)if(local.lua.lua_pcall(L, paramNum, resultNum, 0)!=LUA_OK){ARG_DEF(-1,stdstring,string,_err,"unknow error!");local.lua.lua_pop(L, 1);for(int i=0;i<resultNum;i++){local.lua.lua_pushnil(L);}_err.append("\n");function::ConsoleOutput(_err, 0xFFF08080);}

#define RET(type,value) local.lua.lua_push##type(L,value);return 1

#define RET_TABLE() local.lua.lua_newtable(L)
#define RET_TABLE_KEY(keyType,key,valueType,value) local.lua.lua_push##keyType(L,key);local.lua.lua_push##valueType(L,value);local.lua.lua_settable(L,-3)
#define RET_TABLE_END() return 1

#define MOD_CALLBACK_BEGIN(name){lua_State* L = local.isaac->luaEngine->L;size_t top = local.lua.lua_gettop(L);local.lua.lua_getglobal(L, "Isaac");local.lua.lua_pushstring(L, "GetCallbacks");local.lua.lua_gettable(L, -2);local.lua.lua_pushstring(L, #name);_LUA_PCALL(1, 1);bool terminate = false;local.lua.lua_pushnil(L);while(local.lua.lua_next(L, -2) != 0){local.lua.lua_pushstring(L, "Function");local.lua.lua_gettable(L, -2);local.lua.lua_pushstring(L, "Mod");local.lua.lua_gettable(L, -3);size_t paramNum = 1
#define MOD_CALLBACK_ARG(paramType,...)local.lua.lua_push##paramType(L, __VA_ARGS__);paramNum++
#define MOD_CALLBACK_CALL()_LUA_PCALL(paramNum, 1)
#define MOD_CALLBACK_END()if(!local.lua.lua_isnil(L, -1)){terminate = true;}local.lua.lua_pop(L, 2);}local.lua.lua_settop(L, top);if(terminate){return 1;}}

#define FAST_MOD_CALLBACK_BEGIN(name){lua_State* L = local.isaac->luaEngine->L;size_t top = local.lua.lua_gettop(L);local.lua.lua_getglobal(L, "Isaac");local.lua.lua_pushstring(L, "RunCallback");local.lua.lua_gettable(L, -2);local.lua.lua_pushstring(L, #name);size_t paramNum = 1
#define FAST_MOD_CALLBACK_END()if(local.lua.lua_pcall(L, paramNum, 0, 0)!=LUA_OK){ARG_DEF(-1,string,string,_err,"unknow error!");_err.append("\n");function::ConsoleOutput(_err, 0xFFF08080);}local.lua.lua_settop(L, top);}

#define _METATABLE_ERROR(luaType,name)else{return local.lua.luaL_error(L, "bad value, "#name" should be "#luaType);}}
#define _METATABLE_INDEX(luaType,name,result)if(strcmp(key, #name) == 0){RET(luaType,result);}
#define _METATABLE_NEWINDEX(luaType,name,result,...)if(strcmp(key, #name) == 0){if(local.lua.lua_is##luaType(L,3)){_obj.name = (decltype(_obj.name))local.lua.lua_to##luaType(L,3);__VA_ARGS__;return 0;}_METATABLE_ERROR(luaType,name)

#define METATABLE_BEGIN(type,object)type& _obj = object;const char* key = local.lua.lua_tostring(L, 2)
#define METATABLE_INDEX(luaType,name)_METATABLE_INDEX(luaType,name,_obj.name)
#define METATABLE_NEWINDEX(luaType,name,...)_METATABLE_NEWINDEX(luaType,name,_obj.name,__VA_ARGS__)

#define _METATABLE_INDEX_UDATA(udataType,name,type,and_,star) if (strcmp(key,#name) == 0) {if (local.lua.lua_isnone(L, 3)) {type* p_##name = (type*)local.lua.lua_newuserdata(L, sizeof(type));SET_METATABLE(udataType);*p_##name = and_ _obj.name;return 1;}else { type* _value = (type*)local.lua.luaL_testudata(L,3,#udataType); if(_value){_obj.name =star *_value;return 0;}}}
#define METATABLE_INDEX_UDATA(udataType,name,type) _METATABLE_INDEX_UDATA(udataType,name,type)
#define METATABLE_INDEX_UDATA_P(udataType,name,type) _METATABLE_INDEX_UDATA(udataType,name,type,&,*)

#define METATABLE_INDEX_STRING(name)_METATABLE_INDEX(string,name,_obj.name.c_str())
#define METATABLE_END()return local.lua.luaL_error(L, "Invalid member access.")

struct Image {
	std::vector<uint8_t> data;
	int width = 0, height = 0, channels = 0;

	static int lua_index(lua_State* L) {
		ARG_CPPDATA(1, Image, image);
		METATABLE_BEGIN(Image, *image);
		METATABLE_INDEX(integer, width);
		METATABLE_INDEX(integer, height);
		METATABLE_INDEX(integer, channels);
		METATABLE_END();
	}

	static int lua_newindex(lua_State* L) {
		METATABLE_END();
	}
};

struct RegisterModule {
	inline static std::vector<std::function<void()>> initCallbacks;

	RegisterModule(auto&& f) {
		initCallbacks.emplace_back(std::move(f));
	}

	static void InitAllModules() {
		for (auto const& callback : initCallbacks) {
			callback();
		}
	}
};
