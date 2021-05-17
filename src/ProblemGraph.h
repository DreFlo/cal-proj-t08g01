#ifndef PROJ_PROBLEMGRAPH_H
#define PROJ_PROBLEMGRAPH_H

#include <algorithm>

#include "Graph.h"
#include "Vehicle.h"

typedef int type;

//TODO change types
//All can change
class ProblemGraph {
public:
    Graph<type> * startGraph;
    Graph<type> * processedGraph;
    vector<Vehicle> vehicles;
    vector<MealBasket> orders;
    //IDK
    vector<Node<type> * > destinations;
    Node<type>* hq;

    explicit ProblemGraph(Graph<type> * graph);

    const vector<Vehicle> &getVehicles() const;

    void setVehicles(const vector<Vehicle> &vehicles);

    const vector<MealBasket> &getOrders() const;

    void setOrders(const vector<MealBasket> &orders);

    const vector<Node<type> *> &getDestinations() const;

    void setDestinations(const vector<Node<type> *> &destinations);

    const Node<type>* getHQ() const;

    void setHQ(pair<long double, long double> address);

    void setHQ(int nodePos);

    void addOrder(const MealBasket& mealBasket);

    void addDestination(pair<long double, long double> destination);

    void addVehicle(const Vehicle& vehicle);

    void assignOrdersToVehicles();

    void createClients(int number = 10);
};


#endif //PROJ_PROBLEMGRAPH_H
