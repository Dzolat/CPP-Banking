#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <thread>
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
    Accounts::accounts_vector = Config::Accounts::Read();
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    while (true)
    {
        Action::Act(Action::Choose(), cf);
        Config::Accounts::Write(Accounts::accounts_vector);    
    }
}