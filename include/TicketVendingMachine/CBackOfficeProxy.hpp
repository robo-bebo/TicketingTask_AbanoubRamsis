#pragma once

#include "CommonTypes/CTicketRequest.hpp"
#include "InterprocessCommunication/CHttpClient.hpp"

class BackOfficeProxy
{
  public:
    BackOfficeProxy();
    virtual ~BackOfficeProxy() = default;

    std::string requestTicket(const TicketRequest& request);

  private:
    HttpClient m_httpClient;
};