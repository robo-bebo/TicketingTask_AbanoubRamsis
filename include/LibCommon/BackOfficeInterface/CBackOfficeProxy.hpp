#pragma once

#include "BackOfficeInterface/IBackOfficeClient.hpp"
#include "Types/CTicketData.hpp"
#include "Types/CTicketRequest.hpp"

#include <memory>

class BackOfficeProxy
{
  public:
    BackOfficeProxy(std::unique_ptr<IBackOfficeClient> backOfficeClient);
    virtual ~BackOfficeProxy() = default;

    std::string requestTicket(const TicketRequest& request);
    std::string validateTicket(const TicketData& request);

  private:
    std::unique_ptr<IBackOfficeClient> m_backOfficeClient;
};