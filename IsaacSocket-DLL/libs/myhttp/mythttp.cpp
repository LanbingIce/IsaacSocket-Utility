#include "myhttp.hpp"

#include <mytask/mytask.hpp>
#include <Poco/TaskManager.h>
#include <Poco/ThreadPool.h>
#include <Poco/URI.h>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>

namespace myhttp {
    void MyHTTP::_Connect() {
        try
        {
            _SetState(CONNECTING);
            Poco::URI uri(_url);
            std::shared_ptr<Poco::Net::HTTPClientSession> pSession;

            if (uri.getScheme() == "https")
            {
                pSession = std::make_shared<Poco::Net::HTTPSClientSession>(uri.getHost(), uri.getPort());
            }
            else if (uri.getScheme() == "http")
            {
                pSession = std::make_shared<Poco::Net::HTTPClientSession>(uri.getHost(), uri.getPort());
            }
            else
            {
                throw std::exception("Bad Scheme");
            }

            Poco::Net::HTTPClientSession& session = *pSession;
            Poco::Net::HTTPResponse response;
            session.setTimeout(3 * 1000 * 1000);
            Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPRequest::HTTP_1_1);
            session.sendRequest(request);
            string body;
            session.receiveResponse(response) >> body;
            _SetState(CLOSED);
            OnClose(response, body);
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

    HTTPState MyHTTP::GetState() {
        std::lock_guard lock(_mutex);
        return _state;
    }

    void MyHTTP::_SetState(HTTPState state) {
        std::lock_guard lock(_mutex);
        _state = state;
    }

    void MyHTTP::Connect() {
        static Poco::ThreadPool pool(1, INT_MAX);
        static Poco::TaskManager taskManager(pool);
        mytask::Run([this] {_Connect(); });
        while (GetState() == NONE)
        {
            Sleep(1);
        }
    }

    MyHTTP::MyHTTP(const string& url) :_url(url) {}

    MyHTTP::~MyHTTP() {
        // 只有构造时才是NONE，调用了Connect会立刻变为CONNECTING
        while (GetState() == CONNECTING)
        {
            Sleep(1);
        }
        while (GetState() != DEAD)
        {
            Sleep(1);
        }
    }
}
#undef LOCK_GUARD
