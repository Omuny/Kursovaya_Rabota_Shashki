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
	
	row1 = (int)(rand() % 8);
	col1 = (int)(rand() % 8);
	row2 = (int)(rand() % 8);
	col2 = (int)(rand() % 8);

	if (this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp)) // проверка на возможность хода
	{
		this->board->CellMove(row1, col1, row2, col2, EatOpp); // сам ход
		if (EatOpp == true)
			this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp); // дополнительная проверка на возможность съесть еще одну шашку

		if (EatOpp == false)
			return 1;
		if (EatOpp == true)
			return 2;
	}
	return 0;
}
