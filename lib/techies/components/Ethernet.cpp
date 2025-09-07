#include "core/Config.hpp"
#include "core/event/Manager.hpp"
#include "components/Ethernet.hpp"
#include "components/Log.hpp"
#define TAG "Ethernet"

uint8_t mac[6] = { TCFG_C_ETHERNET_MAC };

inline void techies_components_Ethernet_Init()
{
    Ethernet.begin(
        mac,
        IPAddress(TCFG_C_ETHERNET_IP),
        IPAddress(TCFG_C_ETHERNET_DNS),
        IPAddress(TCFG_C_ETHERNET_GW),
        IPAddress(TCFG_C_ETHERNET_NET)
    );

    auto ip = Ethernet.localIP();
    L->Info(TAG, 
        "Ethernet started. IP: " +
        String(ip[0]) + "." +
        String(ip[1]) + "." +
        String(ip[2]) + "." +
        String(ip[3])
    );
}

inline bool techies_components_Ethernet_HasHardware()
{
    return Ethernet.hardwareStatus() != EthernetNoHardware;
}

inline bool techies_components_Ethernet_HasLink()
{
    return
        techies_components_Ethernet_HasHardware() &&
        (Ethernet.linkStatus() != LinkOFF);
}

namespace techies::components
{

    bool Ethernet::active = false;
    bool Ethernet::last_link = false;
    bool Ethernet::SpoonSocketActive = false;
    EthernetUDP Ethernet::SpoonSocket {};

    void Ethernet::Init()
    {
        L->Trace(TAG, "Initializing ethernet...");

        techies_components_Ethernet_Init();

        if(!techies_components_Ethernet_HasHardware())
        {
            L->Err(TAG, "Ethernet controller hardware could not be found");
        }

        L->Info(TAG,
            "Opening Spoon socket..."
        );

        SpoonSocket.begin(TCFG_C_ETHERNET_SPOON_DEVICE_PORT);
        SpoonSocketActive = true;

        techies::core::event::Manager::BeforeCycle
            .Connect(OnBeforeCycle);

        last_link = !HasLink();
        
        active = true;
    }

    bool Ethernet::Active()
    {
        return active;
    }

    bool Ethernet::HasHardware()
    {
        return techies_components_Ethernet_HasHardware();
    }

    bool Ethernet::HasLink()
    {
        return techies_components_Ethernet_HasLink();
    }

    void Ethernet::OnBeforeCycle()
    {
        auto link = HasLink();

        if(link != last_link)
        {
            last_link = link;

            if(link)
            {
                L->Info(TAG, "Ethernet link: UP");
            }
            else
            {
                L->Info(TAG, "Ethernet link: DOWN");
            }
        }
    }

} // namespace techies::components
