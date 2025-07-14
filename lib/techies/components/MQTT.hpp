#pragma once
#include "core/Config.hpp"
#include "core/Time.hpp"
#include <Arduino.h>
#include <Ethernet.h>
#include <MQTT.h>

#include "MQTTQueue.hpp"
#include "MQTTTopics.hpp"

#ifndef TCFG_C_MQTT_BROKER_IP
#error TCFG has missing C_MQTT_BROKER_IP
#endif

namespace techies::components
{
    class MQTT
    {
    protected:
        static bool active;
        static bool connected;
        static techies::core::time_t connect_time;
        static techies::core::time_t connect_interval;
        static techies::core::time_t failure_delay;
        static short failure_limit;
        static short failure_count;

        static EthernetClient eth;
        static MQTTClient client;

        typedef MQTTQueue<
            TCFG_C_MQTT_MAX_MESSAGES,
            TCFG_C_MQTT_MAX_PAYLOAD
        > CMQTTQueue;
        static CMQTTQueue queue;

        static void OnMQTTConnected();
        static void OnMQTTMessage(String &topic, String &payload);
    public:
        static void Init();
        static bool Active();

        static bool IsConnected();
        static void OnBeforeCycle();

        static bool Receive(MQTTTopics::topic_t topic, char buffer[TCFG_C_MQTT_MAX_PAYLOAD]);
    };
}
