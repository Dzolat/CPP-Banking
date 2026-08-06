#pragma once

#include "config.hpp"
#include "accounts.hpp"
#include "transfers.hpp"
#include "../librarys/input.hpp"
#include <map>


namespace Action
{
    bool Act(const char action, Config::File config_file)
    {
        switch (action)
        {
        case 'c':
            ::Accounts::Act();
            break;
        case 't':
            ::Transfers::Act();
            break;
        case 'e':
            std::cout << "Goodbye, " << config_file.name << "\n";
            return 1;
        default:
            break;
        }

        return 0;
    }

}