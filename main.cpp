#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <thread>

#include "classes/customer.hpp"
#include "librarys/input.hpp"
#include "librarys/system.hpp"
#include "librarys/char_input.hpp"
#include "functions/config.hpp"
#include "functions/actions.hpp"
#include "functions/accounts.hpp"

void Startup()
{
    if (Config::Read().connected == false)
    {
        Config::File config_file;
        config_file.name = get_input<std::string>("Welcome, please enter your full name: ");
        config_file.age = get_input<int>("Now, enter your age: ");
        System::ClearCmd();
        Config::Write(config_file);
    }

    Config::File config_file{Config::Read()};
    std::cout << "Welcome, " << config_file.name << "\n";
}

int main()
{
    Startup();

    Config::File config_file{Config::Read()};
    Accounts::accounts_vector = Config::Accounts::Read();

    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    while (!Action::Act(Character::Get(std::map<char, std::string> { {'c', "Customer"}, {'t', "Transfer"}, {'e', "Exit"} }), config_file))
    {
        Config::Accounts::Write(Accounts::accounts_vector);
    }
}