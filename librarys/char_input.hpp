#pragma once

#include <iostream>
#include <string>
#include <map>

#include "input.hpp"
#include "system.hpp"

namespace Character
{
    char Get(const std::map<char, std::string> valid_actions, std::string input_data = "Please enter your action: ")
    {
        while (true)
        {
            System::ClearCmd();
            for (auto action : valid_actions)
            {
                std::cout << "[" << action.first << "]\t" << action.second << "\n";
            }

            char choice = get_input<char>(input_data);

            if (valid_actions.contains(choice))
                return choice;
        }
    }
}
