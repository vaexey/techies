#include "core/Config.hpp"
#include "IO.hpp"
#include "Time.hpp"
#include "components/Log.hpp"
#include "event/Manager.hpp"
#define TAG "Program"

namespace techies::core
{
    // typedef int T;
    template <class T>
    class Program
    {
    public:
        // Cycle period
        time_t Period = TCFG_CORE_PROGRAM_PERIOD_DEFAULT;

        void CommitCycle()
        {
            memcpy(&Old, &New, sizeof(T));
        }

        void Yield()
        {
            time_t now = GetTime();
            time_t diff = now - last_cycle;

            if(diff >= Period)
            {
                uint16_t sigma = (uint16_t)diff - (uint16_t)Period;
                L->Trace(TAG, "Yield starts cycle with sigma=" + String(sigma));
                
                if(sigma > Period / 10)
                {
                    L->Warn(TAG, "Can't keep up! sigma=" + String(sigma) + ", period=" + String(Period));
                }

                // time for next cycle
                Cycle();
            }
        }

        void Cycle()
        {
            time_t now = GetTime();
            CycleDelta = now - last_cycle;
            last_cycle = now;

            L->Trace(TAG, "Dispatching BeforeCycle");
            event::Manager::BeforeCycle.Dispatch();

            L->Trace(TAG, "Reading inputs...");
            IO::ReadInputs();

            L->Trace(TAG, "Executing program cycle...");
            New.RST = 0;
            T::Cycle(&Old, &New);

            L->Trace(TAG, "Commiting cycle");
            CommitCycle();

            L->Trace(TAG, "Writing outputs...");
            IO::WriteOutputs(New.QX);

            L->Trace(TAG, "Dispatching AfterCycle");
            event::Manager::AfterCycle.Dispatch();
        }

        void Reset()
        {
            L->Info(TAG, "Resetting techies...");

            L->Trace(TAG, "Initializing I/O");
            IO::Init();

            L->Trace(TAG, "Dispatching OnReset");
            event::Manager::Reset.Dispatch();

            L->Trace(TAG, "Resetting program state");
            T::Reset(&New);
            New.RST = 1;
            CommitCycle();
            
            last_cycle = GetTime();
        }

        const T* GetCurrentState()
        {
            return &Old;
        }

    protected:
        // Original program state before cycle start
        T Old;

        // Program state working copy, created for the next cycle
        T New;

        time_t last_cycle = 0;
    };
} // namespace techies::core

#undef TAG