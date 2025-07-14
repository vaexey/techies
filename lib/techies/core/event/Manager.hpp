#include "Collection.hpp"

namespace techies::core::event
{
    class Manager
    {
    public:
        static Collection<TCFG_CORE_EVENT_CONNECTIONS_MAX> Reset;
        static Collection<TCFG_CORE_EVENT_CONNECTIONS_MAX> BeforeCycle;
        static Collection<TCFG_CORE_EVENT_CONNECTIONS_MAX> AfterCycle;
    };
} // namespace techies::core::event
