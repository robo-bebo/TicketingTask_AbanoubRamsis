#pragma once

#include "IReportDatabase.hpp"

#include <string>

class ReportDatabase : public IReportDatabase
{
  public:
    ReportDatabase(const std::string& filePath);
    bool               storeReport(const TransactionsReport& report) override;
    TransactionsReport getReport() override;

  private:
    void               readReportFromFile();
    std::string        m_filePath;
    TransactionsReport m_cachedReport;
};