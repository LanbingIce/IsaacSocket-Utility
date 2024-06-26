﻿#include "myws.hpp"

#include <mytask/mytask.hpp>

#include <Poco/Buffer.h>
#include <Poco/URI.h>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>

using std::string;
using FrameOpcodes = Poco::Net::WebSocket::FrameOpcodes;
using FrameFlags = Poco::Net::WebSocket::FrameFlags;

namespace myws {
    void MyWS::_Connect() {
        try
        {
            Poco::URI uri(_url);
            std::unique_ptr<Poco::Net::HTTPClientSession> pSession;

            if (uri.getScheme() == "wss")
            {
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
            {
                std::lock_guard lock(_mutex);
                if (_state != CONNECTING)
                {
                    _state = CLOSED;
                    throw std::exception("Wrong State!");
                }
                _state = OPEN;
                OnOpen();
            }
            while (true)
            {
                int len = _pws->receiveFrame(buffer, flags);
                std::lock_guard lock(_mutex);
                bool fin = flags & FrameFlags::FRAME_FLAG_FIN;
                bool rsv1 = flags & FrameFlags::FRAME_FLAG_RSV1;
                bool rsv2 = flags & FrameFlags::FRAME_FLAG_RSV2;
                bool rsv3 = flags & FrameFlags::FRAME_FLAG_RSV3;

                FrameOpcodes opcodes = (FrameOpcodes)(flags & FrameOpcodes::FRAME_OP_BITMASK);

                if (rsv1 || rsv2 || rsv3) // rsv必须全部为0
                {
                    _OnClose(1008);
                    break;
                }

                if (!fin)  // 不是终包
                {
                    if (len)  //长度不为0则缓存，等待下一分片
                    {
                        continue;
                    }
                    _OnClose(1008); //长度为0说明消息有误
                    break;
                }

                // 以下为终包 fin = true

                if (opcodes == FrameOpcodes::FRAME_OP_CONT) // 终包和续包是互斥的
                {
                    _OnClose(1008);
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
                    if (buffer.size() < 2)
                    {
                        _OnClose(1008);
                        break;
                    }
                    short closeStatus = 0;
                    char* p = (char*)&closeStatus;
                    string statusDescription{ buffer.begin() + 2, buffer.size() - 2 };
                    //反转字节序
                    p[0] = buffer[1];
                    p[1] = buffer[0];
                    _OnClose(closeStatus, statusDescription);
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
            std::lock_guard lock(_mutex);
            _state = CLOSED;
            OnError(e.displayText());
        }
        catch (const std::exception& e)
        {
            std::lock_guard lock(_mutex);
            _state = CLOSED;
            OnError(e.what());
        }
        catch (...) {
            std::lock_guard lock(_mutex);
            _state = CLOSED;
            OnError("Unknow Exception");
        }
        std::lock_guard lock(_mutex);
        _state = DEAD;
    }

    void MyWS::_OnClose(short closeStatus, const string& statusDescription) {
        if (_state != OPEN)
        {
            return;
        }
        _pws->shutdown(closeStatus, statusDescription);
        _state = CLOSED;
        OnClose(closeStatus, statusDescription);
    }

    int MyWS::Send(const char* message, int len, bool isBinary) {
        std::lock_guard lock(_mutex);
        if (_state != OPEN)
        {
            return -1;
        }
        return _pws->sendFrame(message, len, isBinary ? Poco::Net::WebSocket::FRAME_BINARY : Poco::Net::WebSocket::FRAME_TEXT);
    }

    bool MyWS::Close(short closeStatus, const string& statusDescription) {
        {
            std::lock_guard lock(_mutex);
            if (_state != OPEN)
            {
                return false;
            }
            _state = CLOSING;
            _pws->shutdown(closeStatus, statusDescription);
        }

        while (true)
        {
            Sleep(1);
            std::lock_guard lock(_mutex);
            if (_state != CLOSING)
            {
                break;
            }
        }
        return true;
    }

    WebSocketState MyWS::_GetState() {
        std::lock_guard lock(_mutex);
        return _state;
    }

    void MyWS::Connect() {
        std::lock_guard lock(_mutex);
        if (_state != NONE)
        {
            return;
        }
        _state = CONNECTING;
        mytask::Run([this] {_Connect(); });
    }

    MyWS::MyWS(const string& url) :_url(url) {}

    MyWS::~MyWS() {
        for (int i = NONE + 1; i < DEAD; i++)
        {
            while (true)
            {
                {
                    std::lock_guard lock(_mutex);
                    if (_state != i)
                    {
                        break;
                    }
                    else if (_state == OPEN)
                    {
                        _state = CLOSING;
                        _pws->close();
                    }
                }
                Sleep(1);
            }
        }
    }
}
