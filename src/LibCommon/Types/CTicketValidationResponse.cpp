#include "CTicketValidationResponse.hpp"

TicketValidationResponse TicketValidationResponse::fromString(const std::string& str)
{
    return nlohmann::json::parse(str).get<TicketValidationResponse>();
}

std::string TicketValidationResponse::toString() const
{
    return nlohmann::json(*this).dump();
}