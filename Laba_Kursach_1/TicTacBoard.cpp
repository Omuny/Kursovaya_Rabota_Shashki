#include "pch.h"
#include "TicTacBoard.h"

TicTacBoard::TicTacBoard(unsigned int size)
{
	this->boardsize = size;
	cells = new CellType * [size];
	for (unsigned int i = 0; i < size; i++)
		cells[i] = new CellType[size];
	for (unsigned int i = 0; i < size; i++)
		for (unsigned int j = 0; j < size; j++)
			cells[i][j] = CellType_Empty;
}

TicTacBoard::~TicTacBoard()
{
	for (unsigned int i = 0; i < boardsize; i++)
		delete[]cells[i];
	delete[]cells;
}

void TicTacBoard::Show()
{
	cout << "     ";
	cout << "a b c d e f g h\t\W - Белая шашка, B - черная. V - Белая дамка, P - черная.";
	cout << endl;
	cout << endl;

	for (unsigned int i = 0; i < boardsize; i++)
	{
		cout << 8-i << "    ";
		for (unsigned int j = 0; j < boardsize; j++)
		{
			switch (cells[i][j])
			{
			case CellType_White:
				cout << "W"; // Белая шашка
				break;
			case CellType_Black:
				cout << "B"; // Черная шашка
				break;
			case CellType_White_King:
				cout << "V"; // Белая дамка
				break;
			case CellType_Black_King:
				cout << "P"; // Черная дамка
				break;
			case CellType_Empty:
				if (((i % 2 ==0) && (j % 2 == 0)) || ((i % 2 != 0) && (j % 2 != 0)))
					cout << "-"; // Пустая черная клетка
				else
					cout << " "; // Пустая белая клетка
				break;
			}
			cout << "|";
		}
		cout << endl;
	}
}

void TicTacBoard::SetCell(unsigned int xpos, unsigned int ypos, CellType ct)
{
	cells[ypos][xpos] = ct;
}
