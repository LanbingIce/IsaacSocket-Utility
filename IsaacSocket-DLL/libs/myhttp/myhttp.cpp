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
            const string& path = uri.getPathAndQuery();
            Poco::Net::HTTPRequest request(_post ? Poco::Net::HTTPRequest::HTTP_POST : Poco::Net::HTTPRequest::HTTP_GET, path.empty() ? "/" : path, Poco::Net::HTTPMessage::HTTP_1_1);
            for (const auto& header : _headers) {
                request.set(header.first, header.second);
            }
            request.setContentLength(_body.length());
            session.sendRequest(request) << _body;
            Poco::Net::HTTPResponse response;
            std::ostringstream oss;
            oss << session.receiveResponse(response).rdbuf();
            std::map<string, string> headers(response.begin(), response.end());
            {
                std::lock_guard lock(_mutex);
                _state = COMPLETED;
                OnComplete(response.getStatus(), response.getReason(), headers, oss.str());
            }
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

    MyHTTP::MyHTTP(const string& url, const std::map<string, string>& headers, const string& body, bool post) :_url(url), _headers(headers), _body(body), _post(post) {}
    MyHTTP::MyHTTP(const MyHTTP& http) :_url(http._url), _headers(http._headers), _body(http._body), _post(http._post) {}

    MyHTTP::~MyHTTP() {
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
                }
                Sleep(1);
            }
        }
    }
}
