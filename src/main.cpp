#include <ctime>
#include <iostream>
#include <cstdlib>
#include <chrono>

#include "Graph.h"
#include "PapaRica.h"
#include "Viewer.cpp"


using namespace std;

int main() {
    srand((unsigned int)time(nullptr)); rand();
    Graph<int> myGraph;

    myGraph.readNodesFromFile("GridGraphs/4x4/nodes.txt");
    myGraph.readEdgesFromFileAsBi("GridGraphs/4x4/edges.txt");

    PapaRica papaRica(&myGraph);

    papaRica.input();

    /*
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
        if(papaRica.isAStar())
            papaRica.graph->setEdgePathType(papaRica.graph->getNearestNeighbourPathAStar(papaRica.hq->getPosAtVec(), vehicle));
        else
            papaRica.graph->setEdgePathType(papaRica.graph->getNearestNeighbourPathFloydWarshall(papaRica.hq->getPosAtVec(), vehicle));
        viewGraph(papaRica.graph);
    }*/

    return 0;
}
