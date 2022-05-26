#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
class Graph
{
private:
    std::vector<std::vector<int>> matrix;
public:
    Graph(std::vector<std::vector<int>> incidMatrix);
    int MaxFlow(int start, int end, std::vector<int>& output);
    bool BFS(int start, int end, std::vector<int>& path);
    bool BFS(std::vector<std::vector<int>> graph, int start, int finish, std::vector<int> &path);
    void PrintGraph();
    void UpdateMatrix(std::vector<std::vector<int>> matrix);
    void UpdateMatrixRow(std::vector<int> column, int index);
    std::vector<std::vector<int>> GetMatrix();
};

#endif
