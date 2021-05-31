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
    int white = 0, black = 0, n = 0, FirstCheck = 0, SecondCheck = 0, ThirdCheck = 0; // Счетчики для проверки ничьи
    do
    {
        manager.MakeMove(white, black, n, FirstCheck, SecondCheck, ThirdCheck);
    } while (!manager.IsGameFinished());
    _getch();
    return 0;
}