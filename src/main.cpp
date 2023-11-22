#include "city.hpp"

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "City Simulation");

    
    City c(10, 10); 

   // Road* r1 = new Road({0, 0}, {4, 0}, 10);
    //Road* r2 = new Road({1, 1}, {1, 5}, 10);
    //Road* r3 = new Road({1, 1}, {5, 1}, 10);

    Car* c1 = new Car(4.0, 0.0);
    Car* c2 = new Car(0.0, 0.0);

   // Building* b1 = new Building("Murata", {4, 2});
   // Building* b2 = new Building("ABB", {8, 2});

    c.AddBuilding("Murata", {4, 5});
    //c.AddBuilding("ABB", {8, 2});
    //c.AddBuilding("Store", {8, 9});

    c.AddIntersection({4,0});

    c.AddIntersection({0,0});


    c.AddRoad(c.GetNode({4,0}), c.GetNode({4,5}));
    c.AddRoad(c.GetNode({0,0}), c.GetNode({4,0}));

    c1->SetDestination(c.GetNode({4,5}));
    c2->SetDestination(c.GetNode({4,0}));

    c.AddCar(c1);
    c.AddCar(c2);

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
