#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

struct Segment
{
  Point p1;
  Point p2;

  Segment(Point _p1, Point _p2);

  bool intersects(Segment s);
};

#endif