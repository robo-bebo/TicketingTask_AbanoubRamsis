#pragma once

#include "Database/ITicketStockDatabase.hpp"

#include <gmock/gmock.h>

class ITicketStockDatabaseMock : public ITicketStockDatabase
{
  public:
    MOCK_METHOD(bool, isTicketOnDatabase, (const std::string& ticket), (override));
    MOCK_METHOD(bool, storeTicket, (const std::string& ticket), (override));
    MOCK_METHOD(std::unordered_set<std::string>, getAllTickets, (), (override));
};