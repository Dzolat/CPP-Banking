#include <vector>
#include "../classes/customer.hpp"

namespace Accounts {
    inline static std::vector<Customer> accounts_vector {};

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

    void View(Customer acc)
}