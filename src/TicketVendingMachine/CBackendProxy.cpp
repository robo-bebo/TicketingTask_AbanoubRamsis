#include "InterprocessCommunication/HttpTargets.hpp"
#include "NlohmannJson/json.hpp"
#include "TicketVendingMachine/CBackOfficeProxy.hpp"

BackOfficeProxy::BackOfficeProxy() : m_httpClient("localhost", 8080) {}

std::string BackOfficeProxy::requestTicket(const TicketRequest& request)
{
    return m_httpClient.post(httpTargets::REQUEST_TICKET, request.toString());
}