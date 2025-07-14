#pragma once
#include "core/Config.hpp"

/**
 * This file is mainly auto-generated from
 * config/MQTTTopics.hpp
 * 
 * Syntax:
 * #define PREFIX "..."  -  set prefix for
 *                          all topics
 * TOPICS(...)           -  define topic
 *                          list (once)
 * TOPIC(name, string)   -  define topic name
 *                          and string separately
 * TOPIC_URI(uri...)     -  define topic/uri/a/b/c
 *                          by using varargs
 */

#define TOPIC_URI_1(a) TOPIC(uri, #a)
#define TOPIC_URI_2(a, b) TOPIC(a##__##b, #a "/" #b)
#define TOPIC_URI_3(a, b, c) TOPIC(a##__##b##__##c, #a "/" #b "/" #c)

#define TOPIC_URI_EXPAND(x) x
#define TOPIC_URI_GET(_1, _2, _3, name, ...) name
#define TOPIC_URI(...) \
    TOPIC_URI_EXPAND( \
        TOPIC_URI_GET( \
            __VA_ARGS__, \
            TOPIC_URI_3, \
            TOPIC_URI_2, \
            TOPIC_URI_1 \
        )(__VA_ARGS__) \
    )

namespace techies::components::MQTTTopics::Raw
{
    
    // Strings/lengths
    #define TOPICS(list) list
    #define TOPIC(name, string) \
        const char name##_pstr[] PROGMEM = PREFIX string; \
        const size_t name##_len = sizeof(name##_pstr);

    #include "../config/MQTTTopics.hpp"
    #undef TOPICS
    #undef TOPIC
    #undef PREFIX

    // Array of strings
    #define TOPICS(list) \
        const char *const pstr[] PROGMEM = { \
            list \
        };
    #define TOPIC(name, string) name##_pstr,

    #include "../config/MQTTTopics.hpp"
    #undef TOPICS
    #undef TOPIC
    #undef PREFIX

    // Array of lengths
    #define TOPICS(list) \
        const size_t len[] = { \
            list \
        };
    #define TOPIC(name, string) name##_len,

    #include "../config/MQTTTopics.hpp"
    #undef TOPICS
    #undef TOPIC
    #undef PREFIX

    // Max topic length
    #define TOPICS(list) \
        union max_length_u { \
            list \
        };
    #define TOPIC(name, string) uint8_t name[name##_len];

    #include "../config/MQTTTopics.hpp"
    #undef TOPICS
    #undef TOPIC
    #undef PREFIX

} // namespace techies::components::MQTT::Topics


namespace techies::components::MQTTTopics
{
    // Custom type to break compatibility with indexes
    // not inserted into MQTT Topics config
    union topic_t { size_t i; };

    #define CONCAT_IMPL(A, B) A ## B
    #define CONCAT(A, B) CONCAT_IMPL(A, B)
    const int CONCAT(ben, __COUNTER__) = 1;
    const int CONCAT(ben, __COUNTER__) = 1;
    const int CONCAT(ben, __COUNTER__) = 1;

    namespace Raw { enum { COUNTER_BASE = __COUNTER__ }; };

    #define TOPICS(list) list
    #define TOPIC(name, string) \
        const topic_t name = { .i = ( __COUNTER__ - Raw::COUNTER_BASE - 1 ) };

    #include "../config/MQTTTopics.hpp"
    #undef TOPICS
    #undef TOPIC
    #undef PREFIX

    const size_t topic_count = 
        sizeof(Raw::len) / sizeof(Raw::len[0]);
    const size_t max_topic_length = sizeof(Raw::max_length_u);

    inline void CopyString(size_t topic, char* buffer)
    {
        strcpy_P(buffer, (char*)pgm_read_ptr(&(Raw::pstr[topic])));
    }

    inline void CopyString(topic_t topic, char* buffer)
    {
        CopyString(topic.i, buffer);
    }

} // namespace techies::components::MQTTTopics

#undef TOPIC_URI_1
#undef TOPIC_URI_2
#undef TOPIC_URI_3
#undef TOPIC_URI_EXPAND
#undef TOPIC_URI_GET
#undef TOPIC_URI
