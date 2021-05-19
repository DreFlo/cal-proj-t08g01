#include "graphviewer.h"
#include "Graph.h"

using namespace std;
using GVNode = GraphViewer::Node;
using GVEdge = GraphViewer::Edge;

template <class T>
void viewGraph(Graph<T>* graph){
    GraphViewer gv;
    gv.setScale(7.0);
    gv.setCenter(sf::Vector2f(2500, -500));

    vector<Node<T>*> nodes = graph->getNodeSet();

    for(GraphViewer::id_t i = 0; i < nodes.size(); i++){
        pair<long double, long double> pos = nodes[i]->getPosition();
        GVNode &node = gv.addNode(i, sf::Vector2f(pos.first, pos.second));
    }

    GraphViewer::id_t idEdge = 0;
    for(auto node : nodes){
        for(auto edge : node->getConnections()){
            if (edge.getWeight() == numeric_limits<double>::max())
                continue;
            gv.addEdge(idEdge, gv.getNode(node->getPosAtVec()), gv.getNode(edge.getDest()->getPosAtVec()),
                       GraphViewer::Edge::UNDIRECTED);
            idEdge++;
        }
    }

    //gv.setEnabledNodes(false);
    gv.setEnabledEdgesText(false);
    gv.setZipEdges(true);

    gv.createWindow(1600, 900);
    gv.join();
}

