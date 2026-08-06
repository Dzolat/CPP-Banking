#include <iostream>
#include <vector>
#include <map>

#include "../librarys/key_input.hpp"
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
            for (int i = top; i < top + Constants::MAX_VISIBLE_ACCOUNTS && i < static_cast<int>(accounts_vector.size()); i++)
            {
                if (i == selected)
                {
                    System::Color::BLUE();
                    std::cout << accounts_vector[i].get_name() << " (" << accounts_vector[i].get_balance() << "$)" << " <\n";
                    System::Color::RESET();
                }
                else
                {
                    std::cout << accounts_vector[i].get_name() << " (" << accounts_vector[i].get_balance() << "$)" << " <\n";
                }
            }
            std::cout << "\n[↑] choose account up\n"
                      << "[↓] choose account down\n"
                      << "[Enter] select\n"
                      << "[Esc] cancel\n";

            switch (Input::getkey())
            {
            case Input::Key::Enter:
                return selected;
                break;
            case Input::Key::Escape:
                return -1;
                break;
            case Input::Key::Up:
                if (selected > 0)
                    selected--;

                if (selected < top)
                    top--;
                break;
            case Input::Key::Down:
                if (selected < static_cast<int>(accounts_vector.size()) - 1)
                    selected++;

                if (selected >= top + Constants::MAX_VISIBLE_ACCOUNTS)
                    top++;
                break;
            default:
                break;
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

        std::cout << "Successfully added customer " << first_name << " " << last_name << " to the database\n";
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }

    void Remove()
    {
        int index = Choose();

        if (index == -1)
            return;

        accounts_vector.erase(accounts_vector.begin() + index);

        std::cout << "Successfully removed account.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }

    void Modify()
    {
        int index = Choose();

        if (index == -1)
            return;

        char current_action {};
        const std::map<char, bool> validActions { {'n', true}, {'b', true}, {'e', true}};
        while (true)
        {
                System::ClearCmd();
                std::cout << "[n]\tName\n"
                << "[b]\tBalance\n"
                << "[e]\tExit\n";
                char action{get_input<char>("Please enter your action: ")};

            if (validActions.contains(action))
            {
                current_action = action;
                break;
            }    
        }

        if (current_action == 'n')
        {
            accounts_vector[index].set_first_name( get_input<std::string>("Please enter the first name: "));
            accounts_vector[index].set_last_name( get_input<std::string>("Please enter the last name: "));
        }

        if (current_action == 'b')
        {
            accounts_vector[index].set_balance( get_input<int>("Please enter the new balance: "));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds{1000});
    }
}