#include "pch.h"
#include "TicTacBoard.h"
#include "TicTacHumanPlayer.h"

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

	this->Type = Type;
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
				if (((xpos1 + k) < 8) && ((ypos1 + k) < 8)) // Делаем ограниченя в пределах квадрата
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
				if ((-1 < (xpos1 - k)) && (-1 < (ypos1 - k))) // Делаем ограниченя в пределах квадрата
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
				if (((xpos1 + k) < 8) && (-1 < (ypos1 - k))) // Делаем ограниченя в пределах квадрата
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
				if ((-1 < (xpos1 - k)) && ((ypos1 + k) < 8)) // Делаем ограниченя в пределах квадрата
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
		NowXpos = xpos2; // Ныняшняя x координата походившей шашки
		NowYpos = ypos2; // Ныняшняя y координата походившей шашки
		CheckDamka(xpos2, ypos2); // Проверка шашки может-ли она стать дамкой
	}
	if (EatOpp == true) // если съедаем шашку
	{
		type = cells[xpos1][ypos1];
		cells[xpos1][ypos1] = CellType_Empty; // убираем шашку со старого места
		cells[EatX][EatY] = CellType_Empty; // убираем съеденную шашку
		cells[xpos2][ypos2] = type; // ставим шашку на место хода
		NowXpos = xpos2; // Ныняшняя x координата походившей шашки
		NowYpos = ypos2; // Ныняшняя y координата походившей шашки
		CheckDamka(xpos2, ypos2); // Проверка шашки может-ли она стать дамкой

		this->CheckHod = true; // для повторной проверки
		int SaveX = xpos1;
		int SaveY = ypos1;
		xpos1 = xpos2;
		ypos1 = ypos2;
		xpos2 = SaveX;
		ypos2 = SaveY;
	}
}

void TicTacBoard::CheckEndPP(int j, int i, int& n)
{
	// Проверка правой нижней клетки
	if (cells[i + 1][j + 1] == Type || cells[i + 1][j + 1] == (Type + 2))
		if (cells[i + 2][j + 2] == CellType_Empty)
			n++;
}
void TicTacBoard::CheckEndMM(int j, int i, int& n)
{
	// Проверка левая верхняя клетки
	if (cells[i - 1][j - 1] == Type || cells[i - 1][j - 1] == (Type + 2))
		if (cells[i - 2][j - 2] == CellType_Empty)
			n++;
}
void TicTacBoard::CheckEndPM(int j, int i, int& n)
{
	// Проверка левой нижней клетки
	if (cells[i + 1][j - 1] == Type || cells[i + 1][j - 1] == (Type + 2))
		if (cells[i + 2][j - 2] == CellType_Empty)
			n++;
}
void TicTacBoard::CheckEndMP(int j, int i, int& n)
{
	// Проверка правой верхней клетки
	if (cells[i - 1][j + 1] == Type || cells[i - 1][j + 1] == (Type + 2))
		if (cells[i - 2][j + 2] == CellType_Empty)
			n++;
}

bool TicTacBoard::CheckVictory()
{
	int n = 0; // Счетчик для проверки возможности какого-либо хода
	// Проверка - Если шашки остались, могут ли они ходить
	for (int i = 0; i < boardsize; i++)
		for (int j = 0; j < boardsize; j++)
			if (cells[i][j] != CellType_Empty) // Если клетка не пустая
				if (cells[i][j] != Type && cells[i][j] != Type + 2) // Если шашка противоположного цвета
				{
					// Проверка может ли есть

					// Внешний квадрат
					if (i == 0 || j == 0 || i == 7 || j == 7)
					{
						if ((i == 0) && (j == 1) || (i == 1) && (j == 0)) // Две клетки в левом верхнем углу
							CheckEndPP(j, i, n); // Проверка правой нижней клетки
						if ((i == 6) && (j == 7) || (i == 7) && (j == 6)) // Две клетки в правом нижнем углу
							CheckEndMM(j, i, n); // Проверка левой верхней клетки
						if ((i == 7) && (j == 0)) // Клетка в левом нижнем углу
							CheckEndMP(j, i, n); // Проверка правой верхней клетки
						if ((i == 0) && (j == 7)) // Клетка в правом верхнем углу
							CheckEndPM(j, i, n); // Проверка левой нижней клетки

						if ((i == 7) && (j == 2 || j == 4)) // Нижние две клетки
						{
							CheckEndMP(j, i, n); // Проверка правой верхней клетки
							CheckEndMM(j, i, n); // Проверка левой верхней клетки
						}
						if ((i == 0) && (j == 3 || j == 5)) // Верхние две клетки
						{
							CheckEndPM(j, i, n); // Проверка левой нижней клетки
							CheckEndPP(j, i, n); // Проверка правой нижней клетки
						}
						if ((j == 0) && (i == 3 || i == 5)) // Левые две клетки
						{
							CheckEndPP(j, i, n); // Проверка правой нижней клетки
							CheckEndMP(j, i, n); // Проверка правой верхней клетки
						}
						if (j == 7 && (i == 2 || i == 4)) // Правые две клетки
						{
							CheckEndPM(j, i, n); // Проверка левой нижней клетки
							CheckEndMM(j, i, n); // Проверка левой верхней клетки
						}
					}
					//Серединный квадрат
					if (i == 1 || j == 1 || i == 6 || j == 6)
					{
						if ((i == 6) && (j == 1)) // Нижняя левая угловая клетка
							CheckEndMP(j, i, n); // Проверка правой верхней клетки

						if ((i == 1) && (j == 6)) // Верхняя правая угловая клетка 
							CheckEndPM(j, i, n); // Проверка левой нижней клетки

						if ((j == 1) && (i == 2 || i == 4)) // Левые две клетки
						{
							CheckEndPP(j, i, n); // Проверка правой нижней клетки
							CheckEndMP(j, i, n); // Проверка правой верхней клетки
						}
						if ((j == 6) && (i == 3 || i == 5)) // Правые две клетки
						{
							CheckEndPM(j, i, n); // Проверка левой нижней клетки
							CheckEndMM(j, i, n); // Проверка левой верхней клетки
						}
						if ((i == 1) && (j == 2 || j == 4)) // Верхние две клетки
						{
							CheckEndPP(j, i, n); // Проверка правой нижней клетки
							CheckEndPM(j, i, n); // Проверка левой нижней клетки
						}
						if ((i == 6) && (j == 3 || j == 5)) // Нижние две клетки
						{
							CheckEndMP(j, i, n); // Проверка правой верхней клетки
							CheckEndMM(j, i, n); // Проверка левой верхней клетки
						}
					}
					// Центральный квадрат
					if (((1 < i) && (i < 6)) && ((1 < j) && (j < 6)))
					{
						CheckEndPP(j, i, n); // Проверка правой нижней клетки
						CheckEndMP(j, i, n); // Проверка правой верхней клетки
						CheckEndPM(j, i, n); // Проверка левой нижней клетки
						CheckEndMM(j, i, n); // Проверка левой верхней клетки
					}

					// Проверка обычного хода
					if (cells[i][j] == CellType_White_King || cells[i][j] == CellType_Black_King) // Если дамка
					{
						// Проверяем нижнюю правую диагональ от шашки
						if (((i + 1) < 8) && ((j + 1) < 8)) // Делаем ограниченя в пределах поля
							if (cells[i + 1][j + 1] == CellType_Empty) // Проверям есть ли на пути шашка
								n++;
						// Проверяем верхнюю левую диагональ от шашки
						if ((-1 < (i - 1)) && (-1 < (j - 1))) // Делаем ограниченя в пределах поля
							if (cells[i - 1][j - 1] == CellType_Empty) // Проверям есть ли на пути шашка
								n++;
						// Проверяем нижнюю левую диагональ от шашки
						if (((i + 1) < 8) && (-1 < (j - 1))) // Делаем ограниченя в пределах поля
							if (cells[i + 1][j - 1] == CellType_Empty) // Проверям есть ли на пути шашка
								n++;
						// Проверяем верхнюю правую диагональ от шашки
						if ((-1 < (i - 1)) && ((j + 1) < 8)) // Делаем ограниченя в пределах поля
							if (cells[i - 1][j + 1] == CellType_Empty) // Проверям есть ли на пути шашка
								n++;
					}
					else // Если обычная
					{
						//Проверка может ли ходить
						if (cells[i][j] == CellType_White) // Если белая
							if (i != 0) // Не проверяем 8 строку
							{
								if (j == 0) // Если шашка в 1 столбце
									if (cells[i - 1][j + 1] == CellType_Empty)
										n++;
								if (j == 7) // Если шашка в 8 столбце
									if (cells[i - 1][j - 1] == CellType_Empty)
										n++;
								if (0 < j && j < 7) // Если шашка в любом другом столбце
									if (cells[i - 1][j + 1] == CellType_Empty || cells[i - 1][j - 1] == CellType_Empty)
										n++;
							}
						if (cells[i][j] == CellType_Black) // Если черная
							if (i != 7) // Не проверяем 1 строку
							{
								if (j == 0) // Если шашка в 1 столбце
									if (cells[i + 1][j + 1] == CellType_Empty)
										n++;
								if (j == 7) // Если шашка в 8 столбце
									if (cells[i + 1][j - 1] == CellType_Empty)
										n++;
								if (0 < j && j < 7) // Если шашка в любом другом столбце
									if (cells[i + 1][j + 1] == CellType_Empty || cells[i + 1][j - 1] == CellType_Empty)
										n++;
							}
					}
				}
	if (n == 0)
	{
		// Если ни одной шашки противоположного цвета нет или они не могут ходить
		bVictory = true;
		return true;
	}

	return false;
}

bool TicTacBoard::CheckDraw(int& white, int& black, int& n, int& FirstCheck, int& SecondCheck, int& ThirdCheck)
{
	// Пройдемся по всей доске и посчитаем количество всех видов шашек
	int BChecker = 0, WChecker = 0, BDamka = 0, WDamka = 0; // Переменные для записи количества тех или иных шашек
	for (int i = 0; i < boardsize; i++)
		for (int j = 0; j < boardsize; j++)
		{
			if (cells[i][j] == CellType_White)
				WChecker++; // Количество белых шашек
			if (cells[i][j] == CellType_Black)
				BChecker++; // Количество черных шашек
			if (cells[i][j] == CellType_White_King)
				WDamka++; // Количество белых дамок
			if (cells[i][j] == CellType_Black_King)
				BDamka++; // Количество черных дамок
		}
	int sum = WChecker + BChecker + WDamka + BDamka; // Общее количество шашек на доске

	if (sum < 9) // Если суммарное количество шашек 8 или меньше, то есть наступило окончание партии
	{
		if (Type == CellType_White) // Если ход белых
		{
			if (WDamka > 2 && BDamka == 1) // Если у белых 3 или более дамок и у черных 1 дамка
				white++;
			else
				white = 0;
		}
		else // Если ход черных
		{
			if (BDamka > 2 && WDamka == 1) // Если у черных 3 или более дамок и у белых 1 дамка
				black++;
			else
				black = 0;
		}
	}
	if (white == 16 || black == 16) // Если прошлая ситуация простояла в течении 15 ходов игрока с момента ее установления
		return true;

	if (cells[NowXpos][NowYpos] == CellType_White_King || cells[NowXpos][NowYpos] == CellType_Black_King) // Если ход был сделан дамкой
	{
		if ((OldBChecker == BChecker) && (OldWChecker == WChecker) && (OldBDamka == BDamka) && (OldWDamka == WDamka)) // Если не происходило взятия или превращения, то есть соотношение сил не менялось
			n++;
		else
			n = 0;
	}
	else
		n = 0;
	if (n == 15) // Если в течении 15 ходов игроки делали ходы только дамками
		return true;

	if ((WDamka > 0) && (BDamka > 0)) // Если оба соперника имеют хотя бы 1 дамку
	{
		if ((OldBChecker == BChecker) && (OldWChecker == WChecker) && (OldBDamka == BDamka) && (OldWDamka == WDamka)) // Если не происходило взятия или превращения, то есть соотношение сил не менялось
		{
			if (sum == 2 || sum == 3) // Если количество фигур равно 2 или 3
				ThirdCheck++;
			if (sum == 4 || sum == 5) // Если количество фигур равно 4 или 5
				SecondCheck++;
			if (sum == 6 || sum == 7) // Если количество фигур равно 6 или 7
				FirstCheck++;
		}
		else
		{
			FirstCheck = 0;
			SecondCheck = 0;
			ThirdCheck = 0;
		}
	}
	else
	{
		FirstCheck = 0;
		SecondCheck = 0;
		ThirdCheck = 0;
	}
	// Если в течении 60 ходов предыдущяя позиция не менялась при 6 или 7 фигурах с момента ее наступления
	// Если в течении 30 ходов предыдущяя позиция не менялась при 4 или 5 фигурах с момента ее наступления
	// Если в течении 5 ходов предыдущяя позиция не менялась при 2 или 3 фигурах с момента ее наступления
	if (FirstCheck == 60 || SecondCheck == 30 || ThirdCheck == 5) 
		return true;

	OldBChecker = BChecker;
	OldWChecker = WChecker;
	OldBDamka = BDamka;
	OldWDamka = WDamka;

	return false;
}

bool TicTacBoard::CheckEndCondition(int& white, int& black, int& n, int& FirstCheck, int& SecondCheck, int& ThirdCheck)
{
	if (CheckVictory() || CheckDraw(white, black, n, FirstCheck, SecondCheck, ThirdCheck))
		return true;

	return false;
}
bool TicTacBoard::IsVictory()
{
	return bVictory;
}