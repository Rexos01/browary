#include "lib/graph.h"
#include "lib/graph_reader.h"

void PrintVector(std::vector<int> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i] << " ";
    }
}

int main(int argc, char* argv[])
{
    Graph newGraph = Graph(GraphReader::readToMatrix(argv[1]));
    newGraph.UpdateMatrix(GraphReader::addSource(newGraph.GetMatrix(), argv[2], 'p', 'b'));
    newGraph.PrintGraph();
    int source = newGraph.GetMatrix().size() - 1;
    int dest = newGraph.GetMatrix().size() - 2;
    std::vector<int> browarsOutput;
    std::vector<std::vector<int>> residualGraph;
    std::cout << "Max flow from fields to breweries: " << newGraph.MaxFlow(source, dest, browarsOutput,residualGraph);
    newGraph.UpdateMatrix(GraphReader::readToMatrix(argv[3]));
    newGraph.UpdateMatrix(GraphReader::addSource(newGraph.GetMatrix(), argv[2], 'b', 't'));
    newGraph.UpdateMatrixRow(browarsOutput, source);
    std::cout << std::endl;
    newGraph.PrintGraph();
    std::cout << std::endl;
    std::cout << "Max flow from brewieries to taverns: " << newGraph.MaxFlow(source, dest, browarsOutput, residualGraph);
    return 0;
}
