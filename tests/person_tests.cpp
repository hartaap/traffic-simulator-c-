#include <cassert>
#include <iostream>

#include "test_functions.hpp"

void TestPerson() {
  // Test 1: Construting the object and getting the location, which should be at home.
  {
    Residential home("Home", {0, 0});
    Industrial workplace("Workplace", {1, 1});
    Person person("Aape", PersonType::Active, &workplace, &home);

    auto location = person.GetLocation();
    assert(location.first == 0);
    assert(location.second == 0);
  }

  // Test 2: BuyCar() and GetCar()
  {
    Residential home("Home", {0, 0});
    Industrial workplace("Workplace", {1, 1});
    Person person("Aape", PersonType::Active, &workplace, &home);

    Car car(nullptr);  // Mock car object

    person.BuyCar(&car);
    assert(person.GetCar() == &car);
  }

  // Test 3: InitializeSchedule testing
  {
    Residential home("Home", {0, 0});
    Industrial workplace("Workplace", {1, 1});
    Person person("Aape", PersonType::Active, &workplace, &home);
    Car car(nullptr);

    std::map<int, Node*> schedule;
    schedule[10] = &home;
    schedule[20] = &workplace;

    person.BuyCar(&car);
    person.InitializeSchedule(schedule);

    assert(person.GetSchedule().size() == 2);
    assert(person.GetSchedule().at(10) == &home);
    assert(person.GetSchedule().at(20) == &workplace);

    // check that these worked
    assert(person.GetCar()->GetSchedule().size() == 2);
    assert(person.GetCar()->GetSchedule().at(10) == &home);
    assert(person.GetCar()->GetSchedule().at(20) == &workplace);
  }

  // Test 4: UpdateLocationFromCar testing:
  {
    Residential home("Home", {0, 0});
    Industrial workplace("Workplace", {1, 1});
    Person person("Aape", PersonType::Active, &workplace, &home);

    Car car(nullptr);
    person.BuyCar(&car);

    // Update car location, and check if person's location is updated to same.
    car.UpdateLocation({2.5f, 3.5f});
    person.UpdateLocationFromCar(car.GetLocation());

    auto personLocation = person.GetLocation();
    assert(personLocation.first == 2);
    assert(personLocation.second == 4);  // Rounded from 3.5
  }

  std::cout << "Everything works!" << std::endl;
}
