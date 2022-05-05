#include "graph_reader.h"

std::vector<std::vector<int>> GraphReader::readToMatrix(std::string path)
{
    std::ifstream file(path);

    int matrixSize;

    file >> matrixSize;
    matrixSize += 2; // dodanie zrodla i ujscia

    std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize)); // automatycznie wypelniane zerami

    int u, v, x;

    while (!file.eof())
    {
        file >> u >> v >> x;
        matrix[u][v] = x;
    }

    file.close();

    return matrix;
}

std::vector<std::vector<int>> GraphReader::readToList(std::string path)
{
    std::ifstream file(path); // obs. bledow ?

    int matrixSize;
    matrixSize += 2; // dodanie zrodla i ujscia

    file >> matrixSize;

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
    // char s = z;
    // char d = u;
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
            for (int i = 0; i < matrix.size(); i++)
            {
                matrix[x][dest] += matrix[i][x];
            }
        }
    }

    file.close();

    return matrix;
}
