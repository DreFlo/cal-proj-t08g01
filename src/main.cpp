#include <ctime>
#include <iostream>
#include <cstdlib>

#include "Graph.h"
#include "ProblemGraph.h"
#include "Viewer.cpp"


using namespace std;

int main() {
    srand((unsigned int)time(nullptr)); rand();
    Graph<int> myGraph;

    myGraph.readNodesFromFile("GridGraphs/4x4/nodes.txt");
    myGraph.readEdgesFromFileAsBi("GridGraphs/4x4/edges.txt");

    //myGraph.readNodesFromFile("Porto/porto_full_nodes_xy.txt");
    //myGraph.readEdgesFromFile("Porto/porto_full_edges.txt");

    //viewGraph(myGraph.getLargestSCC());

    //problemGraph.startGraph->floydWarshallShortestPath();
    ProblemGraph problemGraph(&myGraph);
    problemGraph.input();

    /*
    problemGraph.setHQ(0);

    problemGraph.addVehicle(Vehicle());

    problemGraph.createClients(20);

    problemGraph.assignOrdersToVehicles();

    for(auto idk: problemGraph.startGraph->getFloydWarshallPath(problemGraph.startGraph->getNearestNeighbourPath(0, problemGraph.vehicles[0]))) {
        cout << idk << endl;
    }*/
    //(problemGraph.startGraph);
    cout << problemGraph.getOrders().size() << endl;

    return 0;
}
