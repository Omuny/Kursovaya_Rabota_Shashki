#pragma once
#include "CellType.h"

class TicTacBoard
{
private:
	unsigned int boardsize;
	CellType** cells;
public:
	TicTacBoard(unsigned int boardsize);
	virtual ~TicTacBoard();
	void Show();
	void SetCell();
	bool CkeckLegal(unsigned int xpos1, unsigned int ypos1, unsigned int xpos2, unsigned int ypos2);
};

