#include "pch.h"
#include "TicTacHumanPlayer.h"

TicTacHumanPlayer::TicTacHumanPlayer()
{
}

TicTacHumanPlayer::~TicTacHumanPlayer()
{
}

void TicTacHumanPlayer::SetHumanColsRows(bool& closed)
{
	Zanavo: // <-----
	bool doing = true;
	bool select = false;
	bool rowscolsselected = false;
	int Num;
	int xpos1, ypos1, xpos2, ypos2;
	sf::Event event;

	while (doing)
	{

		Vector2i MousePos = Mouse::getPosition(*window);//забираем коорд курсора

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				closed = true;
				return;
			}

			if (event.type == Event::MouseButtonPressed) //если нажата клавиша мыши
				if (event.key.code == Mouse::Left) //а именно левая
				{
					xpos1 = MousePos.x; //забираем координату нажатия курсора Х
					ypos1 = MousePos.y; //и Y
					select = true;
				}

			if (select) //если выбрали объект
				if (event.type == Event::MouseButtonPressed) //если нажата клавиша мыши
					if (event.key.code == Mouse::Right) //а именно правая
					{
						xpos2 = MousePos.x; //забираем координату нажатия курсора Х
						ypos2 = MousePos.y; //и Y
						rowscolsselected = true;
						doing = false;
					}
		}
		if (rowscolsselected)
		{
			doing = false;
			break;
		}
	}

	if (rowscolsselected)
		for (int i = 0; i < 8; i++)
		{
			if (((63 + i * 63) <= xpos1) && (xpos1 <= (125 + i * 63)))
			{
				col1 = i;
			}
			if (((63 + i * 63) <= xpos2) && (xpos2 <= (125 + i * 63)))
			{
				col2 = i;
			}
		}

	for (int j = 0; j < 8; j++)
	{
		if (((114 + j * 63) <= ypos1) && (ypos1 <= (176 + j * 63)))
		{
			row1 = j;
		}
		if (((114 + j * 63) <= ypos2) && (ypos2 <= (176 + j * 63)))
		{
			row2 = j;
		}
	}

	if (row1 == 10 || row2 == 10 || col2 == 10 || col1 == 10)
		goto Zanavo; // ----->
}

int TicTacHumanPlayer::MakeMove()
{
	bool closed = false;
	SetHumanColsRows(closed);
	if (closed)
		return 3;

	if (this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp)) // проверка на возможность хода
	{
		this->board->CellMove(row1, col1, row2, col2, EatOpp); // сам ход
		if (EatOpp == true)
		{
			this->board->Revers(row1, col1, row2, col2, EatOpp); // сам ход
			this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp); // дополнительная проверка на возможность съесть еще одну шашку
		}

		if (EatOpp == false)
			return 1;
		if (EatOpp == true)
			return 2;
	}
	return 0;
}