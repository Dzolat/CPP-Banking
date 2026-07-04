#include <iostream>
#include <fstream>
#include <map>
#include <Windows.h>
#include "classes/customer.hpp"
#include "functions/input.hpp"
#include "functions/random.hpp"
#include "functions/config.hpp"

void Startup()
{
    if (Config::Read().connected == false)
    {
        ConfigFile cf;
        cf.name = get_input<std::string>("Welcome, please enter your full name: ");
        cf.age = get_input<int>("Now, enter your age: ");
        system("cls");
        Config::Write(cf);
    }

    ConfigFile cf{Config::Read()};
    std::cout << "Welcome, " << cf.name << "\n";
}

namespace Action
{
    char Choose();
    void Act(const char action, ConfigFile cf);
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

        void Act(const char action, ConfigFile cf)
        {
            switch (action)
            {
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

    void Act(const char action, ConfigFile cf)
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

int main()
{
    Startup();
    ConfigFile cf{Config::Read()};
    Sleep(1000);
    Action::Act(Action::Choose(), cf);
}