#pragma once

#include <string>

class IBackOfficeClient
{
  public:
    virtual ~IBackOfficeClient() = default;

    virtual std::string requestTicket(const std::string& request)           = 0;
    virtual std::string validateTicket(const std::string& request)          = 0;
    virtual std::string sendTransactionReport(const std::string& xmlReport) = 0;
    virtual std::string getTransactionReport()                              = 0;
};