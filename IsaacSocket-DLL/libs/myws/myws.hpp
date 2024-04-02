#pragma once
#include <Poco/Net/WebSocket.h>

namespace myws {
    enum WebSocketState
    {
        CONNECTING,
        OPEN,
        CLOSING,
        CLOSED
    };

    class MyWS
    {
    public:
        std::function<void()> OnOpen = [] {};
        std::function<void(const char* message, int len, int flags)> OnMessage = [](const char*, int, int) {};
        std::function<void(short closeStatus, const string& statusDescription)> OnClose = [](short, const string&) {};
        std::function<void(const string& error)> OnError = [](const string&) {};

        int Send(const char* message, int len, bool isBinary = false);
        bool Close(short closeStatus = 1000, const string& statusDescription = "");

        void SetState(WebSocketState state);
        WebSocketState GetState();

        MyWS(const string& url);
    private:
        void _Connect(const string& url);
        std::shared_ptr<Poco::Net::WebSocket> _pws;
        std::mutex _mutex;
        WebSocketState _state = CONNECTING;
    };
}
