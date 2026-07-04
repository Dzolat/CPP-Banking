#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct ConfigFile
{
    bool connected;
    std::string name;
    int age;
};

namespace Config
{
    ConfigFile Read()
    {
        std::ifstream file{"config.txt"};
        ConfigFile cf;

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

    bool Write(ConfigFile cf)
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