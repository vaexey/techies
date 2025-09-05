#include "MQTT.hpp"

namespace techies::modules
{
    void MQTT_PUB::Cycle(
        const MQTT_PUB* Old,
        MQTT_PUB* New,
        techies::components::MQTTTopics::topic_t topic,
        const char* payload,
        bool IN
    ) {
        if(IN)
        {
            New->Q = techies::components::MQTT::Send(
                topic,
                payload
            );
        }
        else
        {
            New->Q = false;
        }
    }

    void MQTT_PUB::Reset(MQTT_PUB* New)
    {
        New->Q = false;
    }
} // namespace techies::modules
