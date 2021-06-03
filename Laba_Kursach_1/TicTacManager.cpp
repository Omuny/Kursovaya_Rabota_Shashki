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

	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
	Text text1("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text1.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text1.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	Text text2("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text2.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text2.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	Text text3("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text3.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text3.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	Text text4("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text4.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text4.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	Text text5("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text5.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text5.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	Text text6("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text6.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text6.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	bool doing = true;
	int boardsize = 8;
	string playerName;
	int playertype1 = 0, playertype2 = 0;
	int Num = 0, com1 = 0, com2 = 0;
	this->board = new TicTacBoard(boardsize);

	while (doing)
	{
		//Заглушка//
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

		text1.setString("Введите типы игроков (Человек или Компьютер):");//задает строку тексту
		text1.setPosition(10, 10);//задаем позицию текста
		window.draw(text1);//рисую этот текст

		text1.setString("Игрок белыми");//задает строку тексту
		text1.setPosition(10, 40);//задаем позицию текста
		window.draw(text1);//рисую этот текст

		text2.setString("Человек");//задает строку тексту
		text2.setPosition(10, 80);//задаем позицию текста
		window.draw(text2);//рисую этот текст

		text3.setString("Компьютер");//задает строку тексту
		text3.setPosition(200, 80);//задаем позицию текста
		window.draw(text3);//рисую этот текст

		text1.setString("Игрок черными");//задает строку тексту
		text1.setPosition(10, 120);//задаем позицию текста
		window.draw(text1);//рисую этот текст

		text4.setString("Человек");//задает строку тексту
		text4.setPosition(10, 160);//задаем позицию текста
		window.draw(text4);//рисую этот текст

		text5.setString("Компьютер");//задает строку тексту
		text5.setPosition(200, 160);//задаем позицию текста
		window.draw(text5);//рисую этот текст

		text6.setString("START");//задает строку тексту
		text6.setPosition(280, 300);//задаем позицию текста
		window.draw(text6);//рисую этот текст

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
	
	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.TTF");//передаем нашему шрифту файл шрифта
	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(sf::Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	int possible = 0;

	ShowBoard(window);

    Here: // Лейбл для перехода <---

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
	if(possible == 0) // проверка правильности хода
	{
		text.setString("Не возможный ход! Попробуйте еще раз!");//задает строку тексту
		text.setPosition(10, 10);//задаем позицию текста, центр камеры
		window.draw(Board2);
		window.draw(text);//рисую этот текст
		ShowBoard(window);
		goto Here; // Переход отсюда--->
	}

	if (possible == 2) // если можно съесть еще раз
	{
		text.setString("Вы обязанны есть еще раз!!!"); //задает строку тексту
		text.setPosition(10, 10);//задаем позицию текста
		window.draw(Board2);
		window.draw(text);//рисую этот текст

		ShowBoard(window);
		goto Here; // Переход отсюда--->
	}

	if (this->board->CheckEndCondition(white, black, n, FirstCheck, SecondCheck, ThirdCheck))
	{
		CellType Type;
		if (this->board->IsVictory(Type))
		{
			if (Type == CellType_White)
			{
				text.setString("Белые победили!"); //задает строку тексту
				text.setPosition(10, 10);//задаем позицию текста
				window.draw(Board2);
				window.draw(text);//рисую этот текст
			}
			if (Type == CellType_Black)
			{
				text.setString("Черные победили!"); //задает строку тексту
				text.setPosition(10, 10);//задаем позицию текста
				window.draw(Board2);
				window.draw(text);//рисую этот текст
			}
		}
		else
		{
			text.setString("Ничья!");//задает строку тексту
			text.setPosition(10, 10);//задаем позицию текста, центр камеры
			window.draw(Board2);
			window.draw(text);//рисую этот текст
		}
		this->bGamefinished = true;
		ShowBoard(window);
		return;
	}

	if (possible == 1) // если есть больше нельзя
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
