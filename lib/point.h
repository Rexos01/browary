#ifndef POINT_H
#define POINT_H

struct Point
{
  int x;
  int y;

  Point(int _x, int _y);

  // Point() {}

  friend bool operator==(const Point a, const Point b);
  friend bool operator!=(const Point a, const Point b);
};

#endif