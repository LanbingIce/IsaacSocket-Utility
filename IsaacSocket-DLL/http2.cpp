#include "module.hpp"

#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/TaskManager.h>
#include <Poco/Task.h>
#include "function.hpp"

namespace http2
{
	class MyTask : public Poco::Task {
	public:
		MyTask() : Poco::Task("MyTask") {}

		void runTask() override {
			Sleep(3000);
			function_::ConsoleOutput("Completed!\n");
		}
	};

	static int TaskTest(lua_State* L) {
		MyTask* pTask = new MyTask();
		local.taskManager->start(pTask);
		function_::ConsoleOutput("start\n");
		return 0;
	}

	static int Get(lua_State* L) {
		ARG(1, string, const char*, url);
		try {
			Poco::URI uri(url);
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
			Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPath(), Poco::Net::HTTPRequest::HTTP_1_1);
			session.sendRequest(request);
			Poco::Net::HTTPResponse response;
			std::istream& is = session.receiveResponse(response);

			std::ostringstream oss;
			oss << is.rdbuf();
			RET(string, oss.str().c_str());
		}
		catch (Poco::Exception& ex) {
			RET(string, ex.displayText().c_str());
		}
		catch (std::exception& ex) {
			RET(string, ex.what());
		}
	}

	static RegisterModule Init = [] {
		MODULE_BEGIN(HTTP2);
		MODULE_FUNC(Get);
		MODULE_FUNC(TaskTest);
		MODULE_END();
		};
};
