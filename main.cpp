#include "lib/graph.h"
#include "lib/graph_reader.h"
#include "lib/point.h"
#include "lib/area.h"

void PrintVector(std::vector<int> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i] << " ";
    }
}

int main(int argc, char *argv[])
{
    std::vector<Area> areas = GraphReader::readAreas(argv[4]);
    std::vector<Field> fields = GraphReader::readFieldsPosition(argv[5]);

    for (int i = 0; i < fields.size(); i++)
    {
        for (int j = 0; j < areas.size(); j++)
        {
            if (areas[j].isInTheArea(fields[i].position))
            {
                fields[i].productivity = areas[j].areaValue;
                break;
            }
        }
    }

    Graph newGraph = Graph(GraphReader::readToMatrix(argv[1]));
    newGraph.UpdateMatrix(GraphReader::addSource(newGraph.GetMatrix(), argv[2], 'p', 'b'));
    int source = newGraph.GetMatrix().size() - 1;
    int dest = newGraph.GetMatrix().size() - 2;
    std::vector<int> p(newGraph.GetMatrix().size(), 0);

    for (int i = 0; i < fields.size(); i++)
    {
        if (fields[i].productivity != -1)
        {
            p[fields[i].vectorIndex] = fields[i].productivity;
        }
    }

    // TODO
    newGraph.UpdateMatrixRow(p, source);

    std::vector<int> browarsOutput;
    std::vector<std::vector<int>> residualGraph;
    std::cout << "Max flow from fields to breweries: " << newGraph.MaxFlow(source, dest, browarsOutput, residualGraph);
    newGraph.UpdateMatrix(GraphReader::readToMatrix(argv[3]));
    newGraph.UpdateMatrix(GraphReader::addSource(newGraph.GetMatrix(), argv[2], 'b', 't'));
    newGraph.UpdateMatrixRow(browarsOutput, source);
    newGraph.PrintGraph();
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Max flow from brewieries to taverns: " << newGraph.MaxFlow(source, dest, browarsOutput, residualGraph);
    return 0;
}
