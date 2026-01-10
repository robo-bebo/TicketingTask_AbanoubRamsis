#pragma once

#include "BackOfficeInterface/IBackOfficeClient.hpp"
#include "InterprocessCommunication/CHttpClient.hpp"

class CBackOfficeHttpClient : public IBackOfficeClient
{
  public:
    CBackOfficeHttpClient();
    virtual ~CBackOfficeHttpClient() = default;

    std::string requestTicket(const std::string& request) override;
    std::string validateTicket(const std::string& request) override;
    std::string sendTransactionReport(const std::string& xmlReport) override;

  private:
    HttpClient m_httpClient;
};