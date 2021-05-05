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
    unsigned int used;
public:
    unsigned int getUsed() const;

public:
    explicit Vehicle();

    const vector<MealBasket> &getMeals() const;

    void setMeals(const vector<MealBasket> &meals);

    vehicle_type getType() const;

    void setType(vehicle_type type);

    unsigned int getCap() const;

    void setCap(unsigned int cap);

    void addMeal(const MealBasket& meal);
};


#endif //PROJ_VEHICLE_H
