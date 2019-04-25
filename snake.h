#pragma once
#include <vector>

enum orientation
{
	up,
	down,
	left,
	right,
};

struct Segment
{
	int m_x;
	int m_y;
	orientation m_front;
	Segment(int x, int y, orientation front)
		: m_x{ x }, m_y{ y }, m_front{ front }{}
};

class Snake
{
private:
	std::vector<Segment> m_snake;
	orientation turndir;
public:
	Snake();
	float speed;
	void move();
	void setTurn(orientation o);
	void turn();
	void grow();
	int length();
	Segment &operator[](const int index);
};
