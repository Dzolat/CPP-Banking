#pragma once
#include <string>
#include "../functions/random.hpp"
class Customer {
    private:
        std::string id = Random::MaybeGUID();
        std::string first_name;
        std::string last_name;
        double balance;
    public:
        Customer(std::string fn, std::string ln, double bal)
        {
            first_name = fn;
            last_name = ln;
            balance = bal;
        }
        const std::string getId()
        {
            return id;
        }
};