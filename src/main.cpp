#include <ctime>
#include <iostream>
#include <cstdlib>


#include "Graph.h"
#include "ProblemGraph.h"

using namespace std;

int main() {
    srand((unsigned int)time(nullptr)); rand();
    Graph<int> myGraph;

    myGraph.readNodesFromFile("GridGraphs/16x16/nodes.txt");
    myGraph.readEdgesFromFileAsBi("GridGraphs/16x16/edges.txt");

    myGraph.removeUnnecessaryEdges(1);

    ProblemGraph problemGraph(myGraph.getLargestSCC());

    problemGraph.startGraph->floydWarshallShortestPath();

    problemGraph.setHQ(0);

    problemGraph.addVehicle(Vehicle());

    problemGraph.createClients();

    problemGraph.assignOrdersToVehicles();

    for(auto idk: problemGraph.startGraph->getFloydWarshallPath(problemGraph.startGraph->getNearestNeighbourPath(0, problemGraph.vehicles[0]))) {
        cout << idk << endl;
    }

    return 0;
}
