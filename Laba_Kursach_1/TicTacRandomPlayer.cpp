#include "TicTacRandomPlayer.h"
#include "pch.h"

TicTacRandomPlayer::TicTacRandomPlayer()
{
}

TicTacRandomPlayer::~TicTacRandomPlayer()
{
}

int TicTacRandomPlayer::MakeMove()
{
	int row1, col1, row2, col2;
Tuda: // <-----
	row1 = (int)(rand() % 8);
	col1 = (int)(rand() % 8);
	row2 = (int)(rand() % 8);
	col2 = (int)(rand() % 8);

	if (((col2 % 2 == 0) && (row2 % 2 == 0)) || ((col2 % 2 != 0) && (row2 % 2 != 0))) // если ходим на белую клетку
		goto Tuda; // ---->
	if (((col1 % 2 == 0) && (row1 % 2 == 0)) || ((col1 % 2 != 0) && (row1 % 2 != 0))) // ходим белым болем то же рандомим
		goto Tuda; // ---->
	if ((col1 == col2) && (row1 == row2)) // ходим на туже клетку - рандомим
		goto Tuda; // ---->

	if (this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp)) // проверка на возможность хода
	{
		this->board->CellMove(row1, col1, row2, col2, EatOpp); // сам ход
		if (EatOpp == true)
		{
			this->board->Revers(row1, col1, row2, col2, EatOpp); // сам ход
			this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp); // дополнительна€ проверка на возможность съесть еще одну шашку
		}

		if (EatOpp == false)
			return 1; // ’од сделан
		if (EatOpp == true)
			return 2; // ≈сть возможность съесть еще
	}
	return 0; // Ќе допустимый ход
}
