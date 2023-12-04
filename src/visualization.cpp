#include "visualization.hpp"

void Visualization::PrintGrid(Grid* grid) {
  for (int i = 0; i < grid->GetSizeX(); i++) {
    for (int j = 0; j < grid->GetSizeY(); j++) {
      grid->GetCell(i, j)->Draw(window_, cellSize_, i, j);
    }
  }
}

void Visualization::PrintCars(std::vector<Car*> cars) {
  for (auto car : cars) {
    car->Draw(window_, cellSize_);
  }
}