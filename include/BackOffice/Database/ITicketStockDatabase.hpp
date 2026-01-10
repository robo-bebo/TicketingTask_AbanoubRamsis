#pragma once

#include <string>
#include <unordered_set>

class ITicketStockDatabase
{

  public:
    virtual ~ITicketStockDatabase() = default;

    virtual bool                            isTicketOnDatabase(const std::string& ticket) = 0;
    virtual bool                            storeTicket(const std::string& ticket)        = 0;
    virtual std::unordered_set<std::string> getAllTickets()                               = 0;
};