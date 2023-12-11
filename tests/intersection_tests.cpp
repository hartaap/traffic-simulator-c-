#include <cassert>
#include <iostream>

#include "test_functions.hpp"
#include "../src/trafficlight.hpp"

void TestIntersection() {
  // Test 1: Create an intersection and check its location
  Intersection intersection({2, 3});
  assert(intersection.GetLocation() == std::make_pair(2, 3));

  // Test 2: Create a traffic light and add it to the intersection
  TrafficLight trafficLight({2, 3}, 5, 10, 15);
  intersection.AddTrafficLight(&trafficLight);

  // Test 3: Check the initial state of traffic movement
  assert(intersection.AllowVertical());
  assert(intersection.AllowHorizontal());

  // Test 4: Update the intersection with a small delta time
  intersection.Update(0.1);

  // Test 5: Check if the state has changed after the update
  assert(!intersection.AllowVertical());  // Assuming yellow phase
  assert(intersection.AllowHorizontal());

  // Test 6: Check the state after another update
  intersection.Update(5.0);  // Assuming a long time passed
  assert(intersection.AllowVertical());
  assert(!intersection.AllowHorizontal());

  std::cout << "All Intersection tests passed!" << std::endl;

  return;
}
