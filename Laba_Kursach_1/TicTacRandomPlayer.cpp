#include "TicTacRandomPlayer.h"
#include "pch.h"

TicTacRandomPlayer::TicTacRandomPlayer()
{
}

TicTacRandomPlayer::~TicTacRandomPlayer()
{
}

int TicTacRandomPlayer::MakeMove()
{
	int row1, col1, row2, col2;
Tuda: // <-----
	row1 = (int)(rand() % 8);
	col1 = (int)(rand() % 8);
	row2 = (int)(rand() % 8);
	col2 = (int)(rand() % 8);

	if (((col2 % 2 == 0) && (row2 % 2 == 0)) || ((col2 % 2 != 0) && (row2 % 2 != 0))) // ���� ����� �� ����� ������
		goto Tuda; // ---->
	if (((col1 % 2 == 0) && (row1 % 2 == 0)) || ((col1 % 2 != 0) && (row1 % 2 != 0))) // ����� ����� ����� �� �� ��������
		goto Tuda; // ---->
	if ((col1 == col2) && (row1 == row2)) // ����� �� ���� ������ - ��������
		goto Tuda; // ---->

	if (this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp)) // �������� �� ����������� ����
	{
		this->board->CellMove(row1, col1, row2, col2, EatOpp); // ��� ���
		if (EatOpp == true)
		{
			this->board->Revers(row1, col1, row2, col2, EatOpp); // ��� ���
			this->board->CkeckLegal(row1, col1, row2, col2, cellType, EatOpp); // �������������� �������� �� ����������� ������ ��� ���� �����
		}

		if (EatOpp == false)
			return 1; // ��� ������
		if (EatOpp == true)
			return 2; // ���� ����������� ������ ���
	}
	return 0; // �� ���������� ���
}
