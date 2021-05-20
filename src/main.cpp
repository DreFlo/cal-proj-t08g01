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

    //myGraph.readNodesFromFile("GridGraphs/16x16/nodes.txt");
    //myGraph.readEdgesFromFileAsBi("GridGraphs/16x16/edges.txt");

    myGraph.readNodesFromFile("Porto/porto_full_nodes_xy.txt");
    myGraph.readEdgesFromFile("Porto/porto_full_edges.txt");
    PapaRica papaRica(&myGraph);

    //problemGraph.startGraph->floydWarshallShortestPath();


    papaRica.setHQ(300);
    papaRica.addVehicle(Vehicle());

    papaRica.createClients();

    papaRica.assignOrdersToVehicles();

    papaRica.graph->setEdgePathType(papaRica.graph->getNearestNeighbourPath(papaRica.hq->getPosAtVec(), papaRica.vehicles[0]));
    /*
    for(auto idk: ) {
        cout << idk << endl;
    */

    viewGraph(papaRica.graph);
    return 0;
}
