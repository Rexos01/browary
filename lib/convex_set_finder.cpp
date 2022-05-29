#include "convex_set_finder.h"

#include <algorithm>

std::vector<Point> ConvexSetFinder::findConvexSet(std::vector<Point> points)
{
  std::vector<Point> convexPoints;

  Point lowestLeftPoint = getLowestLeftPoint(points);
  convexPoints.push_back(lowestLeftPoint);

  points.erase(find(points.begin(), points.end(), lowestLeftPoint));

  Point highestRightPoint = getHighestRightPoint(points);
  convexPoints.push_back(highestRightPoint);

  points.erase(find(points.begin(), points.end(), highestRightPoint));

  Point activePoint = lowestLeftPoint;

  Point maxPoint = points[0];

  while (maxPoint != highestRightPoint)
  {
    maxPoint = points[0];
    for (int i = 0; i < points.size(); i++)
    {
      if (calculatePosition(activePoint, maxPoint, points[i]) > 0)
      {
        maxPoint = points[i];
      }
    }
    activePoint = maxPoint;
    points.erase(find(points.begin(), points.end(), maxPoint));
    convexPoints.push_back(maxPoint);
  }

  Point minPoint = points[0];

  activePoint = highestRightPoint;

  while (minPoint != lowestLeftPoint)
  {
    minPoint = points[0];
    for (int i = 0; i < points.size(); i++)
    {
      if (calculatePosition(activePoint, minPoint, points[i]) < 0)
      {
        minPoint = points[i];
      }
    }
    activePoint = minPoint;
    points.erase(find(points.begin(), points.end(), minPoint));
    convexPoints.push_back(minPoint);
  }
}

bool ConvexSetFinder::compareXMin(Point a, Point b)
{
  return a.x < b.x;
}

bool compareYMin(Point a, Point b)
{
  return a.y < b.y;
}

std::vector<Point> ConvexSetFinder::getMinimalX(std::vector<Point> points)
{
  sort(points.begin(), points.end(), compareXMin);

  int minX = points[0].x;

  std::vector<Point> result;
  for (int i = 0; i < points.size(); i++)
  {
    if (points[i].x == minX)
    {
      result.push_back(points[i]);
    }
    else
    {
      result.push_back(points[i]);
      break;
    }
  }

  return result;
}

std::vector<Point> ConvexSetFinder::getMinimalY(std::vector<Point> points)
{
  sort(points.begin(), points.end(), compareYMin);

  int minY = points[0].y;

  std::vector<Point> result;
  for (int i = 0; i < points.size(); i++)
  {
    if (points[i].x == minY)
    {
      result.push_back(points[i]);
    }
    else
    {
      result.push_back(points[i]);
      break;
    }
  }

  return result;
}

Point ConvexSetFinder::getLowestLeftPoint(std::vector<Point> points)
{
  std::vector<Point> lowestPoints = getMinimalX(points);
  std::vector<Point> lowestLeftPoints = getMinimalY(lowestPoints);

  return lowestLeftPoints[0];
}

bool ConvexSetFinder::compareXMax(Point a, Point b)
{
  return a.x > b.x;
}

bool ConvexSetFinder::compareYMax(Point a, Point b)
{
  return a.y > b.y;
}

std::vector<Point> ConvexSetFinder::getMaximumX(std::vector<Point> points)
{
  sort(points.begin(), points.end(), compareXMax);

  int maxX = points[0].x;

  std::vector<Point> result;
  for (int i = 0; i < points.size(); i++)
  {
    if (points[i].x == maxX)
    {
      result.push_back(points[i]);
    }
    else
    {
      result.push_back(points[i]);
      break;
    }
  }

  return result;
}

std::vector<Point> ConvexSetFinder::getMaximumY(std::vector<Point> points)
{
  sort(points.begin(), points.end(), compareYMax);

  int maxY = points[0].y;

  std::vector<Point> result;
  for (int i = 0; i < points.size(); i++)
  {
    if (points[i].x == maxY)
    {
      result.push_back(points[i]);
    }
    else
    {
      result.push_back(points[i]);
      break;
    }
  }

  return result;
}

Point ConvexSetFinder::getHighestRightPoint(std::vector<Point> points)
{
  std::vector<Point> highestPoints = getMaximumX(points);
  std::vector<Point> highestRightPoints = getMaximumY(highestPoints);

  return highestRightPoints[0];
}

int ConvexSetFinder::calculatePosition(Point a, Point b, Point c)
{
  return (a.x * b.y) + (b.x * c.y) + (c.x * a.y) - (b.y * c.x) - (c.y * a.x) - (a.y * b.x);
}
