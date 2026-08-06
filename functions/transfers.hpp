#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <thread>

#include "accounts.hpp"

namespace Transfers
{
    inline static std::vector<::Customer> accounts_vector{};

    void Act();
    void Create();

    void Act()
    {
        const char action = Character::Get(std::map<char, std::string>{{'c', "Create"}, {'e', "Exit"}});
        switch (action)
        {
        case 'c':
            Transfers::Create();
            break;
        default:
            break;
        }
    }

    void Create()
    {
        std::cout << "Firstly, choose the sender." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});

        const int account_from{Accounts::Get()};

        if (account_from == -1)
            return;

        System::ClearCmd();

        std::cout << "Next, choose the receiver." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});

        const int account_to{Accounts::Get()};

        if (account_to == -1)
            return;

        System::ClearCmd();

        if (account_from == account_to)
        {
            std::cout << "You can't choose the same account!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds{1000});
            return;
        }

        const int amount{
            get_input<int>("Lastly, what should be the amount: ")};

        Customer &sender = Accounts::accounts_vector[account_from];
        Customer &receiver = Accounts::accounts_vector[account_to];

        if (amount <= 0)
        {
            std::cout << "The amount must be greater than zero!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds{1000});
            return;
        }

        if (sender.get_balance() < amount)
        {
            std::cout << "The sender doesn't have enough!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds{1000});
            return;
        }

        sender.set_balance(sender.get_balance() - amount);
        receiver.set_balance(receiver.get_balance() + amount);

        std::cout << "Transfer completed!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
}