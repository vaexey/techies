#include "core/Config.hpp"

namespace techies::modules
{
    
    struct STRCMP
    {
        bool Q;

        static void Cycle(
            const STRCMP* Old,
            STRCMP* New,
            const char* STR1,
            const char* STR2,
            const bool IN
        );

        static void Reset(STRCMP* New);
    };

} // namespace techies::modules
