#pragma once

#include "Mqtt/MqttClient.hpp"

#include <chrono>
#include <iostream>
#include <mutex>


class SaleRequestHandler
{
  public:
    void startHandler();

  private:
    static void onRequestReceived(std::string topic, std::string payload);
    void        sendRequestToBackOffice(const std::string& payload);

    mutable std::mutex m_mutex;
};