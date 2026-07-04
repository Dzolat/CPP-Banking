#pragma once
#include <limits>
#include <string>

template <typename T>
T get_input(std::string output)
{
    using std::cin;
    using std::cout;
    while (true)
    {
        std::cout << output;

        std::string line{};
        std::getline(std::cin, line);

        if constexpr (std::is_same_v<T, std::string>)
            return line;
        else
        {
            std::istringstream stream{line};
            T input{};

            if (stream >> input)
                return input;
        }
    }
}