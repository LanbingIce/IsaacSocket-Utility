#include "myws.hpp"

#include <Poco/Buffer.h>
#include <Poco/Task.h>
#include <Poco/TaskManager.h>
#include <Poco/ThreadPool.h>
#include <Poco/URI.h>

#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SSLManager.h>

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
            std::shared_ptr<Poco::Net::HTTPClientSession> pSession;

            if (uri.getScheme() == "wss")
            {
                Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrCert = new Poco::Net::ConsoleCertificateHandler(true);
                Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "");
                Poco::Net::SSLManager::instance().initializeClient(0, ptrCert, ptrContext);
                pSession = std::make_shared<Poco::Net::HTTPSClientSession>(uri.getHost(), uri.getPort());
            }
            else
            {
                pSession = std::make_shared<Poco::Net::HTTPClientSession>(uri.getHost(), uri.getPort());
            }

            Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPath(), Poco::Net::HTTPMessage::HTTP_1_1);
            Poco::Net::HTTPResponse response;
            Poco::Net::HTTPClientSession& session = *pSession;

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
                else if (flags == 0)
                {
                    _SetState(CLOSING);
                    _pws->sendFrame(buffer, len, flags);
                    _SetState(CLOSED);
                    OnClose(1006, "");
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

        while (GetState() == CLOSING)
        {
            Sleep(1);
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

    void MyWS::Connect() {
        static Poco::ThreadPool pool(1, INT_MAX);
        static Poco::TaskManager taskManager(pool);
        taskManager.start(new _Task([this] {
            _Connect(_url);
            }));
        while (GetState() == CONNECTING)
        {
            Sleep(1);
        }
    }

    MyWS::MyWS(const string& url) :_url(url) {}
}
#undef LOCK_GUARD