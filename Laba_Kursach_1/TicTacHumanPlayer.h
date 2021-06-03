#pragma once
#include "TicTacBoard.h"
#include "TicTacPlayer.h"

class TicTacHumanPlayer : public TicTacPlayer
{
public:
	int col1 = 10, row1 = 10, col2 = 10, row2 = 10;
	TicTacHumanPlayer();
	virtual ~TicTacHumanPlayer();
	virtual void SetHumanColsRows(bool& closed);
	virtual int MakeMove();
};


