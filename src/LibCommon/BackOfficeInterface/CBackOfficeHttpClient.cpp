#include "CBackOfficeHttpClient.hpp"

#include "InterprocessCommunication/HttpTargets.hpp"

CBackOfficeHttpClient::CBackOfficeHttpClient() : m_httpClient("localhost", 8080) {}

std::string CBackOfficeHttpClient::requestTicket(const TicketRequest& request)
{
    return m_httpClient.post(httpTargets::REQUEST_TICKET, request.toString());
}

std::string CBackOfficeHttpClient::validateTicket(const TicketData& request)
{
    return m_httpClient.post(httpTargets::VALIDATE_TICKET, request.toBase64());
}