#pragma once
#include <Poco/Net/HTTPResponse.h>

namespace myhttp {
    enum HTTPState
    {
        NONE,
        CONNECTING,
        OPEN,
        CLOSED,
        DEAD
    };

    class MyHTTP
    {
    public:
        std::function<void(const Poco::Net::HTTPResponse&, const string&)>OnClose = [](const Poco::Net::HTTPResponse&, const string&) {};
        std::function<void(const string&) >OnError = [](const string & = "") {};

        void Connect();

        HTTPState GetState();

        MyHTTP(const string& url);
        ~MyHTTP();
    private:
        void _SetState(HTTPState state);
        void _Connect();
        const string _url;
        std::mutex _mutex;
        HTTPState _state = NONE;
    };
}
