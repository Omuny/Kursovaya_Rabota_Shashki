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

	cout << "������� ��� ������, ��������� ������: ";
	getline(cin, playerName);
	player1->SetupPlayer(playerName, CellType_White);

	cout << "������� ��� ������, ��������� �������: ";
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

void TicTacManager::MakeMove(int& white, int& black, int& n, int& FirstCheck, int& SecondCheck, int& ThirdCheck)
{
	int possible;

	ShowBoard();
	Here: // ����� ��� �������� <---
	possible = currentPlayer->MakeMove();
	system("cls");

	if(possible == 0) // �������� ������������ ����
	{
		cout << "������������ ���, ���������� ��� ���!!!" << endl;
		ShowBoard();
		goto Here; // ������� ������--->
	}

	if (possible == 2) // ���� ����� ������ ��� ���
	{
		cout << "����� " << currentPlayer->GetName() << " �� �������� ���� ��� ���!!!" << endl;
		ShowBoard();
		goto Here; // ������� ������--->
	}

	if (this->board->CheckEndCondition(white, black, n, FirstCheck, SecondCheck, ThirdCheck))
	{
		if (this->board->IsVictory())
			cout << "����� " << currentPlayer->GetName() << " �������!" << endl;
		else
			cout << "�����!" << endl;
		this->bGamefinished = true;
		ShowBoard();
		return;
	}

	if (possible == 1) // ���� ���� ������ ������
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool TicTacManager::IsGameFinished()
{
	return bGamefinished;
}