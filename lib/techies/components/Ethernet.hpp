#include "core/Config.hpp"
#include <Arduino.h>
#include <Ethernet.h>

#ifndef TCFG_C_ETHERNET_MAC
#error TCFG has missing C_ETHERNET_MAC
#endif
#ifndef TCFG_C_ETHERNET_IP
#error TCFG has missing C_ETHERNET_IP
#endif
#ifndef TCFG_C_ETHERNET_NET
#error TCFG has missing C_ETHERNET_NET
#endif
#ifndef TCFG_C_ETHERNET_GW
#error TCFG has missing C_ETHERNET_GW
#endif
#ifndef TCFG_C_ETHERNET_DNS
#error TCFG has missing C_ETHERNET_DNS
#endif

namespace techies::components
{
    
    class Ethernet
    {
    protected:
        static bool active;

        static bool last_link;
    public:
        static void Init();
        static bool Active();

        static bool HasHardware();
        static bool HasLink();

        static void OnBeforeCycle();
    };

} // namespace techies::components
