#include "Graph.h"

template<class T>
void Node<T>::addEdge(Node<T> *dest, double weight) {
    connections.push_back(Edge<T>(dest, weight));
}

template<class T>
bool Node<T>::removeEdgeTo(Node<T> *dest) {
    for (auto it = connections.begin(); it != connections.end(); it++) {
        //if edge destination equals dest remove it and return true
        if (it->dest == dest) {
            connections.erase(it);
            return true;
        }
    }
    return false;
}

template<class T>
Node<T>::Node(T contents): contents(contents), visited(false), processing(false), indegree(0) {}

template<class T>
T Node<T>::getContents() const {
    return contents;
}

template<class T>
void Node<T>::setContents(T contents) {
    Node::contents = contents;
}

template<class T>
Edge<T>::Edge(Node<T> *dest, double weight) {
    this->dest = dest;
    this->weight = weight;
}

template<class T>
Node<T> *Graph<T>::findNode(const T &contents) const {
    for (auto node : nodeSet) if (node->contents == contents) return node;
    return nullptr;
}

template<class T>
unsigned int Graph<T>::getNumNodes() const {
    return nodeSet.size();
}

template<class T>
bool Graph<T>::addNode(const T &contents) {
    //if node doesn't exist add it and return true
    if (findNode(contents) == nullptr) {
        nodeSet.push_back(new Node<T>(contents));
        return true;
    }
    return false;
}

template<class T>
bool Graph<T>::removeNode(const T &contents) {
    Node<T> *targetNode;
    //if node exists
    if ((targetNode = findNode(contents)) != nullptr) {
        //remove all edges to target node
        for (auto node : nodeSet) node->removeEdgeTo(targetNode);
        //free target node memory allocated in addNode() and remove it from nodeSet
        for (auto it = nodeSet.begin(); it != nodeSet.end(); it++)
            if (*it == targetNode) {
                delete targetNode;
                nodeSet.erase(it);
                return true;
            }
        return false;
    }
    return false;
}

template<class T>
bool Graph<T>::addEdge(const T &source, const T &dest, double weight) {
    Node<T> *sourceTargetNode, *destTargetNode;
    if ((sourceTargetNode = findNode(source)) != nullptr && (destTargetNode = findNode(dest)) != nullptr) {
        sourceTargetNode->addEdge(destTargetNode, weight);
        return true;
    }
    return false;
}

template<class T>
bool Graph<T>::removeEdge(const T &source, const T &dest) {
    Node<T> *sourceTargetNode, *destTargetNode;
    if ((sourceTargetNode = findNode(source)) != nullptr && (destTargetNode = findNode(dest)) != nullptr) {
        return sourceTargetNode->removeEdgeTo(destTargetNode);
    }
    return false;
}

template<class T>
bool Graph<T>::removeUnnecessaryEdges(const T &source){
    return false;
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    int N = nodeSet.size(); //size of the square matrix
    dist = vector<vector<double> >(N, vector<double>(N));
    next = vector<vector<int> >(N, vector<int>(N));

    //first step, set weight and previous
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            dist[i][j] = edgeCost(i, j);
            next[i][j] = nodePrev(i, j);
        }


    // Floyd-Warshall Algorithm
    for (int k = 0; k < N; k++) {
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j])) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

template<class T>
double Graph<T>::edgeCost(int i, int j) {
    if (i == j)
        return 0;

    for (auto edge : nodeSet[i]->connections)
        if (edge.dest == nodeSet[j])
            return edge.weight;

    return INT_MAX;
}

template<class T>
int Graph<T>::nodePrev(int i, int j) {
    for (auto edge : nodeSet[i]->connections) {
        if (edge.dest == nodeSet[j])
            return j;
    }

    return -1;
}

template<class T>
vector<Node<T> *> Graph<T>::getFloydWarshallPath(Node<T> *src, Node<T> *dest) {
    vector<Node<T> * > result;
    int found = 0;
    int v = src->posAtVec, w = dest->posAtVec;

    result.push_back(nodeSet[v]);
    while (v != w) {
        v = next[v][w];
        if (v < 0)
            break;
        result.push_back(nodeSet[v]);
    }
    return result;
}

template<class T>
Node<T> *Graph<T>::operator[](int n) {
    return nodeSet[n];
}

