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
        static void Run(const std::function<void()>& callback) {
            static Poco::ThreadPool pool(1, INT_MAX);
            static Poco::TaskManager taskManager(pool);
            taskManager.start(new _Task(callback));
        }
    private:
        _Task(const std::function<void()>& callback) : Task(""), _callback(callback) {}
        void runTask() {
            _callback();
        }
        std::function <void()> _callback;
    };

    void MyWS::_Connect() {
        try
        {
            Poco::URI uri(_url);
            std::shared_ptr<Poco::Net::HTTPClientSession> pSession;

            if (uri.getScheme() == "wss")
            {
                Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrCert = new Poco::Net::ConsoleCertificateHandler(true);
                Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "");
                Poco::Net::SSLManager::instance().initializeClient(0, ptrCert, ptrContext);
                pSession = std::make_shared<Poco::Net::HTTPSClientSession>(uri.getHost(), uri.getPort());
            }
            else if (uri.getScheme() == "ws")
            {
                pSession = std::make_shared<Poco::Net::HTTPClientSession>(uri.getHost(), uri.getPort());
            }
            else
            {
                throw std::exception("Bad Scheme");
            }
            const string& path = uri.getPath();
            Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path.empty() ? "/" : path, Poco::Net::HTTPMessage::HTTP_1_1);
            Poco::Net::HTTPResponse response;
            Poco::Net::HTTPClientSession& session = *pSession;
            session.setTimeout(3 * 1000 * 1000);
            Poco::Buffer<char> buffer(0);
            _SetState(CONNECTING);
            _pws = std::make_shared<Poco::Net::WebSocket>(session, request, response);
            _pws->setReceiveTimeout(0);
            _SetState(OPEN);
            OnOpen();
            while (true)
            {
                int flags = 0;
                _pws->receiveFrame(buffer, flags);
                if (flags == 0)
                {
                    _Close(1006);
                    break;
                }
                else if (flags & _pws->FRAME_OP_CLOSE)
                {
                    short closeStatus = 0;
                    char* p = (char*)&closeStatus;
                    string statusDescription = string(buffer.begin() + 2, buffer.size() - 2);
                    //反转字节序
                    p[0] = buffer[1];
                    p[1] = buffer[0];
                    _Close(closeStatus, statusDescription);
                    break;
                }
                else if (flags & _pws->FRAME_FLAG_FIN)
                {
                    OnMessage(buffer.begin(), buffer.size(), flags);
                    buffer.resize(0);
                }
                else
                {
                    throw std::exception("Unknow Message");
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
        catch (...) {
            _SetState(CLOSED);
            OnError("Unknow Exception");
        }
    }

    void MyWS::_Close(short closeStatus, const string& statusDescription) {
        _SetState(CLOSING);
        _pws->shutdown(closeStatus, statusDescription);
        _SetState(CLOSED);
        OnClose(closeStatus, statusDescription);
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
        _Task::Run([this] {_Connect(); });
        while (GetState() == NONE)
        {
            Sleep(1);
        }
    }

    MyWS::MyWS(const string& url) :_url(url) {}

    MyWS::~MyWS() {
        while (GetState() == CONNECTING)
        {
            Sleep(1);
        }
        if (GetState() == OPEN)
        {
            _SetState(CLOSING);
            _pws->close();
        }
        while (GetState() == CLOSING)
        {
            Sleep(1);
        }
    }
}
#undef LOCK_GUARD