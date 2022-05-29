#include <iostream>
#include "convex_set_finder.h"
#include "point.h"

int main()
{
  std::cout << "Hello!" << std::endl;

  std::vector<Point> points = {
      Point(1, 1),
      Point(2, 2),
      Point(0, 5),
      Point(0, 2),
      Point(-1, 2),
      Point(-1, -1)};

  std::vector<Point> set = ConvexSetFinder::findConvexSet(points);

  for (int i = 0; i < set.size(); i++)
  {
    std::cout << set[i].x << " " << set[i].y << std::endl;
  }

  return 0;
}