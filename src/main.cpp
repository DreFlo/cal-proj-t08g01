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


    myGraph.readNodesFromFile("Porto/porto_full_nodes_xy.txt");
    myGraph.readEdgesFromFile("Porto/porto_full_edges.txt");

    PapaRica problemGraph(&myGraph);

    //problemGraph.startGraph->floydWarshallShortestPath();


    problemGraph.setHQ(0);

    problemGraph.addVehicle(Vehicle());

    problemGraph.createClients(20);

    problemGraph.assignOrdersToVehicles();

    /*
    for(auto idk: problemGraph.startGraph->getNearestNeighbourPath(0, problemGraph.vehicles[0])) {
        cout << idk << endl;
    }*/

    return 0;
}
