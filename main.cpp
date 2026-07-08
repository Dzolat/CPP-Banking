#include <iostream>
#include <fstream>
#include <map>
#include <Windows.h>
#include "classes/customer.hpp"
#include "functions/input.hpp"
#include "functions/random.hpp"
#include "functions/config.hpp"
#include "functions/actions.hpp"
#include "functions/system.hpp"

void Startup()
{
    if (Config::Read().connected == false)
    {
        Config::File cf;
        cf.name = get_input<std::string>("Welcome, please enter your full name: ");
        cf.age = get_input<int>("Now, enter your age: ");
        System::ClearCmd();
        Config::Write(cf);
    }

    Config::File cf{Config::Read()};
    std::cout << "Welcome, " << cf.name << "\n";
}

int main()
{
    Startup();
    Config::File cf{Config::Read()};
    
    Sleep(1000);
    while (true)
        Action::Act(Action::Choose(), cf);
}