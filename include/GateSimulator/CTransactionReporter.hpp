#pragma once

#include "BackOfficeInterface/CBackOfficeProxy.hpp"
#include "Types/CSingleTransaction.hpp"
#include "Types/CTransactionsReport.hpp"

#include <memory>

class TransactionReporter
{
  public:
    TransactionReporter(std::shared_ptr<BackOfficeProxy> backOfficeProxy);
    void updateReport(const SingleTransaction& report);

  private:
    void                             getTransactionReportOnStartup();
    std::shared_ptr<BackOfficeProxy> m_backOfficeProxy;
    TransactionsReport               m_report;
};