// Laba_Kursach_1.cpp

#include "pch.h"
#include "TicTacBoard.h"

int main()
{
    setlocale(LC_ALL, "RUS");
    TicTacBoard* board;
    board = new TicTacBoard(8);
    board->SetCell(1, 0, CellType_Black);
    board->SetCell(3, 0, CellType_Black);
    board->SetCell(5, 0, CellType_Black_King);
    board->SetCell(7, 0, CellType_Black);
    board->SetCell(0, 7, CellType_White);
    board->SetCell(2, 7, CellType_White);
    board->SetCell(4, 7, CellType_White_King);
    board->SetCell(6, 7, CellType_White);
    board->Show();
    _getch();
    delete board;
}