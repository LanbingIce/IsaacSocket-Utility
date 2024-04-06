#pragma once
#include <Poco/Net/HTTPResponse.h>

namespace myhttp {
    enum HTTPState
    {
        NONE = 0,
        RUNNING = 1,
        COMPLETED = 2,
        DEAD = 3
    };

    class MyHTTP
    {
    public:
        std::function<void(Poco::Net::HTTPResponse&, const string&)>OnComplete = [](Poco::Net::HTTPResponse&, const string&) {};
        std::function<void(const string&) >OnError = [](const string&) {};

        void Send();

        HTTPState GetState();
        bool IsFaulted();
        MyHTTP(const string& url, bool post);
        MyHTTP(const MyHTTP&);
        ~MyHTTP();
    private:
        void _Connect();
        const string _url;
        bool _post;
        bool _fault = false;
        std::mutex _mutex;
        HTTPState _state = NONE;
    };
}
