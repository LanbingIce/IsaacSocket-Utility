#include "mytask.hpp"

#include <Poco/Task.h>
#include <Poco/TaskManager.h>
#include <Poco/ThreadPool.h>

namespace mytask {
    class _Task :public Poco::Task
    {
    public:
        static void Run(const std::function<void()>& callback) {
            static Poco::ThreadPool pool(1, INT_MAX);
            static Poco::TaskManager taskManager(pool);
            taskManager.start(new _Task(callback));
        }
    private:
        _Task(const std::function<void()>& callback) : Task(""), _callback(callback) {}
        void runTask() {
            _callback();
        }
        std::function <void()> _callback;
    };

    void Run(std::function <void()> callback)
    {
        _Task::Run(callback);
    }
}
