#include <vector>
#include "../classes/customer.hpp"
#include "input.hpp"

namespace Accounts {
    inline static std::vector<::Customer> accounts_vector {};

    void Add()
    {
        const std::string first_name{ get_input<std::string>("What's the customer's first name: ") };
        const std::string last_name{ get_input<std::string>("What's the customer's first name: ") };
        const int balance{ get_input<int>("What's the customer's starting balance: ") };

        accounts_vector.push_back( Customer(first_name, last_name, balance) );

        std::cout << "Sucesfully added customer " << first_name << " " << last_name << " to the database\n";
    }

    void Add(Customer account)
    {
        accounts_vector.push_back(account);
    }

    void Remove(Customer account)
    {
        for (int i = 0; i < accounts_vector.size(); i++)
        {
            if (accounts_vector[i].getId() == account.getId())
                accounts_vector.erase(accounts_vector.begin() + i);
        }
    }
}