#pragma once


#include "CJsonFileDatabaseHandler.hpp"
#include "CReportDatabase.hpp"
#include "CTicketStockDatabase.hpp"

#include <memory>

class CDatabaseFactory
{
  public:
    static inline std::unique_ptr<ITicketStockDatabase> createJsonFileDatabase(const std::string& filePath)
    {
        auto dbHandler = std::make_unique<JsonFileDatabaseHandler>(filePath);
        return std::make_unique<TicketStockDatabase>(std::move(dbHandler));
    }

    static inline std::unique_ptr<IReportDatabase> createReportDatabase(const std::string& filePath)
    {
        return std::make_unique<ReportDatabase>(filePath);
    }
};
