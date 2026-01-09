#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <functional>
#include <thread>
#include <unordered_map>

namespace http = boost::beast::http;
using Request  = http::request<http::string_body>;
using Response = http::response<http::string_body>;

class HttpServer
{
  public:
    using Handler = std::function<Response(const Request&)>;

    HttpServer(uint16_t port);
    ~HttpServer();

    void addRoute(http::verb method, std::string path, Handler h);
    void start();
    void stop();

  private:
    void acceptLoop();
    void handleSession(boost::asio::ip::tcp::socket socket);

    boost::asio::io_context        m_ioc;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::thread                    m_thread;
    bool                           m_running = false;

    std::unordered_map<std::string, Handler> m_routes;
};
