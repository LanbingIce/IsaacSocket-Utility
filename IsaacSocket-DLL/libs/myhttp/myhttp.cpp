#include "myhttp.hpp"

#include <mytask/mytask.hpp>

#include <Poco/URI.h>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>

namespace myhttp {
    void MyHTTP::_Connect() {
        try
        {
            Poco::URI uri(_url);
            std::unique_ptr<Poco::Net::HTTPClientSession> pSession;

            if (uri.getScheme() == "https")
            {
                pSession = std::make_unique<Poco::Net::HTTPSClientSession>(uri.getHost(), uri.getPort());
            }
            else if (uri.getScheme() == "http")
            {
                pSession = std::make_unique<Poco::Net::HTTPClientSession>(uri.getHost(), uri.getPort());
            }
            else
            {
                throw std::exception("Bad Scheme");
            }
            Poco::Net::HTTPClientSession& session = *pSession;
            session.setTimeout(3 * 1000 * 1000);
            Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPRequest::HTTP_1_1);
            session.sendRequest(request);
            Poco::Net::HTTPResponse response;
            string body;
            session.receiveResponse(response) >> body;
            std::lock_guard lock(_mutex);
            _state = COMPLETED;
            OnComplete(response, body);
        }
        catch (Poco::Exception& e)
        {
            std::lock_guard lock(_mutex);
            _state = COMPLETED;
            _fault = true;
            OnError(e.displayText());
        }
        catch (const std::exception& e)
        {
            std::lock_guard lock(_mutex);
            _state = COMPLETED;
            _fault = true;
            OnError(e.what());
        }
        catch (...) {
            std::lock_guard lock(_mutex);
            _state = COMPLETED;
            _fault = true;
            OnError("Unknow Exception");
        }
        std::lock_guard lock(_mutex);
        _state = DEAD;
    }

    HTTPState MyHTTP::GetState() {
        std::lock_guard lock(_mutex);
        return _state;
    }

    bool MyHTTP::IsFaulted() {
        std::lock_guard lock(_mutex);
        return _fault;
    }

    void MyHTTP::Send() {
        std::lock_guard lock(_mutex);
        if (_state != NONE)
        {
            return;
        }
        _state = RUNNING;
        mytask::Run([this] {_Connect(); });
    }

    MyHTTP::MyHTTP(const string& url, bool post) :_url(url), _post(post) {}
    MyHTTP::MyHTTP(const MyHTTP& http) :_url(http._url), _post(http._post) {}

    MyHTTP::~MyHTTP() {
        for (int i = NONE; i < DEAD; i++)
        {
            while (true)
            {
                {
                    std::lock_guard lock(_mutex);
                    if (_state != i)
                    {
                        break;
                    }
                }
                Sleep(1);
            }
        }
    }
}
