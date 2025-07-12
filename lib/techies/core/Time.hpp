#pragma once
#include "HAL.hpp"

namespace techies::core
{
    
    typedef HAL_Time_Type time_t;

    enum class Time : time_t
    {
        MS = 1,
        S = 1000 * MS,
        MIN = 60 * S,
        H = 60 * MIN,
        DAY = 24 * H
    };

    inline time_t GetTime()
    {
        return HAL_Time;
    };

    // Delta time for this exact cycle
    extern time_t CycleDelta;

} // namespace techies::core
