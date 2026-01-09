#pragma once

#include "Types/CTicketData.hpp"
#include "Types/CTicketRequest.hpp"

class IBackOfficeClient
{
  public:
    virtual ~IBackOfficeClient() = default;

    virtual std::string requestTicket(const TicketRequest& request) = 0;
    virtual std::string validateTicket(const TicketData& request)   = 0;
};