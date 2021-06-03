#pragma once
#include"TicTacBoard.h"
#include"TicTacPlayer.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class TicTacManager
{
private:
	TicTacBoard* board;
	TicTacPlayer* player1;
	TicTacPlayer* player2;
	TicTacPlayer* currentPlayer;
	RenderWindow* window;
	bool bGamefinished = false;
public:
	TicTacManager();
	virtual ~TicTacManager();
	bool Init(RenderWindow& window);
	void ShowBoard(RenderWindow& window);
	void MakeMove(int& white, int& black, int& n, int& FirstCheck, int& SecondCheck, int& ThirdCheck, RenderWindow& window, bool& closed);
	bool IsGameFinished();
	void SetWindow(RenderWindow* window);
};

