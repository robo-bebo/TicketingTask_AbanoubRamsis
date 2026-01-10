#pragma once

#include "IDatabaseHandler.hpp"

class JsonFileDatabaseHandler : public IDatabaseHandler
{
  public:
    JsonFileDatabaseHandler(const std::string& filePath);
    ~JsonFileDatabaseHandler() override = default;

    bool                            isTicketOnDatabase(const std::string& ticket) override;
    std::unordered_set<std::string> getAllTickets() override;
    bool                            storeTicket(const std::string& ticket) override;

  private:
    void readAllTicketsFromFile();

    std::string                     m_filePath;
    std::unordered_set<std::string> m_ticketStorage;
};