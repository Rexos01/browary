#include <iostream>
#include "lib/area.h"

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

  Area areaOne(points, 4);

  std::cout << "- " << areaOne.borderPoints.size() << std::endl;
  std::cout << "__" << std::endl;

  for (int i = 0; i < areaOne.borderPoints.size(); i++)
  {
    std::cout << areaOne.borderPoints[i].x << " " << areaOne.borderPoints[i].y << std::endl;
  }

  return 0;
}