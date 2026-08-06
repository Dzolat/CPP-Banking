#pragma once

#include <string>
#include <string_view>

#include "../librarys/random.hpp"

class Customer
{
private:
    std::string m_id{ Random::MaybeGUID() };
    std::string m_first_name;
    std::string m_last_name;
    double m_balance;
public:
    Customer(const std::string_view first_name, const std::string_view last_name, const double& balance)
        : m_first_name { first_name },
          m_last_name { last_name },
          m_balance { balance }
    {
    }

    const std::string& get_id() const
    {
        return m_id;
    }

    const std::string& get_first_name() const
    {
        return m_first_name;
    }

    void set_first_name(const std::string& first_name)
    {
        m_first_name = first_name;
    }

    const std::string& get_last_name() const
    {
        return m_last_name;
    }

    void set_last_name(const std::string_view last_name)
    {
        m_last_name = last_name;
    }

    std::string get_name() const
    {
        return m_first_name + " " + m_last_name;
    }

    double get_balance() const
    {
        return m_balance;
    }

    void set_balance(const double& balance)
    {
        m_balance = balance;
    }
};