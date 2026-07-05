#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

namespace Config
{
    struct File
    {
        bool connected;
        std::string name;
        int age;
    };

    Config::File Read()
    {
        std::ifstream file{"config.txt"};
        Config::File cf;

        if (!file)
        {
            cf.connected = false;
            return cf;
        }

        cf.connected = true;
        std::string currentLine{};

        std::getline(file, currentLine);
        cf.name = currentLine;

        std::getline(file, currentLine);
        cf.age = std::stoi(currentLine);

        return cf;
    }

    bool Write(Config::File cf)
    {
        std::ofstream file{"config.txt"};

        if (!file)
        {
            return false;
        }

        file << cf.name << '\n';
        file << cf.age << '\n';
        return true;
    }
}