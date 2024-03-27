#include "task_.hpp"
#include "state.hpp"
#include "module.hpp"
#include "isaac_socket.hpp"
#include "udata.hpp"

#include <Poco/TaskManager.h>

namespace task_ {
	struct _Task : Poco::Task {
		_Task(std::function<void()> callback) : Task(""), callback(callback) {}
		std::function < void()> callback;
		void runTask() {
			callback();
		}
	};

	size_t New() {
		auto& task = NEW_UDATA(Task);
		return task.id;
	}

	void Run(std::function <void()> callback)
	{
		static Poco::TaskManager taskManager;
		taskManager.start(new _Task(callback));
	}
}
