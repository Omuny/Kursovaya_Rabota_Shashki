// Laba_Kursach.cpp
//Левый клик мыши ---> выбрать шашку для хода
//Правый клик мыши--->выбрать поле куда пойдет шашка

#include <SFML/Graphics.hpp>
#include "pch.h"
#include "TicTacManager.h"
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(626, 676), "Shashky_8x8");
	sf::Event event;

	setlocale(LC_ALL, "Russian");
	TicTacManager manager;
	manager.SetWindow(&window);

	if (!manager.Init(window))
	{
		return 0;
	}
	window.clear();

	bool closed = false;
	int white = 0, black = 0, n = 0, FirstCheck = 0, SecondCheck = 0, ThirdCheck = 0; // Счетчики для проверки ничьи
	do
	{
		manager.MakeMove(white, black, n, FirstCheck, SecondCheck, ThirdCheck, window, closed);
		if (closed == true)
			break;
	} while (!manager.IsGameFinished());

	if(!closed)
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}

	window.close();
	return 0;
}
