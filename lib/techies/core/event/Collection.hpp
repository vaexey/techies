#include "core/Config.hpp"
#include "components/Log.hpp"
#define TAG "EventCollection"

namespace techies::core::event
{
    template<size_t max_connections>
    class Collection
    {
    private:
        void (*connections[max_connections])();
        size_t size = 0;

    public:
        bool Connect(void (*callback)())
        {
            if(size >= max_connections)
            {
                L->Crit(TAG, "Ran out of free connection slots for " + String((unsigned long)callback));

                return false;
            }
            
            connections[size] = callback;
            size++;

            return true;
        }

        void Dispatch()
        {
            for(size_t i = 0; i < size; i++)
                connections[i]();
        }
    };

} // namespace techies::core::event

#undef TAG