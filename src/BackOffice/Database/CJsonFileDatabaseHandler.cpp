#include "CJsonFileDatabaseHandler.hpp"

#include "NlohmannJson/json.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>


JsonFileDatabaseHandler::JsonFileDatabaseHandler(const std::string& filePath) : m_filePath(filePath)
{
    readAllTicketsFromFile();
}

void JsonFileDatabaseHandler::readAllTicketsFromFile()
{
    std::ifstream file(m_filePath);
    if(!file)
    {
        std::cerr << __func__ << " Failed to open file: " << m_filePath << std::endl;
        return;
    }

    nlohmann::json jsonArray;
    try
    {
        file >> jsonArray;
    }
    catch(const std::exception& e)
    {
        std::cerr << __func__ << " Failed to parse JSON: " << e.what() << std::endl;
        return;
    }

    if(!jsonArray.is_array() || jsonArray.empty())
    {
        std::cerr << __func__ << " File is empty or not a JSON array!" << std::endl;
        return;
    }

    m_ticketStorage.clear();
    for(const auto& item : jsonArray)
    {
        m_ticketStorage.insert(item.get<std::string>());
    }
}

std::unordered_set<std::string> JsonFileDatabaseHandler::getAllTickets()
{
    return m_ticketStorage;
}

bool JsonFileDatabaseHandler::isTicketOnDatabase(const std::string& ticket)
{
    return m_ticketStorage.find(ticket) != m_ticketStorage.end();
}

bool JsonFileDatabaseHandler::storeTicket(const std::string& ticket)
{
    m_ticketStorage.insert(ticket);

    nlohmann::json jsonArray = nlohmann::json::array();
    for(const auto& storedTicket : m_ticketStorage)
    {
        jsonArray.push_back(storedTicket);
    }

    std::ofstream file(m_filePath, std::ios::binary | std::ios::trunc);
    if(!file)
    {
        std::cerr << __func__ << " Failed to open file for writing: " << m_filePath << std::endl;
        return false;
    }

    file << jsonArray.dump();
    return true;
}