#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <tuple>

class GraphReader
{
public:
    static std::vector<std::vector<int>> readToMatrix(std::string path);
    static std::vector<std::vector<int>> readToList(std::string path);
    static std::vector<std::tuple<int,int, int>> readAsWeightedList(std::string path);
    static std::vector<std::vector<int>> addSource (std::vector<std::vector<int>> matrix, std::string path, char z, char u);
};

#endif