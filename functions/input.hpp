#pragma once
#include <limits>

// Usage
// 
template <typename T>
T get_input()
{
    using std::cin;
    while (true)
    {
        T input;
        cin >> input;
        
        bool failed = cin.fail();
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (failed)
            continue;
        return input;
    }
}