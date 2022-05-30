#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
class Graph
{
private:
    std::vector<std::vector<int>> matrix;

public:
    std::vector<std::tuple<int,int,int>> neighborsList;
    Graph(std::vector<std::vector<int>> incidMatrix);
    Graph(std::vector<std::tuple<int,int,int>> list);
    int MaxFlow(int start, int end, std::vector<int> &output, std::vector<std::vector<int>> &outputResidual);
    bool BFS(int start, int end, std::vector<int> &path);
    bool BFS(std::vector<std::vector<int>> graph, int start, int finish, std::vector<int> &path);
    void PrintGraph();
    void PrintEdges();
    void UpdateMatrix(std::vector<std::vector<int>> matrix);
    void UpdateMatrixRow(std::vector<int> column, int index);
    std::vector<std::vector<int>> GetMatrix();
    std::vector<int> BellmanFord(std::vector<std::tuple<int,int,int>> neigboorsList, int source);
};

#endif
