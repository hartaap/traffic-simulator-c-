#include "city.hpp"

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "City Simulation");

    
    City c(10, 10); 

   // Road* r1 = new Road({0, 0}, {4, 0}, 10);
    //Road* r2 = new Road({1, 1}, {1, 5}, 10);
    //Road* r3 = new Road({1, 1}, {5, 1}, 10);

    Car* c1 = new Car(4.0, 2.0);

   // Building* b1 = new Building("Murata", {4, 2});
   // Building* b2 = new Building("ABB", {8, 2});

    c.AddBuilding("Murata", {4, 2});
    c.AddBuilding("ABB", {8, 2});
    c.AddBuilding("Store", {8, 9});

    c1->SetDestination(c.GetNode({8,2}));

    c.AddRoad(c.GetNode({4,2}), c.GetNode({8,2}));
    c.AddRoad(c.GetNode({8,2}), c.GetNode({8,9}));

    c.AddCar(c1);

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
        c.UpdateCars(deltaTime);

        //Draw the city and the cars
        c.PrintCity(window);
        c.DrawCars(window);

        window.display();
    }

    return 0;
}
