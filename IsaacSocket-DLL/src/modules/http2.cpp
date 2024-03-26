#include "task_.hpp"
#include "module.hpp"
#include "state.hpp"

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/TaskManager.h>
#include <Poco/Task.h>

namespace http2
{
	static void SetResult(size_t id, string s) {
		std::lock_guard lock(local.mutex);
		local.tasks.push_back(result::TaskResult(id, s));
	}

	static int GetAsync(lua_State* L) {
		ARG(1, string, const char*, url);
		size_t id = task_::New();

		task_::Run([id, url] {

			try {
				Poco::URI uri(url);
				Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
				Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPath(), Poco::Net::HTTPRequest::HTTP_1_1);
				session.sendRequest(request);
				Poco::Net::HTTPResponse response;
				std::istream& is = session.receiveResponse(response);
				std::ostringstream oss;
				oss << is.rdbuf();
				SetResult(id, oss.str());
			}
			catch (Poco::Exception& ex) {
				SetResult(id, ex.displayText());
			}
			catch (std::exception& ex) {
				SetResult(id, ex.what());
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
