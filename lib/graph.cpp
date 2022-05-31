#include "graph.h"

/**
 * Graph constructor 
 * @param _matrix the incidence matrix that represents the graph
 */

Graph::Graph(std::vector<std::vector<int>> _matrix)
{
    matrix = _matrix;
}

/**
 * Graph constructor 
 * @param list the weighted neighbors list that represents the graph
 */
Graph::Graph(std::vector<std::tuple<int, int, int>> list)
{
    neighborsList = list;
}

/**
 * Looks through the graph for the shortest path
 * @param graph incidence matrix of the target graph
 * @param start index of the vertex from which we start
 * @param finish index of the vertex to which we go
 * @param path vector in which we write our road
 * @return returns true if road exists, else returns false 
 */
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

/**
 * Prints the inciedence matrix of the graph
 */
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

/**
 * Allow us to overwrite the existing matrix
 * @param matrix new incidience matrix
 */
void Graph::UpdateMatrix(std::vector<std::vector<int>> matrix)
{
    this->matrix = matrix;
}

/**
 * Allow us to get private matrix
 * @return matrix that represent the graph
 */
std::vector<std::vector<int>> Graph::GetMatrix()
{
    return this->matrix;
}

/**
 * Updates some certain row of the matrix
 * @param row new vector containing the weighted edges
 * @param index index of the vertex
 */
void Graph::UpdateMatrixRow(std::vector<int> row, int index)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        matrix[index][i] = row[i];
    }
}


/**
 * Calculates maxflow of the graph with Edmund-Carp alghorithm
 * @param s source of the given graph
 * @param f destinition of the flow
 * @param output vector that contains value of the destinition can be used as a source weights in the second step
 * @param residualOutput the whole residual graph after calculating max flow
 * @return returns the value of the maxflow
 */
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