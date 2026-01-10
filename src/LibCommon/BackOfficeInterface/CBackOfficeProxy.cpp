#include "CBackOfficeProxy.hpp"

#include "NlohmannJson/json.hpp"

#include <iostream>
#include <thread>

BackOfficeProxy::BackOfficeProxy(std::unique_ptr<IBackOfficeClient> backOfficeClient)
    : m_backOfficeClient(std::move(backOfficeClient))
{
}

std::string BackOfficeProxy::requestTicket(const TicketRequest& request)
{
    return sendRequestWithRetries([this](const std::string& req)
                                  { return m_backOfficeClient->requestTicket(req); },
                                  request.toString());
}

std::string BackOfficeProxy::validateTicket(const TicketData& request)
{
    return sendRequestWithRetries([this](const std::string& req)
                                  { return m_backOfficeClient->validateTicket(req); },
                                  request.toBase64());
}

void BackOfficeProxy::sendTransactionReport(const TransactionsReport& xmlReport)
{
    sendRequestWithRetries([this](const std::string& req)
                           { return m_backOfficeClient->sendTransactionReport(req); },
                           xmlReport.toXMLString());
}

std::string BackOfficeProxy::sendRequestWithRetries(
    const std::function<std::string(std::string)>& requestFunc, const std::string& request)
{
    constexpr int                       MAX_RETRIES = 3;
    constexpr std::chrono::milliseconds BASE_DELAY{200};

    for(int attempt = 1; attempt <= MAX_RETRIES; ++attempt)
    {
        try
        {
            return requestFunc(request);
        }
        catch(const std::exception& e)
        {
            if(attempt == MAX_RETRIES)
            {
                std::cerr << "BackOffice request failed after " << attempt
                          << " attempts: " << e.what() << std::endl;
                throw e;
            }

            auto delay = BASE_DELAY * (1 << (attempt - 1));
            std::cerr << "BackOffice request failed (attempt " << attempt << "), retrying in "
                      << delay.count() << "ms...\n";
            std::this_thread::sleep_for(delay);
        }
    }

    throw std::logic_error("[BackOfficeProxy::sendRequestWithRetries] Reached unreachable code");
}
