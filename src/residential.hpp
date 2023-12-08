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
   * @brief Prints information about the residential building to the standard
   * output
   *
   */
  void Info() const override {
    std::cout << GetName() << " is a residential building!" << std::endl;
  }
};

#endif
