#pragma once

#include "NlohmannJson/json.hpp"

#include <chrono>
#include <stdint.h>
#include <string>

class TicketRequest
{
  public:
    int32_t validityDays;
    int8_t  lineNumber;

    std::string          toString() const;
    static TicketRequest fromString(const std::string& str);
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TicketRequest, validityDays, lineNumber)