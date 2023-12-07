#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "grid.hpp"

class Intersection {
 public:
  /**
   * @brief Construct a new Intersection object.
   *
   * @param location the coordinates of the intersection as std::pair<int, int>
   */
  Intersection(std::pair<int, int> location)
      : location_(location), allowVertical_(true), allowHorizontal_(true) {}

  /**
   * @brief Get the location of the intersection.
   *
   * @return The coordinates of the intersection as std::pair<int, int>
   */
  std::pair<int, int> GetLocation() const { return location_; }

  /**
   * @brief Attempts to update the status of the traffic lights in the
   * intersection, if there are any.
   *
   * @param deltaTime
   */
  void Update(float deltaTime) {
    if (trafficLight_ != nullptr) {
      timePassed_ = timePassed_ + deltaTime;

      if (yellow_) {
        if (timePassed_ >= trafficLight_->GetYellowDuration()) {
          if (allowVertical_) {
            allowVertical_ = false;
            allowHorizontal_ = true;
          } else {
            allowHorizontal_ = false;
            allowVertical_ = true;
          }
          yellow_ = false;
          timePassed_ = 0;
        }
      } else {
        if (timePassed_ >= trafficLight_->GetGreenDuration()) {
          yellow_ = true;
          timePassed_ = 0;
        }
      }
    }
  }

  /**
   * @brief Adds a traffic light to the intersection.
   *
   * @param t A pointer to a TrafficLight object
   */
  void AddTrafficLight(TrafficLight* t) { trafficLight_ = t; }

  /**
   * @brief ?
   * 
   * @return true 
   * @return false 
   */
  bool AllowVertical() { return allowVertical_; }

  /**
   * @brief ?
   * 
   * @return true 
   * @return false 
   */
  bool AllowHorizontal() { return allowHorizontal_; }

  /**
   * @brief Draws the intersection into the SFML window given as parameter.
   * 
   * @param window The SFML window to draw the intersection to
   * @param cellSize The size of a single cell in the window
   */
  void Draw(sf::RenderWindow& window, int cellSize) {
    sf::Color Gray(50, 50, 50);

    // Draw the cell
    sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
    cellShape.setPosition(location_.first * cellSize,
                          location_.second * cellSize);
    cellShape.setFillColor(Gray);
    window.draw(cellShape);

    if (trafficLight_ != nullptr) {
      // Shapes for the traffic lights
      sf::RectangleShape up(sf::Vector2f(10, 10));
      sf::RectangleShape down(sf::Vector2f(10, 10));
      sf::RectangleShape left(sf::Vector2f(10, 10));
      sf::RectangleShape right(sf::Vector2f(10, 10));

      if (yellow_) {
        up.setFillColor(sf::Color::Yellow);
        down.setFillColor(sf::Color::Yellow);
        left.setFillColor(sf::Color::Yellow);
        right.setFillColor(sf::Color::Yellow);
      } else if (allowHorizontal_) {
        up.setFillColor(sf::Color::Red);
        down.setFillColor(sf::Color::Red);
        left.setFillColor(sf::Color::Green);
        right.setFillColor(sf::Color::Green);
      } else {
        up.setFillColor(sf::Color::Green);
        down.setFillColor(sf::Color::Green);
        left.setFillColor(sf::Color::Red);
        right.setFillColor(sf::Color::Red);
      }

      up.setPosition(location_.first * cellSize,
                     location_.second * cellSize - 10);
      down.setPosition(location_.first * cellSize + (cellSize - 10),
                       location_.second * cellSize + cellSize);
      left.setPosition(location_.first * cellSize - 10,
                       location_.second * cellSize + (cellSize - 10));
      right.setPosition(location_.first * cellSize + cellSize,
                        location_.second * cellSize);

      if(grid->GetCell(location_.first, location_.second-1)->GetType().find("Road") != std::string::npos){
         window.draw(up);
      }

      if(grid->GetCell(location_.first, location_.second+1)->GetType().find("Road") != std::string::npos){
         window.draw(down);
      }

      if(grid->GetCell(location_.first-1, location_.second)->GetType().find("Road") != std::string::npos){
         window.draw(left);
      }

      if(grid->GetCell(location_.first+1, location_.second)->GetType().find("Road") != std::string::npos){
         window.draw(right);
      }

    }
  }

 private:
  std::pair<int, int> location_;
  TrafficLight* trafficLight_;
  bool allowVertical_;
  bool allowHorizontal_;
  float timePassed_ = 0.0;
  bool yellow_ = false;
};

#endif
