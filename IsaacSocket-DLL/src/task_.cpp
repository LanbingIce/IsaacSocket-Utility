#include "udata.hpp"
#include "isaac_socket.hpp"
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
        std::lock_guard lock(task._mutex);
        switch (task.state)
        {
        case RUNNING:
            lua_pushnil(L);
            break;
        case COMPLETED:
            if (task.result.type() == typeid(result::ResponseResult))
            {

                auto& response = NEW_UDATA(ResponseResult);
                const auto& result = std::any_cast<result::ResponseResult&>(task.result);
                response.statusCode = result.statusCode;
                response.reasonPhrase = result.reasonPhrase;
                response.headers = result.headers;
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

namespace task_ {
    static result::RegisterResultType HandleResult(
        [](const std::any& aResult, lua_State* L)
        {
            if (aResult.type() == typeid(result::ErrorResult))
            {
                const auto& result = std::any_cast<const result::ErrorResult&>(aResult);

                GET_TASK_AND_TASK_CALLBACK(result.id);
                if (lua_isuserdata(L, -1))
                {
                    auto& task = ARG_UDATA(-1, udata::Task);
                    task.state = task.FAULTED;
                    task.error = result.error;

                    TASK_CALLBACK_AND_SET_NIL(result.id);
                }
            }
            else
            {
                return false;
            }
            return true;
        });
}