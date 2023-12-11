#include <cassert>
#include <iostream>

#include "test_functions.hpp"

#include <iostream>
#include <cassert>

void TestIntersection() {
    // Test 1: Constructor and GetLocation method
    {
        Intersection intersection({1, 2});
        auto location = intersection.GetLocation();
        assert(location.first == 1);
        assert(location.second == 2);
    }

    // Test 2: AddTrafficLight and HasTrafficLight methods
    {
        Intersection intersection({1, 2});
        assert(!intersection.HasTrafficLight());  // No traffic light initially

        TrafficLight trafficlight({1, 3}, 10, 2);
        intersection.AddTrafficLight(&trafficlight);

        assert(intersection.HasTrafficLight());  // Traffic light added
    }

    // Test 3: AllowVertical and AllowHorizontal methods
    {
        Intersection intersection({1, 2});
        assert(intersection.AllowVertical());    // Initially allows vertical movement
        assert(intersection.AllowHorizontal());  // Initially allows horizontal movement

        intersection.AddTrafficLight(nullptr);  // No traffic light

        assert(intersection.AllowVertical());    // Still allows vertical movement
        assert(intersection.AllowHorizontal());  // Still allows horizontal movement
    }

    // Test 4: Update method (No traffic light)
    {
        Intersection intersection({1, 2});
        intersection.Update(1.0);  // Simulate 1 second elapsed time

        // No traffic light, movement permissions should not change
        assert(intersection.AllowVertical());
        assert(intersection.AllowHorizontal());
    }

    // Test 5: Update method (With traffic light)
    {
        Intersection intersection({1, 2});
        TrafficLight trafficlight({1, 3}, 10, 2);
        intersection.AddTrafficLight(&trafficlight);

        // Simulate 1 second elapsed time, should not change permissions without traffic light duration specified
        intersection.Update(1.0);
        assert(intersection.AllowVertical());
        assert(intersection.AllowHorizontal());
    }

    // Add more tests as needed

    std::cout << "All intersection tests passed!" << std::endl;

    return;
}