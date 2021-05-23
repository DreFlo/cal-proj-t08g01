#include <ctime>
#include <iostream>
#include <cstdlib>

#include "Graph.h"
#include "PapaRica.h"
#include "Viewer.cpp"


using namespace std;

int main() {
    srand((unsigned int)time(nullptr)); rand();
    srand((unsigned int)time(nullptr)); rand();
    Graph<int> myGraph;

    myGraph.readNodesFromFile("Porto/porto_full_nodes_xy.txt");
    myGraph.readEdgesFromFile("Porto/porto_full_edges.txt");
    PapaRica papaRica(&myGraph);

    papaRica.input();

    papaRica.setHQ(300);
    papaRica.addVehicle(Vehicle(HEAVY, 35));
    papaRica.addVehicle(Vehicle(HEAVY, 25));
    papaRica.addVehicle(Vehicle(HEAVY, 40));
    papaRica.addVehicle(Vehicle(HEAVY, 20));
    papaRica.addVehicle(Vehicle(HEAVY, 45));
    papaRica.addVehicle(Vehicle(HEAVY, 50));

    papaRica.createClients(rand() % 15 + 5);

    papaRica.assignOrdersToVehicles();

    cout << "Number of trajectories: " << papaRica.getUsedVehicles() << endl;

    for (const Vehicle& vehicle : papaRica.vehicles) {
        if(vehicle.getUsed() > 0) {
            papaRica.graph->resetEdgeTypes();
            if (papaRica.isAStar())
                papaRica.graph->setEdgePathType(
                        papaRica.graph->getNearestNeighbourPathAStar(papaRica.hq->getPosAtVec(), vehicle));
            else
                papaRica.graph->setEdgePathType(
                        papaRica.graph->getNearestNeighbourPathFloydWarshall(papaRica.hq->getPosAtVec(), vehicle));
            viewGraph(papaRica.graph);
        }
    }

    return 0;
}
