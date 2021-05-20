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
    papaRica.addVehicle(Vehicle(HEAVY, 5));
    papaRica.addVehicle(Vehicle(HEAVY, 10));
    papaRica.addVehicle(Vehicle(HEAVY, 15));

    //TODO revert create clients back to random package numbers
    papaRica.createClients(5);

    papaRica.assignOrdersToVehicles();

    for (const Vehicle& vehicle : papaRica.vehicles) {
        papaRica.graph->resetEdgeTypes();
        cout << endl << vehicle.getCap() << endl << vehicle.getUsed() << endl << endl;
        papaRica.graph->setEdgePathType(papaRica.graph->getNearestNeighbourPath(papaRica.hq->getPosAtVec(), vehicle));
        viewGraph(papaRica.graph);
    }
    /*
    for(auto idk: ) {
        cout << idk << endl;
    */

    return 0;
}
