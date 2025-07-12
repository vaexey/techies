#include "HAL.hpp"
#include "IO.hpp"
#include "Time.hpp"
#include "components/Log.hpp"
#include "event/Manager.hpp"

namespace techies::core
{
    // typedef int T;
    template <class T>
    class Program
    {
    public:
        // Cycle period
        time_t Period = 20;

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
                L->Trace("Yield starts cycle with sigma=" + String(sigma));
                
                if(sigma > Period / 10)
                {
                    L->Warn("Can't keep up! sigma=" + String(sigma) + ", period=" + String(Period));
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

            L->Trace(String(GetTime() - last_cycle) + " Dispatching BeforeCycle");
            event::Manager::BeforeCycle.Dispatch();

            L->Trace(String(GetTime() - last_cycle) + " Reading inputs...");
            IO::ReadInputs();

            L->Trace(String(GetTime() - last_cycle) + " Executing program cycle...");
            T::Cycle(&Old, &New);

            L->Trace(String(GetTime() - last_cycle) + " Commiting cycle");
            CommitCycle();

            L->Trace(String(GetTime() - last_cycle) + " Writing outputs...");
            IO::WriteOutputs(New.QX);

            L->Trace(String(GetTime() - last_cycle) + " Dispatching AfterCycle");
            event::Manager::AfterCycle.Dispatch();
        }

    protected:
        // Original program state before cycle start
        T Old;

        // Program state working copy, created for the next cycle
        T New;

        time_t last_cycle = 0;
    };
} // namespace techies::core
