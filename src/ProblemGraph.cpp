#include "ProblemGraph.h"

using namespace std;

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

void ProblemGraph::addOrder(const MealBasket& mealBasket) {
    orders.push_back(mealBasket);
}

void ProblemGraph::addVehicle(const Vehicle& vehicle) {
    vehicles.push_back(vehicle);
}

void ProblemGraph::addDestination(Node<type> *destination) {
    vector<Node<type> * > nodes = processedGraph->getNodeSet();
    if (find(nodes.begin(), nodes.end(), destination) != nodes.end()) {
        destinations.push_back(destination);
    }
}

void ProblemGraph::assignOrdersToVehicles() {
    // First Fit Decreasing
    sort(vehicles.begin(), vehicles.end());
    sort(orders.begin(), orders.end(), greater<MealBasket>());
    for (const MealBasket& order : orders) {
        for (Vehicle vehicle : vehicles) {
            if (vehicle.getUsed() + order.getPackageNumber() <= vehicle.getCap()) {
                vehicle.addMeal(order);
                break;
            }
        }
    }
    orders.clear();
}
