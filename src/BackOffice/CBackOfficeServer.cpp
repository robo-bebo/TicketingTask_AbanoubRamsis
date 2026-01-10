#include "CBackOfficeServer.hpp"

#include "CUniqueNumberGenerator.hpp"
#include "InterprocessCommunication/HttpTargets.hpp"
#include "Types/CTicketData.hpp"
#include "Types/CTicketRequest.hpp"
#include "Types/CTicketValidationResponse.hpp"

#include <iostream>

BackOfficeServer::BackOfficeServer(std::unique_ptr<IHttpServer>     httpServer,
                                   std::unique_ptr<IRequestHandler> requestHandler)
    : m_httpServer(std::move(httpServer)), m_requestHandler(std::move(requestHandler))
{
    m_httpServer->addRoute(http::verb::post, httpTargets::REQUEST_TICKET, [this](const Request& req)
                           { return this->onTicketSaleRequestHandler(req); });
    m_httpServer->addRoute(http::verb::post, httpTargets::VALIDATE_TICKET, [this](const Request& req)
                           { return this->onTicketValidationRequestHandler(req); });
    m_httpServer->addRoute(http::verb::post, httpTargets::TRANSACTION_REPORT, [this](const Request& req)
                           { return this->onPostTransactionReportHandler(req); });
    m_httpServer->addRoute(http::verb::get, httpTargets::TRANSACTION_REPORT, [this](const Request& req)
                           { return this->onGetTransactionReportHandler(req); });
    m_httpServer->start();
}


Response BackOfficeServer::onTicketSaleRequestHandler(const Request& req)
{
    std::string payload = req.body();
    std::cout << __func__ << " Received Ticket Sale Request with payload: " << payload << std::endl;

    return m_requestHandler->ticketSaleRequestHandler(req);
}

Response BackOfficeServer::onTicketValidationRequestHandler(const Request& req)
{
    std::string payload = req.body();
    std::cout << __func__ << " Received Ticket Validation Request with payload: " << payload
              << std::endl;

    return m_requestHandler->ticketValidationRequestHandler(req);
}

Response BackOfficeServer::onPostTransactionReportHandler(const Request& req)
{
    std::string payload = req.body();
    std::cout << __func__ << " Received Transaction Report with payload: " << payload << std::endl;

    return m_requestHandler->postTransactionReportHandler(req);
}

Response BackOfficeServer::onGetTransactionReportHandler(const Request& req)
{
    std::cout << __func__ << " Received Get Transaction Report Request" << std::endl;

    return m_requestHandler->getTransactionReportHandler(req);
}