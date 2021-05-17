#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>
#include <limits>
#include <fstream>
#include <regex>
#include <string>
#include <cmath>
#include <stack>

#include "Vehicle.h"

using namespace std;

#define DOUBLE_MAX numeric_limits<double>::max();

template <class T> class Edge;
template <class T> class Node;
template <class T> class Graph;

template <class T>
class Node {
private:
    T contents;
    //node contents
    std::vector<Edge<T>> connections;    //edges leaving from the node
    std::vector<Edge<T>> transposeConnections;
    bool visited;
    bool processing;
    int indegree;
    bool hidden;//if this node is traversable
    size_t posAtVec;//saves the position of the node in the graph's nodeSet
    pair<long double, long double> position; //position in terms of x and y

    /**
     * @brief Adds a new edge to the node
     * @param dest Destination of the edge
     * @param weight Edge weight
     */
    void addEdge(Node<T> *dest, double weight);
    /**
     * @brief Removes an edge from the node
     * @param dest Destination of the edge to remove
     * @return true if edge existed and was removed, false otherwise
     */
    bool removeEdgeTo(Node<T> *dest);

    void addTransposeEdge(Node<T> *dest, double weight);
public:
    explicit Node(T contents);
    friend class Graph<T>;
    T getContents() const;

    void setContents(T contents);
    vector<Edge<T>> getConnections();
    pair<long double, long double> getPosition();
};

template <class T>
class Edge {
private:
    Node<T> *dest;
    double weight;
public:
    Edge(Node<T> *dest, double weight);
    friend class Graph<T>;
    friend class Node<T>;
    double getWeight();
    Node<T>* getDest();
};

template <class T>
class Graph {
private:
    stack<Node<T> *> nodeStack;
    std::vector<Node<T> *> nodeSet;
    //node set
    std::vector<std::vector<double>> dist;
    //weights
    std::vector<std::vector<int>> next;//to reconstruct the path after running the algorithm

    /**
     * @brief Sets visited to false for all nodes
     */
    void resetVisited();
    /**
     * @brief Depth-first search on graph
     * @param source Node to start DFS in
     */
    void DFS(const T &source);

    void SCCVisit(Node<T> * src);

    vector<Node<T> *> transposeDFS(const T &src);

    explicit Graph(vector<Node<T> *> nodes);
public:
    Graph();
    const vector<std::vector<double>> &getDist() const;
    /**
     * @return Number of nodes in the graph
     */
    unsigned int getNumNodes() const;
    /**
     * @brief Adds a new node to the graph
     * @param contents Contents of the new node
     * @return true if node didn't exist and was added, false otherwise
     */
    bool addNode(const T &contents);
    /**
     * @brief Removes a node from the graph
     * @param contents Contents of the node to remove
     * @return true if node existed and was removed, false otherwise
     */
    bool removeNode(const T &contents);
    /**
     * @brief Adds and edge to the graph
     * @param source Contents of the source node
     * @param dest Contentes of the destination node
     * @param weight Weight of the connection
     * @return true if both nodes exists and edge was added, false otherwise
     */
    bool addUniEdge(const T &source, const T &dest, double weight);

    // TODO: Comment
    void addBiEdge(const T &source, const T &dest, double weight);

    /**
     * @brief Removes an edge from the graph
     * @param source Contents of the source of the edge
     * @param dest Contents of the destination of the edge
     * @return true if edge existed and was removed, false otherwise
     */
    bool removeEdge(const T &source, const T &dest);
    std::vector<Node<T>*> getNodeSet() const;

    /**
     * Remove the unnecessary edges, setting the weight value to infinite
     * @param source initial node
     */
    void removeUnnecessaryEdges(const T &source);

    /**
     * Return the weight value from edge between the node with index i and j
     * @return
     */
    double edgeCost(int i, int j);

    /**
     * Return the nest node of the path
     * @return return -1 if j is not the next path, j otherwise
     */
    int nodePrev(int i, int j);

    /**
     * Floyd Warshall Algorithm
     *  Algorithm used to calculate the shortest path between all the pairs of nodes
     *  in the graph
     */
    void floydWarshallShortestPath();

    /**
     * Sequence of elements in the graph in the path from u to v
     * @param source info from the initial node
     * @param destination info from the final node
     * @return vector with path
     */
    std::vector<T> getFloydWarshallPath(const T &source, const T &destination);

    /**
     * Return the Node in nodeSet with index n
     * @return Node in nodeSet with index n
     */
    Node<T> * operator[](int n);


    std::vector<T> getNearestNeighbourPath(T info, const Vehicle& vehicle);

    void printDist() const;

    void readGraphFromFile(string node_file, string edge_file);
    void readNodesFromFile(string file);
    void readEdgesFromFile(string file);
    void readEdgesFromFileAsBi(string file);
    void addNode(T &contents, pair<double, double> position);
    vector<vector<Node<T> *>> getSCCs();

    Graph<T> * getLargestSCC();

    void setNodeSet(const vector<Node<T> *> &nodeSet);

    Node<T> *findNode(const T &contents) const;
    Node<T> *findNode(const std::pair<long double, long double> &pair) const;

};

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
    this->contents = contents;
}

template <class T>
pair<long double, long double> Node<T>::getPosition(){
    return this->position;
}

template<class T>
vector<Edge<T>> Node<T>::getConnections() {
    return connections;
}

template<class T>
void Node<T>::addTransposeEdge(Node<T> *dest, double weight) {
    transposeConnections.push_back(Edge<T>(dest, weight));
}

template<class T>
Edge<T>::Edge(Node<T> *dest, double weight) {
    this->dest = dest;
    this->weight = weight;
}

template<class T>
double Edge<T>::getWeight(){
    return weight;
}

template<class T>
Node<T>* Edge<T>::getDest() {
    return this->dest;
}

template<class T>
Node<T> *Graph<T>::findNode(const T &contents) const {
    for (auto node : nodeSet) if (node->contents == contents) return node;
    return nullptr;
}

template<class T>
void Graph<T>::resetVisited() {
    for(auto node : nodeSet) node->visited = false;
}

template<class T>
unsigned int Graph<T>::getNumNodes() const {
    return nodeSet.size();
}

template<class T>
bool Graph<T>::addNode(const T &contents) {
    //if node doesn't exist add it and return true
    if (findNode(contents) == nullptr) {
        auto * node = new Node<T>(contents);
        node->posAtVec = nodeSet.size();
        nodeSet.push_back(node);
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
bool Graph<T>::addUniEdge(const T &source, const T &dest, double weight) {
    Node<T> *sourceTargetNode, *destTargetNode;
    if ((sourceTargetNode = findNode(source)) != nullptr && (destTargetNode = findNode(dest)) != nullptr) {
        sourceTargetNode->addEdge(destTargetNode, weight);
        destTargetNode->addTransposeEdge(sourceTargetNode, weight);
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
vector<Node<T>*> Graph<T>::getNodeSet() const {
    return nodeSet;
}

template<class T>
void Graph<T>::removeUnnecessaryEdges(const T &source){
    resetVisited();
    DFS(source);
    for(auto node : nodeSet){
        if (!(node->visited)){
            for(auto &edge : node->connections){
                edge.weight = DOUBLE_MAX;
            }
        }
    }
}

template<class T>
void Graph<T>::DFS(const T &source) {
    Node<T> * node = findNode(source);
    node->visited = true;

    for (auto i = node->connections.begin(); i != node->connections.end(); i++)
        if (!i->dest->visited)
            DFS(i->dest->contents);
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    int N = nodeSet.size(); //size of the square matrix
    dist = vector<vector<double> >(N, vector<double>(N));
    next = vector<vector<int> >(N, vector<int>(N));

    // Set dist to edge cost, and previous edge
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
vector<T> Graph<T>::getFloydWarshallPath(const T &source, const T &destination) {
    Node<T>* src = findNode(source);
    Node<T>* dest = findNode(destination);

    vector<T> result;
    int v = src->posAtVec, w = dest->posAtVec;

    result.push_back(nodeSet[v].info);
    while (v != w) {
        v = next[v][w];
        if (v < 0)
            break;
        result.push_back(nodeSet[v].info);
    }
    return result;
}

template<class T>
Node<T> *Graph<T>::operator[](int n) {
    return nodeSet[n];
}

template<class T>
std::vector<T> Graph<T>::getNearestNeighbourPath(T info, const Vehicle& vehicle) {
    // Working


    std::vector<T> sortedNodes;
    std::vector<T> result;

    result.push_back(info);

    for(MealBasket meal: vehicle.getMeals()) {
        sortedNodes.push_back(findNode(meal.getAddress())->contents);
    }

    while(!sortedNodes.empty()) {
        // Sorted relative to dist to info
        sort(sortedNodes.begin(), sortedNodes.end(),
             [info, dist = getDist(), this](const T& t1, const T& t2) -> bool{
                 return dist[findNode(t1)->posAtVec][findNode(info)->posAtVec]
                        < dist[findNode(t2)->posAtVec][findNode(info)->posAtVec];
             });

        result.push_back(info = sortedNodes[0]);
        sortedNodes.erase(sortedNodes.begin());
    }

    result.push_back(result[0]);

    return result;
}


template<class T>
const vector<std::vector<double>> &Graph<T>::getDist() const {
    return dist;
}

template<class T>
void Graph<T>::addBiEdge(const T &source, const T &dest, double weight) {
    addUniEdge(source, dest, weight);
    addUniEdge(dest, source, weight);
}

template<class T>
void Graph<T>::printDist() const {
    for(int i = 0; i < dist.size(); i++) {
        for(int j = 0; j < dist[i].size(); j++){
            if(dist[i][j] > 100)
                cout << i+1 << " -> " << j+1 << " - dist: INF" << "\t";
            else
                cout << i+1 << " -> " << j+1 << " - dist: " << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

template<class T>
void Graph<T>::readEdgesFromFile(string file) {
    fstream node_file;
    string line;
    vector<Node<T>*> nodes;

    node_file.open(file);
    std::getline(node_file, line);

    string comma = ",";
    size_t pos;
    while(std::getline(node_file, line)){
        string temp;
        T source, dest;
        int pos;

        line = line.substr(1, line.length() - 2);

        pos = line.find(comma);
        temp = line.substr(0, pos);
        source = stoi(temp);
        line.erase(0, pos + 1);

        dest = stoi(line);

        auto src = findNode(source);
        auto dst = findNode(dest);

        pair<long double, long double> posSrc, posDst;
        posSrc = src->getPosition();
        posDst = dst->getPosition();

        long double weight = sqrt(pow(posSrc.first - posDst.first, 2) + pow(posSrc.second - posDst.second, 2));

        addUniEdge(source, dest, weight);
    }
}

template <class T>
void Graph<T>::readNodesFromFile(string file) {
    fstream node_file;
    string line;
    vector<Node<T>*> nodes;
    size_t posAtVec = 0;

    node_file.open(file);
    getline(node_file, line);

    string comma = ",";
    size_t pos;
    while(std::getline(node_file, line)){
        string temp;
        T info;
        pair<long double, long double> position;
        int pos;

        line = line.substr(1, line.length() - 2);

        pos = line.find(comma);
        temp = line.substr(0, pos);
        info = stoi(temp);
        line.erase(0, pos + 1);

        pos = line.find(comma);
        temp = line.substr(0, pos);
        position.first = stold(temp);
        line.erase(0, pos + 1);

        position.second = stold(line);

        Node<T> *node = new Node<T>(info);
        node->position = position;
        node->posAtVec = posAtVec;
        nodes.push_back(node);

        posAtVec++;
    }
    this->nodeSet = nodes;
}

template<class T>
vector<vector<Node<T> *>> Graph<T>::getSCCs() {
    vector<vector<Node<T> *>> res;

    while(!nodeStack.empty()) nodeStack.pop();

    for (auto node : nodeSet) node->visited = false;

    for (auto node : nodeSet) if (!node->visited) SCCVisit(node);

    for (auto node : nodeSet) node->visited = false;

    while (!nodeStack.empty()) {
        Node<T> * node = nodeStack.top();
        nodeStack.pop();

        if (!node->visited) {
            res.push_back(transposeDFS(node->contents));
        }
    }

    return res;
}

template<class T>
void Graph<T>::SCCVisit(Node<T> * src) {
    src->visited = true;

    for (auto edge : src->connections)
        if (!edge.dest->visited)
            SCCVisit(edge.dest);

    nodeStack.push(src);
}

template<class T>
void Graph<T>::setNodeSet(const vector<Node<T> *> &nodeSet) {
    Graph::nodeSet = nodeSet;
}

template<class T>
vector<Node<T> *> Graph<T>::transposeDFS(const T &src) {
    vector<Node<T> * > res;
    Node<T> * node = findNode(src);
    res.push_back(node);
    node->visited = true;

    for (auto i = node->transposeConnections.begin(); i != node->transposeConnections.end(); i++)
        if (!i->dest->visited) {
            vector<Node<T> * > temp = transposeDFS(i->dest->contents);
            res.insert(res.end(), temp.begin(), temp.end());
        }

    return res;
}

template<class T>
Graph<T> * Graph<T>::getLargestSCC() {
    vector<vector<Node<T> *>> SCCs = getSCCs();
    vector<Node<T> *> nodes =  *max_element(SCCs.begin(), SCCs.end(), [](const vector<Node<T> *> &v1, const vector<Node<T> *> &v2) -> bool{
            return v1.size() < v2.size();}
            );
    return new Graph<T>(nodes);
}

template<class T>
Graph<T>::Graph(vector<Node<T> *> nodes) {
    Graph<T>::nodeSet = nodes;
    for (int i = 0; i < nodeSet.size(); i++) nodeSet[i]->posAtVec = i;
}

template<class T>
void Graph<T>::readEdgesFromFileAsBi(string file) {
    fstream node_file;
    string line;
    vector<Node<T>*> nodes;

    node_file.open(file);
    std::getline(node_file, line);

    string comma = ",";
    size_t pos;
    while(std::getline(node_file, line)){
        string temp;
        T source, dest;
        int pos;

        line = line.substr(1, line.length() - 2);

        pos = line.find(comma);
        temp = line.substr(0, pos);
        source = stoi(temp);
        line.erase(0, pos + 1);

        dest = stoi(line);

        auto src = findNode(source);
        auto dst = findNode(dest);

        pair<long double, long double> posSrc, posDst;
        posSrc = src->getPosition();
        posDst = dst->getPosition();

        long double weight = sqrt(pow(posSrc.first - posDst.first, 2) + pow(posSrc.second - posDst.second, 2));

        addBiEdge(source, dest, weight);
    }
}

template<class T>
Node<T> *Graph<T>::findNode(const std::pair<long double, long double> &pair) const {
    for(auto node: nodeSet) if(node->getPosition() == pair) return node;
}

template<class T>
Graph<T>::Graph() = default;

#endif //PROJ_GRAPH_H
