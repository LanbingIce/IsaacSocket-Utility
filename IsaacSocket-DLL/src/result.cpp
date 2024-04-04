#include "result.hpp"

namespace result {
    static std::mutex _resultMutex;
    static std::queue<std::any> _results;
    void Push(const std::any& result) {
        std::lock_guard lock(_resultMutex);
        _results.push(result);
    }

    std::any Pop() {
        std::lock_guard lock(_resultMutex);
        if (_results.empty())
        {
            return std::any{};
        }
        std::any result = _results.front();
        _results.pop();
        return result;
    }

    void Clear() {
        std::lock_guard lock(_resultMutex);
        while (!_results.empty()) {
            _results.pop();
        }
    }
}
