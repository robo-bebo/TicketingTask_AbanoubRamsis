#include "BackOffice/CBackOfficeServer.hpp"

#include "BackOffice/CUniqueNumberGenerator.hpp"
#include "CommonTypes/CTicketData.hpp"
#include "CommonTypes/CTicketRequest.hpp"
#include "InterprocessCommunication/HttpTargets.hpp"

#include <iostream>

BackOfficeServer::BackOfficeServer() : m_httpServer(8080)
{
    m_httpServer.addRoute(http::verb::post, httpTargets::REQUEST_TICKET, TicketSaleRequestHandler);
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