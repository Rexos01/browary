#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

struct EdgeData
{
    int flow;
    int capacity;
    int cost;
};

class GraphReader
{
public:
    static std::vector<std::vector<int>> readToMatrix(std::string path);
    static std::vector<std::vector<EdgeData>> readToMatrixOfCosts(std::string path);
    static std::vector<std::vector<int>> readToList(std::string path);
    static std::vector<std::vector<int>> addSource (std::vector<std::vector<int>> matrix, std::string path, char z, char u);
    static std::vector<std::vector<EdgeData>> addSourceToMatrixOfCosts(std::vector<std::vector<EdgeData>> matrix, std::string path, char z, char u);

};

#endif
