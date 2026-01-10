#pragma once


#include "CJsonFileDatabaseHandler.hpp"
#include "CTicketStockDatabase.hpp"

class CDatabaseFactory
{
  public:
    static inline std::unique_ptr<ITicketStockDatabase> createJsonFileDatabase(const std::string& filePath)
    {
        auto dbHandler = std::make_unique<JsonFileDatabaseHandler>(filePath);
        return std::make_unique<TicketStockDatabase>(std::move(dbHandler));
    }
};
