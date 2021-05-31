#pragma once
#include "CellType.h"

class TicTacBoard
{
private:
	int boardsize;
	CellType** cells;
	bool CheckHod = false;
	int EatX;
	int EatY;
public:
	TicTacBoard(int boardsize);
	virtual ~TicTacBoard();
	void Show();
	void SetCell();
	bool CkeckLegal(int ypos1, int xpos1, int xpos2, int ypos2, CellType Type, bool& EatOpp);
	void CellMove(int& xpos1, int& ypos1, int& xpos2, int& ypos2, bool& EatOpp);
	void CheckDamka(int xpos2, int ypos2);

	void CheckPP(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1, 
		bool& EatOrNot,bool& EatApportunity, CellType Type); //CheckPlusPlus
	void CheckMM(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1,
		bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckMinusMinus
	void CheckPM(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1,
		bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckPlusMinus
	void CheckMP(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1,
		bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckMinusPlus
};

