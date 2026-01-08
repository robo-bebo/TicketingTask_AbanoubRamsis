#pragma once

#include "NlohmannJson/json.hpp"

#include <chrono>
#include <stdint.h>
#include <string>

class TicketRequest
{
  public:
    int32_t ValidityDays;
    int8_t  lineNumber;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TicketRequest, ValidityDays, lineNumber)