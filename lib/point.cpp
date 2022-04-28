#include "point.h"

Point::Point(int _x, int _y)
{
  x = _x;
  y = _y;
}

bool operator==(const Point a, const Point b)
{
  return a.x == b.x && b.y == b.y;
}

bool operator!=(const Point a, const Point b)
{
  return a.x != b.x || a.y != b.y;
}