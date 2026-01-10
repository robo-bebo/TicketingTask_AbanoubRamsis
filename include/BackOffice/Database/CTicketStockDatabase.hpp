#pragma once


#include "IDatabaseHandler.hpp"
#include "ITicketStockDatabase.hpp"

#include <memory>
#include <string>
#include <unordered_set>

class TicketStockDatabase : public ITicketStockDatabase
{

  public:
    TicketStockDatabase(std::unique_ptr<IDatabaseHandler> dbHandler);
    ~TicketStockDatabase() = default;

    bool                            isTicketOnDatabase(const std::string& ticket) override;
    bool                            storeTicket(const std::string& ticket) override;
    std::unordered_set<std::string> getAllTickets() override;

  private:
    std::unique_ptr<IDatabaseHandler> m_dbHandler;
};