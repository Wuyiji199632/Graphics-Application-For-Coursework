#pragma once
class Point
{
public:
	Point();
	Point(int x,int y);
	Point(const Point& point);
	~Point();


public:
	int m_x=0, m_y=0;
};

