#pragma once
#include <string>
class Customer {
    private:
        std::string id;
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
};