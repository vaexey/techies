#include "core/Config.hpp"
#include "components/MQTT.hpp"

namespace techies::modules
{
    template<size_t payload_size>
    struct MQTT_RCV
    {
        bool Q;
        char Payload[payload_size];

        static void Cycle(
            const MQTT_RCV* Old,
            MQTT_RCV* New,
            techies::components::MQTTTopics::topic_t topic,
            bool IN
        ) {
            if(IN)
            {
                New->Q = techies::components::MQTT::Receive(
                    topic,
                    New->Payload
                );
            }
            else
            {
                New->Q = false;
            }
        }

        static void Reset(MQTT_RCV* New)
        {
            New->Q = false;
        }
    };

    typedef MQTT_RCV<TCFG_C_MQTT_MAX_PAYLOAD> MQTT_RCVD;

} // namespace techies::modules
