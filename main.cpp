#include <iostream>
#include <fstream>
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

int main()
{
    Startup();
}