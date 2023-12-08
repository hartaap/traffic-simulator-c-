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
             const std::pair<int, int>& location)
      : Building(buildingName, location, "Industrial") {
    maxPersonCapacity_ = 30;
    maxCarCapacity_ = 25;
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
