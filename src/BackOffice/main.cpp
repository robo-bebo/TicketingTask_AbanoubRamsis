#include "CBackOfficeServer.hpp"
#include "CRequestHandler.hpp"
#include "Database/CDatabaseFactory.hpp"
#include "InterprocessCommunication/CHttpServer.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main()
{
    std::unique_ptr<RequestHandler> requestHandler = std::make_unique<RequestHandler>(
        CDatabaseFactory::createJsonFileDatabase("ticket_database.json"),
        CDatabaseFactory::createReportDatabase("transaction_report.xml"));

    std::unique_ptr<HttpServer> httpServer = std::make_unique<HttpServer>(8080);
    BackOfficeServer            server(std::move(httpServer), std::move(requestHandler));

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
