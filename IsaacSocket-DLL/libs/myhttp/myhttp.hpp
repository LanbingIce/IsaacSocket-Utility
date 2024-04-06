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
        std::function<void(Poco::Net::HTTPResponse::HTTPStatus, const string&, const std::map<string, string>&, const string&)>OnComplete = [](Poco::Net::HTTPResponse::HTTPStatus, const string&, const std::map<string, string>&, const string&) {};
        std::function<void(const string&) >OnError = [](const string&) {};

        void Send();

        HTTPState GetState();
        bool IsFaulted();
        MyHTTP(const string& url, const std::map<string, string>& headers, const string& body = "", bool post = false);
        MyHTTP(const MyHTTP&);
        ~MyHTTP();
    private:
        void _Connect();
        string _url;
        std::map<string, string> _headers;
        bool _post;
        bool _fault = false;
        string _body;
        std::mutex _mutex;
        HTTPState _state = NONE;
    };
}
