#include <ctime>
#include <iostream>
#include <cstdlib>

#include "Graph.h"
#include "PapaRica.h"
#include "Viewer.cpp"


using namespace std;

int main() {
    srand((unsigned int)time(nullptr)); rand();
    Graph<int> myGraph;

    myGraph.readNodesFromFile("GridGraphs/16x16/nodes.txt");
    myGraph.readEdgesFromFileAsBi("GridGraphs/16x16/edges.txt");

    //myGraph.readNodesFromFile("Porto/porto_full_nodes_xy.txt");
    //myGraph.readEdgesFromFile("Porto/porto_full_edges.txt");
    PapaRica papaRica(&myGraph);

    viewGraph(papaRica.graph);

    //problemGraph.startGraph->floydWarshallShortestPath();

    /*
    problemGraph.setHQ(0);

    problemGraph.addVehicle(Vehicle());

    problemGraph.createClients(50);

    problemGraph.assignOrdersToVehicles();*/

    /*for(auto idk: problemGraph.graph->getNearestNeighbourPath(0, problemGraph.vehicles[0])) {
        cout << idk << endl;*/
    return 0;
}
