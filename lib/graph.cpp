#include "graph.h"

Graph::Graph(std::vector<std::vector<int>> _matrix)
{
    matrix = _matrix;
}

Graph::Graph(std::vector<std::tuple<int, int, int>> list)
{
    neighborsList = list;
}

bool Graph::BFS(std::vector<std::vector<int>> graph, int start, int finish, std::vector<int> &path)
{
    std::vector<bool> visited = std::vector<bool>(graph.size());
    std::queue<int> visitedVertecies;
    for (int i = 0; i < visited.size(); i++)
    {
        visited[i] = false;
    }
    path[start] = -1;
    visited[start] = true;
    visitedVertecies.push(start);
    while (!visitedVertecies.empty())
    {
        start = visitedVertecies.front();
        visitedVertecies.pop();
        for (int i = 0; i < graph[start].size(); i++)
        {
            if (!visited[i] && graph[start][i] > 0)
            {
                if (i == finish)
                {
                    path[i] = start;
                    return true;
                }
                visited[i] = true;
                path[i] = start;
                visitedVertecies.push(i);
            }
        }
    }
    return false;
}

void Graph::PrintGraph()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::UpdateMatrix(std::vector<std::vector<int>> matrix)
{
    this->matrix = matrix;
}

std::vector<std::vector<int>> Graph::GetMatrix()
{
    return this->matrix;
}

void Graph::UpdateMatrixRow(std::vector<int> column, int index)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        matrix[index][i] = column[i];
    }
}

int Graph::MaxFlow(int s, int f, std::vector<int> &output, std::vector<std::vector<int>> &residualOutput)
{

    int u, v;

    std::vector<std::vector<int>> residualGraph(matrix);
    std::vector<int> path = std::vector<int>(matrix.size());
    int maxFlow = 0;
    while (Graph::BFS(residualGraph, s, f, path))
    {
        int pathFlow = INT_MAX;
        for (v = f; v != s; v = path[v])
        {
            u = path[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
        }

        for (v = f; v != s; v = path[v])
        {
            u = path[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    output = residualGraph[matrix.size() - 2];
    residualOutput = residualGraph;
    return maxFlow;
}