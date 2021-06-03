#include "pch.h"
#include "TicTacManager.h"
#include "TicTacHumanPlayer.h"
#include "TicTacComputerPlayer.h"
#include <SFML/Graphics.hpp>

#pragma warning(disable : 4996)
using namespace sf;

TicTacManager::TicTacManager()
{

}

TicTacManager::~TicTacManager()
{
	delete this->player2;
	delete this->player1;
	delete this->board;
}

bool TicTacManager::Init(RenderWindow& window)
{
	Texture TextureWood;
	Sprite Wood;
	TextureWood.loadFromFile("images/Wood.jpg");
	Wood.setTexture(TextureWood);

	Font font;//����� 
	font.loadFromFile("CyrilicOld.TTF");//�������� ������ ������ ���� ������
	Text text1("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text1.setColor(sf::Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text1.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	Text text2("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text2.setColor(sf::Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text2.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	Text text3("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text3.setColor(sf::Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text3.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	Text text4("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text4.setColor(sf::Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text4.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	Text text5("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text5.setColor(sf::Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text5.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
	Text text6("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text6.setColor(sf::Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text6.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

	bool doing = true;
	int boardsize = 8;
	string playerName;
	int playertype1 = 0, playertype2 = 0;
	int Num = 0, com1 = 0, com2 = 0;
	this->board = new TicTacBoard(boardsize);

	while (doing)
	{
		//��������//
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return false;
			}
		}
		///////////

		window.draw(Wood);

		text1.setString("������� ���� ������� (������� ��� ���������):");//������ ������ ������
		text1.setPosition(10, 10);//������ ������� ������
		window.draw(text1);//����� ���� �����

		text1.setString("����� ������");//������ ������ ������
		text1.setPosition(10, 40);//������ ������� ������
		window.draw(text1);//����� ���� �����

		text2.setString("�������");//������ ������ ������
		text2.setPosition(10, 80);//������ ������� ������
		window.draw(text2);//����� ���� �����

		text3.setString("���������");//������ ������ ������
		text3.setPosition(200, 80);//������ ������� ������
		window.draw(text3);//����� ���� �����

		text1.setString("����� �������");//������ ������ ������
		text1.setPosition(10, 120);//������ ������� ������
		window.draw(text1);//����� ���� �����

		text4.setString("�������");//������ ������ ������
		text4.setPosition(10, 160);//������ ������� ������
		window.draw(text4);//����� ���� �����

		text5.setString("���������");//������ ������ ������
		text5.setPosition(200, 160);//������ ������� ������
		window.draw(text5);//����� ���� �����

		text6.setString("START");//������ ������ ������
		text6.setPosition(280, 300);//������ ������� ������
		window.draw(text6);//����� ���� �����

		if (com1 == 0) { text2.setColor(Color::Red); text3.setColor(Color::Red); }
		if (com1 == 1) { text2.setColor(Color(63, 224, 208)); text3.setColor(Color::Red); }
		if (com1 == 2) { text2.setColor(Color::Red); text3.setColor(Color(63, 224, 208)); }
		if (com2 == 0) { text4.setColor(Color::Red); text5.setColor(Color::Red); }
		if (com2 == 1) { text4.setColor(Color(63, 224, 208)); text5.setColor(Color::Red); }
		if (com2 == 2) { text4.setColor(Color::Red); text5.setColor(Color(63, 224, 208)); }
		text6.setColor(Color::Red);

		if (IntRect(10, 85, 85, 20).contains(Mouse::getPosition(window))) { text2.setColor(Color(63, 224, 208)); Num = 1; }
		if (IntRect(200, 85, 110, 20).contains(Mouse::getPosition(window))) { text3.setColor(Color(63, 224, 208)); Num = 2; }
		if (IntRect(10, 165, 85, 20).contains(Mouse::getPosition(window))) { text4.setColor(Color(63, 224, 208)); Num = 3; }
		if (IntRect(200, 165, 110, 20).contains(Mouse::getPosition(window))) { text5.setColor(Color(63, 224, 208)); Num = 4; }
		if (IntRect(300, 305, 60, 20).contains(Mouse::getPosition(window))) { text6.setColor(Color(63, 224, 208)); Num = 5; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (Num == 1) { com1 = 1; }
			if (Num == 2) { com1 = 2; }
			if (Num == 3) { com2 = 1; }
			if (Num == 4) { com2 = 2; }
			if (Num == 5 && com1 != 0 && com2 != 0)
			{
				doing = false;
			}
		}

		window.display();
	}
	playertype1 = com1;
	playertype2 = com2;

	if (playertype1 == 1)
		this->player1 = new TicTacHumanPlayer();
	else
		this->player1 = new TicTacComputerPlayer();

	if (playertype2 == 1)
		this->player2 = new TicTacHumanPlayer();
	else
		this->player2 = new TicTacComputerPlayer();

	this->player1->SetWindow(&window);
	this->player2->SetWindow(&window);

	playerName = "White";
	player1->SetupPlayer(playerName, CellType_White);

	playerName = "Black";
	player2->SetupPlayer(playerName, CellType_Black);
	player1->SetBoard(this->board);
	player2->SetBoard(this->board);
	board->SetCell();
	currentPlayer = player1;

	return true;
}


void TicTacManager::ShowBoard(RenderWindow& window)
{
	this->board->Show(window);
}

void TicTacManager::MakeMove(int& white, int& black, int& n, int& FirstCheck, int& SecondCheck, int& ThirdCheck, RenderWindow& window, bool& closed)
{

	Texture TextureBoard2;
	Sprite Board2;
	TextureBoard2.loadFromFile("images/Board-background.jpg");
	Board2.setTexture(TextureBoard2);
	Board2.setTextureRect(IntRect(0, 0, 626, 50));
	Board2.setPosition(0, 0);
	window.draw(Board2);
	
	Font font;//����� 
	font.loadFromFile("CyrilicOld.TTF");//�������� ������ ������ ���� ������
	Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setColor(sf::Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

	int possible = 0;

	ShowBoard(window);

    Here: // ����� ��� �������� <---

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			closed = true;
			window.close();
		}
	}
	if (possible == 3)
	{
		closed = true;
		return;
	}

	possible = currentPlayer->MakeMove();

	if (possible == 3)
	{
		closed = true;
		return;
	}

	window.clear();
	if(possible == 0) // �������� ������������ ����
	{
		text.setString("�� ��������� ���! ���������� ��� ���!");//������ ������ ������
		text.setPosition(10, 10);//������ ������� ������, ����� ������
		window.draw(Board2);
		window.draw(text);//����� ���� �����
		ShowBoard(window);
		goto Here; // ������� ������--->
	}

	if (possible == 2) // ���� ����� ������ ��� ���
	{
		text.setString("�� �������� ���� ��� ���!!!"); //������ ������ ������
		text.setPosition(10, 10);//������ ������� ������
		window.draw(Board2);
		window.draw(text);//����� ���� �����

		ShowBoard(window);
		goto Here; // ������� ������--->
	}

	if (this->board->CheckEndCondition(white, black, n, FirstCheck, SecondCheck, ThirdCheck))
	{
		CellType Type;
		if (this->board->IsVictory(Type))
		{
			if (Type == CellType_White)
			{
				text.setString("����� ��������!"); //������ ������ ������
				text.setPosition(10, 10);//������ ������� ������
				window.draw(Board2);
				window.draw(text);//����� ���� �����
			}
			if (Type == CellType_Black)
			{
				text.setString("������ ��������!"); //������ ������ ������
				text.setPosition(10, 10);//������ ������� ������
				window.draw(Board2);
				window.draw(text);//����� ���� �����
			}
		}
		else
		{
			text.setString("�����!");//������ ������ ������
			text.setPosition(10, 10);//������ ������� ������, ����� ������
			window.draw(Board2);
			window.draw(text);//����� ���� �����
		}
		this->bGamefinished = true;
		ShowBoard(window);
		return;
	}

	if (possible == 1) // ���� ���� ������ ������
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool TicTacManager::IsGameFinished()
{
	return bGamefinished;
}

void TicTacManager::SetWindow(RenderWindow* window)
{
	this->window = window;
}
