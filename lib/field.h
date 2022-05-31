#ifndef FIELD_H
#define FIELD_H

#include "point.h"

struct Field
{
  int vectorIndex;
  Point position;
  int productivity;

  Field(int _vectorIndex, int _x, int _y)
  {
    vectorIndex = _vectorIndex;
    position = Point(_x, _y);
    productivity = -1;
  }
};

#endif