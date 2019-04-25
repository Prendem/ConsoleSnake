#include "pch.h"
#include <iostream>
#include <chrono>
#include <Windows.h>
#include "Snake.h"
#include "Board.h"

void getUserInput(Snake &snake)
{
	std::chrono::time_point<std::chrono::steady_clock> begin, end;
	begin = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration;
	do
	{
		if (GetKeyState(VK_UP) & 0x8000 && (snake[0].m_front==left || snake[0].m_front == right))
			snake.setTurn(up);
		if (GetKeyState(VK_DOWN) & 0x8000 && (snake[0].m_front == left || snake[0].m_front == right))
			snake.setTurn(down);
		if (GetKeyState(VK_LEFT) & 0x8000 && (snake[0].m_front == up || snake[0].m_front == down))
			snake.setTurn(left);
		if (GetKeyState(VK_RIGHT) & 0x8000 && (snake[0].m_front == up || snake[0].m_front == down))
			snake.setTurn(right);
		
		end = std::chrono::high_resolution_clock::now();
		duration = end - begin;
	} while (duration.count() <= 0.25f/(snake.speed));
}

int main()
{

		Board b;
		Snake s;
		b.update(s);
		b.print();
		Sleep(500);
		system("cls");
		while (b.snakeAlive())
		{
			s.turn();
			s.move();
			b.checkDeath(s);
			b.checkEat(s);
			b.update(s);
			b.print();
			getUserInput(s);
			system("cls");
		}
		b.update(s);
		b.print();
}
