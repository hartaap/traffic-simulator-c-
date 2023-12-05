#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#include "car.hpp"
#include "grid.hpp"

class Visualization {
 public:
  Visualization(int cellSize, Grid* g);

  sf::RenderWindow& GetWindow();

  void PrintGrid(Grid* grid);

  void PrintCars(std::vector<Car*> cars);

 private:
  sf::RenderWindow window_;
  int cellSize_;
};

#endif