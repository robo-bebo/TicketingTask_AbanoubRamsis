#pragma once

#include "Database/IReportDatabase.hpp"

#include <gmock/gmock.h>

class IReportsDatabaseMock : public IReportDatabase
{
  public:
    MOCK_METHOD(bool, storeReport, (const TransactionsReport& report), (override));
    MOCK_METHOD(TransactionsReport, getReport, (), (override));
};