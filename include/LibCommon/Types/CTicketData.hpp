#pragma once

#include "CDateTime.hpp"
#include "NlohmannJson/json.hpp"
#include "primitives.hpp"

#include <boost/beast/core/detail/base64.hpp>
#include <string>

class TicketData
{
  public:
    TicketId   ticketID;
    Days       ValidityDays;
    LineNumber lineNumber;
    DateTime   creationDate;

    std::string       toBase64() const;
    static TicketData fromBase64(const std::string& base64Str);
};

void to_json(nlohmann::json& json, const TicketData& data);
void from_json(const nlohmann::json& json, TicketData& data);
