#include "graph.h"
#include "graph_reader.h"

void PrintVector(std::vector<int> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        std::cout << vector[i] << " ";
    }
}

int main()
{
    Graph newGraph = Graph(GraphReader::readToMatrix("graph.txt"), GraphReader::readToMatrixOfCosts("graph.txt"));
    newGraph.UpdateMatrix(GraphReader::addSource(newGraph.GetMatrix(), "sources.txt", 'p', 'b'));
    //newGraph.PrintGraph();
    int source = newGraph.GetMatrix().size() - 1;
    int dest = newGraph.GetMatrix().size() - 2;
    std::vector<int> browarsOutput;
    std::vector<std::vector<int>> residualGraph;
    std::cout << "Max flow from fields to breweries: " << newGraph.MaxFlow(source, dest, browarsOutput, residualGraph);

    std::cout << std::endl;
    newGraph.UpdateMatrixOfCosts(GraphReader::addSourceToMatrixOfCosts(newGraph.GetMatrixOfCosts(), "sources.txt", 'b', 't'));
    newGraph.AssignToMatrixofcosts(residualGraph);
    newGraph.Print(residualGraph);
        std::cout << std::endl;

    newGraph.PrintMatrixOfCosts();
        std::cout << std::endl;


    newGraph.BellmanFord(source);
    newGraph.PrintMatrixOfCosts();   //?????

    /*
        newGraph.UpdateMatrix(GraphReader::readToMatrix("brew_tavern.txt"));
        newGraph.UpdateMatrix(GraphReader::addSource(newGraph.GetMatrix(), "sources.txt", 'b', 't'));
        newGraph.UpdateMatrixRow(browarsOutput, source);
        std::cout << std::endl;
        newGraph.PrintGraph();
        std::cout << std::endl;
        newGraph.Print(residualGraph);
        std::cout << std::endl;
            std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        newGraph.Print(residualGraph);

        std::cout << "Max flow from brewieries to taverns: " << newGraph.MaxFlow(source, dest, browarsOutput, residualGraph);
        std::cout << std::endl;
    */
    return 0;
}
