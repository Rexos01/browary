#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> CreateGraph(int);
bool BFS(vector<vector<int>>, int, int , vector<int>&);
int MaxFlow(vector<vector<int>>, int, int);
void PrintRoad(vector<int>);
void PrintGraph(vector<vector<int>>);
int main()
{
    vector<vector<int>> graph = CreateGraph(6);
    PrintGraph(graph);
    int maxflow = MaxFlow(graph,0, 5);
    cout << "Max flow: " << maxflow << endl; 
    return 0;
}

vector<vector<int>> CreateGraph(int v)
{
    cout << "Creating Graph" << endl;
    vector<vector<int>> graph(v, vector<int>(v, 0));
    int value = 0;
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (i != j)
            {
                cout << "From vertex " << i << " to vertex " << j << ": ";
                cin >> value;
                graph[i][j] = value;
            }else{
                graph[i][j] = 0;
            }
        }
    }
    return graph;
}

void PrintGraph(vector<vector<int>> graph){
    for(int i = 0; i < graph.size(); i++){
        for(int j = 0;  j < graph[i].size(); j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

bool BFS(vector<vector<int>> graph, int start, int finish, vector<int> &path)
{
    vector<bool> visited = vector<bool>(graph.size());
    queue<int> visitedVertecies;
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

int MaxFlow(vector<vector<int>> graph, int s, int f)
{

    int u, v;

    vector<vector<int>> residualGraph(graph);
    vector<int> path = vector<int>(graph.size());
    int maxFlow = 0;

    while (BFS(residualGraph, s, f, path))
    {
        int pathFlow = INT_MAX;
        for (v = f; v != s; v = path[v])
        {
            u = path[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for (v = f; v != s; v = path[v])
        {
            u = path[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

void PrintRoad(vector<int> road)
{
    for (int i = 0; i < road.size(); i++)
    {
        cout << road[i] << " -> ";
    }
}