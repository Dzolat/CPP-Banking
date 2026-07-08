#pragma once
#include <Windows.h>

namespace System
{
    namespace Color
    {
        void BLUE()
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        }

        void RESET()
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    }

    void ClearCmd()
    {
        system("cls");
    }
}