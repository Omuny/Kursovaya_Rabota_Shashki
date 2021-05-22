// Laba_Kursach_1.cpp

#include "pch.h"
#include "TicTacBoard.h"

int main()
{
    setlocale(LC_ALL, "RUS");
    TicTacBoard* board;
    board = new TicTacBoard(8);
    board->SetCell();
    board->Show();
    _getch();
    delete board;
    return 0;
}