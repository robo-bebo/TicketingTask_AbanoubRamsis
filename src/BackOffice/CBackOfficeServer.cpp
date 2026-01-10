#include "CBackOfficeServer.hpp"

#include "CUniqueNumberGenerator.hpp"
#include "InterprocessCommunication/HttpTargets.hpp"
#include "Types/CTicketData.hpp"
#include "Types/CTicketRequest.hpp"
#include "Types/CTicketValidationResponse.hpp"

#include <iostream>

BackOfficeServer::BackOfficeServer(std::unique_ptr<ITicketStockDatabase> ticketDatabase)
    : m_httpServer(8080), m_ticketDatabase(std::move(ticketDatabase))
{
    m_httpServer.addRoute(http::verb::post, httpTargets::REQUEST_TICKET, [this](const Request& req)
                          { return this->TicketSaleRequestHandler(req); });
    m_httpServer.addRoute(http::verb::post, httpTargets::VALIDATE_TICKET, [this](const Request& req)
                          { return this->TicketValidationRequestHandler(req); });
    m_httpServer.addRoute(http::verb::post, httpTargets::TRANSACTION_REPORT,
                          [this](const Request& req) { return this->TransactionReportHandler(req); });
    m_httpServer.start();
}


Response BackOfficeServer::TicketSaleRequestHandler(const Request& req)
{
    std::string payload = req.body();
    std::cout << "Received Ticket Sale Request with payload: " << payload << std::endl;

    TicketRequest ticketRequest = TicketRequest::fromString(payload);
    TicketData    ticketData;
    ticketData.ValidityDays = ticketRequest.validityDays;
    ticketData.lineNumber   = ticketRequest.lineNumber;
    ticketData.creationDate = DateTime();
    ticketData.ticketID     = UniqueNumberGenerator::getNext();

    if(!m_ticketDatabase->storeTicket(ticketData.toBase64()))
    {
        std::cerr << __func__ << "Failed to store ticket in database!" << std::endl;
        std::abort();
    }

    Response res{http::status::ok, req.version()};
    res.set(http::field::content_type, "application/json");
    res.body() = ticketData.toBase64();
    res.prepare_payload();
    return res;
}

Response BackOfficeServer::TicketValidationRequestHandler(const Request& req)
{
    std::string payload = req.body();
    std::cout << "Received Ticket Validation Request with payload: " << payload << std::endl;

    TicketData ticketData = TicketData::fromBase64(payload);
    if(!m_ticketDatabase->isTicketOnDatabase(payload))
    {
        TicketValidationResponse validationResponse;
        validationResponse.valid = false;

        Response res{http::status::ok, req.version()};
        res.set(http::field::content_type, "application/json");
        res.body() = validationResponse.toString();
        res.prepare_payload();
        return res;
    }
    const DateTime           expiryDate = ticketData.creationDate.addDays(ticketData.ValidityDays);
    TicketValidationResponse validationResponse;
    validationResponse.valid = DateTime() <= expiryDate;

    Response res{http::status::ok, req.version()};
    res.set(http::field::content_type, "application/json");
    res.body() = validationResponse.toString();
    res.prepare_payload();
    return res;
}

Response BackOfficeServer::TransactionReportHandler(const Request& req)
{
    std::string payload = req.body();
    std::cout << "Received Transaction Report with payload: " << payload << std::endl;

    // Here you would typically process/store the transaction report.
    // For this example, we just acknowledge receipt.

    Response res{http::status::ok, req.version()};
    res.set(http::field::content_type, "text/plain");
    res.body() = "Transaction report received";
    res.prepare_payload();
    return res;
}