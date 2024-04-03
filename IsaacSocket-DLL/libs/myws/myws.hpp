#pragma once
#include <Poco/Net/WebSocket.h>

namespace myws {
    enum WebSocketState
    {
        NONE,
        CONNECTING,
        OPEN,
        CLOSING,
        CLOSED
    };

    class MyWS
    {
    public:
        void (*OnOpen)() = [] {};
        void (*OnMessage)(const char* message, int len, int flags) = [](const char*, int, int) {};
        void (*OnClose)(short closeStatus, const string& statusDescription) = [](short, const string&) {};
        void (*OnError)(const string& error) = [](const string&) {};

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
