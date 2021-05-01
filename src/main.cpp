#include <iostream>
#include "Graph.h"
#include "Vehicle.h"

using namespace std;

int main() {
    Graph<int> myGraph;

    for(int i = 1; i < 8; i++)
        myGraph.addNode(i);

    myGraph.addEdge(1, 2, 3);
    myGraph.addEdge(1, 3, 2);
    myGraph.addEdge(2, 5, 4);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 3, 1);
    myGraph.addEdge(3, 5, 2);
    myGraph.addEdge(4, 6, 2);
    myGraph.addEdge(5, 6, 3);
}
