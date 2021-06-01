#pragma once
#include"TicTacBoard.h"
#include"pch.h"
class TicTacPlayer
{
protected:
	TicTacBoard* board;
	CellType cellType;
	string name;
	bool EatOpp = false;
public:
	TicTacPlayer();
	virtual ~TicTacPlayer();
	void SetupPlayer(string name, CellType cellType);
	void SetBoard(TicTacBoard* board);
	virtual int MakeMove() = 0;
	string GetName();
};

