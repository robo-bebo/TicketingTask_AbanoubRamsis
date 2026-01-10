#pragma once

#include "Database/IReportDatabase.hpp"
#include "Database/ITicketStockDatabase.hpp"
#include "InterprocessCommunication/CHttpServer.hpp"

#include <memory>

class BackOfficeServer
{
  public:
    BackOfficeServer(std::unique_ptr<ITicketStockDatabase> ticketDatabase,
                     std::unique_ptr<IReportDatabase>      reportDatabase);

  private:
    Response TicketSaleRequestHandler(const Request& req);
    Response TicketValidationRequestHandler(const Request& req);
    Response postTransactionReportHandler(const Request& req);
    Response getTransactionReportHandler(const Request& req);

    HttpServer                            m_httpServer;
    std::unique_ptr<ITicketStockDatabase> m_ticketDatabase;
    std::unique_ptr<IReportDatabase>      m_reportDatabase;
};