#include "pch.h"
#include "TicTacBoard.h"

TicTacBoard::TicTacBoard(unsigned int size)
{
	this->boardsize = size;
	cells = new CellType * [size];
	for (unsigned int i = 0; i < size; i++)
		cells[i] = new CellType[size];
	for (unsigned int i = 0; i < size; i++)
		for (unsigned int j = 0; j < size; j++)
			cells[i][j] = CellType_Empty;
}

TicTacBoard::~TicTacBoard()
{
	for (unsigned int i = 0; i < boardsize; i++)
		delete[]cells[i];
	delete[]cells;
}

void TicTacBoard::Show()
{
	cout << endl;
	cout << "     ";
	cout << " A B C D E F G H\t\W - Белая шашка, B - черная. V - Белая дамка, P - черная. ";
	cout << endl;
	cout << endl;

	for (unsigned int i = 0; i < boardsize; i++)
	{
		cout << 8-i << "    |";
		for (unsigned int j = 0; j < boardsize; j++)
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

bool TicTacBoard::CkeckLegal(unsigned int xpos1, unsigned int ypos1, unsigned int xpos2, unsigned int ypos2, CellType Type) // проверка возможности хода
{
	/* !!!!! Внимание. Важно! Я перепутал местами xpos и ypos, поэтому теперь xpos отвечает за строки, а ypos отвечает за столбцы !!!!! */

	if (cells[xpos1][ypos1] == CellType_Empty) // Если пытаемся пойти пустой клеткой
		return false;
	if (cells[xpos1][ypos1] != Type) // Попытка пойти шашкой не своего цвета
		return false;
	if (((ypos2 % 2 == 0) && (xpos2 % 2 == 0)) || ((ypos2 % 2 != 0) && (xpos2 % 2 != 0))) // если поле белое
		return false;
	if ((xpos2 < 0) || (xpos2 > boardsize) || (ypos2 < 0) || (ypos2 > boardsize)) // если выходим за пределы доски
		return false;
	if (cells[xpos2][ypos2] != CellType_Empty) // если на клетке есть другая шашка
		return false;
	if ((xpos2 == xpos1) && (ypos2 == ypos1)) // попытка пойти на ту же клетку
		return false;

	int a; // шашка которой производится ход
	bool EatApportunity = false; // Возможность съесть шашку

	if (cells[xpos1][ypos1] == CellType_White)
		a = 1;
	if (cells[xpos1][ypos1] == CellType_Black)
		a = 2;
	if (cells[xpos1][ypos1] == CellType_White_King)
		a = 3;
	if (cells[xpos1][ypos1] == CellType_Black_King)
		a = 4;

	switch (a) // проверка край доски
	{
	case 1:
		if (xpos1 == 0)
		{
			cout << "Ход этой шашкой не возможен" << endl;
			return false;
		}
		break;
	case 2:
		if (xpos1 == 7)
		{
			cout << "Ход этой шашкой не возможен" << endl;
			return false;
		}
		break;
	default:
		break;
	}

	// Проверка на возможность съесть другую шашку
	switch (a) // проверка возможности съесть
	{
	case 1: //белая шашка
		if (xpos1 == 0 || ypos1 == 0 || xpos1 == 7 || ypos1 == 7) // Внешний квадрат
		{
			if ((xpos1 == 0) && (ypos1 == 1) || (xpos1 == 1) && (ypos1 == 0)) // Две клетки в левом верхнем углу
			{
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_Black || cells[xpos1 + 1][ypos1 + 1] == CellType_Black_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 6) && (ypos1 == 7) || (xpos1 == 7) && (ypos1 == 6)) // Две клетки в правом нижнем углу
			{
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_Black || cells[xpos1 - 1][ypos1 - 1] == CellType_Black_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 7) && (ypos1 == 0)) // Клетка в левом нижнем углу
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_Black || cells[xpos1 - 1][ypos1 + 1] == CellType_Black_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 0) && (ypos1 == 7)) // Клетка в правом верхнем углу
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_Black || cells[xpos1 + 1][ypos1 - 1] == CellType_Black_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 7) // Нижние две клетки
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_Black || cells[xpos1 - 1][ypos1 + 1] == CellType_Black_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_Black || cells[xpos1 - 1][ypos1 - 1] == CellType_Black_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 0) // Верхние две клетки
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_Black || cells[xpos1 + 1][ypos1 - 1] == CellType_Black_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_Black || cells[xpos1 + 1][ypos1 + 1] == CellType_Black_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 0) // Левые две клетки
			{
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_Black || cells[xpos1 + 1][ypos1 + 1] == CellType_Black_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_Black || cells[xpos1 - 1][ypos1 + 1] == CellType_Black_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 7) // Правые две клетки
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_Black || cells[xpos1 + 1][ypos1 - 1] == CellType_Black_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_Black || cells[xpos1 - 1][ypos1 - 1] == CellType_Black_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
		}
		if (xpos1 == 1 || ypos1 == 1 || xpos1 == 6 || ypos1 == 6) //Серединный квадрат
		{
			if ((xpos1 == 6) && (ypos1 == 1)) // Нижняя левая угловая клетка
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_Black || cells[xpos1 - 1][ypos1 + 1] == CellType_Black_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 1) && (ypos1 == 6)) // Верхняя правая угловая клетка 
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_Black || cells[xpos1 + 1][ypos1 - 1] == CellType_Black_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 1) // Левые две клетки
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_Black || cells[xpos1 - 1][ypos1 + 1] == CellType_Black_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_Black || cells[xpos1 + 1][ypos1 + 1] == CellType_Black_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 6) // Правые две клетки
			{
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_Black || cells[xpos1 - 1][ypos1 - 1] == CellType_Black_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_Black || cells[xpos1 + 1][ypos1 - 1] == CellType_Black_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 1) // Верхние две клетки
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_Black || cells[xpos1 + 1][ypos1 - 1] == CellType_Black_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_Black || cells[xpos1 + 1][ypos1 + 1] == CellType_Black_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 6) // Нижние две клетки
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_Black || cells[xpos1 - 1][ypos1 + 1] == CellType_Black_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_Black || cells[xpos1 - 1][ypos1 - 1] == CellType_Black_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}

		}
		else // Центральный квадрат
		{
			if (cells[xpos1 + 1][ypos1 + 1] == CellType_Black || cells[xpos1 + 1][ypos1 + 1] == CellType_Black_King) // Проверка правой нижней клетки
			{
				if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
						return true;
				}
				if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
						return false;
			}
			if (cells[xpos1 - 1][ypos1 - 1] == CellType_Black || cells[xpos1 - 1][ypos1 - 1] == CellType_Black_King) // Проверка левой верхнней клетки клетки
			{
				if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
						return true;
				}
				if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
						return false;
			}
			if (cells[xpos1 + 1][ypos1 - 1] == CellType_Black || cells[xpos1 + 1][ypos1 - 1] == CellType_Black_King) // Проверка левой нижней клетки
			{
				if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
						return true;
				}
				if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
						return false;
			}
			if (cells[xpos1 - 1][ypos1 + 1] == CellType_Black || cells[xpos1 - 1][ypos1 + 1] == CellType_Black_King) // Проверка правой верхней клетки
			{
				if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
						return true;
				}
				if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
						return false;
			}
			if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
				return false;
		} 
		break;

	case 2: // черная шашка
		if (xpos1 == 0 || ypos1 == 0 || xpos1 == 7 || ypos1 == 7) // Внешний квадрат
		{
			if ((xpos1 == 0) && (ypos1 == 1) || (xpos1 == 1) && (ypos1 == 0)) // Две клетки в левом верхнем углу
			{
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_White || cells[xpos1 + 1][ypos1 + 1] == CellType_White_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 6) && (ypos1 == 7) || (xpos1 == 7) && (ypos1 == 6)) // Две клетки в правом нижнем углу
			{
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_White || cells[xpos1 - 1][ypos1 - 1] == CellType_White_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 7) && (ypos1 == 0)) // Клетка в левом нижнем углу
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_White || cells[xpos1 - 1][ypos1 + 1] == CellType_White_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 0) && (ypos1 == 7)) // Клетка в правом верхнем углу
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_White || cells[xpos1 + 1][ypos1 - 1] == CellType_White_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 7) // Нижние две клетки
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_White || cells[xpos1 - 1][ypos1 + 1] == CellType_White_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_White || cells[xpos1 - 1][ypos1 - 1] == CellType_White_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 0) // Верхние две клетки
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_White || cells[xpos1 + 1][ypos1 - 1] == CellType_White_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_White || cells[xpos1 + 1][ypos1 + 1] == CellType_White_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 0) // Левые две клетки
			{
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_White || cells[xpos1 + 1][ypos1 + 1] == CellType_White_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_White || cells[xpos1 - 1][ypos1 + 1] == CellType_White_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 7) // Правые две клетки
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_White || cells[xpos1 + 1][ypos1 - 1] == CellType_White_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_White || cells[xpos1 - 1][ypos1 - 1] == CellType_White_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
		}
		if (xpos1 == 1 || ypos1 == 1 || xpos1 == 6 || ypos1 == 6) //Серединный квадрат
		{
			if ((xpos1 == 6) && (ypos1 == 1)) // Нижняя левая угловая клетка
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_White || cells[xpos1 - 1][ypos1 + 1] == CellType_White_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if ((xpos1 == 1) && (ypos1 == 6)) // Верхняя правая угловая клетка 
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_White || cells[xpos1 + 1][ypos1 - 1] == CellType_White_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 1) // Левые две клетки
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_White || cells[xpos1 - 1][ypos1 + 1] == CellType_White_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_White || cells[xpos1 + 1][ypos1 + 1] == CellType_White_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (ypos1 == 6) // Правые две клетки
			{
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_White || cells[xpos1 - 1][ypos1 - 1] == CellType_White_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_White || cells[xpos1 + 1][ypos1 - 1] == CellType_White_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 1) // Верхние две клетки
			{
				if (cells[xpos1 + 1][ypos1 - 1] == CellType_White || cells[xpos1 + 1][ypos1 - 1] == CellType_White_King) // Проверка левой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (cells[xpos1 + 1][ypos1 + 1] == CellType_White || cells[xpos1 + 1][ypos1 + 1] == CellType_White_King) // Проверка правой нижней клетки
				{
					if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}
			if (xpos1 == 6) // Нижние две клетки
			{
				if (cells[xpos1 - 1][ypos1 + 1] == CellType_White || cells[xpos1 - 1][ypos1 + 1] == CellType_White_King) // Проверка правой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
							return false;
				}
				if (cells[xpos1 - 1][ypos1 - 1] == CellType_White || cells[xpos1 - 1][ypos1 - 1] == CellType_White_King) // Проверка левой верхней клетки
				{
					if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
					{
						EatApportunity = true;
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return true;
					}
					if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
						if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
							return false;
				}
				if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
					return false;
			}

		}
		else // Центральный квадрат
		{
			if (cells[xpos1 + 1][ypos1 + 1] == CellType_White || cells[xpos1 + 1][ypos1 + 1] == CellType_White_King) // Проверка правой нижней клетки
			{
				if (cells[xpos1 + 2][ypos1 + 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
						return true;
				}
				if (cells[xpos1 + 2][ypos1 + 2] != CellType_Empty)
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 + 2))
						return false;
			}
			if (cells[xpos1 - 1][ypos1 - 1] == CellType_White || cells[xpos1 - 1][ypos1 - 1] == CellType_White_King) // Проверка левой верхнней клетки клетки
			{
				if (cells[xpos1 - 2][ypos1 - 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
						return true;
				}
				if (cells[xpos1 - 2][ypos1 - 2] != CellType_Empty)
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 - 2))
						return false;
			}
			if (cells[xpos1 + 1][ypos1 - 1] == CellType_White || cells[xpos1 + 1][ypos1 - 1] == CellType_White_King) // Проверка левой нижней клетки
			{
				if (cells[xpos1 + 2][ypos1 - 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
						return true;
				}
				if (cells[xpos1 + 2][ypos1 - 2] != CellType_Empty)
					if ((xpos2 == xpos1 + 2) && (ypos2 == ypos1 - 2))
						return false;
			}
			if (cells[xpos1 - 1][ypos1 + 1] == CellType_White || cells[xpos1 - 1][ypos1 + 1] == CellType_White_King) // Проверка правой верхней клетки
			{
				if (cells[xpos1 - 2][ypos1 + 2] == CellType_Empty)
				{
					EatApportunity = true;
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
						return true;
				}
				if (cells[xpos1 - 2][ypos1 + 2] != CellType_Empty)
					if ((xpos2 == xpos1 - 2) && (ypos2 == ypos1 + 2))
						return false;
			}
			if (EatApportunity == true) // Если не съели ни одну шашку, при возможности, то неверный ход
				return false;
		}
		break;

	case 3: // белая дамка
		break;

	case 4: // черная дамка
		break;

	default:
		break;;
	}

	if (a == 1) // Обычный ход белой шашки
	{
		if ((xpos2 < xpos1) || (xpos2 == xpos1 - 1))
			if ((ypos2 == ypos1 - 1) || (ypos2 == ypos1 + 1))
				return true;
		return false;
	}
	if (a == 2) // Обычный ход черной шашки
	{
		if ((xpos2 > xpos1) || (xpos2 == xpos1 + 1))
			if ((ypos2 == ypos1 - 1) || (ypos2 == ypos1 + 1))
				return true;
		return false;
	}
	
}

void TicTacBoard::CellMove(unsigned int xpos1, unsigned int ypos1, unsigned int xpos2, unsigned int ypos2)
{
	CellType type;
	int a;

	if(ypos1 > ypos2)
		a = fmod(ypos1,ypos2); // Находим разницу между строками
	if (ypos1 < ypos2)
		a = fmod(ypos2, ypos1);

	if ((cells[xpos1][ypos1] == CellType_Black) || (cells[xpos1][ypos1] == CellType_White))
	{
		if (a == 1) // если обычный ход
		{
			type = cells[xpos1][ypos1];
			cells[xpos1][ypos1] = CellType_Empty;
			cells[xpos2][ypos2] = type;
		}
		if (a == 2) // если съедаем шашку
		{
			type = cells[xpos1][ypos1];
			cells[xpos1][ypos1] = CellType_Empty;

			if (xpos1 > xpos2)
				if (ypos1 > ypos2)
					cells[xpos1 - 1][ypos1 - 1] == CellType_Empty; // если едим в лево вверх
				else
					cells[xpos1 - 1][ypos1 + 1] == CellType_Empty; // если едим в право вверх
			else
				if (ypos1 > ypos2)
					cells[xpos1 + 1][ypos1 - 1] == CellType_Empty; // если едим в лево вниз
				else
					cells[xpos1 + 1][ypos1 + 1] == CellType_Empty; // если едим в право вниз

			cells[xpos2][ypos2] = type;
		}
	}
}
