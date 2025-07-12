#include "TIMERS.hpp"

namespace techies::modules
{
    void TON::Cycle(
        const TON* Old,
        TON* New,
        bool IN,
        techies::core::time_t PT
    ) {
        if(IN)
        {
            New->ET =
                Old->ET +
                techies::core::CycleDelta;

            if(New->ET >= PT)
            {
                New->ET = PT;
                New->Q = 1;
            } else {
                New->Q = 0;
            }
        }
        else
        {
            New->ET = 0;
            New->Q = 0;
        }
    };

    void TOF::Cycle(
        const TOF* Old,
        TOF* New,
        bool IN,
        techies::core::time_t PT
    ) {
        if(IN)
        {
            New->ET = 0;
            New->Q = 1;
        }
        else
        {
            New->ET =
                Old->ET +
                techies::core::CycleDelta;

            if(New->ET >= PT)
            {
                New->ET = PT;
                New->Q = 0;
            } else {
                New->Q = 1;
            }
        }
    };
} // namespace techies::modules
