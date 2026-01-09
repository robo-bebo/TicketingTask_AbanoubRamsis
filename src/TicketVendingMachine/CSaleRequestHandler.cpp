#include "CSaleRequestHandler.hpp"

#include "MqttClient/MqttTopics.hpp"
#include "Types/CTicketData.hpp"
#include "Types/CTicketRequest.hpp"

#include <chrono>
#include <iostream>
#include <thread>


SaleRequestHandler::SaleRequestHandler(std::unique_ptr<BackOfficeProxy> backOfficeClient)
    : m_backOfficeProxy(std::move(backOfficeClient)), m_mqttClient("VendingMachine")
{
}

void SaleRequestHandler::startHandler()
{
    if(!m_mqttClient.connect("localhost", 1883))
    {
        throw std::runtime_error("Failed to connect to MQTT broker");
    }

    m_mqttClient.setMessageCallback(
        [this](std::string topic, std::string payload)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            this->onRequestReceived(std::move(topic), std::move(payload));
        });
    m_mqttClient.subscribe(mqttTopics::TICKET_SALE_REQUEST);
}

void SaleRequestHandler::onRequestReceived(std::string topic, std::string payload)
{
    std::cout << "Received request on topic: " << topic << " with payload: " << payload << std::endl;

    TicketRequest request;
    request = nlohmann::json::parse(payload);


    const std::string base64TicketData = m_backOfficeProxy->requestTicket(request);
    const TicketData  ticketData       = TicketData::fromBase64(base64TicketData);
    std::cout << "Received Ticket: " << base64TicketData << std::endl;
    std::cout << "Ticket Data: TicketID: " << ticketData.ticketID
              << ", ValidityDays: " << ticketData.ValidityDays
              << ", lineNumber: " << static_cast<int>(ticketData.lineNumber)
              << ", creationDate: " << ticketData.creationDate.toString() << std::endl;
}