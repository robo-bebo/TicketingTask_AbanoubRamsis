#pragma once
#include <functional>
#include <mosquitto.h>
#include <string>

class MqttClient
{
  public:
    MqttClient(const std::string& id);
    ~MqttClient();

    bool connect(const std::string& host, int port);
    void publish(const std::string& topic, const std::string& payload);
    void subscribe(const std::string& topic);
    void setMessageCallback(std::function<void(std::string, std::string)> cb);

  private:
    mosquitto*                                    m_mosq;
    std::function<void(std::string, std::string)> m_messageCallback;
};
