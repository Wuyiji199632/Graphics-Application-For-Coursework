#include "Point.h"

Point::Point():m_x(0),m_y(0)
{
}

Point::Point(int x,int y):m_x(x),m_y(y)
{
}

Point::Point(const Point& point) :m_x(point.m_x), m_y(point.m_y)
{
}

Point::~Point()
{
}
