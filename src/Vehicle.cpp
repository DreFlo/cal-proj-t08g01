#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle():type(HEAVY), cap(UINT_MAX), used(0) {}

const vector<MealBasket> &Vehicle::getMeals() const {
    return meals;
}

void Vehicle::setMeals(const vector<MealBasket> &meals) {
    Vehicle::meals = meals;
}

vehicle_type Vehicle::getType() const {
    return type;
}

void Vehicle::setType(vehicle_type type) {
    Vehicle::type = type;
}

unsigned int Vehicle::getCap() const {
    return cap;
}

void Vehicle::setCap(unsigned int cap) {
    Vehicle::cap = cap;
}

void Vehicle::addMeal(const MealBasket& meal) {
    meals.push_back(meal);
    used += meal.getPackageNumber();
}

unsigned int Vehicle::getUsed() const {
    return used;
}
