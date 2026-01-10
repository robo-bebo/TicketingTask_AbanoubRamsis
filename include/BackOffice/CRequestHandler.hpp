#pragma once

#include "Database/IReportDatabase.hpp"
#include "Database/ITicketStockDatabase.hpp"
#include "IRequestHandler.hpp"

class RequestHandler : public IRequestHandler
{
  public:
    RequestHandler(std::unique_ptr<ITicketStockDatabase> ticketDatabase,
                   std::unique_ptr<IReportDatabase>      reportDatabase);


    Response ticketSaleRequestHandler(const Request& req) override;
    Response ticketValidationRequestHandler(const Request& req) override;
    Response postTransactionReportHandler(const Request& req) override;
    Response getTransactionReportHandler(const Request& req) override;

  private:
    std::unique_ptr<ITicketStockDatabase> m_ticketDatabase;
    std::unique_ptr<IReportDatabase>      m_reportDatabase;
};