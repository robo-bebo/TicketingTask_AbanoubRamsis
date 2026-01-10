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
        auto ticketNode                             = transactions.append_child("Ticket");
        ticketNode.append_child("Ticket").text()    = tx.ticket.c_str();
        ticketNode.append_child("Status").text()    = tx.isValid ? "Valid" : "Invalid";
        ticketNode.append_child("Timestamp").text() = tx.validationDate.toString().c_str();
    }

    std::ostringstream oss;
    doc.save(oss, "  "); // pretty print with 2 spaces
    return oss.str();
}

bool TransactionsReport::fromXMLString(const std::string& xml)
{
    pugi::xml_document doc;
    if(!doc.load_string(xml.c_str()))
        return false;

    auto root = doc.child("TicketReport");
    if(!root)
        return false;

    gateID = root.attribute("GateID").as_uint();

    auto summary = root.child("Summary");
    total        = summary.child("Total").text().as_uint();
    valid        = summary.child("Valid").text().as_uint();
    invalid      = summary.child("Invalid").text().as_uint();

    lastTransactions.clear();
    for(auto node : root.child("LastTransactions").children("Ticket"))
    {
        SingleTransaction tx;
        tx.ticket  = node.child("Ticket").text().as_string();
        tx.isValid = std::string(node.child("Status").text().as_string()) == "Valid";
        tx.validationDate.fromString(node.child("Timestamp").text().as_string());
        lastTransactions.push_back(tx);
    }

    return true;
}