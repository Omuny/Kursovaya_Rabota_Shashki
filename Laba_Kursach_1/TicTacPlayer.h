#pragma once
#include"TicTacBoard.h"

class TicTacPlayer
{
private:
	TicTacBoard* board;
	CellType cellType;
	string name;
	bool EatOpp = false;
public:
	TicTacPlayer();
	virtual ~TicTacPlayer();
	void SetupPlayer(string name, CellType cellType);
	void SetBoard(TicTacBoard* board);
	int MakeMove();
	string GetName();
};


