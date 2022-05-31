#include "graph_reader.h"


std::vector<std::vector<int>> GraphReader::readToMatrix(std::string path)
{
    std::ifstream file(path);

        int matrixSize;

        file >> matrixSize;

        matrixSize += 2; // dodanie zrodla i ujscia

        std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize)); 

        // b --> s --> d --> start --> end
        int a, b; //wspolrzedne w macierzy
        int u, v, x, c;    //wierzcholek pocz, wierzcholek konc, przepustowosc(?), koszt

        while(!file.eof())
        {
            file >> u >> v >> x >> c;
            matrix[u][v] = x;
        }
    
    return matrix;
}


std::vector<std::vector<EdgeData>> GraphReader::readToMatrixOfCosts(std::string path)
{
    std::ifstream file(path);

        int matrixSize;

        file >> matrixSize;

        matrixSize += 2; // dodanie zrodla i ujscia

        std::vector<std::vector<EdgeData>> matrix(matrixSize, std::vector<EdgeData>(matrixSize)); 

        int a, b; //wspolrzedne w macierzy
        int u, v, x, c;    //wierzcholek pocz, wierzcholek konc, przepustowosc(?), koszt

        while(!file.eof())
        {
            file >> u >> v >> x >> c;
            matrix[u][v].capacity = x;
            matrix[u][v].cost = c;
            //matrix[v][u].cost = -c;
        }
    
    return matrix;
}

std::vector<std::vector<int>> GraphReader::readToList(std::string path)
{
    std::ifstream file(path); // obs. bledow ?

    int matrixSize;

    file >> matrixSize;
    matrixSize += 2; // dodanie zrodla i ujscia

    std::vector<std::vector<int>> neighboursList;

    int u, v, x;

    while (!file.eof())
    {
        file >> u >> v >> x;
        neighboursList[u].push_back(v);
    }

    file.close();

    return neighboursList;
}

std::vector<std::vector<int>> GraphReader::addSource(std::vector<std::vector<int>> matrix, std::string path, char z, char u)
{
    /*  file ex.
        k 3 9
        p 5 2
        b 2 2
        p 4 9
    */

    std::ifstream file(path); // obs. bledow ?

    char name;
    int x, y;

    // matrix zostal powiekszony przy wczytywaniu danych

    while (!file.eof())
    {
        file >> name >> x >> y;

        int source = matrix.size() - 1;
        int dest = matrix.size() - 2;

        if (name == z)
        {
            matrix[source][x] = y;
        }
        else if (name == u)
        {
            matrix[x][dest] = y;
        }
    }

    file.close();
    return matrix;
}

std::vector<std::vector<EdgeData>> GraphReader::addSourceToMatrixOfCosts(std::vector<std::vector<EdgeData>> matrix, std::string path, char z, char u)
{
    /*  file ex.
        k 3 9
        p 5 2
        b 2 2
        p 4 9
    */

    std::ifstream file(path); // obs. bledow ?

    char name;
    int x, y;

    // matrix zostal powiekszony przy wczytywaniu danych

    while (!file.eof())
    {
        file >> name >> x >> y;

        int source = matrix.size() - 1;
        int dest = matrix.size() - 2;

        if (name == z)
        {
            matrix[source][x].cost = 1;
        }
        else if (name == u)
        {
            matrix[x][dest].cost = 1;
        }
    }

    file.close();
    return matrix;
}

