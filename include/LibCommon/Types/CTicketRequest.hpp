#pragma once

#include "NlohmannJson/json.hpp"
#include "primitives.hpp"

#include <string>

class TicketRequest
{
  public:
    Days       validityDays;
    LineNumber lineNumber;

    std::string          toString() const;
    static TicketRequest fromString(const std::string& str);
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TicketRequest, validityDays, lineNumber)