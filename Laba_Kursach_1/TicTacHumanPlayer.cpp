#include "pch.h"
#include "TicTacHumanPlayer.h"

TicTacHumanPlayer::TicTacHumanPlayer()
{
}

TicTacHumanPlayer::~TicTacHumanPlayer()
{
}

int TicTacHumanPlayer::MakeMove()
{
	int row1, col1, row2, col2;
	int b, d;
	bool check_a = false, check_c = false;
	char a, �;
	cout << "����� " << this->name << ", ��� ���..." << endl;
	cout << "������� ��������� �����, ������� �� ������ ������. ������ ����� ������: G4, h7, A2, f8" << endl;
	cout << "������� �������: ";
	cin >> a;
	cout << "������� ������: ";
	cin >> b;
	row1 = 8 - b;
	// �������� ����� �������� ��������
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
		check_a = true;
		break;
	}
	// �������� ����� ���������� ��������
	switch (a)
	{
	case 'a':
		col1 = 0;
		break;
	case 'b':
		col1 = 1;
		break;
	case 'c':
		col1 = 2;
		break;
	case 'd':
		col1 = 3;
		break;
	case 'e':
		col1 = 4;
		break;
	case 'f':
		col1 = 5;
		break;
	case 'g':
		col1 = 6;
		break;
	case 'h':
		col1 = 7;
		break;
	default:
		if (check_a == true) // ���� �� ���� �� ���� �� �������
			return 0;
		else
			break;
	}

	cout << endl;
	cout << "������� ���������� ����. ������ ����� ������: G4, H7, A2" << endl;
	cout << "������� �������: ";
	cin >> �;
	cout << "������� ������: ";
	cin >> d;
	row2 = 8 - d;
	// �������� ����� �������� ��������
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
		check_c = true;
		break;
	}
	// �������� ����� ���������� ��������
	switch (�)
	{
	case 'a':
		col2 = 0;
		break;
	case 'b':
		col2 = 1;
		break;
	case 'c':
		col2 = 2;
		break;
	case 'd':
		col2 = 3;
		break;
	case 'e':
		col2 = 4;
		break;
	case 'f':
		col2 = 5;
		break;
	case 'g':
		col2 = 6;
		break;
	case 'h':
		col2 = 7;
		break;
	default:
		if (check_c == true) // ���� �� ���� �� ���� �� �������
			return 0;
		else
			break;
	}
	cout << endl;
	if (0 > row1 || row1 > 7 || 0 > row2 || row2 > 7) // �������� ������������ ��������� ������
		return 0;

	if (this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp)) // �������� �� ����������� ����
	{
		this->board->CellMove(row1, col1, row2, col2, EatOpp); // ��� ���
		if(EatOpp == true)
			this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp); // �������������� �������� �� ����������� ������ ��� ���� �����

		if (EatOpp == false)
			return 1;
		if (EatOpp == true)
			return 2;
	}
	return 0;
}