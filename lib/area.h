#ifndef AREA_H
#define AREA_H

#include <vector>
#include "point.h"

class Area
{
public:
  Area(std::vector<Point> _borderPoints, int _areaValue);

  std::vector<Point> borderPoints;
  int areaValue;
  int minY;
  int minX;
  int maxY;
  int maxX;

  bool isInTheArea(Point point);

private:
  Area();

  std::vector<Point> findConvexSet(std::vector<Point> points);
  int calculatePosition(Point a, Point b, Point c);
};

#endif