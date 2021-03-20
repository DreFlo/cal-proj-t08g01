cmake_minimum_required(VERSION 3.17)
project(proj)

set(CMAKE_CXX_STANDARD 14)

add_executable(proj main.cpp MealBasket.cpp MealBasket.h Vehicle.cpp Vehicle.h Graph.cpp Graph.h)