#include "graph.h"

Graph::Graph(std::vector<std::vector<int>> _matrix,std::vector<std::vector<EdgeData>> _matrixofcosts){
    matrix = _matrix;
    matrixOfCosts=_matrixofcosts;
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

void Graph::PrintGraph(){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout<<std::endl;
    }
}

void Graph::Print(std::vector<std::vector<int>>matrix)
{
      for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix.size(); j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout<<std::endl;
    }
}

void Graph::UpdateMatrix(std::vector<std::vector<int>> matrix){
    this->matrix = matrix;
}

void Graph::UpdateMatrixOfCosts(std::vector<std::vector<EdgeData>> matrix){
    this->matrixOfCosts = matrix;
}

std::vector<std::vector<int>> Graph::GetMatrix(){
    return this->matrix;
}

std::vector<std::vector<EdgeData>> Graph::GetMatrixOfCosts(){
    return this->matrixOfCosts;
}


void Graph::UpdateMatrixRow(std::vector<int> column, int index){
    for(int i = 0; i < matrix.size(); i ++){
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
            matrixOfCosts[u][v].flow += pathFlow;
        }

        maxFlow += pathFlow;
    }
    output = residualGraph[matrix.size() - 2];
    residualOutput = residualGraph;
    return maxFlow;
}


void Graph::BellmanFord(int start)
{
    int negativeCycle = -1;

    std::vector<data> tab(matrixOfCosts.size());   // table of distances and previous vertex

    for(int i=0; i<matrixOfCosts.size(); i++)
    {
      tab[i].distance = INT_MAX;
      tab[i].previous = -1;      //bylo -1
    }

    tab[start].distance = 0;

    for(int j=0; j<matrixOfCosts.size()-1; j++)
    {
      for (int u = 0; u < matrixOfCosts.size(); u++) 
      {
        for (int v = 0; v < matrixOfCosts.size(); v++) 
        {
          if(matrixOfCosts[u][v].cost!=0 && tab[v].distance>tab[u].distance + matrixOfCosts[u][v].cost)
          {
            tab[v].distance = tab[u].distance + matrixOfCosts[u][v].cost;
            tab[v].previous = u;
          }
        }
      }
    }

    // n-te przejście pętli
    for(int i=0; i<tab.size(); i++)
    {
      if(tab[i].distance > tab[tab[i].previous].distance + matrixOfCosts[tab[i].previous][i].cost)
      {
          //istnieje ujemny cykl i przypisujemy zmiennej id wierzcholka z ujemnego cyklu
        negativeCycle =  i; 
        break;
      } 
    }

    

    if(negativeCycle != -1)     //istnieje ujemny cykl
    {
        std::vector<int> cycle;
        int index = negativeCycle;
        int index2;

        cycle.push_back(index);
        index = tab[index].previous;
            
        for(int i = cycle.size()-1; i > 0; i--)
        {
            std::cout << cycle[i] << " " << std::endl;
        }

        for (int i = 0; i < cycle.size(); i++)
        {
            if(cycle[i] == index) break;        // znalezlismy cykl do ktorego (na pewno) nalezy index
        }





        cycle.clear();
        index2 = index;

        cycle.push_back(index);     
        while((index2 = tab[index2].previous) != index)
        {
            cycle.push_back(index2);
        }
        cycle.push_back(index); 

        ///wypisac????

        int m = matrixOfCosts[cycle[0]][cycle[1]].capacity; //minimalna przepustowosc
        for(int i = 1; i < cycle.size()-1; i++) // szukamy minimalnej przepustowosci w ujemnym cyklu
        {
            if(m > matrixOfCosts[cycle[i]][cycle[i+1]].capacity)
            {
                m = matrixOfCosts[cycle[i]][cycle[i+1]].capacity;
            }
        }

        for(int i = cycle.size()-1; i > 0; i--) // szukamy minimalnej przepustowosci w ujemnym cyklu
        {
            if(matrixOfCosts[cycle[i]][cycle[i-1]].capacity > 0)
            {
                if(matrixOfCosts[cycle[i]][cycle[i-1]].cost > 0)    //strzalki zgodnie z grafem 
                {
                    matrixOfCosts[cycle[i]][cycle[i-1]].flow + m;
                    matrixOfCosts[cycle[i]][cycle[i-1]].capacity - m;
                }
                else if(matrixOfCosts[cycle[i]][cycle[i-1]].cost < 0)   //strzalki przeciwne do tych w grafie
                {
                    matrixOfCosts[cycle[i-1]][cycle[i]].flow - m;
                    matrixOfCosts[cycle[i-1]][cycle[i]].capacity + m;   //???????????????????????
                }

                // 0 <- 1 <- 3 <- 4 <- 0
            }
        }

        for(int i = cycle.size()-1; i > 0; i--)
        {
            std::cout << cycle[i] << " " << std::endl;
        }

    }
    else std::cout << "NIE MA CYKLI :C" << std::endl;
}

    void Graph::AssignToMatrixofcosts(std::vector<std::vector<int>>residual)
    {
       

        for (int i = 0; i < residual.size(); i++)
        {
            for (int j = 0; j < residual.size(); j++)
            {
                //obliczamy przeplyw na podstawie poczatkowego grafu i sieci rezidualnej.
                //przeplyw = poczatkowa przepustowosc - koncowa przepustowosc

                //matrixOfCosts[i][j].flow = matrixOfCosts[i][j].capacity - residual[j][i];  
                //if(matrixOfCosts[i][j].capacity - residual[i][j] > 0) 
                //matrixOfCosts[i][j].flow = matrixOfCosts[i][j].capacity - residual[j][i];  

                //jesli w poczatkowym grafie nie bylo krawedzi a w rezidualnej juz jest to 
                //dajemy tej krawedzi koszt przeciwnej wartosci
                if(matrixOfCosts[i][j].capacity == 0 && residual[i][j] != 0)    
                {
                    matrixOfCosts[i][j].cost = -matrixOfCosts[j][i].cost;
                }

                matrixOfCosts[i][j].capacity = residual[i][j];
            }
        }
        

    }


void Graph::PrintMatrixOfCosts()
{
    for (int i = 0; i < matrixOfCosts.size(); i++)
    {
        for (int j = 0; j < matrixOfCosts.size(); j++)
        {
            std::cout << matrixOfCosts[i][j].flow << " ";
        }
        std::cout << std::endl;
    }
}
