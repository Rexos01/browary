#include "area.h"
#include "point.h"
#include "segment.h"

#include <algorithm>
#include <vector>

bool compareXMax(Point a, Point b);
bool compareYMax(Point a, Point b);
bool compareXMin(Point a, Point b);
bool compareYMin(Point a, Point b);

std::vector<Point> getMinimalY(std::vector<Point> points);
std::vector<Point> getMinimalX(std::vector<Point> points);
std::vector<Point> getMaximumY(std::vector<Point> points);
std::vector<Point> getMaximumX(std::vector<Point> points);

Point getBottomLeftPoint(std::vector<Point> points);
Point getTopRightPoint(std::vector<Point> points);

Area::Area(std::vector<Point> _borderPoints, int _areaValue)
{
  borderPoints = findConvexSet(_borderPoints);
  areaValue = _areaValue;

  maxX = getMaximumX(borderPoints)[0].x;

  if (borderPoints.size() > 1)
  {
    for (int i = 0; i < borderPoints.size(); i++)
    {
      segments.push_back(Segment(borderPoints[i], borderPoints[i + 1]));
    }
    segments.push_back(Segment(borderPoints[borderPoints.size() - 1], borderPoints[0]));
  }
}

bool Area::isInTheArea(Point point)
{
  Segment examiningSegment = Segment(point, Point(maxX + 1, point.y));
  int crossedSegments = 0;

  for (int i = 0; i < segments.size(); i++)
  {
    if (examiningSegment.intersects(segments[i]))
    {
      crossedSegments++;
    }
  }

  return crossedSegments % 2 != 0;
}

std::vector<Point> Area::findConvexSet(std::vector<Point> points)
{
  std::vector<Point> convexPoints;

  Point bottomLeftPoint = getBottomLeftPoint(points);
  Point topRightPoint = getTopRightPoint(points);

  Point activePoint = bottomLeftPoint;
  Point maxPoint = points[0];

  while (maxPoint != topRightPoint)
  {
    maxPoint = points[0];
    for (int i = 0; i < points.size(); i++)
    {
      int position = calculatePosition(activePoint, maxPoint, points[i]);
      if (position < 0)
      {
        maxPoint = points[i];
      }
    }
    activePoint = maxPoint;
    points.erase(find(points.begin(), points.end(), maxPoint));
    convexPoints.push_back(maxPoint);
  }

  Point minPoint = points[0];
  activePoint = topRightPoint;

  while (minPoint != bottomLeftPoint && points.size() != 0)
  {
    minPoint = points[0];
    for (int i = 0; i < points.size(); i++)
    {
      if (calculatePosition(activePoint, minPoint, points[i]) > 0)
      {
        minPoint = points[i];
      }
    }
    activePoint = minPoint;
    points.erase(find(points.begin(), points.end(), minPoint));
    convexPoints.push_back(minPoint);
  }
  // points.erase(find(points.begin(), points.end(), highestRightPoint));
  // convexPoints.push_back(highestRightPoint);

  // points.erase(find(points.begin(), points.end(), lowestLeftPoint));
  // convexPoints.push_back(lowestLeftPoint);

  return convexPoints;
}

int Area::calculatePosition(Point a, Point b, Point c)
{
  return (a.x * b.y) + (b.x * c.y) + (c.x * a.y) - (b.y * c.x) - (c.y * a.x) - (a.y * b.x);
}

//
// Utility functions
//

bool compareXMax(Point a, Point b)
{
  return a.x > b.x;
}

bool compareYMax(Point a, Point b)
{
  return a.y > b.y;
}

bool compareXMin(Point a, Point b)
{
  return a.x < b.x;
}

bool compareYMin(Point a, Point b)
{
  return a.y < b.y;
}

std::vector<Point> getMinimalX(std::vector<Point> points)
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

std::vector<Point> getMinimalY(std::vector<Point> points)
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

std::vector<Point> getMaximumX(std::vector<Point> points)
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

std::vector<Point> getMaximumY(std::vector<Point> points)
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

Point getBottomLeftPoint(std::vector<Point> points)
{
  std::vector<Point> lowestPoints = getMinimalX(points);
  std::vector<Point> lowestLeftPoints = getMinimalY(lowestPoints);

  return lowestLeftPoints[0];
}

Point getTopRightPoint(std::vector<Point> points)
{
  std::vector<Point> highestPoints = getMaximumX(points);
  std::vector<Point> highestRightPoints = getMaximumY(highestPoints);

  return highestRightPoints[0];
}
