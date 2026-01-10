#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <functional>

namespace http = boost::beast::http;
using Request  = http::request<http::string_body>;
using Response = http::response<http::string_body>;


class IHttpServer
{
  public:
    using Handler = std::function<Response(const Request&)>;

    virtual ~IHttpServer() = default;

    virtual void addRoute(http::verb method, std::string path, Handler h) = 0;
    virtual void start()                                                  = 0;
    virtual void stop()                                                   = 0;
};