#include "myws.hpp"

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Buffer.h>
#include <Poco/Task.h>
#include <Poco/TaskManager.h>
#include <Poco/ThreadPool.h>

namespace myws {
    class _Task :public Poco::Task
    {
    public:
        _Task(std::function<void()> callback) : Task(""), _callback(callback) {}
        void runTask() {
            _callback();
        }
    private:
        std::function <void()> _callback;
    };

    void MyWS::_Connect(const string& url) {
        try
        {
            Poco::URI uri(url);
            Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
            Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/?encoding=text", Poco::Net::HTTPMessage::HTTP_1_1);
            request.set("origin", "http://www.websocket.org");
            Poco::Net::HTTPResponse response;
            _pws = std::make_shared<Poco::Net::WebSocket>(session, request, response);
            _pws->setReceiveTimeout(0);
            Poco::Buffer<char> _buffer(0);
            _SetState(OPEN);
            OnOpen();
            while (true)
            {
                _buffer.resize(0);
                int flags = 0;
                int len = _pws->receiveFrame(_buffer, flags);
                const char* buffer = _buffer.begin();
                if (flags & _pws->FRAME_OP_CLOSE)
                {
                    _SetState(CLOSING);
                    short closeStatus = 0;
                    char* p = (char*)&closeStatus;
                    //反转字节序
                    p[0] = buffer[1];
                    p[1] = buffer[0];
                    _pws->sendFrame(buffer, len, flags);
                    _SetState(CLOSED);
                    OnClose(closeStatus, string(buffer + 2, len - 2));
                    break;
                }
                else
                {
                    OnMessage(buffer, len, flags);
                }
            }
        }
        catch (Poco::Exception& e)
        {
            _SetState(CLOSED);
            OnError(e.displayText());
        }
        catch (const std::exception& e)
        {
            _SetState(CLOSED);
            OnError(e.what());
        }
    }

    int MyWS::Send(const char* message, int len, bool isBinary) {
        if (GetState() != OPEN)
        {
            return -1;
        }
        return  _pws->sendFrame(message, len, isBinary ? Poco::Net::WebSocket::FRAME_BINARY : Poco::Net::WebSocket::FRAME_TEXT);
    }

    bool MyWS::Close(short closeStatus, const string& statusDescription) {
        if (GetState() != OPEN)
        {
            return false;
        }
        _SetState(CLOSING);

        _pws->shutdown(closeStatus, statusDescription);

        while (true)
        {
            Sleep(1);
            if (GetState() != CLOSING)
            {
                break;
            }
        }
        return true;
    }

    WebSocketState MyWS::GetState() {
        std::lock_guard lock(_mutex);
        return _state;
    }

    void MyWS::_SetState(WebSocketState state) {
        std::lock_guard lock(_mutex);
        _state = state;
    }

    MyWS::MyWS(const string& url) {
        static Poco::ThreadPool pool(2, 256);
        static Poco::TaskManager taskManager(pool);
        taskManager.start(new _Task([this, url] {
            _Connect(url);
            }));
    }
}
#undef LOCK_GUARD