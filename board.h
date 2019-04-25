#pragma once
#include "Snake.h"

enum cellType
{
	empty,
	xborder,
	yborder,
	food,
	lsnake,
	deadsnake,
};

class Board
{
	cellType m_board[31][31];
	bool m_bgameover;
	int m_foodx;
	int m_foody;
	int getRandomNumber(int min, int max);
	int m_score;
public:
	Board();
	void update(Snake &snake);
	void checkEat(Snake &snake);
	void checkDeath(Snake &snake);
	void newFood();
	bool snakeAlive();
	void print();
};
