#include "pch.h"
#include "Snake.h"


Snake::Snake() : turndir{ left }, speed{ 1.0f }
{
	Segment s1(20, 15, left);
	Segment s2(21, 15, left);
	Segment s3(22, 15, left);
	m_snake.push_back(s1);
	m_snake.push_back(s2);
	m_snake.push_back(s3);
}

void Snake::move()
{
	for (int index{ static_cast<int>(m_snake.size()) - 1 }; index > 0; --index)
	{
		m_snake[index] = m_snake[index - 1];
	}
	switch (m_snake[0].m_front)
	{
	case up:
		++m_snake[0].m_y;
		break;
	case down:
		--m_snake[0].m_y;
		break;
	case left:
		--m_snake[0].m_x;
		break;
	case right:
		++m_snake[0].m_x;
	}
}

void Snake::setTurn(orientation o)
{
	turndir = o;
}

void Snake::turn()
{
	m_snake[0].m_front = turndir;
}

void Snake::grow()
{
	Segment &last{ m_snake[m_snake.size() - 1] };
	if (last.m_front == up)
		m_snake.push_back(Segment(last.m_x, last.m_y-1, last.m_front));
	if (last.m_front == down)
		m_snake.push_back(Segment(last.m_x, last.m_y + 1, last.m_front));
	if (last.m_front == left)
		m_snake.push_back(Segment(last.m_x+1, last.m_y, last.m_front));
	if (last.m_front == right)
		m_snake.push_back(Segment(last.m_x-1, last.m_y, last.m_front));
}

int Snake::length()
{
	return m_snake.size();
}

Segment &Snake::operator[](const int index)
{
	return m_snake[index];
}
