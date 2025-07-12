#include "Collection.hpp"

namespace techies::core::event
{
    class Manager
    {
    public:
        static Collection<10> BeforeCycle;
        static Collection<10> AfterCycle;
    };
} // namespace techies::core::event
