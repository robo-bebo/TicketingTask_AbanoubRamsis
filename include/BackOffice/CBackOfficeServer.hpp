#pragma once

#include "InterprocessCommunication/CHttpServer.hpp"

class BackOfficeServer
{
  public:
    BackOfficeServer();

  private:
    static Response TicketSaleRequestHandler(const Request& req);
    static Response TicketValidationRequestHandler(const Request& req);

    HttpServer m_httpServer;
};