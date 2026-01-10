#pragma once

#include "Types/CTransactionsReport.hpp"

class IReportDatabase
{
  public:
    virtual bool               storeReport(const TransactionsReport& report) = 0;
    virtual TransactionsReport getReport()                                   = 0;
};