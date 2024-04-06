#include "module.hpp"
#include "result.hpp"
#include "udata.hpp"
#include "isaac_socket.hpp"

#include <myhttp/myhttp.hpp>
#include <Poco/Net/HTTPResponse.h>

namespace udata {
    int ResponseResult::lua_index(lua_State* L) {
        auto& result = ARG_UDATA(1, udata::ResponseResult);
        METATABLE_BEGIN(ResponseResult, result);
        METATABLE_INDEX(stdstring, body);
        METATABLE_END();
    }
    int ResponseResult::lua_newindex(lua_State* L) {
        METATABLE_END();
    }
}

namespace result {
    static RegisterResultType HandleResult(
        [](const std::any& aResult, lua_State* L)
        {
            if (aResult.type() == typeid(result::ResponseResult))
            {
                const auto& result = std::any_cast<const result::ResponseResult&>(aResult);

                GET_TASK_AND_TASK_CALLBACK(result.id);
                if (lua_isuserdata(L, -1))
                {
                    auto& task = ARG_UDATA(-1, udata::Task);
                    task.result = result;
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

namespace http
{
    static int GetAsync(lua_State* L) {
        ARG(1, string, const char*, url);
        auto& task = NEW_UDATA(Task);
        task.executor = myhttp::MyHTTP(url, false);
        auto& http = std::any_cast<myhttp::MyHTTP&>(task.executor);

        http.OnComplete = [&task](Poco::Net::HTTPResponse& response, const string& body) {
            std::lock_guard lock(task._mutex);
            if (task.state == task.RUNNING)
            {
                task.state = task.COMPLETED;
                result::Push(result::ResponseResult(task.id, response, body));
            }
            };
        http.OnError = [&task](const string& error) {
            std::lock_guard lock(task._mutex);
            if (task.state == task.RUNNING)
            {
                task.state = task.FAULTED;
                result::Push(result::ErrorResult(task.id, error));
            }
            };
        http.Send();
        return 1;
    }

    static RegisterModule InitModules = [] {
        MODULE_BEGIN(HTTP);
        MODULE_FUNC(GetAsync);
        MODULE_END();
        };
};
