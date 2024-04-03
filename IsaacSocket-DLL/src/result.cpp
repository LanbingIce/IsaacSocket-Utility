#include "result.hpp"

namespace result {
    static std::mutex _resultMutex;
    static std::queue<std::shared_ptr<result::Result>> pResults;
    void Push(const std::shared_ptr<result::Result>& result) {
        std::lock_guard lock(_resultMutex);
        pResults.push(result);
    }

    std::shared_ptr<result::Result> Pop() {
        std::lock_guard lock(_resultMutex);
        if (pResults.empty())
        {
            return nullptr;
        }
        auto p = pResults.front();
        pResults.pop();
        return p;
    }

    void Clear() {
        std::lock_guard lock(_resultMutex);
        while (!pResults.empty()) {
            pResults.pop();
        }
    }
}
