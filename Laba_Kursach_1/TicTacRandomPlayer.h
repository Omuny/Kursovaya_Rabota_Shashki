#pragma once
#include "pch.h"
#include "TicTacPlayer.h"

class TicTacRandomPlayer :
    public TicTacPlayer
{
public:
    TicTacRandomPlayer();
    virtual ~TicTacRandomPlayer();
    virtual int MakeMove();
};

