#include <iostream>
#include "Graph.h"
#include "ProblemGraph.h"

using namespace std;

int main() {
    Graph<int> myGraph;

    myGraph.readNodesFromFile("GridGraphs/16x16/nodes.txt");
    myGraph.readEdgesFromFileAsBi("GridGraphs/16x16/edges.txt");

    myGraph.removeUnnecessaryEdges(1);

    ProblemGraph problemGraph(myGraph.getLargestSCC());

    problemGraph.startGraph->floydWarshallShortestPath();

    problemGraph.setHQ(0);

    problemGraph.addVehicle(Vehicle());

    problemGraph.addOrder(MealBasket(10, 0, "Client1",
                                     pair<long double, long double>(0, 37)));
    problemGraph.addOrder(MealBasket(13, 1, "Client2",
                                     pair<long double, long double>(0, 222)));

    problemGraph.assignOrdersToVehicles();

    for (auto idk : problemGraph.startGraph->getNearestNeighbourPath(0, problemGraph.vehicles[0])) {
        cout << problemGraph.startGraph->findNode(idk)->getPosition().second << endl;
    }

    return 0;
}
