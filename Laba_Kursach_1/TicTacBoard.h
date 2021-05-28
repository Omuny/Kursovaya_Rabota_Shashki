#pragma once
#include "CellType.h"

class TicTacBoard
{
private:
	int boardsize;
	CellType** cells;
	bool CheckHod = false;
public:
	TicTacBoard(unsigned int boardsize);
	virtual ~TicTacBoard();
	void Show();
	void SetCell();
	bool CkeckLegal(unsigned int ypos1, unsigned int xpos1, unsigned int xpos2, unsigned int ypos2, CellType Type, bool& EatOpp);
	void CellMove(unsigned int& xpos1, unsigned int& ypos1, unsigned int& xpos2, unsigned int& ypos2, bool& EatOpp);
};

