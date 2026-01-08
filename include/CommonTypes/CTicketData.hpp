#pragma once

#include "CommonTypes/CDateTime.hpp"
#include "NlohmannJson/json.hpp"

#include <boost/beast/core/detail/base64.hpp>
#include <stdint.h>
#include <string>

class TicketData
{
  public:
    uint64_t ticketID;
    int32_t  ValidityDays;
    int8_t   lineNumber;
    DateTime creationDate;

    std::string       toBase64() const;
    static TicketData fromBase64(const std::string& base64Str);
};

void to_json(nlohmann::json& json, const TicketData& data)
{

    json["ticketID"]     = data.ticketID;
    json["ValidityDays"] = data.ValidityDays;
    json["lineNumber"]   = data.lineNumber;
    json["creationDate"] = data.creationDate.toString();
}


void from_json(const nlohmann::json& json, TicketData& data)
{
    data.ticketID     = json.at("ticketID").get<uint64_t>();
    data.ValidityDays = json.at("ValidityDays").get<int32_t>();
    data.lineNumber   = json.at("lineNumber").get<int8_t>();
    data.creationDate = DateTime::fromString(json.at("creationDate").get<std::string>());
}