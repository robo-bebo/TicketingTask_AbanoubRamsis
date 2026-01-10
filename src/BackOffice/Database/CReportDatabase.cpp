#include "CReportDatabase.hpp"

#include <fstream>
#include <iostream>

ReportDatabase::ReportDatabase(const std::string& filePath) : m_filePath(filePath)
{
    readReportFromFile();
}

bool ReportDatabase::storeReport(const TransactionsReport& report)
{

    std::ofstream file(m_filePath, std::ios::binary | std::ios::trunc);
    if(!file)
    {
        std::cerr << __func__ << " Failed to open file for writing: " << m_filePath << std::endl;
        return false;
    }

    m_cachedReport = report;
    file << m_cachedReport.toXMLString();

    return true;
}

TransactionsReport ReportDatabase::getReport()
{
    return m_cachedReport;
}

void ReportDatabase::readReportFromFile()
{
    std::ifstream file(m_filePath, std::ios::binary);
    if(!file)
    {
        std::cerr << __func__ << " Failed to open file: " << m_filePath << std::endl;
        return;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string xmlStr = ss.str();

    m_cachedReport = TransactionsReport::fromXMLString(xmlStr);
}
