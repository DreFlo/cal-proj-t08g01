#ifndef PROJ_GRAPH_H
#define PROJ_GRAPH_H

#include <vector>

using namespace std;

template <class T> class Edge;
template <class T> class Vertex;
template <class T> class Graph;

template <class T>
class Vertex {
private:
    T contents; //node contents
    vector<Edge<T>> connections;    //edges leaving from the node
    bool visited;
    bool processing;
    int indegree;

    /**
     * @brief Adds a new edge to the node
     * @param dest Destination of the edge
     * @param weight Edge weight
     */
    void addEdge(Vertex<T> *dest, double weight);
    /**
     * @brief Removes an edge from the node
     * @param dest Destination of the edge to remove
     * @return true if edge existed and was removed, false otherwise
     */
    bool removeEdgeTo(Vertex<T> *dest);
public:
    explicit Vertex(T contents);
    friend class Graph<T>;
};

template <class T>
class Edge {
private:
    Vertex<T> *dest;
    double weight;
public:
    Edge(Vertex<T> *dest, double weight);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph {
private:
    vector<Vertex<T> *> vertexSet;  //node set

    Vertex<T> *findVertex(const T &contents) const;
    //TODO idk qual o melhor metodo de procura
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
};



#endif //PROJ_GRAPH_H
