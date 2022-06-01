#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

/**
 * Klasa reprezentująca odcinek
 */
struct Segment
{
  /**
   * Punkt początkowy
   */
  Point p1;

  /**
   * Punkt końcowy
   */
  Point p2;

  /**
   * Konstruktor klasy odcinka składającego się z dwóch punktów
   * @param _p1 punkt początkowy Point
   * @param _p2 punkt końcowy Point
   */
  Segment(Point _p1, Point _p2);

  /**
   * Sprawdza, czy dwa odcinki się przecinają
   * @param s odcinek do sprawdzenia
   * @return true, jeśli odcinki się przecinają, false w p. w.
   */
  bool intersects(Segment s);
};

#endif