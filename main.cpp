#include <iostream>
#include <vector>
#include <algorithm>

#include "lib/convex_set_finder.h"
#include "lib/point.h"

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

  std::cout << "__" << std::endl;

  std::vector<Point> set = ConvexSetFinder::findConvexSet(points);

  std::cout << "- " << set.size() << std::endl;
  std::cout << "__" << std::endl;

  for (int i = 0; i < set.size(); i++)
  {
    std::cout << set[i].x << " " << set[i].y << std::endl;
  }

  return 0;
}