#include "TicketVendingMachine/SaleRequestHandler.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    SaleRequestHandler handler;
    handler.startHandler();

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
