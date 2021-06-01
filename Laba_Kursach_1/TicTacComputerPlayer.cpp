#include "pch.h"
#include "TicTacComputerPlayer.h"

TicTacComputerPlayer::TicTacComputerPlayer()
{
}

TicTacComputerPlayer::~TicTacComputerPlayer()
{
}

int TicTacComputerPlayer::MakeMove()
{
	vector <TicTacBoardMonteCarloEvaluator*> evaluators;
	for (int xpos1 = 0; xpos1 < 8; xpos1++)
		for (int ypos1 = 0; ypos1 < 8; ypos1++) // Перебираем шашки 
			for (int xpos2 = 0; xpos2 < 8; xpos2++)
				for (int ypos2 = 0; ypos2 < 8; ypos2++) // Перебираем возможные ходы для каждой шашки
					if (this->board->CkeckLegal(xpos1, ypos1, xpos2, ypos2, this->cellType, this->EatOpp))
					{
						this->board->CellMove(xpos1, ypos1, xpos2, ypos2, this->EatOpp);
						evaluators.push_back(new TicTacBoardMonteCarloEvaluator(this->board, 1000, (this->cellType == CellType_White) ? CellType_Black : CellType_White, xpos1, ypos1, xpos2, ypos2, this->EatOpp));
						this->board->CancelMove(xpos1, ypos1, xpos2, ypos2, this->EatOpp); // Отменяем все изменения
					}

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		(*evaluator)->Evaluate();

	int biggestVictories = -1;

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		if (this->cellType == CellType_White)
		{
			if ((*evaluator)->GetVictories() > biggestVictories)
				biggestVictories = (*evaluator)->GetVictories();
		}
		else
		{
			if ((*evaluator)->GetLosses() > biggestVictories)
				biggestVictories = (*evaluator)->GetLosses();
		}

	vector <TicTacBoardMonteCarloEvaluator*> biggestWinEvaluators;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
	{
		int numVictories;
		if (this->cellType == CellType_White)
			numVictories = (*evaluator)->GetVictories();
		else
			numVictories = (*evaluator)->GetLosses();
		if (numVictories == biggestVictories)
			biggestWinEvaluators.push_back((*evaluator));
	}

	this->board->CellMove(biggestWinEvaluators[0]->GetXPos1(), biggestWinEvaluators[0]->GetYPos1(), biggestWinEvaluators[0]->GetXPos2(), biggestWinEvaluators[0]->GetYPos2(), biggestWinEvaluators[0]->GetEatOpp());
	
	////// Я тут сейчас
	
		//this->board->CellMove(row1, col1, row2, col2, EatOpp);
		if (EatOpp == true)
			this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp); // дополнительная проверка на возможность съесть еще одну шашку

		if (EatOpp == false)
			return 1;
		if (EatOpp == true)
			return 2;

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		delete(*evaluator);
	evaluators.clear();
	biggestWinEvaluators.clear();
	return 0;
}