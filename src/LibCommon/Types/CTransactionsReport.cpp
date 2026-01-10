#include "CTransactionsReport.hpp"

#include <pugixml.hpp>


std::string TransactionsReport::toXMLString() const
{
    pugi::xml_document doc;

    // Root element with GateID attribute
    auto root                       = doc.append_child("TicketReport");
    root.append_attribute("GateID") = gateID;

    // Summary section
    auto summary                           = root.append_child("Summary");
    summary.append_child("Total").text()   = total;
    summary.append_child("Valid").text()   = valid;
    summary.append_child("Invalid").text() = invalid;

    // LastTransactions section
    auto transactions = root.append_child("LastTransactions");
    for(const auto& tx : lastTransactions)
    {
        auto ticketNode                             = transactions.append_child("Transaction");
        ticketNode.append_child("Ticket").text()    = tx.ticket.c_str();
        ticketNode.append_child("Status").text()    = tx.isValid ? "Valid" : "Invalid";
        ticketNode.append_child("Timestamp").text() = tx.validationDate.toString().c_str();
    }

    std::ostringstream oss;
    doc.save(oss, "  ");
    return oss.str();
}

TransactionsReport TransactionsReport::fromXMLString(const std::string& xml)
{
    TransactionsReport report;
    pugi::xml_document doc;
    if(!doc.load_string(xml.c_str()))
        return report;

    auto root = doc.child("TicketReport");
    if(!root)
        return report;
    report.gateID = root.attribute("GateID").as_uint();

    auto summary   = root.child("Summary");
    report.total   = summary.child("Total").text().as_uint();
    report.valid   = summary.child("Valid").text().as_uint();
    report.invalid = summary.child("Invalid").text().as_uint();

    for(auto node : root.child("LastTransactions").children("Transaction"))
    {
        SingleTransaction tx;
        tx.ticket         = node.child("Ticket").text().as_string();
        tx.isValid        = std::string(node.child("Status").text().as_string()) == "Valid";
        tx.validationDate = DateTime::fromString(node.child("Timestamp").text().as_string());
        report.lastTransactions.push_back(tx);
    }

    return report;
}