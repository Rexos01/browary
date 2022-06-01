#ifndef FIELD_H
#define FIELD_H

#include "point.h"

/**
 * Klasa pola uprawnego
 */
struct Field
{
  /**
   * Indeks wierzchołka powiązanego z polem
   */
  int vectorIndex;

  /**
   * Pozycja pola na badanym obszarze
   */
  Point position;

  /**
   * Wydajność pola wyznaczana na podstawie położenia.
   * Początkowa wartość przed obliczeniami to -1.
   */
  int productivity;

  /**
   * Konstruktor klasy pola uprawnego
   * @param _vectorIndex indeks powiązanego wierzchołka
   * @param _x współrzędna x położenia
   * @param _y współrzędna y położenia
   */
  Field(int _vectorIndex, int _x, int _y)
  {
    vectorIndex = _vectorIndex;
    position = Point(_x, _y);
    productivity = -1;
  }
};

#endif