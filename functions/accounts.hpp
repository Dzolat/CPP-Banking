#include <iostream>
#include <vector>
#include <conio.h>
#include "../classes/customer.hpp"
#include "system.hpp"
#include "input.hpp"

namespace Constants
{
    constexpr int MAX_VISIBLE_ACCOUNTS = 5;
}
namespace Accounts
{
    inline static std::vector<::Customer> accounts_vector{};

    int Choose()
    {

        if (accounts_vector.empty())
            return -1;

        int selected = 0;
        int top = 0;

        while (true)
        {
            System::ClearCmd();
            for (int i = top; i < top + Constants::MAX_VISIBLE_ACCOUNTS && i < accounts_vector.size(); i++)
            {
                if (i == selected)
                {
                    System::Color::BLUE();
                    std::cout << accounts_vector[i].get_name() << " <\n";
                    System::Color::RESET();
                }
                else
                {
                    std::cout << accounts_vector[i].get_name() << "\n";
                }
            }
            std::cout << "\n[↑] choose account up\n"
                      << "[↓] choose account down\n"
                      << "[Enter] select\n"
                      << "[Esc] cancel\n";
            
            int key = _getch();

            if (key == 13)
                return selected;
            else if (key == 27)
                return -1;
            else if (key == 224)
            {
                key = _getch();

                if (key == 72)
                {
                    if (selected > 0)
                        selected--;

                    if (selected < top)
                        top--;
                }
                else if (key == 80)
                {
                    if (selected < accounts_vector.size() - 1)
                        selected++;

                    if (selected >= top + Constants::MAX_VISIBLE_ACCOUNTS)
                        top++;
                }
            }
        }
    }

    void Add()
    {
        System::ClearCmd();
        const std::string first_name{get_input<std::string>("What's the customer's first name: ")};
        System::ClearCmd();
        const std::string last_name{get_input<std::string>("What's the customer's last name: ")};
        System::ClearCmd();
        const int balance{get_input<int>("What's the customer's starting balance: ")};
        System::ClearCmd();

        accounts_vector.push_back(Customer(first_name, last_name, balance));

        std::cout << "Sucesfully added customer " << first_name << " " << last_name << " to the database\n";
        Sleep(1000);
    }

    void Remove()
    {
        int index = Choose();

        if (index == -1)
            return;
        
        accounts_vector.erase(accounts_vector.begin() + index);

        std::cout << "Successfully removed account.\n";
        Sleep(1000);
    }
}