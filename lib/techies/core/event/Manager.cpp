#include "Manager.hpp"

namespace techies::core::event
{
    Collection<TCFG_CORE_EVENT_CONNECTIONS_MAX> Manager::Reset;
    Collection<TCFG_CORE_EVENT_CONNECTIONS_MAX> Manager::BeforeCycle;
    Collection<TCFG_CORE_EVENT_CONNECTIONS_MAX> Manager::AfterCycle;
} // namespace techies::core::event
