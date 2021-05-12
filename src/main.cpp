#include <iostream>
#include "Graph.h"
#include "Vehicle.h"
#include "ProblemGraph.h"
#include <string>

using namespace std;

int main() {
    Graph<int> myGraph;

    myGraph.readNodesFromFile("GridGraphs/4x4/nodes.txt");
    myGraph.readEdgesFromFile("GridGraphs/4x4/edges.txt");

    vector<Node<int>*> nodes = myGraph.getNodeSet();

    /*
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

    myGraph.floydWarshallShortestPath();
    auto result = myGraph.getNearestNeighbour(1);

    for(auto i: result) {
        cout << i << endl;
    }
    */

    return 0;
}
