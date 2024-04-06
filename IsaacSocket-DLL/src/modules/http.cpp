#include "module.hpp"
#include "result.hpp"
#include "udata.hpp"
#include "isaac_socket.hpp"

#include <mytask/mytask.hpp>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>

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

                    task.state = task.COMPLETED;
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
        mytask::Run([&task, url] {
            try {
                Poco::URI uri(url);

                Poco::Net::HTTPSClientSession https(uri.getHost(), uri.getPort());
                Poco::Net::HTTPClientSession http(uri.getHost(), uri.getPort());

                Poco::Net::HTTPClientSession* p;
                p = &http;

                if (uri.getScheme() == "https")
                {
                    p = &https;
                }

                auto& session = *p;

                Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPath(), Poco::Net::HTTPRequest::HTTP_1_1);
                session.sendRequest(request);
                Poco::Net::HTTPResponse response;
                string body;
                session.receiveResponse(response) >> body;
                result::Push(result::ResponseResult(task.id, response, body));
            }
            catch (Poco::Exception& ex) {
                result::Push(result::ErrorResult(task.id, ex.displayText()));
            }
            catch (std::exception& ex) {
                result::Push(result::ErrorResult(task.id, ex.what()));
            }
            });
        return 1;
    }

    static RegisterModule InitModules = [] {
        MODULE_BEGIN(HTTP);
        MODULE_FUNC(GetAsync);
        MODULE_END();
        };
};
