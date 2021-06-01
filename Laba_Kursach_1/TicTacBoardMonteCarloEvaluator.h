#pragma once
#include "pch.h"
#include "TicTacBoard.h"
#include "TicTacRandomPlayer.h"

class TicTacBoardMonteCarloEvaluator
{
private:
	TicTacBoard* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	int white = 0, black = 0, n = 0, FirstCheck = 0, SecondCheck = 0, ThirdCheck = 0; // —четчики дл€ проверки ничьи
	unsigned int xpos, ypos;
	CellType startCellType;
public:
	TicTacBoardMonteCarloEvaluator(TicTacBoard* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos);
	~TicTacBoardMonteCarloEvaluator();
	void EvaluateBoard();
	void Evaluate();
};