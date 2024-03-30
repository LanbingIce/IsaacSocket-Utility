#include "udata.hpp"
#include "module.hpp"
#include "state.hpp"
#include <Poco/TaskManager.h>

udata::Task::Task() {
    std::lock_guard lock(local.mutex);
    id = ++nextId;
}

int udata::Task::IsCompletedSuccessfully(lua_State* L) {
    auto& task = ARG_UDATA(1, udata::Task);
    lua_pushboolean(L, task.state == task.COMPLETED);
    return 1;
}

int udata::Task::IsFaulted(lua_State* L) {
    auto& task = ARG_UDATA(1, udata::Task);
    lua_pushboolean(L, task.state == task.FAULTED);
    return 1;
}

int udata::Task::IsCompleted(lua_State* L) {
    auto& task = ARG_UDATA(1, udata::Task);
    lua_pushboolean(L, task.state != task.RUNNING);
    return 1;
}

int udata::Task::GetResult(lua_State* L) {
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

int udata::Task::Then(lua_State* L) {
    auto& task = ARG_UDATA(1, udata::Task);
    ARG_CALLBACK(2, continuation);
    lua_settop(L, 2);
    int id = task.id;
    SET_CALLBACK(2, taskCallbacks);
    return 0;
}

int udata::Task::lua_index(lua_State* L) {
    auto& task = ARG_UDATA(1, udata::Task);
    METATABLE_BEGIN(Task, task);
    METATABLE_INDEX(cfunction, Then);
    METATABLE_INDEX(cfunction, IsCompletedSuccessfully);
    METATABLE_INDEX(cfunction, IsFaulted);
    METATABLE_INDEX(cfunction, IsCompleted);
    METATABLE_INDEX(cfunction, GetResult);
    METATABLE_END();
}

int udata::Task::lua_newindex(lua_State* L) {
    METATABLE_END();
}

namespace task_ {
    struct _Task : Poco::Task {
        _Task(std::function<void()> callback) : Task(""), callback(callback) {}
        std::function < void()> callback;
        void runTask() {
            callback();
        }
    };

    Poco::Task* Run(std::function <void()> callback)
    {
        static Poco::TaskManager taskManager;
        auto pTask = new _Task(callback);
        taskManager.start(pTask);
        return pTask;
    }
}
