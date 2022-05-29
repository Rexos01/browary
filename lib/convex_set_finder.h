#ifndef CONVEX_SET_FINDER_H
#define CONVEX_SET_FINDER_H

#include <vector>
#include "point.h"

class ConvexSetFinder
{

public:
  static std::vector<Point> findConvexSet(std::vector<Point> points);

private:
  static bool compareXMin(Point a, Point b);
  static bool compareYMin(Point a, Point b);
  static bool compareXMax(Point a, Point b);
  static bool compareYMax(Point a, Point b);

  static std::vector<Point> getMinimalX(std::vector<Point> points);
  static std::vector<Point> getMinimalY(std::vector<Point> points);

  static std::vector<Point> getMaximumX(std::vector<Point> points);
  static std::vector<Point> getMaximumY(std::vector<Point> points);

  static Point getLowestLeftPoint(std::vector<Point> points);
  static Point getHighestRightPoint(std::vector<Point> points);

  static int calculatePosition(Point a, Point b, Point c);

  ConvexSetFinder() {}
};

#endif