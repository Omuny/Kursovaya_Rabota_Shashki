#pragma once
#include "TicTacBoard.h"
#include "TicTacPlayer.h"
class TicTacComputerPlayer :
    public TicTacPlayer
{
public:
	TicTacComputerPlayer();
	virtual ~TicTacComputerPlayer();
	virtual int MakeMove();
};

