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
	int xpos1, ypos1, xpos2, ypos2;
	bool EatOpp;
	CellType startCellType;
public:
	TicTacBoardMonteCarloEvaluator(TicTacBoard* board, int numIterations, CellType startCellType, int xpos1, int ypos1, int xpos2, int ypos2, bool EatOpp);
	~TicTacBoardMonteCarloEvaluator();
	void EvaluateBoard();
	void Evaluate();
	int GetVictories() { return numVictories; }
	int GetLosses() { return numLosses; }
	int GetDraws() { return numDraws; }
	int GetXPos1() { return xpos1; }
	int GetYPos1() { return ypos1; }
	int GetXPos2() { return xpos2; }
	int GetYPos2() { return ypos2; }
	int GetEatOpp() { return EatOpp; }
};