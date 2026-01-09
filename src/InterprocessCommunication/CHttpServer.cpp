#include "InterprocessCommunication/CHttpServer.hpp"

using tcp = boost::asio::ip::tcp;

HttpServer::HttpServer(uint16_t port) : m_acceptor(m_ioc, tcp::endpoint(tcp::v4(), port)) {}

HttpServer::~HttpServer()
{
    stop();
}

void HttpServer::addRoute(http::verb method, std::string path, Handler h)
{
    m_routes[std::to_string((int)method) + path] = std::move(h);
}

void HttpServer::start()
{
    m_running = true;
    m_thread  = std::thread([this] { acceptLoop(); });
}

void HttpServer::stop()
{
    if(!m_running)
    {
        return;
    }
    m_running = false;
    m_ioc.stop();
    if(m_thread.joinable())
    {
        m_thread.join();
    }
}

void HttpServer::acceptLoop()
{
    while(m_running)
    {
        tcp::socket socket(m_ioc);
        m_acceptor.accept(socket);
        std::thread(&HttpServer::handleSession, this, std::move(socket)).detach();
    }
}

void HttpServer::handleSession(tcp::socket socket)
{
    boost::beast::flat_buffer buffer;
    Request                   req;
    http::read(socket, buffer, req);

    Response res{http::status::not_found, req.version()};
    res.set(http::field::server, "BeastServer");

    auto it = m_routes.find(std::to_string((int)req.method()) + std::string(req.target()));
    if(it != m_routes.end())
    {
        res = it->second(req);
    }

    res.keep_alive(req.keep_alive());
    http::write(socket, res);
}
