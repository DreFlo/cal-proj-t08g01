#include "Graph.h"

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double weight) {
    connections.push_back(Edge<T>(dest, weight));
}

template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *dest) {
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
Vertex<T>::Vertex(T contents): contents(contents), visited(false), processing(false), indegree(0) {}

template<class T>
Edge<T>::Edge(Vertex<T> *dest, double weight) {
    this->dest = dest;
    this->weight = weight;
}

template<class T>
Vertex<T> *Graph<T>::findVertex(const T &contents) const {
    for (auto vertex : vertexSet) if (vertex->contents == contents) return vertex;
    return nullptr;
}

template<class T>
unsigned int Graph<T>::getNumNodes() const {
    return vertexSet.size();
}

template<class T>
bool Graph<T>::addNode(const T &contents) {
    //if node doesn't exist add it and return true
    if (findVertex(contents) == nullptr) {
        vertexSet.push_back(new Vertex<T>(contents));
        return true;
    }
    return false;
}

template<class T>
bool Graph<T>::removeNode(const T &contents) {
    Vertex<T> *targetVertex;
    //if node exists
    if ((targetVertex = findVertex(contents)) != nullptr) {
        //remove all edges to target node
        for (auto vertex : vertexSet) vertex->removeEdgeTo(targetVertex);
        //free target node memory allocated in addNode() and remove it from vertexSet
        for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
            if (*it == targetVertex) {
                delete targetVertex;
                vertexSet.erase(it);
                return true;
            }
        return false;
    }
    return false;
}

template<class T>
bool Graph<T>::addEdge(const T &source, const T &dest, double weight) {
    Vertex<T> *sourceTargetVertex, *destTargetVertex;
    if ((sourceTargetVertex = findVertex(source)) != nullptr && (destTargetVertex = findVertex(dest)) != nullptr) {
        sourceTargetVertex->addEdge(destTargetVertex, weight);
        return true;
    }
    return false;
}

template<class T>
bool Graph<T>::removeEdge(const T &source, const T &dest) {
    Vertex<T> *sourceTargetVertex, *destTargetVertex;
    if ((sourceTargetVertex = findVertex(source)) != nullptr && (destTargetVertex = findVertex(dest)) != nullptr) {
        return sourceTargetVertex->removeEdgeTo(destTargetVertex);
    }
    return false;
}

template<class T>
bool Graph<T>::removeUnnecessaryEdges(const T &source){
    return false;
}
