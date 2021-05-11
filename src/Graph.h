#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <algorithm>
#include <vector>
#include <climits>
#include <iostream>
#include <limits>

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
    bool visited;
    bool processing;
    int indegree;
    bool hidden;//if this node is traversable
    size_t posAtVec;//saves the position of the node in the graph's nodeSet

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
public:
    explicit Node(T contents);
    friend class Graph<T>;
    T getContents() const;

    void setContents(T contents);
    vector<Edge<T>> getConnections();
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
};

template <class T>
class Graph {
private:
    std::vector<Node<T> *> nodeSet;  //node set
    std::vector<std::vector<double>> dist;
    //weights
    std::vector<std::vector<int>> next;//to reconstruct the path after running the algorithm

    Node<T> *findNode(const T &contents) const;
    /**
     * @brief Sets visited to false for all nodes
     */
    void resetVisited();
    /**
     * @brief Depth-first search on graph
     * @param source Node to start dfs in
     */
    void dfs(const T &source);
public:

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


    // TODO: comment
    void sortRelativeToDistQuick(T info, std::vector<T> &sortedNodes, int i = -1, int j = 100);
    void sortRelativeToDistInsertion(T info, std::vector<T> &sortedNodes);

    std::vector<T> getNearestNeighbour(T info);

    void printDist() const;
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

template<class T>
vector<Edge<T>> Node<T>::getConnections() {
    return connections;
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
    dfs(source);
    for(auto node : nodeSet){
        if (!(node->visited)){
            for(auto &edge : node->connections){
                edge.weight = DOUBLE_MAX;
            }
        }
    }
}

template<class T>
void Graph<T>::dfs(const T &source) {
    auto node = findNode(source);
    node->visited = true;

    for (auto edge : node->connections) {
        if (!(edge.dest->visited)) {
            dfs(edge.dest->contents);
        }
    }
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
std::vector<T> Graph<T>::getNearestNeighbour(T info) {

    std::vector<T> sortedNodes;

    for(Node<T>* node: nodeSet)
        if(node->info != info)
            sortedNodes.push_back(node->info);



    std::vector<T> result;
    result.push_back(info);

    while(!sortedNodes.empty()) {
        sort(sortedNodes.begin(), sortedNodes.end(),
             [info, dist = getDist()](const T& t1, const T& t2) -> bool{
                 return dist[t1][info] < dist[t2][info];
             });
    }
    return result;
}


template<class T>
void Graph<T>::sortRelativeToDistQuick(T info, std::vector<T> &sortedNodes, int ii, int jj) {
    sort(sortedNodes.begin(), sortedNodes.end(),
         [info, dist = getDist()](const T& t1, const T& t2) -> bool{
             return dist[t1][info] < dist[t2][info];
         });
    /*
    // Using quick sort
    if(jj - ii < 10) {
        sortRelativeToDistInsertion(info, sortedNodes);
    }
    int i, j;

    if(i < 0) {
        i = 0; j = sortedNodes.size()-1;
    } else {
        i = ii, j = jj-1;
    }

    int m = dist[sortedNodes[(i + j)/2]][info];

    while( true ) {
        while( dist[sortedNodes[i]][info] < m ) {
            i++;
        }
        while( dist[sortedNodes[j]][info] > m ) {
            j++;
        }

        if( i < j ) {
            int aux = sortedNodes[i];
            sortedNodes[i] = sortedNodes[j];
            sortedNodes[j] = sortedNodes[i];
        } else {
            break;
        }

    }
    sortRelativeToDistQuick(info, sortedNodes, ii, i-1);
    sortRelativeToDistQuick(info, sortedNodes, i+1, jj);
    */
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
void Graph<T>::sortRelativeToDistInsertion(T info, vector<T> &sortedNodes) {
    for(int i = 1; i < sortedNodes.size(); i++) {
        T comp = dist[sortedNodes[i]][info];
        int j;
        for(j = i; j > 0 && comp < dist[sortedNodes[j-1]][info]; j--) {
            sortedNodes[j] = sortedNodes[j-1];
        }
        sortedNodes[j] = comp;
    }
}

#endif //PROJ_GRAPH_H
