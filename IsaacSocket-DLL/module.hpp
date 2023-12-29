#pragma once

#include "lua.hpp"
#include "state.hpp"

#define DEFMOD(name) lua_State* L = local.isaac->luaVM->L; int top = local.lua.lua_gettop(L); local.lua.lua_getglobal(L, "_ISAAC_SOCKET"); local.lua.lua_pushstring(L, "IsaacSocket"); local.lua.lua_gettable(L, -2); local.lua.lua_pushstring(L, #name); local.lua.lua_newtable(L);
#define DEF(name) local.lua.lua_pushstring(L, #name);local.lua.lua_pushcfunction(L, name); local.lua.lua_settable(L, -3)
#define ENDMOD() local.lua.lua_settable(L, -3); local.lua.lua_settop(L, top);

#define _CHECK_ARG(index,luaType,type,name) if(local.lua.lua_is##luaType(L,index)){name = (type)local.lua.lua_to##luaType(L,index);}else{return local.lua.luaL_error(L, "bad argument #"#index": "#name" should be "#luaType);}
#define ARG(index,luaType,type,name) type name; _CHECK_ARG(index,luaType,type,name)
#define ARG_DEF(index,luaType,type,name,def) type name;if(local.lua.lua_isnoneornil(L,index)){name=def;}else _CHECK_ARG(index,luaType,type,name)
#define ARG_RANGE(name,range) if (name >= range){std::ostringstream oss;oss<<"invalid "#name": "<<std::to_string(name); return local.lua.luaL_error(L, oss.str().c_str());}
#define RET(type,value) local.lua.lua_push##type(L,value);return 1;
