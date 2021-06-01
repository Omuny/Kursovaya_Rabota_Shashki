#include "TicTacBoardMonteCarloEvaluator.h"
#include "pch.h"

TicTacBoardMonteCarloEvaluator::TicTacBoardMonteCarloEvaluator(TicTacBoard* board, int numIterations, CellType startCellType, int xpos1, int ypos1, int xpos2, int ypos2, bool EatOpp)
{
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numVictories = 0;
	this->numLosses = 0;
	this->xpos1 = xpos1;
	this->ypos1 = ypos1;
	this->xpos2 = xpos2;
	this->ypos2 = ypos2;
	this->EatOpp = EatOpp;
	this->startCellType = startCellType;
}

TicTacBoardMonteCarloEvaluator::~TicTacBoardMonteCarloEvaluator()
{
}

void TicTacBoardMonteCarloEvaluator::EvaluateBoard()
{
	TicTacBoard* b = new TicTacBoard(this->board);
	TicTacRandomPlayer* player1 = new TicTacRandomPlayer();
	TicTacRandomPlayer* player2 = new TicTacRandomPlayer();
	TicTacRandomPlayer* currentPlayer;
	bool bGameFinished = false;

	player1->SetupPlayer("RandomWhite", CellType_White);
	player2->SetupPlayer("RandomBlack", CellType_Black);
	player1->SetBoard(b);
	player2->SetBoard(b);
	currentPlayer = (this->startCellType == CellType_White) ? player1 : player2;

	//Checking already end condition!
	if (b->CheckEndCondition(white, black, n, FirstCheck, SecondCheck, ThirdCheck))
	{
		if (b->IsVictory())
			if (currentPlayer == player1)
				numLosses++;
			else
				numVictories++;
		else
			numDraws++;
		bGameFinished = true;
		return;
	}

	while (!bGameFinished)
	{
		while (currentPlayer->MakeMove() != 1);

		if (b->CheckEndCondition(white, black, n, FirstCheck, SecondCheck, ThirdCheck))
		{
			if (b->IsVictory())
				if (currentPlayer == player1)
					numVictories++;
				else
					numLosses++;
			else
				numDraws++;
			bGameFinished = true;
		}
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
}

void TicTacBoardMonteCarloEvaluator::Evaluate()
{
	for (int i = 0; i < numGames; i++)
	{
		// После каждой игры обнуляем счетчики
		white = 0; 
		black = 0; 
		n = 0; 
		FirstCheck = 0; 
		SecondCheck = 0; 
		ThirdCheck = 0;
		EvaluateBoard();
	}
	white = 0; 
	black = 0; 
	n = 0; 
	FirstCheck = 0; 
	SecondCheck = 0; 
	ThirdCheck = 0;
}
