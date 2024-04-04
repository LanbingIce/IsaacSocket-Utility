#include "myws.hpp"

#include <mytask/mytask.hpp>

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

using FrameOpcodes = Poco::Net::WebSocket::FrameOpcodes;
using FrameFlags = Poco::Net::WebSocket::FrameFlags;

namespace myws {
    void MyWS::_Connect() {
        try
        {
            _SetState(CONNECTING);
            Poco::URI uri(_url);
            std::unique_ptr<Poco::Net::HTTPClientSession> pSession;

            if (uri.getScheme() == "wss")
            {
                Poco::Net::SSLManager::InvalidCertificateHandlerPtr ptrCert = new Poco::Net::ConsoleCertificateHandler(true);
                Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "");
                Poco::Net::SSLManager::instance().initializeClient(0, ptrCert, ptrContext);
                pSession = std::make_unique<Poco::Net::HTTPSClientSession>(uri.getHost(), uri.getPort());
            }
            else if (uri.getScheme() == "ws")
            {
                pSession = std::make_unique<Poco::Net::HTTPClientSession>(uri.getHost(), uri.getPort());
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
            int flags = 0;
            _pws = std::make_shared<Poco::Net::WebSocket>(session, request, response);
            _pws->setReceiveTimeout(0);
            _SetState(OPEN);
            OnOpen();
            while (true)
            {
                int len = _pws->receiveFrame(buffer, flags);
                bool fin = flags & FrameFlags::FRAME_FLAG_FIN;
                bool rsv1 = flags & FrameFlags::FRAME_FLAG_RSV1;
                bool rsv2 = flags & FrameFlags::FRAME_FLAG_RSV2;
                bool rsv3 = flags & FrameFlags::FRAME_FLAG_RSV3;

                FrameOpcodes opcodes = (FrameOpcodes)(flags & FrameOpcodes::FRAME_OP_BITMASK);

                if (rsv1 || rsv2 || rsv3) // rsv必须全部为0
                {
                    _Close(1006);
                    break;
                }

                if (!fin)  // 不是终包
                {
                    if (len)  //长度不为0则缓存，等待下一分片
                    {
                        continue;
                    }
                    _Close(1006); //长度为0说明消息有误
                    break;
                }

                // 以下为终包 fin = true

                if (opcodes == FrameOpcodes::FRAME_OP_CONT) // 终包和续包是互斥的
                {
                    _Close(1006);
                    break;
                }
                else if (opcodes == FrameOpcodes::FRAME_OP_TEXT)//文本
                {
                    OnMessage(buffer.begin(), buffer.size(), false);
                }
                else if (opcodes == FrameOpcodes::FRAME_OP_BINARY)//二进制
                {
                    OnMessage(buffer.begin(), buffer.size(), true);
                }
                else if (opcodes == FrameOpcodes::FRAME_OP_CLOSE)//关闭
                {
                    short closeStatus = 0;
                    char* p = (char*)&closeStatus;
                    string statusDescription{ buffer.begin() + 2, buffer.size() - 2 };
                    //反转字节序
                    p[0] = buffer[1];
                    p[1] = buffer[0];
                    _Close(closeStatus, statusDescription);
                    break;
                }
                else if (opcodes == FrameOpcodes::FRAME_OP_PING)//PING
                {
                    _pws->sendFrame(buffer.begin(), buffer.size(), FrameFlags::FRAME_FLAG_FIN | FrameOpcodes::FRAME_OP_PONG);
                }
                buffer.resize(0);
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
        _SetState(DEAD);
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
        mytask::Run([this] {_Connect(); });
        while (GetState() == NONE)
        {
            Sleep(1);
        }
    }

    MyWS::MyWS(const string& url) :_url(url) {}

    MyWS::~MyWS() {
        // 只有构造时才是NONE，调用了Connect会立刻变为CONNECTING
        while (GetState() == CONNECTING)
        {
            Sleep(1);
        }
        if (GetState() == OPEN)
        {
            _SetState(CLOSING);
            _pws->close();
        }
        while (GetState() != DEAD)
        {
            Sleep(1);
        }
    }
}
#undef LOCK_GUARD