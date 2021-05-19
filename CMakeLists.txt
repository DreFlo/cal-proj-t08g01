cmake_minimum_required(VERSION 3.17)
project(proj)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(GRAPHVIEWERCPP_PATH src/GraphViewerCpp)
add_subdirectory(${GRAPHVIEWERCPP_PATH})
include_directories(${GRAPHVIEWERCPP_PATH}/include)

include_directories(include)
file(GLOB GRAPHVIEWER_FILES CONFIGURE_DEPENDS
        "src/GraphViewerCpp/*.cpp"
        )

add_executable(proj src/Components/MealBasket.cpp src/Components/MealBasket.h src/Components/Vehicle.cpp src/Components/Vehicle.h src/Graph.h src/main.cpp
        src/PapaRica.cpp src/PapaRica.h ${GRAPHVIEWER_FILES} src/Viewer.cpp)

target_link_libraries(proj graphviewer)