#ifndef PROJ_VEHICLE_H
#define PROJ_VEHICLE_H

#include <vector>
#include "MealBasket.h"

using namespace std;

enum vehicle_type {HEAVY, LIGHT, MOTORCYCLE};

class Vehicle {
    vector<MealBasket> meals;           //Meals to deliver
    vehicle_type type;                  //Vehicle type
    unsigned int cap;                   //Capacity in terms of number of packages it can hold
    unsigned int used;                  //Used capacity
public:
    explicit Vehicle();

    Vehicle(vehicle_type type, unsigned int cap);

    const vector<MealBasket> &getMeals() const;

    void setMeals(const vector<MealBasket> &meals);

    vehicle_type getType() const;

    void setType(vehicle_type type);

    unsigned int getCap() const;

    void setCap(unsigned int cap);

    void addMeal(const MealBasket& meal);

    unsigned int getUsed() const;

    bool operator<(const Vehicle &rhs) const;
};


#endif //PROJ_VEHICLE_H
