#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <list>
#include <algorithm> 

class GraphReader
{
    static std::vector<std::vector<int>> readToMatrix(std::string path);
    static std::vector<std::vector<int>> readToList(std::string path);
};

#endif