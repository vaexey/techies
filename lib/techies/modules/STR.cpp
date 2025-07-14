#include "STR.hpp"

namespace techies::modules
{
    
    void STRCMP::Cycle(
        const STRCMP* Old,
        STRCMP* New,
        const char* STR1,
        const char* STR2,
        const bool IN
    ) {
        if(IN)
            New->Q = !strcmp(STR1, STR2);
        else
            New->Q = false;
    }

    void STRCMP::Reset(STRCMP* New)
    {
        New->Q = false;
    }

} // namespace techies::modules
