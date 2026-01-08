#include "Mqtt/MqttClient.hpp"

#include <iostream>


MqttClient::MqttClient(const std::string& id)
{
    mosquitto_lib_init();
    m_mosq = mosquitto_new(id.c_str(), true, this);
}

MqttClient::~MqttClient()
{
    mosquitto_loop_stop(m_mosq, true);
    mosquitto_disconnect(m_mosq);
    mosquitto_destroy(m_mosq);
    mosquitto_lib_cleanup();
}

bool MqttClient::connect(const std::string& host, int port)
{
    mosquitto_message_callback_set(m_mosq,
                                   [](mosquitto*, void* userdata, const mosquitto_message* msg)
                                   {
                                       auto* self = static_cast<MqttClient*>(userdata);
                                       if(self && self->m_messageCallback)
                                       {
                                           std::string topic = msg->topic;
                                           std::string payload((char*)msg->payload, msg->payloadlen);
                                           self->m_messageCallback(topic, payload);
                                       }
                                   });

    const bool isConnected = mosquitto_connect(m_mosq, host.c_str(), port, 60) == MOSQ_ERR_SUCCESS;
    if(isConnected)
    {
        mosquitto_loop_start(m_mosq);
    }

    return isConnected;
}

void MqttClient::publish(const std::string& topic, const std::string& payload)
{
    mosquitto_publish(m_mosq, nullptr, topic.c_str(), payload.size(), payload.c_str(), 0, false);
}

void MqttClient::subscribe(const std::string& topic)
{
    mosquitto_subscribe(m_mosq, nullptr, topic.c_str(), 0);
}

void MqttClient::setMessageCallback(std::function<void(std::string, std::string)> cb)
{
    m_messageCallback = cb;
}
