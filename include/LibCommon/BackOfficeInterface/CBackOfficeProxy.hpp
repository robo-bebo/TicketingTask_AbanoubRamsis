#pragma once

#include "BackOfficeInterface/IBackOfficeClient.hpp"
#include "Types/CTicketData.hpp"
#include "Types/CTicketRequest.hpp"
#include "Types/CTransactionsReport.hpp"

#include <memory>

class BackOfficeProxy
{
  public:
    BackOfficeProxy(std::unique_ptr<IBackOfficeClient> backOfficeClient);
    virtual ~BackOfficeProxy() = default;

    BackOfficeProxy(const BackOfficeProxy&)            = delete;
    BackOfficeProxy& operator=(const BackOfficeProxy&) = delete;

    BackOfficeProxy(BackOfficeProxy&&)            = default;
    BackOfficeProxy& operator=(BackOfficeProxy&&) = default;

    std::string requestTicket(const TicketRequest& request);
    std::string validateTicket(const TicketData& request);
    void        sendTransactionReport(const TransactionsReport& xmlReport);

  private:
    std::unique_ptr<IBackOfficeClient> m_backOfficeClient;
    std::string sendRequestWithRetries(const std::function<std::string(std::string)>& requestFunc,
                                       const std::string&                             request);
};