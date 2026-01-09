#include "BackOfficeInterface/CBackOfficeClientFactory.hpp"
#include "BackOfficeInterface/CBackOfficeProxy.hpp"
#include "CValidationRequestHandler.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    std::unique_ptr<IBackOfficeClient> backOfficeClient = BackOfficeClientFactory::createHttpClient();
    std::unique_ptr<BackOfficeProxy> backOfficeProxy
        = std::make_unique<BackOfficeProxy>(std::move(backOfficeClient));
    ValidationRequestHandler handler(std::move(backOfficeProxy));
    handler.startHandler();

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
