#include <iostream>

#include "city.hpp"

int main() {
  // Create an SFML window
  sf::RenderWindow window(sf::VideoMode(800, 600), "City Simulation");

  City c(10, 10);

  c.AddIndustrial("Murata", {4, 5});
  c.AddIndustrial("ABB", {0, 4});
  c.AddCommercial("Alepa", {2, 4}, SHOP);
  c.AddCommercial("Lidl", {8, 8}, SHOP);

  c.AddIntersection({4, 0});
  c.AddIntersection({0, 0});
  c.AddIntersection({2, 8});
  c.AddIntersection({8, 5});

  c.AddRoad({4, 5}, {4, 0});
  c.AddRoad({4, 0}, {0, 0});
  c.AddRoad({0, 4}, {0, 0});
  c.AddRoad({0, 4}, {2, 4});
  c.AddRoad({2, 4}, {2, 8});
  c.AddRoad({2, 8}, {8, 8});
  c.AddRoad({8, 8}, {8, 5});
  c.AddRoad({8, 5}, {4, 5});

  Car* c1 = new Car(4.0, 5.0, c.GetNode({4, 5}));

  c1->AddEvent(10, c.GetNode({0, 4}));
  c1->AddEvent(50, c.GetNode({8, 8}));
  c1->AddEvent(80, c.GetNode({4, 5}));

  c.AddCar(c1);

  sf::Clock clock;

  float previousTime = 0.0;

  // Main loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    float currentTime = clock.getElapsedTime().asSeconds();

    float deltaTime = currentTime - previousTime;

    previousTime = currentTime;

    std::cout << "Delta time: " << deltaTime << std::endl;
    std::cout << "Total time: " << currentTime << std::endl;

    // Move cars
    c.UpdateCars(deltaTime, currentTime);

    window.clear();

    // Draw the city and the cars
    c.PrintCity(window);
    c.DrawCars(window);

    window.display();
  }

  return 0;
}
