#pragma once

#include <string>
#include <utility>

#include "../functions/random.hpp"

    class Customer
{
private:
    std::string id{Random::MaybeGUID()};
    std::string first_name;
    std::string last_name;
    double balance;

public:
    Customer(std::string fn, std::string ln, double bal)
        : first_name{std::move(fn)},
          last_name{std::move(ln)},
          balance{bal}
    {
    }

    const std::string &get_id() const
    {
        return id;
    }

    const std::string &get_first_name() const
    {
        return first_name;
    }

    void set_first_name(std::string new_first_name)
    {
        first_name = std::move(new_first_name);
    }

    const std::string &get_last_name() const
    {
        return last_name;
    }

    void set_last_name(std::string new_last_name)
    {
        last_name = std::move(new_last_name);
    }

    std::string get_name() const
    {
        return first_name + " " + last_name;
    }

    double get_balance() const
    {
        return balance;
    }

    void set_balance(double new_balance)
    {
        balance = new_balance;
    }
};