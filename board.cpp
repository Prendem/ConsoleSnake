#include "pch.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int Board::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

Board::Board() : m_bgameover{ false }, m_foodx{ 5 }, m_foody{ 15 }, m_score{ 0 }
{
	for (int yindex{ 0 }; yindex < 31; ++yindex)
	{
		m_board[0][yindex] = yborder;
		m_board[30][yindex] = yborder;
	}

	for (int xindex{ 0 }; xindex < 31; ++xindex)
	{
		m_board[xindex][0] = xborder;
		m_board[xindex][30] = xborder;
	}

	for (int xindex{ 1 }; xindex < 30; ++xindex)
		for (int yindex{ 1 }; yindex < 30; ++yindex)
			m_board[xindex][yindex] = empty;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::rand();

	m_board[m_foodx][m_foody] = food;
}

void Board::update(Snake &snake)
{
	for (int yindex{1}; yindex < 30; ++yindex)
		for (int xindex{ 1 }; xindex < 30; ++xindex)
		{
			if (m_board[xindex][yindex] == food)
				continue;
			else
				m_board[xindex][yindex] = empty;
		}
	if (snakeAlive())
	{
		for (int index{ 0 }; index < snake.length(); ++index)
			m_board[snake[index].m_x][snake[index].m_y] = lsnake;
	}
	else
	{
		for (int index{ 0 }; index < snake.length(); ++index)
			m_board[snake[index].m_x][snake[index].m_y] = deadsnake;
	}

}

void Board::checkEat(Snake &snake)
{
	if (snake[0].m_x == m_foodx && snake[0].m_y == m_foody)
	{
		snake.grow();
		newFood();
		++m_score;
		snake.speed += 0.1f;
	}
}

void Board::checkDeath(Snake &snake)
{
	if (snake[0].m_x == 0 || snake[0].m_x == 30 || snake[0].m_y == 0 || snake[0].m_y == 30)
		m_bgameover = true;
	for (int index{ 1 }; index < snake.length(); ++index)
	{
		if (snake[0].m_x == snake[index].m_x && snake[0].m_y == snake[index].m_y)
			m_bgameover = true;
	}
}

void Board::newFood()
{
	int x;
	int y;
	bool validSpot{ false };
	while (!validSpot)
	{
		x = getRandomNumber(1, 30);
		y = getRandomNumber(1, 30);
		if (m_board[x][y] == empty)
			validSpot = true;
	}
	m_foodx = x;
	m_foody = y;
	m_board[m_foodx][m_foody] = food;
}

bool Board::snakeAlive()
{
	return !m_bgameover;
}

void Board::print()
{
	for (int y{ 30 }; y > -1; --y)
	{
		for (int x{ 0 }; x < 31; ++x)
		{
			switch (m_board[x][y])
			{
			case (empty):
				std::cout << "  ";
				break;
			case(xborder):
				std::cout << "# ";
				break;
			case (yborder):
				std::cout << "# ";
				break;
			case (food):
				std::cout << "x ";
				break;
			case (lsnake):
				std::cout << "O ";
				break;
			case (deadsnake):
				std::cout << "X ";
				break;
			}
		}
		std::cout << "\n";
	}
	std::cout << "Score: " << m_score;
}
