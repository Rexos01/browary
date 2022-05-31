#include "segment.h"

int sign(int x);
int calculatePosition(Point a, Point b, Point c);

Segment::Segment(Point _p1, Point _p2)
{
  p1 = _p1;
  p2 = _p2;
}

bool Segment::intersects(Segment s)
{
  return (sign(calculatePosition(p1, p2, s.p1)) != sign(calculatePosition(p1, p2, s.p2))) &&
         (sign(calculatePosition(s.p1, s.p2, p1)) != sign(calculatePosition(s.p1, s.p2, p2)));
}

int calculatePosition(Point a, Point b, Point c)
{
  return (a.x * b.y) + (b.x * c.y) + (c.x * a.y) - (b.y * c.x) - (c.y * a.x) - (a.y * b.x);
}

int sign(int x)
{
  if (x > 0)
    return 1;
  if (x < 0)
    return -1;
  return 0;
}
