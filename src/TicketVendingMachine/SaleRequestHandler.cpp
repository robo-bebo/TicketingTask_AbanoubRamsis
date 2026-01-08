#include "TicketVendingMachine/SaleRequestHandler.hpp"

#include "Mqtt/MqttTopics.hpp"
#include "CommonTypes/CTicketRequest.hpp"
#include "CommonTypes/CTicketData.hpp"

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

}