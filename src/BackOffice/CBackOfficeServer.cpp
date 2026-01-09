#include "CBackOfficeServer.hpp"

#include "CUniqueNumberGenerator.hpp"
#include "InterprocessCommunication/HttpTargets.hpp"
#include "Types/CTicketData.hpp"
#include "Types/CTicketRequest.hpp"
#include "Types/CTicketValidationResponse.hpp"

#include <iostream>

BackOfficeServer::BackOfficeServer() : m_httpServer(8080)
{
    m_httpServer.addRoute(http::verb::post, httpTargets::REQUEST_TICKET, TicketSaleRequestHandler);
    m_httpServer.addRoute(http::verb::post, httpTargets::VALIDATE_TICKET,
                          TicketValidationRequestHandler);
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
    // TODO: check if it exists on DB
    const DateTime expiryDate = ticketData.creationDate.addDays(ticketData.ValidityDays);

    TicketValidationResponse validationResponse;
    validationResponse.valid = DateTime() <= expiryDate;

    Response res{http::status::ok, req.version()};
    res.set(http::field::content_type, "application/json");
    res.body() = validationResponse.toString();
    res.prepare_payload();
    return res;
}