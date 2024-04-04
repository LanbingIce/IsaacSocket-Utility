#include "udata.hpp"
#include "module.hpp"

namespace udata {
    Task::Task() :id(
        [] {
            static int nextId;
            static std::mutex _mutex;
            std::lock_guard lock(_mutex);
            return  ++nextId;
        }())
    {
        int top = lua_gettop(L);
        SET_CALLBACK(top, tasks);
    }

    int Task::IsCompletedSuccessfully(lua_State* L) {
        auto& task = ARG_UDATA(1, udata::Task);
        lua_pushboolean(L, task.state == task.COMPLETED);
        return 1;
    }

    int Task::IsFaulted(lua_State* L) {
        auto& task = ARG_UDATA(1, udata::Task);
        lua_pushboolean(L, task.state == task.FAULTED);
        return 1;
    }

    int Task::IsCompleted(lua_State* L) {
        auto& task = ARG_UDATA(1, udata::Task);
        lua_pushboolean(L, task.state != task.RUNNING);
        return 1;
    }

    int Task::GetResult(lua_State* L) {
        auto& task = ARG_UDATA(1, udata::Task);

        switch (task.state)
        {
        case RUNNING:
            lua_pushnil(L);
            break;
        case COMPLETED:
            if (typeid(*task.pResult).name() == typeid(result::ResponseResult).name())
            {

                auto& response = NEW_UDATA(ResponseResult);
                auto& result = (result::ResponseResult&)*task.pResult;
                response.body = result.body;
            }
            break;
        case FAULTED:
            lua_pushstring(L, task.error.c_str());
            break;
        }
        return 1;
    }

    int Task::Then(lua_State* L) {
        auto& task = ARG_UDATA(1, udata::Task);
        ARG_CALLBACK(2, continuation);
        lua_settop(L, 2);
        int id = task.id;
        SET_CALLBACK(2, taskCallbacks);
        return 0;
    }

    int Task::lua_index(lua_State* L) {
        auto& task = ARG_UDATA(1, udata::Task);
        METATABLE_BEGIN(Task, task);
        METATABLE_INDEX(cfunction, Then);
        METATABLE_INDEX(cfunction, IsCompletedSuccessfully);
        METATABLE_INDEX(cfunction, IsFaulted);
        METATABLE_INDEX(cfunction, IsCompleted);
        METATABLE_INDEX(cfunction, GetResult);
        METATABLE_END();
    }

    int Task::lua_newindex(lua_State* L) {
        METATABLE_END();
    }
}