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
        switch (nodes[i]->getType()) {
            case HQ:
                node.setColor(sf::Color::Magenta);
                node.setLabel("HQ");
                node.setLabelSize(100);
                node.setSize(100.0);
                break;
            case CLIENT:
                node.setColor(sf::Color::Blue);
                node.setLabel("CLIENT");
                node.setLabelSize(100);
                node.setSize(100.0);
                break;
            case OTHER:
                node.setColor(sf::Color::Red);
                break;
        }
    }

    GraphViewer::id_t idEdge = 0;
    for(auto node : nodes){
        for(auto edge : node->getConnections()){
            if (edge.getWeight() == numeric_limits<double>::max())
                continue;
            GVEdge &gvEdge = gv.addEdge(idEdge, gv.getNode(node->getPosAtVec()), gv.getNode(edge.getDest()->getPosAtVec()),
                            GraphViewer::Edge::UNDIRECTED);
            switch (edge.getType()) {
                case PATH:
                    gvEdge.setColor(sf::Color::Blue);
                    gvEdge.setThickness(10.0);
                    break;
                default:
                    gvEdge.setColor(sf::Color::Black);
                    gvEdge.setDashed(true);
                    break;
            }
            idEdge++;
        }
    }

    //gv.setEnabledNodes(false);
    gv.setEnabledEdgesText(false);
    gv.setZipEdges(true);

    gv.createWindow(1600, 900);
    gv.join();
}

