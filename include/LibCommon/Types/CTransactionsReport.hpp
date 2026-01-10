#pragma once

#include "CSingleTransaction.hpp"

#include <string>
#include <vector>


class TransactionsReport
{
  public:
    uint32_t                       gateID  = 0;
    uint32_t                       total   = 0;
    uint32_t                       valid   = 0;
    uint32_t                       invalid = 0;
    std::vector<SingleTransaction> lastTransactions;


    std::string               toXMLString() const;
    static TransactionsReport fromXMLString(const std::string& xmlStr);
};