#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "building.hpp"

/**
 * @brief One of the concretizing classes for the abstract class Building.
 *
 */
class Residential : public Building {
 public:
  /**
   * @brief Construct a new Residential object
   *
   * @param buildingName The name of the residential building
   * @param location The coordinates of the residential building
   */
  Residential(const std::string& buildingName,
              const std::pair<int, int>& location)
      : Building(buildingName, location, "Residential") {
    maxPersonCapacity_ = 5;
    maxCarCapacity_ = 2;
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
    cellShape.setFillColor(sf::Color::Magenta);
    cellShape.setPosition(x * cellSize, y * cellSize);
    window.draw(cellShape);
  }

  /**
   * @brief Prints information about the residential building to the standard
   * output
   *
   */
  std::string GetType() const override {
    return type_;
  }
};

#endif

