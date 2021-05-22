#include "pch.h"
#include "TicTacPlayer.h"

TicTacPlayer::TicTacPlayer()
{
}

TicTacPlayer::~TicTacPlayer()
{
}

void TicTacPlayer::SetupPlayer(string name, CellType cellType)
{
	this->name = name;
	this->cellType = cellType;
}

void TicTacPlayer::SetBoard(TicTacBoard* board)
{
	this->board = board;
}

bool TicTacPlayer::MakeMove()
{
	unsigned int row1, col1, row2, col2;
	unsigned int b, d;
	char a, �;
	cout << "����� " << name << ", ��� ���..." << endl;
	cout << "������� ��������� �����, ������� �� ������ ������. ������ ����� ������: G4, H7, A2" << endl;
	cout << "������� �������: ";
	cin >> a;
	cout << "������� ������: ";
	cin >> b;
	row1 = 8 - b;
	switch (a)
	{
	case 'A':
		col1 = 0;
		break;
	case 'B':
		col1 = 1;
		break;
	case 'C':
		col1 = 2;
		break;
	case 'D':
		col1 = 3;
		break;
	case 'E':
		col1 = 4;
		break;
	case 'F':
		col1 = 5;
		break;
	case 'G':
		col1 = 6;
		break;
	case 'H':
		col1 = 7;
		break;
	default:
		break;
	}
	cout << endl;
	cout << "������� ���������� ����. ������ ����� ������: G4, H7, A2" << endl;
	cout << "������� �������: ";
	cin >> �;
	cout << "������� ������: ";
	cin >> d;
	row2 = 8 - d;
	switch (�)
	{
	case 'A':
		col2 = 0;
		break;
	case 'B':
		col2 = 1;
		break;
	case 'C':
		col2 = 2;
		break;
	case 'D':
		col2 = 3;
		break;
	case 'E':
		col2 = 4;
		break;
	case 'F':
		col2 = 5;
		break;
	case 'G':
		col2 = 6;
		break;
	case 'H':
		col2 = 7;
		break;
	default:
		break;
	}
	if (this->board->CkeckLegal(col1, row1, col2, row2, cellType)) // ��������
	{
		this->board->CellMove(col1, row1, col2, row2); // ��� ���
		return true;
	}
	return false;
}

string TicTacPlayer::GetName()
{
	return this->name;
}