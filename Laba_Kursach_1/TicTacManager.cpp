#include "pch.h"
#include "TicTacManager.h"

TicTacManager::TicTacManager()
{

}

TicTacManager::~TicTacManager()
{
	delete this->player2;
	delete this->player1;
	delete this->board;
}

bool TicTacManager::Init()
{
	int boardsize = 8;
	string playerName;

	this->board = new TicTacBoard(boardsize);
	this->player1 = new TicTacPlayer();
	this->player2 = new TicTacPlayer();
	//cin.ignore();

	cout << "Введите имя игрока, играющего белыми: ";
	getline(cin, playerName);
	player1->SetupPlayer(playerName, CellType_White);

	cout << "Введите имя игрока, играющего черными: ";
	getline(cin, playerName);
	player2->SetupPlayer(playerName, CellType_Black);
	player1->SetBoard(this->board);
	player2->SetBoard(this->board);
	board->SetCell();
	currentPlayer = player1;

	return true;
}

void TicTacManager::ShowBoard()
{
	this->board->Show();
}

void TicTacManager::MakeMove()
{
	int possible;
	string name;

	ShowBoard();
	Here: // Лейбл для перехода
	possible = currentPlayer->MakeMove(name);
	system("cls");

	if(possible == 0) // проверка правильности хода
	{
		cout << "Недопустимый ход, попробуйте еще раз!!!" << endl;
		ShowBoard();
		goto Here; // Переход отсюда
	}

	if (possible == 2) // если можно съесть еще раз
	{
		cout << "Игрок " << name << " вы обязанны есть еще раз!!!" << endl;
		ShowBoard();
		goto Here; // Переход отсюда
	}

	if (possible == 1) // если есть больше нельзя
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
}