#include "EDGE.hpp"

namespace techies::modules
{

    void POSEDGE::Cycle(const POSEDGE* Old, POSEDGE* New, bool IN)
    {
        New->memory = IN;

        New->Q = IN &&
            Old->memory != New->memory;
    }

    void POSEDGE::Reset(POSEDGE* New)
    {
        New->memory = 0;
        New->Q = 0;
    }

    void NEGEDGE::Cycle(const NEGEDGE* Old, NEGEDGE* New, bool IN)
    {
        New->memory = IN;

        New->Q = !IN &&
            Old->memory != New->memory;
    }


    void NEGEDGE::Reset(NEGEDGE* New)
    {
        New->memory = 1;
        New->Q = 0;
    }

} // namespace techies::modules
