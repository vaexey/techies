#include "components/MQTT.hpp"
#include "components/Log.hpp"
#include "core/event/Manager.hpp"
#define TAG "MQTT"

namespace techies::components
{
    bool MQTT::active = false;
    bool MQTT::connected = false;
    techies::core::time_t MQTT::connect_time = 1;
    techies::core::time_t MQTT::connect_interval = 1500;
    techies::core::time_t MQTT::failure_delay = 60000;
    short MQTT::failure_limit = 5;
    short MQTT::failure_count = 0;

    EthernetClient MQTT::eth;
    MQTTClient MQTT::client;

    MQTT::CMQTTQueue MQTT::queue{};

    void MQTT::Init()
    {
        L->Trace(TAG, "Initializing MQTT...");

        eth.setConnectionTimeout(TCFG_C_MQTT_TIMEOUT);
        eth.setTimeout(TCFG_C_MQTT_TIMEOUT);
        client.setTimeout(TCFG_C_MQTT_TIMEOUT);
        
        client.begin(
            IPAddress(TCFG_C_MQTT_BROKER_IP),
            eth
        );
        client.onMessage(OnMQTTMessage);

        techies::core::event::Manager::BeforeCycle
            .Connect(OnBeforeCycle);

        active = true;
    }

    bool MQTT::Active()
    {
        return active;
    }

    bool MQTT::IsConnected()
    {
        return connected;
    }
    
    void MQTT::OnBeforeCycle()
    {
        if(client.connected())
            client.loop();

        connected = client.connected();
        auto now = techies::core::GetTime();

        if(!connected)
        {
            bool failure_streak = failure_count >= 5;
            auto interval = failure_streak ? failure_delay : connect_interval;

            if(now > connect_time + interval)
            {
                if(connect_time == 0)
                {
                    L->Debug(TAG, "MQTT connection lost, retrying...");
                }
                else
                {
                    L->Debug(TAG, "Reconnect interval passed, starting MQTT connection...");
                }

                connect_time = now;
                
                bool ok = client.connect(
                    TCFG_C_MQTT_ID,
                    TCFG_C_MQTT_USERNAME,
                    TCFG_C_MQTT_PASSWORD
                );

                if(ok)
                {
                    L->Info(TAG, "MQTT connection successful");
                    connect_time = 0;
                    failure_count = 0;

                    OnMQTTConnected();
                }
                else
                {
                    failure_count++;
                    if(failure_count >= failure_limit)
                    {
                        L->Err(TAG, 
                            "Could not connect to MQTT. Failure limit reached, retrying in " +
                            String(failure_delay)
                        );
                    }
                    else
                    {
                        L->Warn(TAG, "Could not connect to MQTT, retrying in " + String(connect_interval));
                    }
                }
            }
        }
    }

    void MQTT::OnMQTTConnected()
    {
        L->Debug(TAG, "Subscribing...");

        size_t subs = 0;

        char buffer[MQTTTopics::max_topic_length];
        for(size_t i = 0; i < MQTTTopics::topic_count; i++)
        {
            if(!MQTTTopics::ShouldBeSubscribed(i))
                continue;

            MQTTTopics::CopyString(i, buffer);
            L->Trace("MQTT_SUB", buffer);
            client.subscribe(buffer);
            subs++;
        }

        L->Trace(TAG,
            "Done. Subscribed topics: " +
            String(subs) +
            "/" +
            String(MQTTTopics::topic_count)
        );
    }
    
    void MQTT::OnMQTTMessage(String &topic, String &payload)
    {
        L->Debug("MQTT_RCV_T", topic);
        L->Trace("MQTT_RCV_P", payload);

        if(payload.length() > TCFG_C_MQTT_MAX_PAYLOAD)
        {
            L->Warn(TAG, 
                "Payload of length " + 
                String(payload.length()) +
                "was truncated"
            );
        }

        queue.Add(0, payload.c_str());
    }


    bool MQTT::Receive(MQTTTopics::topic_t topic, char buffer[TCFG_C_MQTT_MAX_PAYLOAD])
    {
        return queue.Remove(topic.i, buffer);
    }
} // namespace techies::components
