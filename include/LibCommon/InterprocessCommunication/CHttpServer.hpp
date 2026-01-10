#pragma once
#include "IHttpServer.hpp"

#include <thread>
#include <unordered_map>

class HttpServer : public IHttpServer
{
  public:
    using Handler = IHttpServer::Handler;

    HttpServer(uint16_t port);
    ~HttpServer();

    void addRoute(http::verb method, std::string path, Handler h) override;
    void start() override;
    void stop() override;

  private:
    void acceptLoop();
    void handleSession(boost::asio::ip::tcp::socket socket);

    boost::asio::io_context        m_ioc;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::thread                    m_thread;
    bool                           m_running = false;

    std::unordered_map<std::string, Handler> m_routes;
};
