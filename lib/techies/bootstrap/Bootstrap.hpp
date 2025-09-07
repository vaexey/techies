#include "techies.hpp"
#define TAG "Bootstrap"

namespace techies::bootstrap
{
    // techies::components::PrintLogger DefaultLogger(&Serial);
    // techies::components::SpoonLogger DefaultLogger;
    techies::components::FullLogger DefaultLogger(&Serial);
    struct DataState;


#ifdef TCFG_C_LCDHMI
    void LCDHMI_Printer(techies::components::LCDHMI_Display* HMI);
    void LCDHMI_Printer_Impl(techies::components::LCDHMI_Display* HMI, const DataState* Old);
#endif
} // namespace name

// Shortcut macros
#define BOOTSTRAP_DATASTATE techies::bootstrap::DataState
#define BOOTSTRAP_PROGRAM techies::bootstrap::Program
#define BOOTSTRAP_PROGRAM_TYPE techies::core::Program<BOOTSTRAP_DATASTATE>

#ifdef TCFG_C_LCDHMI
#define BOOTSTRAP_LCDHMI_PRINTER techies::bootstrap::LCDHMI_Printer
#endif

// Expand macros
#define BState() struct BOOTSTRAP_DATASTATE : public techies::core::State
#define BModule(type, name) techies::modules::type name = techies::modules::type
#define BCycle() static void Cycle(const BOOTSTRAP_DATASTATE* Old, BOOTSTRAP_DATASTATE* New)
#define BReset() static void Reset(BOOTSTRAP_DATASTATE* New)
#define BProgram() namespace techies::bootstrap { BOOTSTRAP_PROGRAM_TYPE Program; };

#define BInit() { techies::bootstrap::Init<BOOTSTRAP_PROGRAM_TYPE>(&BOOTSTRAP_PROGRAM); };
#define BYield() { techies::bootstrap::Yield<BOOTSTRAP_PROGRAM_TYPE>(&BOOTSTRAP_PROGRAM); };

#ifdef TCFG_C_LCDHMI
#define BLCDHMIPrinter() \
    void techies::bootstrap::LCDHMI_Printer(techies::components::LCDHMI_Display* HMI) { LCDHMI_Printer_Impl(HMI, BOOTSTRAP_PROGRAM.GetCurrentState()); };\
    void techies::bootstrap::LCDHMI_Printer_Impl(techies::components::LCDHMI_Display* HMI, const DataState* Old)
#endif

// Example bootstrap invocation:
// BState()
// {
//     BCycle()
//     {
//     };
//     BReset()
//     {
//     };
// };
// BProgram(); or BMain();

namespace techies::bootstrap
{
    template<typename T>
    inline void Init(T* program)
    {
        Serial.begin(TCFG_BOOTSTRAP_BAUD);

        L = &techies::bootstrap::DefaultLogger;
        L->Info(TAG,
            "Booting techies v."
            TECHIES_CORE_VERSION
            " using bootstrap @("
            TCFG_BOOTSTRAP_PROGRAM_NOTE
            ")"
        );

        techies::components::Ethernet::Init();
        techies::components::MQTT::Init();

#ifdef TCFG_C_LCDHMI
        techies::components::LCDHMI::Init();
        techies::components::LCDHMI::SetPrinter(&BOOTSTRAP_LCDHMI_PRINTER);
#endif

        program->Reset();
    }

    template<typename T>
    inline void Yield(T* program)
    {
        program->Yield();
    }
} // namespace techies::bootstrap

#undef TAG