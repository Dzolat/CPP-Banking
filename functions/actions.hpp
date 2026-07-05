#pragma once
#include "config.hpp"
#include "input.hpp"
#include "accounts.hpp"
#include <map>

namespace Action
{
    char Choose();
    void Act(const char action, Config::File cf);
    namespace Customer
    {
        char Choose()
        {
            std::map<char, bool> validActions{{'a', true}, {'r', true}, {'m', true}, {'e', true}};

            while (true)
            {
                system("cls");
                std::cout << "[a]\tAdd\n"
                << "[r]\tRemove\n"
                << "[m]\tModify\n"
                << "[e]\tExit\n";
                char action{get_input<char>("Please enter your action:")};

                if (validActions.contains(action))
                    return action;
               
            }
        }

        void Act(const char action, Config::File cf)
        {
            switch (action)
            {
            case 'a':
                
                break;
            case 'e':
                Action::Act(Action::Choose(), cf);
                break;
            default:
                break;
            }
        }
    }

    char Choose()
    {
        std::map<char, bool> validActions{{'c', true}, {'e', true}};
        while (true)
        {
            system("cls");
            std::cout << "[c]\tCustomers\n"
            << "[e]\tExit\n";
            char action{get_input<char>("Please enter your action:")};

            if (validActions.contains(action))
                return action;
            
        }
    }

    void Act(const char action, Config::File cf)
    {
        switch (action)
        {
        case 'c':
            Action::Customer::Act(Action::Customer::Choose(), cf);
            break;
        case 'e':
            std::cout << "Goodbye, " << cf.name << "\n";
            abort();
            break;
        default:
            break;
        }
    }

}