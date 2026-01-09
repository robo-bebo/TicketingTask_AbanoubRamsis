#include "BackOffice/CBackOfficeServer.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    BackOfficeServer server;

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
