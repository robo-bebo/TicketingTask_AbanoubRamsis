#pragma once

#include "BackOfficeInterface/CBackOfficeProxy.hpp"
#include "MqttClient/MqttClient.hpp"

#include <iostream>
#include <memory>
#include <mutex>


class SaleRequestHandler
{
  public:
    SaleRequestHandler(std::unique_ptr<BackOfficeProxy> backOfficeClient);
    void startHandler();

  private:
    void onRequestReceived(std::string topic, std::string payload);
    void sendRequestToBackOffice(const std::string& payload);

    MqttClient                       m_mqttClient;
    std::unique_ptr<BackOfficeProxy> m_backOfficeProxy;

    mutable std::mutex m_mutex;
};