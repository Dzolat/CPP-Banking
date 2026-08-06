#pragma once

#include <iostream>

namespace System
{
    namespace Color
    {
        inline void BLUE()
        {
            std::cout << "\033[94m";
        }

        inline void RESET()
        {
            std::cout << "\033[0m";
        }
    }

    inline void ClearCmd()
    {
        std::cout   << "\033[2H"
                    << "\033[2J"
                    << "\033[3J"
                    << std::flush;
    }
}