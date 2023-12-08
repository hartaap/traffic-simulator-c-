#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief An abstract class for representing the buildings in the simulated
 * city. Each building is either a commercial, a residential, or an industrial
 * building.
 *
 */
class Building {
 public:
  /**
   * @brief Construct a new Building object.
   *
   * @param buildingName The name of the building
   * @param location The coordinates of the building
   * @param type The type of the building ("industrial",
   * "residential", "shop", "gym", or "restaurant")
   */
  Building(const std::string& buildingName, const std::pair<int, int>& location,
           const std::string& type);

  /**
   * @brief Destroy the Building object.
   *
   */
  virtual ~Building();

  /**
   * @brief Get the max number of people that can be in the building.
   *
   * @return An integer representing the maximum person capacity of the building
   */
  int GetMaxPeopleCapacity() const;

  /**
   * @brief Get the max number of cars that can be in the building.
   *
   * @return An integer representing the maximum car capacity of the building
   */
  int GetMaxCarCapacity() const;

  /**
   * @brief Get the number of people currently in the building.
   *
   * @return The number of people currently in the building
   */
  int GetPeopleAmount() const;

  /**
   * @brief Get the number of cars currently in the building.
   *
   * @return The number of cars currently in the building
   */
  int GetCarAmount() const;

  /**
   * @brief Returns a boolean value indicating if the maximum people capacity
   * has been reached.
   *
   * @return True if the building is currently full, false otherwise
   */
  bool isFull() const;

  /**
   * @brief Get the name of the building.
   *
   * @return The name of the building as std::string&
   */
  const std::string& GetName() const;

  /**
   * @brief Get the location of the building.
   *
   * @return The coordinates of the building as std::pair<int, int>&
   */
  const std::pair<int, int>& GetLocation() const;

  /**
   * @brief The only purpose of this function is to make the class abstract.
   *
   */
  virtual void Info() const = 0;

 protected:
  std::string buildingName_;
  std::pair<int, int> location_;
  int personAmount_;
  int carAmount_;
  int maxPersonCapacity_;
  int maxCarCapacity_;
  const std::string type_;
};

#endif
