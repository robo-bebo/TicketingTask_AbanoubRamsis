#pragma once

#include "CommonTypes/CTicketRequest.hpp"

class BackOfficeProxy
{
  public:
    BackOfficeProxy()          = default;
    virtual ~BackOfficeProxy() = default;

    virtual void requestTicket(const TicketRequest& requestJson) = 0;
};