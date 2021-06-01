#pragma once
#include "TicTacBoard.h"
#include "TicTacPlayer.h"

class TicTacHumanPlayer : public TicTacPlayer
{
public:
	TicTacHumanPlayer();
	virtual ~TicTacHumanPlayer();
	virtual int MakeMove();
};


