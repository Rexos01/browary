#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <tuple>

#include "area.h"
#include "field.h"

class GraphReader
{
public:
    static std::vector<std::vector<int>> readToMatrix(std::string path);
    static std::vector<std::vector<int>> readToList(std::string path);
    static std::vector<std::tuple<int,int, int>> readAsWeightedList(std::string path);
    static std::vector<std::vector<int>> addSource (std::vector<std::vector<int>> matrix, std::string path, char z, char u);
    static std::vector<Area> readAreas(std::string path);
    static std::vector<Field> readFieldsPosition(std::string path);
};

#endif