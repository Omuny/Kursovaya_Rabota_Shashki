// Laba_Kursach.cpp

#include "pch.h"
#include "TicTacManager.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    TicTacManager manager;
    if (!manager.Init())
    {
        cout << "Неверным данные, выходим...";
        _getch();
        return 0;
    }
    while (!manager.IsGameFinished())
    {
        manager.MakeMove();
    }
    _getch();
    return 0;
}