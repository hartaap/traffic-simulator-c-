#include <cassert>
#include <iostream>

#include "test_functions.hpp"

void TestBuilding() {

    // Test 1: Create a building and check its basic properties:
    const std::string buildingName = "TestBuilding";
    const std::pair<int, int> location = {0, 0};
    const std::string type = "residential";
    Building* building = new Building(buildingName, location, type);

    assert(building->GetName() == buildingName);
    assert(building->GetLocation() == location);
    assert(building->GetType() == type);

    // Test 2: Check the initial state of capacities and amounts:
    assert(building->GetMaxPeopleCapacity() == 0); 
    assert(building->GetMaxCarCapacity() == 0);     
    assert(building->GetPeopleAmount() == 0);
    assert(building->GetCarAmount() == 0);

    // Test 3: Check if the building is initially not full:
    assert(!building->isFull()); 

    // Test 4: Check if the building is full after reaching max capacities:
    assert(building->isFull()); 

    delete building;

    std::cout << "Everything works!" << std::endl;
}
