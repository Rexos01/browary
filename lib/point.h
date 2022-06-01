#ifndef POINT_H
#define POINT_H

/**
 * Klasa punktu geometrycznego
 */
struct Point
{
  /**
   * Współrzędna x punktu
   */
  int x;

  /**
   * Współrzędna y punktu
   */
  int y;

  /**
   * Konstruktor klasy punktu
   * @param _x współrzędna x położenia
   * @param _y współrzędna y położenia
   */
  Point(int _x, int _y);

  Point() {}

  friend bool operator==(const Point a, const Point b);
  friend bool operator!=(const Point a, const Point b);
};

#endif