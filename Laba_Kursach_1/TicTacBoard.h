#pragma once
#include "CellType.h"

class TicTacBoard
{
private:
	int boardsize;
	CellType** cells;
	bool CheckHod = false;
public:
	TicTacBoard(unsigned int boardsize);
	virtual ~TicTacBoard();
	void Show();
	void SetCell();
	bool CkeckLegal(unsigned int ypos1, unsigned int xpos1, unsigned int xpos2, unsigned int ypos2, CellType Type, bool& EatOpp);
	void CellMove(unsigned int& xpos1, unsigned int& ypos1, unsigned int& xpos2, unsigned int& ypos2, bool& EatOpp);

	void CheckPP(unsigned int ypos1, unsigned int xpos1, unsigned int xpos2, unsigned int ypos2, unsigned int SaveXpos1, unsigned int SaveYpos1, 
		bool& EatOrNot,bool& EatApportunity, CellType Type); //CheckPlusPlus
	void CheckMM(unsigned int ypos1, unsigned int xpos1, unsigned int xpos2, unsigned int ypos2, unsigned int SaveXpos1, unsigned int SaveYpos1,
		bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckMinusMinus
	void CheckPM(unsigned int ypos1, unsigned int xpos1, unsigned int xpos2, unsigned int ypos2, unsigned int SaveXpos1, unsigned int SaveYpos1,
		bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckPlusMinus
	void CheckMP(unsigned int ypos1, unsigned int xpos1, unsigned int xpos2, unsigned int ypos2, unsigned int SaveXpos1, unsigned int SaveYpos1,
		bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckMinusPlus
};

