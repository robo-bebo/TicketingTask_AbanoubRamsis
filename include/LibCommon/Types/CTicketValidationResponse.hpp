#pragma once

#include "NlohmannJson/json.hpp"

#include <string>

class TicketValidationResponse
{
  public:
    bool valid;

    static TicketValidationResponse fromString(const std::string& str);
    std::string                     toString() const;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TicketValidationResponse, valid)