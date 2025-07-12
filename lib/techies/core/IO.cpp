#include "IO.hpp"

namespace techies::core
{
    namespace IO
    {
        bool Raw_IX[HAL_IX_COUNT] = { 0 };
        const bool* IX = Raw_IX;

        void Init()
        {
            for(size_t i = 0; i < HAL_IX_COUNT; i++)
                HAL_IX_INIT(i);
            for(size_t i = 0; i < HAL_QX_COUNT; i++)
                HAL_QX_INIT(i);
        }

        void ReadInputs()
        {
            for(size_t i = 0; i < HAL_IX_COUNT; i++)
                Raw_IX[i] = HAL_IX_READ(i);
        }

        void WriteOutputs(const bool* QX)
        {
            for(size_t i = 0; i < HAL_QX_COUNT; i++)
                HAL_QX_WRITE(i, QX[i]);
        }
        
    } // namespace IO
} // namespace techies::core
