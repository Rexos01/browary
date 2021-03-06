#include "graph_reader.h"

/**
 * Wczytuje dane do macierzy incydencji
 * @param path  sciezka do pliku z danymi
 * @return zwraca macierz incydencji z danymi
 */
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

/**
 * Wczytuje dane do list sasiedzstwa
 * @param path  sciezka do pliku z danymi
 * @return zwraca liste sasiedzstwa z danymi
 */
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


std::vector<std::tuple<int,int, int>> GraphReader::readAsWeightedList(std::string path)
{
    std::ifstream stream(path);
    int size;
    stream >> size;
    std::vector<std::tuple<int,int,int>> weightedList;
    int s, d, w;
    while(!stream.eof())
    {
        stream >> s >> d >> w;
        weightedList.push_back(std::tuple<int,int,int>(s, d, w));
    }
    stream.close();
    return weightedList;
}

/**
 * Dodaje wierszolki do macierzy incydencji
 * @param matrix macierz ktora ma byc zupdatowana
 * @param path  sciezka do pliku z danymi
 * @param z symbol reprezentujacy zrodlo
 * @param u symbol reprezentujacy ujscie
 * @return zwraca zzupdatowana macierz incydencji
 */
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
            matrix[x][dest] = y;
        }
    }

    file.close();

    return matrix;
}

/**
 * Na podstawie danych z pliku podanego w parametrze tworzy vector obszar??w typu Area
 * @param path ??cie??ka do pliku z danymi o obszarach
 * @return zbi??r dost??pnych obszar??w
 */
std::vector<Area> GraphReader::readAreas(std::string path)
{
    std::ifstream file(path);

    std::vector<Area> areas;
    std::vector<Point> points;
    int areaSize, areaValue, areaIndex;
    int x, y;

    areaIndex = 0;

    while (!file.eof())
    {
        file >> areaSize >> areaValue;
        for (int i = 0; i < areaSize; i++)
        {
            file >> x >> y;
            points.push_back(Point(x, y));
        }
        areas.push_back(Area(points, areaValue));
        points.clear();
        areaIndex++;
    }
    file.close();
    return areas;
}

/**
 * Na podstawie danych z pliku podanego w parametrze tworzy zbi??r p??l uprawnych wraz z ich po??o??eniem
 * @param path ??cie??ka do pliku z danymi o polach uprawnych
 * @return zbi??r przetworzonych p??l
 */
std::vector<Field> GraphReader::readFieldsPosition(std::string path)
{
    std::ifstream file(path);
    std::vector<Field> fields;

    int i, x, y;

    while (!file.eof())
    {
        file >> i >> x >> y;
        fields.push_back(Field(i, x, y));
    }
    file.close();

    return fields;
}
