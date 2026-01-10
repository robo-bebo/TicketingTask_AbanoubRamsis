#include "CBackOfficeServer.hpp"
#include "Database/CDatabaseFactory.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    BackOfficeServer server(CDatabaseFactory::createJsonFileDatabase("ticket_database.json"),
                            CDatabaseFactory::createReportDatabase("transaction_report.xml"));

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
