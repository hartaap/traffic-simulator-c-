#include "city.hpp"

/* 
    For testing.
    Creates a 2x2 city with roads on the edges and a building in the middle, with a single road connected to the building.
    Adds one car to the city.

     i1:(0,0) _____________ i2:(0,2)
             |      r1     |
           r3|             |
             |______b1     |r5
             |  r6         |
           r4|             |
             |_____________|
     i3:(2,0)       r2      i4:(2,2)

    Returns the created city.
*/
City CreateSmallCity() {

    // Initialize the city
    City c(2, 2);

    // Create the roads
    Road* r1 = new Road({0, 0}, {0, 2}, 10);
    Road* r2 = new Road({2, 0}, {2, 2}, 10);    
    Road* r3 = new Road({0, 0}, {1, 0}, 10);
    Road* r4 = new Road({1, 0}, {2, 0}, 10);
    Road* r5 = new Road({0, 2}, {2, 2}, 10);
    Road* r6 = new Road({1, 0}, {1, 1}, 10);

    // Create the building
    Industrial* b1 = new Industrial("Murata", {1, 1});

    // Create the intersections
    Intersection* i1 = new Intersection({0, 0}, {r1, r3});
    Intersection* i2 = new Intersection({0, 2}, {r1, r5});
    Intersection* i3 = new Intersection({2, 0}, {r2, r4});
    Intersection* i4 = new Intersection({2, 2}, {r2, r5});
    Intersection* i5 = new Intersection({1, 0}, {r3, r4, r6});

    // Create a car to the city
    Car* c1 = new Car(0.0, 0.0);

    // Add the objects to the city
    c.AddRoad(r1);
    c.AddRoad(r2);
    c.AddRoad(r3);
    c.AddRoad(r4);
    c.AddRoad(r5);
    c.AddRoad(r6);
    c.AddBuilding(b1);    
    c.AddIntersection(i1);
    c.AddIntersection(i2);
    c.AddIntersection(i3);
    c.AddIntersection(i4);
    c.AddIntersection(i5);
    c.AddCar(c1);

    return c;
}

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "City Simulation");

    City city = CreateSmallCity();

    sf::Clock clock;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

       float deltaTime = clock.restart().asSeconds();

        window.clear();

        //Move cars
        city.UpdateCars(deltaTime);

        //Draw the city and the cars
        city.PrintCity(window);
        city.DrawCars(window);

        window.display();
    }

    return 0;
}
