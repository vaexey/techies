#include "HAL.hpp"

namespace techies::core
{
    namespace IO
    {
        extern bool Raw_IX[HAL_IX_COUNT];
        extern const bool* IX;

        void Init();

        void ReadInputs();
        void WriteOutputs(const bool* QX);
        
    } // namespace IO
} // namespace techies::core
