#include "core/Config.hpp"
#include "IO.hpp"

namespace techies::core
{
    struct State
    {
        bool QX[HAL_QX_COUNT];
        inline bool IX(const size_t &i) const
        {
            return IO::IX[i];
        };

        // static void Cycle(const State* Old, State* New);
    };
} // namespace techies::core
