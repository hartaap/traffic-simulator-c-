#include <iostream>

#include "city.hpp"
#include "simulator.hpp"

int main() {
  Simulator simulator;
  City c = simulator.StartSimulation();

  // Create an SFML window
  sf::RenderWindow window(sf::VideoMode(800, 600), "City Simulation");
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
