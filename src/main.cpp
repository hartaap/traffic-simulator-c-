#include "city.hpp"

int main() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "City Simulation");

    
    City c(10, 10); 

    Road* r1 = new Road({0, 0}, {4, 0}, 10);
    Road* r2 = new Road({1, 1}, {1, 5}, 10);
    Road* r3 = new Road({1, 1}, {5, 1}, 10);

    Car* c1 = new Car(0.0, 0.0);

    Building* b1 = new Building("Murata", {4, 2});
    Building* b2 = new Building("ABB", {-1, -1});

    c.AddRoad(r1);
    c.AddRoad(r2);
    c.AddRoad(r3);
    c.AddBuilding(b1);
    c.AddBuilding(b2);
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

/*
int main() {

    int columns = 10;
    int rows = 10;

    City c = City(columns, rows);

    Road* r1 = new Road({0, 0}, {4, 0}, 10);
    Road* r2 = new Road({1, 1}, {1, 5}, 10);
    Road* r3 = new Road({1, 1}, {5, 1}, 10);

    Building* b1 = new Building("Murata", {4, 2});
    Building* b2 = new Building("ABB", {-1, -1});

    c.AddRoad(r1);
    c.AddRoad(r2);
    c.AddRoad(r3);
    c.AddBuilding(b1);
    c.AddBuilding(b2);
    c.PrintCity();
}
*/