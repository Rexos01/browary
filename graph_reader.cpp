#include "graph_reader.h"


std::vector<std::vector<int>> GraphReader::readToMatrix(std::string path)
{
    std::ifstream file(path);

        int matrixSize;

        path >> matrixSize;

        std::vector<std::vector<int>> neighboursList;
        std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize));

        // b --> s --> d --> start --> end
        int a, b; //wspolrzedne w macierzy
        int u, v, x;

        while(!file.eof())
        {
            file >> u >> v >> x;
            matrix[u][v] = x;
        }

    return matrix;
}

std::vector<std::vector<int>> GraphReader::readToList(std::string path)
{
    std::ifstream file(path);

        int matrixSize;

        path >> matrixSize;

        std::vector<std::vector<int>> neighboursList;
        std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize));

        // b --> s --> d --> start --> end
        int a, b; //wspolrzedne w macierzy
        int u, v, x;

        while(!file.eof())
        {
            file >> u >> v >> x;
             neighboursList[u].push_back(v);
        }
}