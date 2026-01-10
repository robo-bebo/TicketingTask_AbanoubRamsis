#pragma once

#include "BackOfficeInterface/CBackOfficeProxy.hpp"
#include "CTransactionReporter.hpp"
#include "MqttClient/MqttClient.hpp"

#include <iostream>
#include <memory>
#include <mutex>


class ValidationRequestHandler
{
  public:
    ValidationRequestHandler(std::shared_ptr<BackOfficeProxy>     backOfficeClient,
                             std::unique_ptr<TransactionReporter> transactionReporter);
    void startHandler();

  private:
    void onRequestReceived(std::string topic, std::string payload);
    void sendRequestToBackOffice(const std::string& payload);

    MqttClient                           m_mqttClient;
    std::shared_ptr<BackOfficeProxy>     m_backOfficeProxy;
    std::unique_ptr<TransactionReporter> m_transactionReporter;

    mutable std::mutex m_mutex;
};