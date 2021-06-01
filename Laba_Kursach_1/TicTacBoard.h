#pragma once
#include "CellType.h"

class TicTacBoard
{
private:
	int boardsize;
	CellType** cells;
	CellType Type;
	bool CheckHod = false;
	CellType SaveType;
	int EatX, EatY, NowXpos, NowYpos;
	int OldBChecker = 0, OldWChecker = 0, OldBDamka = 0, OldWDamka = 0; // Переменные для сохранения количества тех или иных шашек
	bool bVictory = false;
	bool CheckVictory();
	bool CheckDraw(int& white, int& black, int& n, int& FirstCheck, int& SecondCheck, int& ThirdCheck);
public:

	TicTacBoard(int boardsize);
	TicTacBoard(TicTacBoard* board);
	virtual ~TicTacBoard();
	void Show();
	void SetCell();
	bool CkeckLegal(int xpos1, int ypos1, int xpos2, int ypos2, CellType Type, bool& EatOpp);
	void CellMove(int xpos1, int ypos1, int xpos2, int ypos2, bool EatOpp);
	void Revers(int& xpos1, int& ypos1, int& xpos2, int& ypos2, bool EatOpp);
	void CancelMove(int xpos1, int ypos1, int xpos2, int ypos2, bool EatOpp);
	void CheckDamka(int xpos2, int ypos2);

	void CheckPP(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1, bool& EatOrNot,bool& EatApportunity, CellType Type); //CheckPlusPlus
	void CheckMM(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1,bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckMinusMinus
	void CheckPM(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1,bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckPlusMinus
	void CheckMP(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1,bool& EatOrNot, bool& EatApportunity, CellType Type); //CheckMinusPlus

	bool CheckEndCondition(int& white, int& black, int& n, int& FirstCheck, int& SecondCheck, int& ThirdCheck);
	bool IsVictory();

	void CheckEndPP(int j, int i, int& n); //CheckEndPlusPlus
	void CheckEndMM(int j, int i, int& n); //CheckEndMinusMinus
	void CheckEndPM(int j, int i, int& n); //CheckEndPlusMinus
	void CheckEndMP(int j, int i, int& n); //CheckEndMinusPlus
};