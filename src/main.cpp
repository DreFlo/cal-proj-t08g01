#include <iostream>
#include "Graph.h"
#include "Vehicle.h"
#include "ProblemGraph.h"

using namespace std;

int main() {
    Graph<int> myGraph;

    for(int i = 1; i < 7; i++)
        myGraph.addNode(i);

    myGraph.addBiEdge(1, 2, 3);
    myGraph.addBiEdge(1, 3, 2);
    myGraph.addBiEdge(2, 5, 4);
    myGraph.addBiEdge(2, 4, 3);
    myGraph.addBiEdge(2, 3, 1);
    myGraph.addBiEdge(3, 5, 2);
    myGraph.addBiEdge(4, 6, 2);
    myGraph.addBiEdge(5, 6, 3);

    std::vector<int> vec = {1, 2, 3, 4, 5};
    myGraph.floydWarshallShortestPath();

    myGraph.printDist();

    myGraph.sortRelativeToDistQuick(0, vec);

    for(auto i: vec) {
        cout << i+1 << "\t";
    }
    cout << endl;
    return 0;
}
