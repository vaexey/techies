#include "techies.hpp"
#define TAG "Bootstrap"

namespace techies::bootstrap
{
    techies::components::PrintLogger DefaultLogger(&Serial);
    struct DataState;
} // namespace name

#define BOOTSTRAP_DATASTATE techies::bootstrap::DataState
#define BOOTSTRAP_PROGRAM techies::bootstrap::Program
#define BOOTSTRAP_PROGRAM_TYPE techies::core::Program<BOOTSTRAP_DATASTATE>

#define BState() struct BOOTSTRAP_DATASTATE : public techies::core::State
#define BCycle() static void Cycle(const BOOTSTRAP_DATASTATE* Old, BOOTSTRAP_DATASTATE* New)
#define BReset() static void Reset(BOOTSTRAP_DATASTATE* New)
#define BProgram() namespace techies::bootstrap { BOOTSTRAP_PROGRAM_TYPE Program; };

#define BInit() { techies::bootstrap::Init<void>(); };
#define BYield() { techies::bootstrap::Yield<void>(); };

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

        program->Reset();
    }

    template<typename T>
    inline void Yield(T* program)
    {
        program->Yield();
    }
} // namespace techies::bootstrap

#undef TAG