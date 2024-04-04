#include "module.hpp"
#include "result.hpp"
#include "udata.hpp"

#include <mytask/mytask.hpp>

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>

int udata::ResponseResult::lua_index(lua_State* L) {
    auto& result = ARG_UDATA(1, udata::ResponseResult);
    METATABLE_BEGIN(ResponseResult, result);
    METATABLE_INDEX(stdstring, body);
    METATABLE_END();
}
int udata::ResponseResult::lua_newindex(lua_State* L) {
    METATABLE_END();
}

namespace http
{
    static int GetAsync(lua_State* L) {
        ARG(1, string, const char*, url);
        lua_settop(L, 1);
        auto& task = NEW_UDATA(Task);
        int id = task.id;
        SET_CALLBACK(2, tasks);
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
                result::Push(std::make_shared<result::ResponseResult>(task.id, body, response));
            }
            catch (Poco::Exception& ex) {
                result::Push(std::make_shared<result::ErrorResult>(task.id, ex.displayText()));
            }
            catch (std::exception& ex) {
                result::Push(std::make_shared<result::ErrorResult>(task.id, ex.what()));
            }
            });
        return 1;
    }

    static RegisterModule InitModules = [] {
        MODULE_BEGIN(HTTP2);
        MODULE_FUNC(GetAsync);
        MODULE_END();
        };
};
