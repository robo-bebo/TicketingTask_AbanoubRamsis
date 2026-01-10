#include "CValidationRequestHandler.hpp"

#include "MqttClient/MqttTopics.hpp"
#include "Types/CTicketData.hpp"
#include "Types/CTicketValidationResponse.hpp"

#include <chrono>
#include <iostream>
#include <thread>


ValidationRequestHandler::ValidationRequestHandler(std::shared_ptr<BackOfficeProxy> backOfficeClient,
                                                   std::unique_ptr<TransactionReporter> transactionReporter)
    : m_backOfficeProxy(std::move(backOfficeClient)),
      m_transactionReporter(std::move(transactionReporter)),
      m_mqttClient("GateSimulator")
{
}

void ValidationRequestHandler::startHandler()
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
    m_mqttClient.subscribe(mqttTopics::TICKET_VALIDATION_REQUEST);
}

void ValidationRequestHandler::onRequestReceived(std::string topic, std::string payload)
{
    std::cout << "Received request on topic: " << topic << " with payload: " << payload << std::endl;
    const TicketData ticketData = TicketData::fromBase64(payload);

    SingleTransaction transaction;
    transaction.ticket         = payload;
    transaction.validationDate = DateTime();

    try
    {
        const TicketValidationResponse response
            = TicketValidationResponse::fromString(m_backOfficeProxy->validateTicket(ticketData));
        if(response.valid)
        {
            std::cout << "Open Gate" << std::endl;
            transaction.isValid = true;
        }
        else
        {
            std::cout << "Ticket is invalid" << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "BackOffice not reachable, falling back to local validation: " << e.what()
                  << std::endl;
        const DateTime expiryDate = ticketData.creationDate.addDays(ticketData.ValidityDays);
        if(DateTime() > expiryDate)
        {
            std::cout << "Ticket has expired on " << expiryDate.toString() << std::endl;
        }
        else
        {
            std::cout << "Open Gate" << std::endl;
            transaction.isValid = true;
        }
    }

    m_transactionReporter->updateReport(transaction);
}