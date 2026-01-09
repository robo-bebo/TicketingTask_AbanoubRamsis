#include "CTicketRequest.hpp"


std::string TicketRequest::toString() const
{
    const std::string requestStr = nlohmann::json(*this).dump();
    return requestStr;
}

TicketRequest TicketRequest::fromString(const std::string& str)
{
    nlohmann::json json = nlohmann::json::parse(str);
    return json.get<TicketRequest>();
}