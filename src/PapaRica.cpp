#include "PapaRica.h"

#include <cstdlib>

using namespace std;

typedef MealBasket Client;

PapaRica::PapaRica(Graph<type> *graph) {
    PapaRica::graph = graph->getLargestSCC();
    aStar = true;
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
            hq->setType(HQ);
            break;
        }
    }
}

void PapaRica::addOrder(const MealBasket& mealBasket) {
    orders.push_back(mealBasket);
    this->addDestination(mealBasket.getAddress());
}

bool PapaRica::addOrderB(const MealBasket& mealBasket) {
    auto pos = mealBasket.getAddress();
    for(auto node : graph->getNodeSet()){
        if(pos == node->getPosition()){
            orders.push_back(mealBasket);
            this->addDestination(mealBasket.getAddress());
            return true;
        }
    }
    return false;
}

void PapaRica::addVehicle(const Vehicle& vehicle) {
    vehicles.push_back(vehicle);
}

void PapaRica::addDestination(pair<long double, long double> destination) {
    vector<Node<type> * > nodes = graph->getNodeSet();
    for(auto node : nodes){
        if(node->getPosition() == destination){
            destinations.push_back(node);
            node->setType(CLIENT);
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
    hq->setType(HQ);
}

void PapaRica::createClients(int number) {
    for(int i = 0; i < number; i++) {
        Client client;
        client.setPackageNumber( 5);
        client.setAddress(graph->getRandomNode()->getPosition());
        addOrder(client);
    }
}

void PapaRica::input() {
    while(true) {
        string answer;
        cout << "Do you want to add anything before starting?" << endl;
        cout << "[0] Add nothing." << endl;
        cout << "[1] Add a Vehicle." << endl;
        cout << "[2] Add an Order." << endl;
        cin >> answer;
        if(answer == "0"){
            while(true) {
                string algorithm;
                cout << "With which algorithm do you want to run the program with?" << endl;
                cout << "[0] A*" << endl;
                cout << "[1] Floyd-Warshall" << endl;
                cin >> algorithm;
                if (algorithm == "0") return;
                else if (algorithm == "1") {
                    setUpFloydWarshall();
                    return;
                }
                else{
                    cout << "Invalid Choice. It can only be 0 or 1." << endl;
                }
            }
        }
        else if(answer == "1"){
            bool add = true;
            while(add){
                string type;
                cout << "Select vehicle type:" << endl;
                cout << "[0] Heavy" << endl;
                cout << "[1] Light" << endl;
                cout << "[2] Motorcycle" << endl;
                cout << "[3] Go to the main menu" << endl;
                cin.ignore(1000, '\n');
                getline(cin, type);
                vehicle_type v_type;
                if(type == "0" || type == "1" || type == "2"){
                    if(type == "0") v_type = HEAVY;
                    else if(type == "1") v_type =  LIGHT;
                    else if(type == "2") v_type = MOTORCYCLE;
                    while(add){
                        string s_cap;
                        cout << "Input vehicle capacity (Write 0 if infinite or -1 to go back to the main menu):" << endl;
                        cin >> s_cap;
                        int cap;
                        if(s_cap == "-1") add = false;
                        else if(!isNumber(s_cap)) cout << "Invalid choice." << endl << endl;
                        else if(stoi(s_cap) < 0) cout << "Invalid Choice." << endl << endl;
                        else{
                            if(s_cap == "0") cap = INT_MAX;
                            else cap = stoi(s_cap);
                            Vehicle vehicle = Vehicle();
                            vehicle.setType(v_type);
                            vehicle.setCap(cap);
                            add = false;
                            cout << "Vehicle added." << endl;
                        }
                    }
                }
                else if (type == "3") add = false;
                else cout << "Invalid choice. It can only by 0, 1, 2 or 3." << endl << endl;
            }
        }
        else if(answer == "2"){
            bool add = true;
            while(add){
                string number;
                cout << "How many meals in the basket? (Write 0 to go back to the main menu)" << endl;
                cin >> number;
                if(number == "0") add = false;
                else if (!isNumber(number)) cout << "Invalid choice." << endl << endl;
                else if (stoi(number) < 0) cout << "Invalid choice." << endl << endl;
                else{
                    int packageNumber = stoi(number);
                    string name;
                    cout << "Write your name 'First Last' (Write 0 to go back to the main menu):" << endl;
                    cin.ignore(1000, '\n');
                    getline(cin, name);
                    if(name == "0") add = false;
                    else{
                        bool add_pos = true;
                        while(add_pos) {
                            string pos_x;
                            cout << "Write the address in terms of x and y coordinates (Write 'a' to go back to the main menu):"
                                 << endl;
                            cout << "x: ";
                            cin >> pos_x;
                            if (pos_x == "a"){
                                add = false;
                                add_pos = false;
                            }
                            else if(!isNumber(pos_x)) cout << "Invalid Number." << endl;
                            else {
                                long double x = stold(pos_x);
                                string pos_y;
                                cout << "y: ";
                                cin >> pos_y;
                                if (pos_y == "a"){
                                    add = false;
                                    add_pos = false;
                                }
                                else if(!isNumber(pos_y)) cout << "Invalid number." << endl;
                                else {
                                    long double y = stold(pos_y);
                                    pair<long double, long double> node_pos(x, y);
                                    if (!addOrderB(MealBasket(packageNumber, name, node_pos))) {
                                        string answer;
                                        cout << "Node doesn't belong to graph or isn't reachable." << endl;
                                        cout << "Do you want to try again?" << endl;
                                        cout << "[0] Yes" << endl;
                                        cout << "[1] Go back to the main menu" << endl;
                                        cin >> answer;
                                        if (answer == "0") continue;
                                        else {
                                            add = false;
                                            add_pos = false;
                                        }
                                    }
                                    else{
                                        cout << "Order added." << endl;
                                        add = false;
                                        add_pos = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
        else cout << "Invalid choice. It can only by 0, 1 or 2." << endl << endl;
    }
}

void PapaRica::setUpFloydWarshall() {
    aStar = false;
    graph->floydWarshallShortestPath();
}

bool PapaRica::isAStar() {
    return aStar;
}

bool PapaRica::isNumber(string text) {
    bool foundPoint = false;
    for(string::iterator it = text.begin(); it != text.end(); it++){
        if(it == text.begin() && *it == '-') continue;
        else if(*it == '.' && !foundPoint) foundPoint = true;
        else if(!isdigit(*it)) return false;
    }
    return true;
}
