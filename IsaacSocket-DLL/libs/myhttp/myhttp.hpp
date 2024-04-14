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
        std::function<void(Poco::Net::HTTPResponse::HTTPStatus, const std::string&, const std::map<std::string, std::string>&, const std::string&)>OnComplete = [](Poco::Net::HTTPResponse::HTTPStatus, const std::string&, const std::map<std::string, std::string>&, const std::string&) {};
        std::function<void(const std::string&) >OnError = [](const std::string&) {};

        void Send();

        HTTPState GetState();
        bool IsFaulted();
        MyHTTP(const std::string& url, const std::map<std::string, std::string>& headers, const std::string& body = "", bool post = false);
        MyHTTP(const MyHTTP&);
        ~MyHTTP();
    private:
        void _Connect();
        std::string _url;
        std::map<std::string, std::string> _headers;
        bool _post;
        bool _fault = false;
        std::string _body;
        std::mutex _mutex;
        HTTPState _state = NONE;
    };
}
