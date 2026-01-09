#include "CBackOfficeProxy.hpp"

#include "InterprocessCommunication/HttpTargets.hpp"
#include "NlohmannJson/json.hpp"

#include <iostream>
#include <thread>

BackOfficeProxy::BackOfficeProxy(std::unique_ptr<IBackOfficeClient> backOfficeClient)
    : m_backOfficeClient(std::move(backOfficeClient))
{
}

std::string BackOfficeProxy::requestTicket(const TicketRequest& request)
{
    constexpr int                       MAX_RETRIES = 3;
    constexpr std::chrono::milliseconds BASE_DELAY{200};

    for(int attempt = 1; attempt <= MAX_RETRIES; ++attempt)
    {
        try
        {
            return m_backOfficeClient->requestTicket(request);
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

    throw std::logic_error("[BackOfficeProxy::requestTicket] Reached unreachable code");
}

std::string BackOfficeProxy::validateTicket(const TicketData& request)
{
    constexpr int                       MAX_RETRIES = 3;
    constexpr std::chrono::milliseconds BASE_DELAY{200};

    for(int attempt = 1; attempt <= MAX_RETRIES; ++attempt)
    {
        try
        {
            return m_backOfficeClient->validateTicket(request);
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

    throw std::logic_error("[BackOfficeProxy::validateTicket] Reached unreachable code");
}
