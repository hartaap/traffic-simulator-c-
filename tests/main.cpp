#include <iostream>
#include <SFML/Graphics.hpp>

#include "test_functions.hpp"

int main() {
    TestIntersection();
    TestTrafficLight();
    TestCar();
    TestSimulationClockInitialization();
    TestSimulationClockTimeConversion();

    std::cout << "All tests finished." << std::endl;
    return 0;
}