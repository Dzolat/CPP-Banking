#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../classes/customer.hpp"

namespace Config
{
    namespace Accounts
    {
        const std::vector<::Customer> Read()
        {
            std::ifstream file("accounts.txt");
            std::vector<::Customer> customer_vector{};
            if (!file)
            {
                return std::vector<::Customer> {};
            }

            std::string currentLine;

            while (std::getline(file, currentLine))
            {
                std::string first_name{currentLine};

                if (!std::getline(file, currentLine))
                    return std::vector<::Customer> {};

                std::string last_name{currentLine};

                if (!std::getline(file, currentLine))
                    return std::vector<::Customer> {};


                double balance{std::stod(currentLine)};

                customer_vector.push_back(Customer { first_name, last_name, balance } );
            }

            return customer_vector;
        }

        bool Write(const std::vector<::Customer>& customer_vector)
        {
            std::ofstream file ("accounts.txt");

            if (!file)
            {
                return false;
            }

            for (int i = 0, v_size = static_cast<int>(customer_vector.size()); i < v_size; i++)
            {
                file << customer_vector[i].get_first_name() << '\n';
                file << customer_vector[i].get_last_name() << '\n';
                file << customer_vector[i].get_balance() << '\n';
            }
            return true;
        }
    }

    struct File
    {
        bool connected;
        std::string name;
        int age;
    };

    Config::File Read()
    {
        std::ifstream file{"config.txt"};
        Config::File config_file;

        if (!file)
        {
            config_file.connected = false;
            return config_file;
        }

        config_file.connected = true;
        std::string currentLine{};

        std::getline(file, currentLine);
        config_file.name = currentLine;

        std::getline(file, currentLine);
        config_file.age = std::stoi(currentLine);

        return config_file;
    }

    bool Write(const Config::File& config_file)
    {
        std::ofstream file{"config.txt"};

        if (!file)
        {
            return false;
        }

        file << config_file.name << '\n';
        file << config_file.age << '\n';
        return true;
    }
}