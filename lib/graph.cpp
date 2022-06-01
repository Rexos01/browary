#include "graph.h"

/**
 * Konstruktor klasy graf
 * @param _matrix macierz incydencji reprezentujacej graf
 */

Graph::Graph(std::vector<std::vector<int>> _matrix)
{
    matrix = _matrix;
}

/**
 *Konstruktor klasy graf
 * @param list ważona lista sasiedzstwa reprezentujaca graf
 */
Graph::Graph(std::vector<std::tuple<int, int, int>> list)
{
    neighborsList = list;
}

/**
 * Wyszykiwanie najkrutszej sciezki w grafie
 * @param graph macierz incydencji danego grafu
 * @param start poczatkowy wierszolek
 * @param finish koncowy wierszolek
 * @param path vektor przychowywajacy droge od start do finish
 * @return zwraza true jesli droga istneje, w przeciwnym wypadku zwraca false
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
 * Wypisuje zawartosc macierzy incydencji
 */
void Graph::PrintGraph()
{
    std::cout << std::endl;
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
 * Nadpisuje macierz incydencji nowa
 * @param matrix new incidience matrix
 */
void Graph::UpdateMatrix(std::vector<std::vector<int>> matrix)
{
    this->matrix = matrix;
}

/**
 * Zwraca macierz incydencji na zewnatrz klasy
 * @return macierz incydencji reprezentujaca graf
 */
std::vector<std::vector<int>> Graph::GetMatrix()
{
    return this->matrix;
}

/**
 * Zmienia wagi pewnego wierszholku w grafie
 * @param row nowy vector wag wierszholka
 * @param index index wierszholka
 */
void Graph::UpdateMatrixRow(std::vector<int> row, int index)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        matrix[index][i] = row[i];
    }
}

/**
 * Oblicza maksymalny przeplyw od punktu s do punktu f
 * @param s zrodlo grafu
 * @param f ujscie grafu
 * @param output wagi zrodla po obliczaniu przeplywu
 * @param residualOutput cala siec residualna
 * @return zwraca wartosc maksymalnego przeplywu
 */
int Graph::MaxFlow(int s, int f, std::vector<int> &output, std::vector<std::vector<int>> &residualOutput)
{

    int u, v;

    std::vector<std::vector<int>> residualGraph(matrix);
    std::vector<int> path = std::vector<int>(matrix.size());
    int maxFlow = 0;
    while (Graph::BFS(residualGraph, s, f, path))
    {
        for (v = f; v != s; v = path[v])
        {
            std::cout << path[v] << " ";
        }
        std::cout << std::endl;

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