#ifndef AREA_H
#define AREA_H

#include <vector>
#include "point.h"
#include "segment.h"

/**
 * Klasa obszaru
 */
class Area
{
public:
  /**
   * Konstruktor klasy obszaru
   * @param _borderPoints punkty graniczne obszaru
   * @param _areaValue wartość wydajności pól na obszarze
   */
  Area(std::vector<Point> _borderPoints, int _areaValue);

  /**
   * Punkty graniczne obszaru
   */
  std::vector<Point> borderPoints;

  /**
   * Granice obszaru (odcinki)
   */
  std::vector<Segment> segments;

  /**
   * Wydajność pól uprawnych na obszarze
   */
  int areaValue;

  int maxX;

  /**
   * Sprawdza, czy punkt znajduje się w danym obszarze
   * @param point dane punktu
   * @return true, w przypadku poprawnego wprawdzenia, false w p. w.
   */
  bool isInTheArea(Point point);

private:
  Area();

  /**
   * Wyznacza otoczkę zbioru punktów, wyznaczając obszar
   * @param points punkty do sprawdzenia
   * @return zbiór punktów należących do otoczki
   */
  std::vector<Point> findConvexSet(std::vector<Point> points);

  /**
   * Oblicza wyznacznik macierzy 3x3, pozwalając określić położenie punktu c, względem a i b
   * @param a punkt a
   * @param b punkt b
   * @param c punkt c
   * @return wyznacznik macierzy
   */
  int calculatePosition(Point a, Point b, Point c);
};

#endif