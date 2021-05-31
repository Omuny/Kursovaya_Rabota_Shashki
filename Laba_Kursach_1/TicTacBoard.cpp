#include "pch.h"
#include "TicTacBoard.h"
#include "TicTacPlayer.h"

TicTacBoard::TicTacBoard(int size)
{
	this->boardsize = size;
	cells = new CellType * [size];
	for (int i = 0; i < size; i++)
		cells[i] = new CellType[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cells[i][j] = CellType_Empty;
}

TicTacBoard::~TicTacBoard()
{
	for (int i = 0; i < boardsize; i++)
		delete[]cells[i];
	delete[]cells;
}

void TicTacBoard::Show()
{
	cout << endl;
	cout << "     ";
	cout << " A B C D E F G H\tW - Белая шашка, B - черная. V - Белая дамка, P - черная. ";
	cout << endl;
	cout << endl;

	for (int i = 0; i < boardsize; i++)
	{
		cout << 8-i << "    |";
		for (int j = 0; j < boardsize; j++)
		{
			switch (cells[i][j])
			{
			case CellType_White:
				cout << "W"; // Белая шашка
				break;
			case CellType_Black:
				cout << "B"; // Черная шашка
				break;
			case CellType_White_King:
				cout << "V"; // Белая дамка
				break;
			case CellType_Black_King:
				cout << "P"; // Черная дамка
				break;
			case CellType_Empty:
				if (((i % 2 ==0) && (j % 2 == 0)) || ((i % 2 != 0) && (j % 2 != 0)))
					cout << "-"; // Пустая белая клетка
				else
					cout << " "; // Пустая черная клетка
				break;
			}
			cout << "|";
		}
		cout << endl;
	}
	cout << endl;
}

void TicTacBoard::SetCell()
{
	/*
	for (int i = 0; i < boardsize; i++)
		for (int j = 0; j < boardsize; j++)
		{
			if (i == 0 && j % 2 != 0)
				cells[i][j] = CellType_Black;
			if (i == 1 && j % 2 == 0)
				cells[i][j] = CellType_Black;
			if (i == 2 && j % 2 != 0)
				cells[i][j] = CellType_Black;
			if (i == 5 && j % 2 == 0)
				cells[i][j] = CellType_White;
			if (i == 6 && j % 2 != 0)
				cells[i][j] = CellType_White;
			if (i == 7 && j % 2 == 0)
				cells[i][j] = CellType_White;
		}
		*/
	for (int j = 0; j < boardsize; j++)
	{
		if (j % 2 != 0)
			cells[0][j] = CellType_Black;
		if (j % 2 == 0)
			cells[7][j] = CellType_White;
	}
}

void TicTacBoard::CheckPP(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1, 
	bool& EatOrNot, bool& EatApportunity, CellType Type) // Проверка на возможность съесть ++
{
	// Проверка правой нижней клетки
	if (cells[xpos1 + 1][ypos1 + 1] != Type && cells[xpos1 + 1][ypos1 + 1] != (Type + 2) && cells[xpos1 + 1][ypos1 + 1] != CellType_Empty)
	{
		if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
		{
			EatApportunity = true;
			if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2) && (xpos1 == SaveXpos1) && (ypos1 == SaveYpos1)) // съеле ли той шашкой, которая может съесть
			{
				EatOrNot = true;
				EatX = xpos1 + 1;
				EatY = ypos1 + 1;
			}
		}
	}
}

void TicTacBoard::CheckMM(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1, 
	bool& EatOrNot, bool& EatApportunity, CellType Type) // Проверка на возможность съесть --
{
	// Проверка левой верхней клетки
	if (cells[xpos1 - 1][ypos1 - 1] != Type && cells[xpos1 - 1][ypos1 - 1] != (Type + 2) && cells[xpos1 - 1][ypos1 - 1] != CellType_Empty)
	{
		if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
		{
			EatApportunity = true;
			if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2) && (xpos1 == SaveXpos1) && (ypos1 == SaveYpos1)) // съеле ли той шашкой, которая может съесть
			{
				EatOrNot = true;
				EatX = xpos1 - 1;
				EatY = ypos1 - 1;
			}
		}
	}
}

void TicTacBoard::CheckPM(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1, 
	bool& EatOrNot, bool& EatApportunity, CellType Type) // Проверка на возможность съесть +-
{
	// Проверка левой нижней клетки
	if (cells[xpos1 + 1][ypos1 - 1] != Type && cells[xpos1 + 1][ypos1 - 1] != (Type + 2) && cells[xpos1 + 1][ypos1 - 1] != CellType_Empty)
	{
		if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
		{
			EatApportunity = true;
			if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2) && (xpos1 == SaveXpos1) && (ypos1 == SaveYpos1)) // съеле ли той шашкой, которая может съесть
			{
				EatOrNot = true;
				EatX = xpos1 + 1;
				EatY = ypos1 - 1;
			}
		}
	}
}

void TicTacBoard::CheckMP(int ypos1, int xpos1, int xpos2, int ypos2, int SaveXpos1, int SaveYpos1, 
	bool& EatOrNot, bool& EatApportunity, CellType Type) // Проверка на возможность съесть -+
{
	// Проверка правой верхней клетки
	if (cells[xpos1 - 1][ypos1 + 1] != Type && cells[xpos1 - 1][ypos1 + 1] != (Type + 2) && cells[xpos1 - 1][ypos1 + 1] != CellType_Empty)
	{
		if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
		{
			EatApportunity = true;
			if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2) && (xpos1 == SaveXpos1) && (ypos1 == SaveYpos1)) // съеле ли той шашкой, которая может съесть
			{
				EatOrNot = true;
				EatX = xpos1 - 1;
				EatY = ypos1 + 1;
			}
		}
	}
}


bool TicTacBoard::CkeckLegal(int xpos1, int ypos1, int xpos2, int ypos2, CellType Type, bool& EatOpp) // Проверка возможности хода
{
	/* !!!!!!!!!!!!!!!!!!!! Внимание. Важно! Я перепутал местами xpos и ypos, поэтому теперь xpos отвечает за строки, а ypos отвечает за столбцы! !!!!!!!!!!!!!!!!!!!! */

	if ((xpos2 < 0) || (xpos2 > boardsize) || (ypos2 < 0) || (ypos2 > boardsize)) // если выходим за пределы доски
		return false;
	if (((ypos2 % 2 == 0) && (xpos2 % 2 == 0)) || ((ypos2 % 2 != 0) && (xpos2 % 2 != 0))) // если поле белое
		return false;
	if (cells[xpos1][ypos1] == CellType_Empty) // Если пытаемся пойти пустой клеткой
		return false;
	if (cells[xpos2][ypos2] != CellType_Empty) // если на клетке есть другая шашка
		return false;
	if (cells[xpos1][ypos1] != Type && cells[xpos1][ypos1] != (Type + 2)) // Попытка пойти шашкой не своего цвета
		return false;
	if ((xpos2 == xpos1) && (ypos2 == ypos1)) // попытка пойти на ту же клетку
		return false;

	bool EatApportunity = false; // Возможность съесть шашку
	bool EatOrNot = false; // Съели при возможности или нет
	int SaveXpos1, SaveYpos1;
	SaveXpos1 = xpos1;
	SaveYpos1 = ypos1;
	
	//Цикл проверки всех шашек на возможность съесть
	for (xpos1 = 0; xpos1 < boardsize; xpos1++)
	{
		for (ypos1 = 0; ypos1 < boardsize; ypos1++)
		{
			if (cells[xpos1][ypos1] == Type) // Проверка обычных шашек только цвета текущего игрока
			{
				 // Внешний квадрат
				if (xpos1 == 0 || ypos1 == 0 || xpos1 == 7 || ypos1 == 7)
				{
					if ((xpos1 == 0) && (ypos1 == 1) || (xpos1 == 1) && (ypos1 == 0)) // Две клетки в левом верхнем углу
						CheckPP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой нижней клетки

					if ((xpos1 == 6) && (ypos1 == 7) || (xpos1 == 7) && (ypos1 == 6)) // Две клетки в правом нижнем углу
						CheckMM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой верхней клетки

					if ((xpos1 == 7) && (ypos1 == 0)) // Клетка в левом нижнем углу
						CheckMP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой верхней клетки

					if ((xpos1 == 0) && (ypos1 == 7)) // Клетка в правом верхнем углу
						CheckPM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой нижней клетки

					if ((xpos1 == 7) && (ypos1 == 2 || ypos1 == 4)) // Нижние две клетки
					{
						CheckMP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой верхней клетки
						CheckMM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой верхней клетки
					}
					if ((xpos1 == 0) && (ypos1 == 3 || ypos1 == 5)) // Верхние две клетки
					{
						CheckPM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой нижней клетки
						CheckPP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой нижней клетки
					}
					if ((ypos1 == 0) && (xpos1 == 3 || xpos1 == 5)) // Левые две клетки
					{
						CheckPP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой нижней клетки
						CheckMP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой верхней клетки
					}
					if (ypos1 == 7 && (xpos1 == 2 || xpos1 == 4)) // Правые две клетки
					{
						CheckPM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой нижней клетки
						CheckMM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой верхней клетки
					}
				}

				//Серединный квадрат
				if (xpos1 == 1 || ypos1 == 1 || xpos1 == 6 || ypos1 == 6) 
				{
					if ((xpos1 == 6) && (ypos1 == 1)) // Нижняя левая угловая клетка
						CheckMP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой верхней клетки

					if ((xpos1 == 1) && (ypos1 == 6)) // Верхняя правая угловая клетка 
						CheckPM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой нижней клетки

					if ((ypos1 == 1) && (xpos1 == 2 || xpos1 == 4)) // Левые две клетки
					{
						CheckPP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой нижней клетки
						CheckMP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой верхней клетки
					}
					if ((ypos1 == 6) && (xpos1 == 3 || xpos1 == 5)) // Правые две клетки
					{
						CheckPM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой нижней клетки
						CheckMM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой верхней клетки
					}
					if ((xpos1 == 1) && (ypos1 == 2 || ypos1 ==4)) // Верхние две клетки
					{
						CheckPP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой нижней клетки
						CheckPM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой нижней клетки
					}
					if ((xpos1 == 6) && (ypos1 == 3 || ypos1 == 5)) // Нижние две клетки
					{
						CheckMP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой верхней клетки
						CheckMM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой верхней клетки
					}
				}

				// Центральный квадрат
				if (((1 < xpos1) && (xpos1 < 6)) && ((1 < ypos1) && (ypos1 < 6)))
				{
					CheckPP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой нижней клетки
					CheckMP(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка правой верхней клетки
					CheckPM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой нижней клетки
					CheckMM(ypos1, xpos1, xpos2, ypos2, SaveXpos1, SaveYpos1, EatOrNot, EatApportunity, Type); // Проверка левой верхней клетки
				}
			}
			if (cells[xpos1][ypos1] == (Type + 2)) // Проверка дамки цвета игрока
			{
				bool diagUR = false; // Правая верхняя диагональ
				bool diagUL = false; // Левая верхняя диагональ
				bool diagDR = false; // Правая нижняя диагональ
				bool diagDL = false; // Левая нижняя диагональ
				for (int k = 1; k < 7; k++) // Проверяем диагонали во все стороны
				{
					// Проверяем нижнюю правую диагональ от шашки
					if (diagDR == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
						if (((xpos1 + k) < 7) && ((ypos1 + k) < 7)) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка
							if (cells[xpos1 + k][ypos1 + k] != CellType_Empty) // Проверям есть ли на пути шашка
							{
								diagDR = true;
								if ((cells[xpos1 + k][ypos1 + k] != Type) && (cells[xpos1 + k][ypos1 + k] != Type + 2)) // Если шашка противоположного цвета
									if (cells[xpos1 + (k + 1)][ypos1 + (k + 1)] == CellType_Empty) // Если поле за шашкой пустое, значит мы можем съесть
									{
										EatApportunity = true;
										if((SaveXpos1 == xpos1) && (SaveYpos1 == ypos1)) // Проверка ходим ли мы проверяемой в данный момент шашкой
											for (int n = (k + 1); n < 8; n++) // Проходимся по всем полям за съедаемой шашкой, чтобы проверить как далеко после съедания может пойти дамка
												if (((xpos1 + n) < 8) && ((ypos1 + n) < 8)) // Проверка не выходим ли мы за пределы поля
												{
													if (cells[xpos1 + n][ypos1 + n] != CellType_Empty) // Как только на пути встречается шашка, выходим из цикла проверки
														break;
													if ((xpos2 == xpos1 + n) && (ypos2 == ypos1 + n)) // Если мы едим эту шашку
													{
														EatOrNot = true;
														EatX = xpos1 + k;
														EatY = ypos1 + k;
													}
												}
									}
							}
					// Проверяем верхнюю левую диагональ от шашки
					if (diagUL == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
						if ((0 < (xpos1 - k)) && (0 < (ypos1 - k))) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка
							if (cells[xpos1 - k][ypos1 - k] != CellType_Empty) // Проверям есть ли на пути шашка
							{
								diagUL = true;
								if ((cells[xpos1 - k][ypos1 - k] != Type) && (cells[xpos1 - k][ypos1 - k] != Type + 2)) // Если шашка противоположного цвета
									if (cells[xpos1 - (k + 1)][ypos1 - (k + 1)] == CellType_Empty) // Если поле за шашкой пустое, значит мы можем съесть
									{
										EatApportunity = true;
										if ((SaveXpos1 == xpos1) && (SaveYpos1 == ypos1)) // Проверка ходим ли мы проверяемой в данный момент шашкой
											for (int n = (k + 1); n < 8; n++) // Проходимся по всем полям за съедаемой шашкой, чтобы проверить как далеко после съедания может пойти дамка
												if ((-1 < (xpos1 - n)) && (-1 < (ypos1 - n))) // Проверка не выходим ли мы за пределы поля
												{
													if (cells[xpos1 - n][ypos1 - n] != CellType_Empty) // Как только на пути встречается шашка, выходим из цикла проверки
														break;
													if ((xpos2 == xpos1 - n) && (ypos2 == ypos1 - n)) // Если мы едим эту шашку
													{
														EatOrNot = true;
														EatX = xpos1 - k;
														EatY = ypos1 - k;
													}
												}
									}
							}
					// Проверяем нижнюю левую диагональ от шашки
					if (diagDL == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
						if (((xpos1 + k) < 7) && (0 < (ypos1 - k))) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка
							if (cells[xpos1 + k][ypos1 - k] != CellType_Empty) // Проверям есть ли на пути шашка
							{
								diagDL = true;
								if ((cells[xpos1 + k][ypos1 - k] != Type) && (cells[xpos1 + k][ypos1 - k] != Type + 2)) // Если шашка противоположного цвета
									if (cells[xpos1 + (k + 1)][ypos1 - (k + 1)] == CellType_Empty) // Если поле за шашкой пустое, значит мы можем съесть
									{
										EatApportunity = true;
										if ((SaveXpos1 == xpos1) && (SaveYpos1 == ypos1)) // Проверка ходим ли мы проверяемой в данный момент шашкой
											for (int n = (k + 1); n < 8; n++) // Проходимся по всем полям за съедаемой шашкой, чтобы проверить как далеко после съедания может пойти дамка
												if (((xpos1 + n) < 8) && (-1 < (ypos1 - n))) // Проверка не выходим ли мы за пределы поля
												{
													if (cells[xpos1 + n][ypos1 - n] != CellType_Empty) // Как только на пути встречается шашка, выходим из цикла проверки
														break;
													if ((xpos2 == xpos1 + n) && (ypos2 == ypos1 - n)) // Если мы едим эту шашку
													{
														EatOrNot = true;
														EatX = xpos1 + k;
														EatY = ypos1 - k;
													}
												}
									}
							}
					// Проверяем верхнюю правую диагональ от шашки
					if (diagUR == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
						if ((0 < (xpos1 - k)) && ((ypos1 + k) < 7)) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка
							if (cells[xpos1 - k][ypos1 + k] != CellType_Empty) // Проверям есть ли на пути шашка
							{
								diagUR = true;
								if ((cells[xpos1 - k][ypos1 + k] != Type) && (cells[xpos1 - k][ypos1 + k] != Type + 2)) // Если шашка противоположного цвета
									if (cells[xpos1 - (k + 1)][ypos1 + (k + 1)] == CellType_Empty) // Если поле за шашкой пустое, значит мы можем съесть
									{
										EatApportunity = true;
										if ((SaveXpos1 == xpos1) && (SaveYpos1 == ypos1)) // Проверка ходим ли мы проверяемой в данный момент шашкой
											for (int n = (k + 1); n < 8; n++) // Проходимся по всем полям за съедаемой шашкой, чтобы проверить как далеко после съедания может пойти дамка
												if ((-1 < (xpos1 - n)) && ((ypos1 + n) < 8)) // Проверка не выходим ли мы за пределы поля
												{
													if (cells[xpos1 - n][ypos1 + n] != CellType_Empty) // Как только на пути встречается шашка, выходим из цикла проверки
														break;
													if ((xpos2 == xpos1 - n) && (ypos2 == ypos1 + n)) // Если мы едим эту шашку
													{
														EatOrNot = true;
														EatX = xpos1 - k;
														EatY = ypos1 + k;
													}
												}
									}
							}
				}
			}
			if (EatOrNot == true)
				break;
		}
		if (EatOrNot == true)
			break;
	}
	xpos1 = SaveXpos1;
	ypos1 = SaveYpos1;
	EatOpp = EatApportunity;

	if (this->CheckHod == false)
	{
		if ((EatApportunity == true) && (EatOrNot == true)) // если съели при возможности
			return true;
		if ((EatApportunity == true) && (EatOrNot == false)) // если не съели при возможности
			return false;
	}
	if (this->CheckHod == true)
	{
		CheckHod = false;
		return true;
	}

	if (cells[xpos1][ypos1] == CellType_White) // Обычный ход белой шашки
	{
		if ((xpos2 < xpos1) && (xpos2 == xpos1 - 1))
			if ((ypos2 == ypos1 - 1) || (ypos2 == ypos1 + 1))
				return true;
		return false;
	}
	if (cells[xpos1][ypos1] == CellType_Black) // Обычный ход черной шашки
	{
		if ((xpos2 > xpos1) && (xpos2 == xpos1 + 1))
			if ((ypos2 == ypos1 - 1) || (ypos2 == ypos1 + 1))
				return true;
		return false;
	}

	bool MoveDamka = false;
	if (cells[xpos1][ypos1] == CellType_White_King || cells[xpos1][ypos1] == CellType_Black_King)// Обычный ход дамкой
	{
		bool diagUR = false; // Правая верхняя диагональ
		bool diagUL = false; // Левая верхняя диагональ
		bool diagDR = false; // Правая нижняя диагональ
		bool diagDL = false; // Левая нижняя диагональ
		for (int k = 1; k < 8; k++) // цикл для проверки всех диагоналей
		{
			// Проверяем нижнюю правую диагональ от шашки
			if (diagDR == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
				if (((xpos1 + k) < 8) && ((ypos1 + k) < 8)) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка
				{
					if (cells[xpos1 + k][ypos1 + k] == CellType_Empty) // Проверям есть ли на пути шашка
					{
						if (((xpos1 + k) == xpos2) && ((ypos1 + k) == ypos2)) // Ходим ли мы на это поле
							MoveDamka = true;
					}
					else
						diagDR = true;
				}
			// Проверяем верхнюю левую диагональ от шашки
			if (diagUL == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
				if ((-1 < (xpos1 - k)) && (-1 < (ypos1 - k))) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка (-1 < (xpos1 - n)) && (-1 < (ypos1 - n))
				{
					if (cells[xpos1 - k][ypos1 - k] == CellType_Empty) // Проверям есть ли на пути шашка
					{
						if (((xpos1 - k) == xpos2) && ((ypos1 - k) == ypos2)) // Ходим ли мы на это поле
							MoveDamka = true;
					}
					else
						diagUL = true;
				}
			// Проверяем нижнюю левую диагональ от шашки
			if (diagDL == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
				if (((xpos1 + k) < 8) && (-1 < (ypos1 - k))) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка
				{
					if (cells[xpos1 + k][ypos1 - k] == CellType_Empty) // Проверям есть ли на пути шашка
					{
						if (((xpos1 + k) == xpos2) && ((ypos1 - k) == ypos2)) // Ходим ли мы на это поле
							MoveDamka = true;
					}
					else
						diagDL = true;
				}
			// Проверяем верхнюю правую диагональ от шашки
			if (diagUR == false) // Если этот прарметр true, значит на пути была шашка и проверять дальше диагональ нельзя
				if ((-1 < (xpos1 - k)) && ((ypos1 + k) < 8)) // Делаем ограниченя в пределах квадрата, в котором потенциально может быть съедаемая шашка
				{
					if (cells[xpos1 - k][ypos1 + k] == CellType_Empty) // Проверям есть ли на пути шашка
					{
						if (((xpos1 - k) == xpos2) && ((ypos1 + k) == ypos2)) // Ходим ли мы на это поле
							MoveDamka = true;
					}
					else
						diagUR = true;
				}
			if (MoveDamka == true)
				return true;
		}
		if (MoveDamka == false)
			return false;
	}
	return false;
}

void TicTacBoard::CheckDamka(int xpos2, int ypos2) // Проверка шакшки и превращение в дамку
{
	if ((xpos2 == 0) && (cells[xpos2][ypos2] == CellType_White))
		cells[xpos2][ypos2] = CellType_White_King;
	if ((xpos2 == 7) && (cells[xpos2][ypos2] == CellType_Black))
		cells[xpos2][ypos2] = CellType_Black_King;
}

void TicTacBoard::CellMove(int& xpos1, int& ypos1, int& xpos2, int& ypos2, bool& EatOpp) // Метод реализации ходов шашки
{
	CellType type;

	if (EatOpp == false) // если обычный ход
	{
		type = cells[xpos1][ypos1];
		cells[xpos1][ypos1] = CellType_Empty; // убираем шашку со старого места
		cells[xpos2][ypos2] = type; // ставим шашку на место хода
		
		CheckDamka(xpos2, ypos2); // Проверка шашки можетли она стать дамкой
	}
	if (EatOpp == true) // если съедаем шашку
	{
		type = cells[xpos1][ypos1];
		cells[xpos1][ypos1] = CellType_Empty; // убираем шашку со старого места
		cells[EatX][EatY] = CellType_Empty; // убираем съеденную шашку
		cells[xpos2][ypos2] = type; // ставим шашку на место хода

		CheckDamka(xpos2, ypos2); // Проверка шашки можетли она стать дамкой

		this->CheckHod = true; // для повторной проверки
		int SaveX = xpos1;
		int SaveY = ypos1;
		xpos1 = xpos2;
		ypos1 = ypos2;
		xpos2 = SaveX;
		ypos2 = SaveY;
	}
}
