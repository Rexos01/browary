#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "graph_reader.h"

struct data 
{
  int distance;
  int previous;
};

/*
struct edgeData
{
    int flow;
    int capacity;
    int cost;
};
*/

class Graph
{
private:
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<EdgeData>> matrixOfCosts;

public:
    Graph(std::vector<std::vector<int>> incidMatrix);
    int MaxFlow(int start, int end, std::vector<int> &output, std::vector<std::vector<int>> &outputResidual);
    bool BFS(int start, int end, std::vector<int>& path);
    bool BFS(std::vector<std::vector<int>> graph, int start, int finish, std::vector<int> &path);
    void PrintGraph();
    void UpdateMatrix(std::vector<std::vector<int>> matrix);
    void UpdateMatrixRow(std::vector<int> column, int index);
    std::vector<std::vector<int>> GetMatrix();

    void UpdateMatrixofcosts(std::vector<std::vector<EdgeData>> matrix);
    void PrintMatrixOfCosts();
    std::vector<data> BellmanFord(std::vector<std::vector<EdgeData>> matrix, int start);  
};

#endif
