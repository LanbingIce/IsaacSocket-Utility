#pragma once
#include <Poco/Net/WebSocket.h>

namespace myws {
    enum WebSocketState
    {
        NONE = 0,
        CONNECTING = 1,
        OPEN = 2,
        CLOSING = 3,
        CLOSED = 4,
        DEAD = 5
    };

    class MyWS
    {
    public:
        std::function<void()>OnOpen = [] {};
        std::function<void(const char*, int, bool)>OnMessage = [](const char*, int, bool = false) {};
        std::function<void(short, const string&)>OnClose = [](short = 1000, const string & = "") {};
        std::function<void(const string&) >OnError = [](const string & = "") {};

        void Connect();
        int Send(const char* message, int len, bool isBinary = false);
        bool Close(short closeStatus = 1000, const string& statusDescription = "");

        WebSocketState GetState();

        MyWS(const string& url);
        ~MyWS();
    private:
        void _SetState(WebSocketState state);
        void _Connect();
        void _Close(short closeStatus = 1000, const string& statusDescription = "");
        const string _url;
        std::shared_ptr<Poco::Net::WebSocket> _pws;
        std::mutex _mutex;
        WebSocketState _state = NONE;
    };
}
