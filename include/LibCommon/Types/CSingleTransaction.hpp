#pragma once

#include "CDateTime.hpp"

#include <string>


class SingleTransaction
{
  public:
    std::string ticket;
    DateTime    validationDate;
    bool        isValid;
};