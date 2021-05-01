#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <vector>
#include <climits>

using namespace std;

template <class T> class Edge;
template <class T> class Node;
template <class T> class Graph;

template <class T>
class Node {
private:
    T contents;
    //node contents
    vector<Edge<T>> connections;    //edges leaving from the node
    bool visited;
    bool processing;
    int indegree;
    bool hidden;//if this node is transversable
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
};

template <class T>
class Graph {
private:
    vector<Node<T> *> nodeSet;  //node set
    vector<vector<double>> dist;//weights
    vector<vector<int>> next;//to reconstruct the path after running the algorithm

    Node<T> *findNode(const T &contents) const;
public:
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
    bool addEdge(const T &source, const T &dest, double weight);
    /**
     * @brief Removes an edge from the graph
     * @param source Contents of the source of the edge
     * @param dest Contents of the destination of the edge
     * @return true if edge existed and was removed, false otherwise
     */
    bool removeEdge(const T &source, const T &dest);

    /**
     * Remove the unnecessary edges, setting the weight value to infinite
     * @param source initial node
     */
    bool removeUnnecessaryEdges(const T &source);

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
    vector<T> getFloydWarshallPath(const T &source, const T &destination);

    /**
     * Return the Node in nodeSet with index n
     * @return Node in nodeSet with index n
     */
    Node<T> * operator[](int n);
};



#endif //PROJ_GRAPH_H
