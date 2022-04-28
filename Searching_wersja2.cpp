// b --> s --> d --> start --> end


#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <list>

#include <algorithm>    // std::remove_if

using namespace std;
class Graph
{
//private:
public:
    vector<vector<int>> neighboursList;
    vector<vector<int>> matrix;
    vector<int> demand;        //zapotrzebowanie ds    //t
    vector<int> possibilities; //mozliwoscy produkcyjne    //s

    vector <int> pi;
    vector <int> road;

    vector<vector<int>> residual;

public:
    Graph()
    {
        Wczytaj();
    }

    void Wczytaj()
    {
        ifstream dane("dane.txt");

        int number_of_brewery;     //n
        int number_of_dormitories; //m
        int number_of_crossings;   //k
        int number_of_edges;       //t

        dane >> number_of_brewery;
        dane >> number_of_dormitories;
        dane >> number_of_crossings;
        dane >> number_of_edges;

        int x;
        string u, v;

        x = number_of_brewery + number_of_crossings + number_of_dormitories + 2;

        neighboursList.resize(x);
        matrix.resize(x);
        residual.resize(x);
        for (int i=0; i<x; i++)
        {
            matrix[i].resize(x);
            residual[i].resize(x);
        }

        for (int i=0; i<number_of_brewery; i++)
        {
            dane >> x;
            possibilities.push_back(x);
        }

        for (int i=0; i<number_of_dormitories; i++)
        {
            dane >> x;
            demand.push_back(x);
        }

        // b --> s --> d --> start --> end
        int a, b; //wspolrzedne w macierzy
        string c;

        for (int i=0; i<number_of_edges; i++)
        {
            dane >> u >> v >> x;

            switch (u[0])
            {
            case 'b':
                a = stoi(u.substr(1, u.size() - 1)) - 1;
                break;
            case 's':
                a = stoi(u.substr(1, u.size() - 1)) - 1 + number_of_brewery;
                break;
            case 'd':
                a = stoi(u.substr(1, u.size() - 1)) - 1 + number_of_brewery + number_of_crossings;
                break;
            }

            switch (v[0])
            {
            case 'b':
                b = stoi(v.substr(1, v.size() - 1)) - 1;
                break;
            case 's':
                b = stoi(v.substr(1, v.size() - 1)) - 1 + number_of_brewery;
                break;
            case 'd':
                b = stoi(v.substr(1, v.size() - 1)) - 1 + number_of_brewery + number_of_crossings;
                break;
            }

            matrix[a][b] = x;
            neighboursList[a].push_back(b);
        }


// dodanie zrodla i ujscia
/*
        for (int i=0; i<number_of_brewery; i++)
        {
            int h=0;
            for(int j=0; j<matrix[i].size(); j++)
            {
                h += matrix[i][j];
            }
            matrix[matrix.size()-2][i] = h;
            neighboursList[neighboursList.size()-2].push_back(i);
        }
*/
        for (int i=0; i<number_of_brewery; i++)
        {
            matrix[matrix.size()-2][i] = possibilities[i];
            neighboursList[neighboursList.size()-2].push_back(i);
        }


/*
        for (int i=0; i<number_of_dormitories; i++)
        {
            int h=0;
            for(int j=0; j<matrix[i].size(); j++)
            {
                h += matrix[j][i+number_of_brewery+number_of_crossings];
            }
            matrix[i+number_of_brewery+number_of_crossings][matrix.size()-1] = h;
            neighboursList[i+number_of_brewery+number_of_crossings].push_back(neighboursList.size()-1);
        }
*/

        for (int i=0; i<number_of_dormitories; i++)
        {
            matrix[i+number_of_brewery+number_of_crossings][matrix.size()-1] = demand[i];
            neighboursList[i+number_of_brewery+number_of_crossings].push_back(neighboursList.size()-1);
        }



// przypisanie dla residual macierzy matrix
    for (int i=0; i<matrix.size(); i++)
    {
        residual[i] = matrix[i];
    }


// wypisywanie

        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
            {
                cout << matrix[i][j] << "  ";
            }
            cout << endl;
        }

        cout << endl << endl;

        for (int i = 0; i < neighboursList.size(); i++)
        {
            cout << i << " : ";
            for (int j = 0; j < neighboursList[i].size(); j++)
            {
                cout << neighboursList[i][j] << "  ";
            }
            cout << endl;
        }

        dane.close();
    }



    void BFS_Visit(int s)
    {
        int u, v;
        queue <int> kolejka;
        vector <int> kolor(neighboursList.size()); //0-bialy; 1-szary; 2-czarny

        //kolor.resize(neighboursList.size());


        for(int i=0; i<neighboursList.size(); i++)
        {
            pi.push_back(-2);
        }

        kolor[s] = 1;
        kolejka.push(s);

        while(kolejka.size() != 0)
        {
            u = kolejka.front();
            for(int i=0; i<neighboursList[u].size(); i++)
            {
                v = neighboursList[u][i];
                if(kolor[v] == 0)
                {
                    kolor[v] = 1;
                    pi[v] = u;
                    kolejka.push(v);
                }
            }
            kolejka.pop();
            kolor[u] = 2;
        }
    }


    void minRoad(int s, int v)
    {
        if(s == v) road.push_back(v);
        else if(pi[v] == -2) return;
        else
        {
            minRoad(s,pi[v]);
            road.push_back(v);
        }
    }

    int getFlow()
    {
        BFS_Visit(19);

        road.clear();   //zmienic

        minRoad(19,20);

        if(road.size() == 0) return 0;

        int flow = residual[road[0]][road[1]];

        for(int i=1; i<road.size()-1; i++)
        {
            if(flow > residual[road[i]][road[i+1]])
            {
                flow  = residual[road[i]][road[i+1]];
            }
        }
        return flow;
    }


    int updateMatrix()
    {
        int flow = getFlow();

        cout << "[" << flow << "]";

        if(flow == 0) return 0;

        {
            for(int i=0; i<road.size()-1; i++)
            {
                residual[road[i]][road[i+1]] -= flow;

                //remove edge if flow == 0 (from neighboursList)
                if(residual[road[i]][road[i+1]] == 0)
                {
                    for(int j=0; j<neighboursList[road[i]].size(); j++)
                    {
                        if(neighboursList[road[i]][j] == road[i+1])
                        {
                            neighboursList[road[i]].erase(neighboursList[road[i]].begin() + j);
                        }
                    }
                }

                residual[road[i+1]][road[i]] += flow;
                neighboursList[road[i+1]].push_back(road[i]);
            }
        }
        return 1;
    }
/*
    void Karp()
    {
        int flow = getFlow();

        while(flow > 0)
        {
            updateMatrix(flow);
            flow = getFlow();
        }
    }
*/
};


int main()
{
    Graph graph = Graph();

    //vector<int> road = graph.BFS(0);

    //graph.BFS_Visit(19);    // zmienic
    //graph.print(19,20);     // zmienic

    //cout << graph.getFlow() << endl;

    cout << endl;
    //cout << graph.getFlow();
    //int flow = graph.getFlow();
    //cout << flow << endl;

    //graph.minRoad(19, 20);

    while(graph.updateMatrix() == 1)
    {

        //graph.Karp();
        cout << endl;

/*
        for (int i = 0; i < graph.neighboursList.size(); i++)
        {

            for (int j = 0; j < graph.neighboursList.size(); j++)
            {
                cout << graph.residual[i][j] << " " ;
            }
        }
*/

            for(int i=0; i<graph.road.size(); i++)
            {
                cout << graph.road[i] << " ";
            }

            cout << endl;
    }




    return 0;
}








/*

#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

class Graph
{
    int getFlow()
    {

    }

    int getEdgeThrouput(int from, int to)
    {

    }

    int getSourceIndex()
    {

    }

    int getTargetIndex()
    {

    }

    int getRoadMinFlow(vector<int> road)
    {
        vector<int> edgeThroughputs = [];

        edgeThroughputs.push_back(this.getEdgeThrouput(this.getSourceIndex(), road[0]));
        for(int i = 0; i < road.size - 2; i++)
        {
            edgeThroughputs.push_back(this.getEdgeThrouput(road[i], road[i+1]));
        }
        edgeThroughputs.push_back(this.getEdgeThrouput(road[road.size-1], this.getTargetIndex));
    }
};


int main() {
    cout << "Hello";

    int theta;
    vector<int> road;

    while((road = getShortestRoad) !== NULL && g.getFlow() < theta)
    {
        roadMinFlow = *min_element(begin(road), end(road));

    }

    return 0;
}

*/
