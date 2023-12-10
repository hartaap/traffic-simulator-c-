#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "building.hpp"

/**
 * @brief One of the concretizing classes for the abstract class Building.
 *
 */
class Industrial : public Building {
 public:
  /**
   * @brief Construct a new Industrial object
   *
   * @param buildingName The name of the industrial building
   * @param location The coordinates of the idnustrial building
   */
  Industrial(const std::string& buildingName,
             const std::pair<int, int>& location, Node* node)
      : Building(buildingName, location, "Industrial", node) {
    maxPersonCapacity_ = 30;
    maxCarCapacity_ = 25;
  }

  /**
   * @brief Draws the building to the SFML window given as a parameter. Each
   * subclass defines the draw function themselves.
   *
   * @param window A reference to the SFML window where the building should be
   * drawn
   * @param cellSize The size of the cell to be drawn
   */
  virtual void Draw(sf::RenderWindow& window, int cellSize) override {
    sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
    int x = location_.first;
    int y = location_.second;
    cellShape.setFillColor(sf::Color::Black);
    cellShape.setPosition(x * cellSize, y * cellSize);
    window.draw(cellShape);
  }

  /**
   * @brief Prints information about the industrial building to the standard
   * output
   *
   */
  void Info() const override {
    std::cout << GetName() << " is an industrial building!" << std::endl;
  }
};

#endif

