#include "CTicketStockDatabase.hpp"

TicketStockDatabase::TicketStockDatabase(std::unique_ptr<IDatabaseHandler> dbHandler)
    : m_dbHandler(std::move(dbHandler))
{
}

bool TicketStockDatabase::isTicketOnDatabase(const std::string& ticket)
{
    return m_dbHandler->isTicketOnDatabase(ticket);
}

std::unordered_set<std::string> TicketStockDatabase::getAllTickets()
{
    return m_dbHandler->getAllTickets();
}

bool TicketStockDatabase::storeTicket(const std::string& ticket)
{
    return m_dbHandler->storeTicket(ticket);
}
