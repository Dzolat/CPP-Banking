#pragma once
#include <random>
#include <chrono>

namespace Random {
    std::mt19937 generator()
    {
        static std::random_device rd{};
        // Create a sequence with the time + 7 random device calls
        std::seed_seq ss { static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

        return std::mt19937 { ss };
    }
    
    inline std::mt19937 mt { generator() };

    inline int Number(int min, int max)
    {
        return std::uniform_int_distribution{ min, max }(mt);
    }
}