#ifndef PROJ_VEHICLE_H
#define PROJ_VEHICLE_H

#include <vector>
#include "MealBasket.h"

using namespace std;

enum vehicle_type {HEAVY, LIGHT, MOTORCYCLE};

class Vehicle {
    vector<MealBasket> meals;
    vehicle_type type;
    unsigned int cap;
public:
    explicit Vehicle(vector<MealBasket> & meals);
};


#endif //PROJ_VEHICLE_H
