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
    newGraph.AssignToMatrixofcosts(residualGraph);
    newGraph.UpdateMatrixOfCosts(GraphReader::addSourceToMatrixOfCosts(newGraph.GetMatrixOfCosts(), "sources.txt", 'p', 'b'));

    std::cout << "Graph (capacity) after 1 MaxFlow:" << std::endl;
    newGraph.Print(residualGraph);
    std::cout << std::endl;
    std::cout << "Graph (flow) after 1 MaxFlow:" << std::endl;
    newGraph.PrintMatrixOfCosts();
    std::cout << std::endl;

    
    int bf=1;

    while((bf=newGraph.BellmanFord(source)) != -1);
 
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Graph (flow) after BellmanFord:" << std::endl;
    //newGraph.PrintMatrixOfCosts(); //?????



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


/*

0 7 3 0 0 0 0 0 2
0 0 0 0 0 0 0 0 6
2 0 0 2 1 0 0 0 4
0 4 1 0 0 0 0 0 0
0 2 2 0 0 1 0 0 0
0 0 3 0 0 0 0 0 0
0 0 0 5 4 3 0 8 0
0 0 0 0 0 0 12 0 0
1 1 0 0 0 0 0 0 0 

0 0 2 0 0 0 0 0 0
0 0 0 4 2 0 0 0 0
0 0 0 1 2 3 0 0 0
0 0 0 0 0 0 5 0 0
0 0 0 0 0 0 4 0 0
0 0 0 0 0 0 3 0 0
0 0 0 0 0 0 0 12 0 
0 0 0 0 0 0 0 0 0
2 6 4 0 0 0 0 0 0

0 2 2 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
-2 0 0 3 5 0 0 0 0
0 0 -3 0 0 0 0 0 0
0 0 -5 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0

*/