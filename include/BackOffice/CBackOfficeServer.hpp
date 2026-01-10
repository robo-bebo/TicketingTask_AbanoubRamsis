#pragma once

#include "Database/ITicketStockDatabase.hpp"
#include "InterprocessCommunication/CHttpServer.hpp"

#include <memory>

class BackOfficeServer
{
  public:
    BackOfficeServer(std::unique_ptr<ITicketStockDatabase> ticketDatabase);

  private:
    Response TicketSaleRequestHandler(const Request& req);
    Response TicketValidationRequestHandler(const Request& req);
    Response TransactionReportHandler(const Request& req);

    HttpServer                            m_httpServer;
    std::unique_ptr<ITicketStockDatabase> m_ticketDatabase;
};