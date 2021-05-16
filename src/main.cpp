#include <iostream>
#include "Graph.h"
#include "Vehicle.h"
#include "ProblemGraph.h"
#include <string>

using namespace std;

int main() {
    Graph<int> myGraph;

    myGraph.readNodesFromFile("GridGraphs/16x16/nodes.txt");
    myGraph.readEdgesFromFile("GridGraphs/16x16/edges.txt");

    myGraph.removeUnnecessaryEdges(1);

    ProblemGraph problemGraph(&myGraph);

    problemGraph.addVehicle(Vehicle());

    problemGraph.addOrder(MealBasket(10, 0, "Client1",
                                     pair<long double, long double>(0, 37)));
    problemGraph.addOrder(MealBasket(13, 1, "Client1",
                                     pair<long double, long double>(0, 222)));

    problemGraph.assignOrdersToVehicles();

    return 0;
}
