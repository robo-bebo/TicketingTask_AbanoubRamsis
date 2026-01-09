#pragma once

#include "CDateTime.hpp"
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

void to_json(nlohmann::json& json, const TicketData& data);
void from_json(const nlohmann::json& json, TicketData& data);
