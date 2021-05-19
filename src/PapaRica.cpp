#include "PapaRica.h"

#include <cstdlib>

using namespace std;

typedef MealBasket Client;

PapaRica::PapaRica(Graph<type> *graph) {
    graph->removeUnnecessaryEdges(1);
    PapaRica::graph = graph->getLargestSCC();
}

const vector<Vehicle> &PapaRica::getVehicles() const {
    return vehicles;
}

void PapaRica::setVehicles(const vector<Vehicle> &vehicles) {
    PapaRica::vehicles = vehicles;
}

const vector<MealBasket> &PapaRica::getOrders() const {
    return orders;
}

void PapaRica::setOrders(const vector<MealBasket> &orders) {
    PapaRica::orders = orders;
}

const vector<Node<type> *> &PapaRica::getDestinations() const {
    return destinations;
}

void PapaRica::setDestinations(const vector<Node<type> *> &destinations) {
    PapaRica::destinations = destinations;
}

const Node<type>* PapaRica::getHQ() const {
    return hq;
}

void PapaRica::setHQ(pair<long double, long double> address) {
    vector<Node<type> * > nodes = graph->getNodeSet();
    for(auto node : nodes){
        if(node->getPosition() == address){
            hq = node;
            break;
        }
    }
}

void PapaRica::addOrder(const MealBasket& mealBasket) {
    orders.push_back(mealBasket);
    this->addDestination(mealBasket.getAddress());
}

void PapaRica::addVehicle(const Vehicle& vehicle) {
    vehicles.push_back(vehicle);
}

void PapaRica::addDestination(pair<long double, long double> destination) {
    vector<Node<type> * > nodes = graph->getNodeSet();
    for(auto node : nodes){
        if(node->getPosition() == destination){
            destinations.push_back(node);
            break;
        }
    }
}

void PapaRica::assignOrdersToVehicles() {
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

void PapaRica::setHQ(int nodePos) {
    PapaRica::hq = graph->getNodeSet()[nodePos];
}

void PapaRica::createClients(int number) {
    for(int i = 0; i < number; i++) {
        Client client;
        client.setPackageNumber((rand() % 10) + 5);
        client.setAddress(graph->getRandomNode()->getPosition());
        orders.push_back(client);
    }
}
