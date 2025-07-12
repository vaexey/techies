#include "core/Time.hpp"

namespace techies::modules
{
    struct TON
    {
        techies::core::time_t ET;
        bool Q;

        void Cycle(
            const TON* Old,
            TON* New,
            bool IN,
            techies::core::time_t PT
        );
    };

    struct TOF
    {
        techies::core::time_t ET;
        bool Q;

        void Cycle(
            const TOF* Old,
            TOF* New,
            bool IN,
            techies::core::time_t PT
        );
    };
} // namespace techies::modules
