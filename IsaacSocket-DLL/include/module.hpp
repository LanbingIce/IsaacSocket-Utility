#pragma once
#include "pch.h"

#define _SET_METATABLE(udataName,type) if(luaL_newmetatable(L, typeid(type).name())){luaL_Reg _metatable[] = { { "__index", udataName::__index },{ "__newindex", udataName::__newindex },{ NULL, NULL } };luaL_setfuncs(L, _metatable, 0);}lua_setmetatable(L, -2)

#define _CHECK_ARG(index,luaType,type,name) if(lua_is##luaType(L,index)){name = (type)lua_to##luaType(L,index);}else{return luaL_error(L, "bad argument #"#index": "#name" should be "#luaType);}
#define _CHECK_ARG_UDATA(index,type)p = luaCPP_getuserdata<type>(L, index) ;return p

#define NEW_UDATA(type)*new (luaCPP_newuserdata<udata::type>(L, udata::type::lua_index,udata::type::lua_newindex, lua_cppdata_gc<udata::type>)) udata::type
#define NEW_UDATA_META(type,metaName)*[L]{auto p=(type*)lua_newuserdata(L, sizeof(type));_SET_METATABLE(metaName,type);return p;}()

#define ARG_UDATA(index,type)*[L]{type* p; _CHECK_ARG_UDATA(index,type);}()
#define ARG_UDATA_DEF(index,type,def)*[L]{type* p; if(lua_isnoneornil(L,index)){p=&def;}else _CHECK_ARG_UDATA(index,type);}()

#define ARG(index,luaType,type,name) type name; _CHECK_ARG(index,luaType,type,name)
#define ARG_DEF(index,luaType,type,name,def) type name;if(lua_isnoneornil(L,index)){name=def;}else _CHECK_ARG(index,luaType,type,name)
#define ARG_RANGE(name,minValue,maxValue) if (name<minValue || name>maxValue){return luaL_error(L, ((string)("invalid "#name": ")+std::to_string(name)).c_str());}

#define MODULE_BEGIN(name) int top = lua_gettop(L); lua_getglobal(L, "_ISAAC_SOCKET"); lua_pushstring(L, "IsaacSocket"); lua_gettable(L, -2); lua_pushstring(L, #name); lua_newtable(L)
#define MODULE_FUNC(name) lua_pushstring(L, #name);lua_pushcfunction(L, lua_cppfunction<name>()); lua_settable(L, -3)
#define MODULE_UDATA(name,type,value)lua_pushstring(L, #name);type** pp_##name = (type**)lua_newuserdata(L, sizeof(type*));_SET_METATABLE(udata::p_##name,type*);*pp_##name = &value;lua_settable(L, -3)
#define MODULE_END() lua_settable(L, -3); lua_settop(L, top)

#define LUA_PCALL(paramNum,resultNum)if(lua_pcall(L, paramNum, resultNum, 0)!=LUA_OK){string _err;if(lua_type(L,-1)==LUA_TSTRING)_err=lua_tostring(L,-1);else _err="unknow error!";lua_pop(L, 1);if constexpr(resultNum) for(int i=0;i<resultNum;i++){lua_pushnil(L);}isaac_socket::ConsoleOutput(_err+"\n", 0xFFF08080);}

#define RET(type,value) lua_push##type(L,value);return 1

#define RET_TABLE() lua_newtable(L)
#define RET_TABLE_KEY(keyType,key,valueType,value) lua_push##keyType(L,key);lua_push##valueType(L,value);lua_settable(L,-3)
#define RET_TABLE_END() return 1

#define _MOD_CALLBACK_BEGIN(name)int top = lua_gettop(L);lua_getglobal(L, "Isaac");lua_pushstring(L, "GetCallbacks");lua_gettable(L, -2);lua_pushstring(L, #name);LUA_PCALL(1, 1);lua_pushnil(L);while(lua_next(L, -2) != 0){lua_pushstring(L, "Function");lua_gettable(L, -2);lua_pushstring(L, "Mod");lua_gettable(L, -3);size_t paramNum = 1
#define MOD_CALLBACK_BEGIN(name){bool terminate = false;_MOD_CALLBACK_BEGIN(name)
#define MOD_CALLBACK_ARG(paramType,...)lua_push##paramType(L, __VA_ARGS__);paramNum++
#define MOD_CALLBACK_CALL()LUA_PCALL(paramNum, 1)
#define MOD_CALLBACK_END()if(!lua_isnil(L, -1)){terminate = true;}lua_pop(L, 2);}lua_settop(L, top);if(terminate){return 1;}}

#define FAST_MOD_CALLBACK_BEGIN(name){_MOD_CALLBACK_BEGIN(name)
#define FAST_MOD_CALLBACK_END()MOD_CALLBACK_CALL();lua_pop(L, 2);}lua_settop(L, top);}

#define _METATABLE_ERROR(luaType,name)else{return luaL_error(L, "bad value, "#name" should be "#luaType);}}
#define _METATABLE_INDEX(luaType,name,result)if(strcmp(key, #name) == 0){RET(luaType,result);}
#define _METATABLE_NEWINDEX(luaType,name,result,...)if(strcmp(key, #name) == 0){if(lua_is##luaType(L,3)){_obj.name = (decltype(_obj.name))lua_to##luaType(L,3);__VA_ARGS__;return 0;}_METATABLE_ERROR(luaType,name)

#define METATABLE_BEGIN(type,object)type& _obj = object;const char* key = lua_tostring(L, 2)
#define METATABLE_INDEX(luaType,name)_METATABLE_INDEX(luaType,name,_obj.name)
#define METATABLE_NEWINDEX(luaType,name,...)_METATABLE_NEWINDEX(luaType,name,_obj.name,__VA_ARGS__)

#define _METATABLE_NEWINDEX_UDATA(udataName,name,type,star) if (strcmp(key,#name) == 0) { type* _value = (type*)luaL_testudata(L,3,#udataName); if(_value){_obj.name =star *_value;return 0;}}
#define METATABLE_NEWINDEX_UDATA(udataName,name,type) _METATABLE_NEWINDEX_UDATA(udataName,name,type)
#define METATABLE_NEWINDEX_UDATA_P(udataName,name,type) _METATABLE_NEWINDEX_UDATA(udataName,name,type,*)

#define _METATABLE_INDEX_UDATA(udataName,name,type,and_) if (strcmp(key,#name) == 0) {if (lua_isnone(L, 3)) {type* p_##name = (type*)lua_newuserdata(L, sizeof(type));_SET_METATABLE(udataName,type);*p_##name = and_ _obj.name;return 1;}}
#define METATABLE_INDEX_UDATA(udataName,name,type) _METATABLE_INDEX_UDATA(udataName,name,type)
#define METATABLE_INDEX_UDATA_P(udataName,name,type) _METATABLE_INDEX_UDATA(udataName,name,type,&)

#define METATABLE_INDEX_STRING(name)_METATABLE_INDEX(string,name,_obj.name.c_str())
#define METATABLE_END()return luaL_error(L, "Invalid member access.")

#define DO_STRING(code){int _top=lua_gettop(L);luaL_dostring(L,code);lua_settop(L,_top);}

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
