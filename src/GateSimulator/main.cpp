#include "BackOfficeInterface/CBackOfficeClientFactory.hpp"
#include "BackOfficeInterface/CBackOfficeProxy.hpp"
#include "CValidationRequestHandler.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    std::unique_ptr<IBackOfficeClient> backOfficeClient = BackOfficeClientFactory::createHttpClient();

    std::shared_ptr<BackOfficeProxy> backOfficeProxy
        = std::make_shared<BackOfficeProxy>(std::move(backOfficeClient));

    std::unique_ptr<TransactionReporter> transactionReporter
        = std::make_unique<TransactionReporter>(backOfficeProxy);

    ValidationRequestHandler handler(std::move(backOfficeProxy), std::move(transactionReporter));
    handler.startHandler();

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
