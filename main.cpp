#include <iostream>
#include <fstream>
#include <map>
#include <Windows.h>
#include "classes/customer.hpp"
#include "functions/input.hpp"
#include "functions/random.hpp"
#include "functions/config.hpp"

std::map<char, bool> validActions{{'c', true}, {'e', true}};

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
    char Choose()
    {
        std::cout << "[c]\tCustomers\n";
        std::cout << "[e]\tExit\n";
        while (true)
        {
            char action{get_input<char>("Please enter your action:")};

            if (validActions.contains(action))
                return action;
        }
    }

    void Act(const char action)
    {
        switch (action)
        {
        case 'c':
            /* code */
            break;
        case 'e':
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

    Action::Act(Action::Choose());
}