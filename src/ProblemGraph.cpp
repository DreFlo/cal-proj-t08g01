#include "ProblemGraph.h"

#include <cstdlib>

using namespace std;

typedef MealBasket Client;

ProblemGraph::ProblemGraph(Graph<type> *graph):startGraph(graph) {
    processedGraph = graph;
}

const vector<Vehicle> &ProblemGraph::getVehicles() const {
    return vehicles;
}

void ProblemGraph::setVehicles(const vector<Vehicle> &vehicles) {
    ProblemGraph::vehicles = vehicles;
}

const vector<MealBasket> &ProblemGraph::getOrders() const {
    return orders;
}

void ProblemGraph::setOrders(const vector<MealBasket> &orders) {
    ProblemGraph::orders = orders;
}

const vector<Node<type> *> &ProblemGraph::getDestinations() const {
    return destinations;
}

void ProblemGraph::setDestinations(const vector<Node<type> *> &destinations) {
    ProblemGraph::destinations = destinations;
}

const Node<type>* ProblemGraph::getHQ() const {
    return hq;
}

void ProblemGraph::setHQ(pair<long double, long double> address) {
    vector<Node<type> * > nodes = processedGraph->getNodeSet();
    for(auto node : nodes){
        if(node->getPosition() == address){
            hq = node;
            break;
        }
    }
}

void ProblemGraph::addOrder(const MealBasket& mealBasket) {
    orders.push_back(mealBasket);
    this->addDestination(mealBasket.getAddress());
}

void ProblemGraph::addVehicle(const Vehicle& vehicle) {
    vehicles.push_back(vehicle);
}

void ProblemGraph::addDestination(pair<long double, long double> destination) {
    vector<Node<type> * > nodes = processedGraph->getNodeSet();
    for(auto node : nodes){
        if(node->getPosition() == destination){
            destinations.push_back(node);
            break;
        }
    }
}

void ProblemGraph::assignOrdersToVehicles() {
    // First Fit Decreasing
    sort(vehicles.begin(), vehicles.end());
    sort(orders.begin(), orders.end(), greater<>());
    for (const MealBasket& order : orders) {
        for (Vehicle& vehicle : vehicles) {
            if (vehicle.getUsed() + order.getPackageNumber() <= vehicle.getCap()) {
                vehicle.addMeal(order);
                break;
            }
        }
    }
    orders.clear();
}

void ProblemGraph::setHQ(int nodePos) {
    ProblemGraph::hq = startGraph->getNodeSet()[nodePos];
}

void ProblemGraph::createClients(int number) {
    for(int i = 0; i < number; i++) {
        Client client;
        client.setPackageNumber((rand() % 10) + 5);
        client.setAddress(startGraph->getRandomNode()->getPosition());
        orders.push_back(client);
    }
}
