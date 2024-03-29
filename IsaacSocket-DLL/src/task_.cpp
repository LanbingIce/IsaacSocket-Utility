#include <Poco/TaskManager.h>

namespace task_ {
	struct _Task : Poco::Task {
		_Task(std::function<void()> callback) : Task(""), callback(callback) {}
		std::function < void()> callback;
		void runTask() {
			callback();
		}
	};

	void Run(std::function <void()> callback)
	{
		static Poco::TaskManager taskManager;
		taskManager.start(new _Task(callback));
	}
}
