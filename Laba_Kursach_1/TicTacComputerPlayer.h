#pragma once
#include "pch.h"
#include "TicTacPlayer.h"
#include "TicTacBoardMonteCarloEvaluator.h"
class TicTacComputerPlayer :
    public TicTacPlayer
{
public:
	TicTacComputerPlayer();
	virtual ~TicTacComputerPlayer();
	virtual int MakeMove();
};

