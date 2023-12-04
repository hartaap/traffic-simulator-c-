#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#include "building.hpp"
#include "car.hpp"
#include "cell.hpp"
#include "grid.hpp"
#include "industrial.hpp"
#include "intersection.hpp"
#include "node.hpp"
#include "road.hpp"
#include "trafficlight.hpp"

class Visualization {
 public:
  Visualization(int cellSize)
      : window_(sf::VideoMode(800, 600), "Traffic Simulation"),
        cellSize_(cellSize) {}

  sf::RenderWindow& GetWindow() { return window_; }

  void PrintGrid(Grid* grid);
  void PrintCars(std::vector<Car*> cars);

 private:
  sf::RenderWindow window_;
  int cellSize_;
};
