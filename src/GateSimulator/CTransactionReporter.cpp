#include "CTransactionReporter.hpp"

TransactionReporter::TransactionReporter(std::shared_ptr<BackOfficeProxy> backOfficeProxy)
    : m_backOfficeProxy(std::move(backOfficeProxy))
{
    getTransactionReportOnStartup();
}

void TransactionReporter::updateReport(const SingleTransaction& report)
{
    // Update summary
    m_report.total += 1;
    if(report.isValid)
    {
        m_report.valid += 1;
    }
    else
    {
        m_report.invalid += 1;
    }

    // Add to last transactions
    m_report.lastTransactions.push_back(report);
    if(m_report.lastTransactions.size() > 10)
    {
        m_report.lastTransactions.erase(m_report.lastTransactions.begin());
    }

    // Send updated report to BackOffice
    const std::string xmlReport = m_report.toXMLString();
    m_backOfficeProxy->postTransactionReport(m_report);
}

void TransactionReporter::getTransactionReportOnStartup()
{
    const std::string xmlReport = m_backOfficeProxy->getTransactionReport();
    std::cout << __func__ << " Received XML Report: " << xmlReport << std::endl;
    m_report = TransactionsReport::fromXMLString(xmlReport);
}