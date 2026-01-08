#include "Mqtt/MqttClient.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    MqttClient client("VebdingMachine");

    if(!client.connect("localhost", 1883))
    {
        std::cerr << "Failed to connect to MQTT broker" << std::endl;
        return -1;
    }

    client.setMessageCallback([](std::string topic, std::string payload)
                              { std::cout << "[" << topic << "] " << payload << std::endl; });

    client.subscribe("demo/topic");

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
