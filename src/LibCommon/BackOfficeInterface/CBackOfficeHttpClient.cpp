#include "CBackOfficeHttpClient.hpp"

#include "InterprocessCommunication/HttpTargets.hpp"

CBackOfficeHttpClient::CBackOfficeHttpClient() : m_httpClient("localhost", 8080) {}

std::string CBackOfficeHttpClient::requestTicket(const std::string& request)
{
    return m_httpClient.post(httpTargets::REQUEST_TICKET, request);
}

std::string CBackOfficeHttpClient::validateTicket(const std::string& request)
{
    return m_httpClient.post(httpTargets::VALIDATE_TICKET, request);
}

std::string CBackOfficeHttpClient::sendTransactionReport(const std::string& xmlReport)
{
    return m_httpClient.post(httpTargets::TRANSACTION_REPORT, xmlReport, "application/xml");
}