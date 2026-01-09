#pragma once

#include "BackOfficeInterface/IBackOfficeClient.hpp"
#include "InterprocessCommunication/CHttpClient.hpp"

class CBackOfficeHttpClient : public IBackOfficeClient
{
  public:
    CBackOfficeHttpClient();
    virtual ~CBackOfficeHttpClient() = default;

    std::string requestTicket(const TicketRequest& request) override;
    std::string validateTicket(const TicketData& request) override;

  private:
    HttpClient m_httpClient;
};