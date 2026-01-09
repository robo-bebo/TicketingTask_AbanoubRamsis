#include "CHttpClient.hpp"

namespace http = boost::beast::http;
using tcp      = boost::asio::ip::tcp;

HttpClient::HttpClient(std::string host, uint16_t port)
    : m_resolver(m_ioc), m_socket(m_ioc), m_host(std::move(host)), m_port(port)
{
}

void HttpClient::connect()
{
    if(m_connected)
    {
        return;
    }

    auto results = m_resolver.resolve(m_host, std::to_string(m_port));
    boost::asio::connect(m_socket, results.begin(), results.end());
    m_connected = true;
}

std::string HttpClient::get(const std::string& target)
{
    connect();

    http::request<http::string_body> req{http::verb::get, target, 11};
    req.set(http::field::host, m_host);
    req.set(http::field::user_agent, "BeastClient");

    http::write(m_socket, req);

    boost::beast::flat_buffer         buffer;
    http::response<http::string_body> res;
    http::read(m_socket, buffer, res);

    return res.body();
}

std::string HttpClient::post(const std::string& target, const std::string& body,
                             const std::string& contentType)
{
    connect();

    http::request<http::string_body> req{http::verb::post, target, 11};
    req.set(http::field::host, m_host);
    req.set(http::field::user_agent, "BeastClient");
    req.set(http::field::content_type, contentType);
    req.keep_alive(false);
    req.body() = body;
    req.prepare_payload();

    http::write(m_socket, req);

    boost::beast::flat_buffer         buffer;
    http::response<http::string_body> res;
    http::read(m_socket, buffer, res);

    m_socket.shutdown(tcp::socket::shutdown_both);
    m_socket.close();
    m_connected = false;

    return res.body();
}
