#pragma once
#include "core/Config.hpp"
#include "components/Log.hpp"
#define TAG "MQTTQueue"

namespace techies::components
{

    template<size_t max_payload>
    struct MQTTQueueElement
    {
        bool free;
        size_t topic;
        char payload[max_payload];
    };

    template<size_t max_messages, size_t max_payload>
    class MQTTQueue
    {
    protected:
        MQTTQueueElement<max_payload> queue[max_messages];
    
    public:

        MQTTQueue()
        {
            for(size_t i = 0; i < max_messages; i++)
                queue[i].free = true;
        }
        
        bool Add(size_t topic, const char* payload)
        {
            for(size_t i = 0; i < max_messages; i++)
            {
                if(queue[i].free)
                {
                    queue[i].free = false;
                    queue[i].topic = topic;
                    strncpy(queue[i].payload, payload, max_payload - 1);
                    return true;
                }
            }

            L->Err(TAG, "Queue is full! Message lost: " + String(topic));
            return false;
        }

        bool Remove(size_t topic, char dest[max_payload])
        {
            for(size_t i = 0; i < max_messages; i++)
            {
                if(!queue[i].free && queue[i].topic == topic)
                {
                    queue[i].free = true;
                    strncpy(dest, queue[i].payload, max_payload);
                    return true;
                }
            }

            return false;
        }
    };

} // namespace techies::components

#undef TAG