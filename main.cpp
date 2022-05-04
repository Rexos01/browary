#include "graph.h"
#include "graph_reader.h"

int main(){
    Graph newGraph = Graph(GraphReader::readToMatrix("graph.txt"));
    newGraph.PrintGraph();
    std::cout<< "Max flow: " << newGraph.MaxFlow(0, 5);
    return 0;
}