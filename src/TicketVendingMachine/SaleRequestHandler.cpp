#include "TicketVendingMachine/SaleRequestHandler.hpp"

#include "CommonTypes/CTicketData.hpp"
#include "CommonTypes/CTicketRequest.hpp"
#include "Mqtt/MqttTopics.hpp"
#include "TicketVendingMachine/CBackOfficeProxy.hpp"

#include <chrono>
#include <iostream>
#include <thread>


SaleRequestHandler::SaleRequestHandler() : m_mqttClient("VendingMachine") {}

void SaleRequestHandler::startHandler()
{
    if(!m_mqttClient.connect("localhost", 1883))
    {
        throw std::runtime_error("Failed to connect to MQTT broker");
    }

    m_mqttClient.setMessageCallback(onRequestReceived);
    m_mqttClient.subscribe(mqttTopics::TICKET_SALE_REQUEST);
}

void SaleRequestHandler::onRequestReceived(std::string topic, std::string payload)
{
    std::cout << "Received request on topic: " << topic << " with payload: " << payload << std::endl;

    TicketRequest request;
    request = nlohmann::json::parse(payload);

    std::cout << "Parsed Ticket Request - ValidityDays: " << static_cast<int>(request.validityDays)
              << ", lineNumber: " << static_cast<int>(request.lineNumber) << std::endl;

    BackOfficeProxy backOfficeProxy;

    try
    {
        const std::string base64TicketData = backOfficeProxy.requestTicket(request);
        const TicketData  ticketData       = TicketData::fromBase64(base64TicketData);
        std::cout << "Received Ticket Data - TicketID: " << ticketData.ticketID
                  << ", ValidityDays: " << ticketData.ValidityDays
                  << ", lineNumber: " << static_cast<int>(ticketData.lineNumber)
                  << ", creationDate: " << ticketData.creationDate.toString() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error requesting ticket from BackOffice: " << e.what() << std::endl;
    }
}