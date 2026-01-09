#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <string>

class HttpClient
{
  public:
    HttpClient(std::string host, uint16_t port);

    std::string get(const std::string& target);
    std::string post(const std::string& target, const std::string& body,
                     const std::string& contentType = "application/json");

  private:
    void connect();

    boost::asio::io_context        m_ioc;
    boost::asio::ip::tcp::resolver m_resolver;
    boost::asio::ip::tcp::socket   m_socket;

    std::string m_host;
    uint16_t    m_port;
    bool        m_connected = false;
};
