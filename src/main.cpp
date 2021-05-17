#include <iostream>
#include "Graph.h"
#include "Vehicle.h"
#include "ProblemGraph.h"
#include <string>

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

    for (auto idk : problemGraph.startGraph->getNearestNeighbour(0)) {
        cout << idk << endl;
    }

    return 0;
}
