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

    /* VIEW PORTO's GRAPHIC
     * WARNING: SLOW
    myGraph.readNodesFromFile("Porto/porto_strong_nodes_xy.txt");
    myGraph.readEdgesFromFile("Porto/porto_strong_edges.txt");

    viewGraph(&myGraph);
     */

    myGraph.readNodesFromFile("GridGraphs/16x16/nodes.txt");
    myGraph.readEdgesFromFile("GridGraphs/16x16/edges.txt");

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
