#pragma once

#include "IRequestHandler.hpp"
#include "InterprocessCommunication/IHttpServer.hpp"

#include <memory>

class BackOfficeServer
{
  public:
    BackOfficeServer(std::unique_ptr<IHttpServer>     httpServer,
                     std::unique_ptr<IRequestHandler> requestHandler);

  private:
    Response onTicketSaleRequestHandler(const Request& req);
    Response onTicketValidationRequestHandler(const Request& req);
    Response onPostTransactionReportHandler(const Request& req);
    Response onGetTransactionReportHandler(const Request& req);

    std::unique_ptr<IHttpServer>     m_httpServer;
    std::unique_ptr<IRequestHandler> m_requestHandler;
};