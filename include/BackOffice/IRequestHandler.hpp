#pragma once

#include "InterprocessCommunication/IHttpServer.hpp"

class IRequestHandler
{
  public:
    virtual ~IRequestHandler() = default;

    virtual Response ticketSaleRequestHandler(const Request& req)       = 0;
    virtual Response ticketValidationRequestHandler(const Request& req) = 0;
    virtual Response postTransactionReportHandler(const Request& req)   = 0;
    virtual Response getTransactionReportHandler(const Request& req)    = 0;
};