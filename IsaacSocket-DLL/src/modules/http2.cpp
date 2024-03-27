#include "task_.hpp"
#include "module.hpp"
#include "state.hpp"
#include "result.hpp"

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/TaskManager.h>
#include <Poco/Task.h>

namespace http2
{
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
				local.pResults.push_back(new result::TaskResult{id, oss.str() });
			}
			catch (Poco::Exception& ex) {
				local.pResults.push_back(new result::TaskResult(id, ex.displayText()));
			}
			catch (std::exception& ex) {
				local.pResults.push_back(new result::TaskResult(id, ex.what()));
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
