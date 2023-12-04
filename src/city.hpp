#ifndef CITY_H
#define CITY_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#include "building.hpp"
#include "car.hpp"
#include "cell.hpp"
#include "commercial.hpp"
#include "grid.hpp"
#include "industrial.hpp"
#include "intersection.hpp"
#include "invalidcityexception.hpp"
#include "node.hpp"
#include "residential.hpp"
#include "road.hpp"
#include "trafficlight.hpp"

class City {
 public:
  City(int sizeX, int sizeY);

  ~City();

  bool IsValidRoad(std::pair<int, int> start, std::pair<int, int> end) const;

  void AddRoad(std::pair<int, int> start, std::pair<int, int> end);

  bool IsValidBuilding(Building* b) const;

  void AddBuilding(std::string name, std::pair<int, int> location,
                   const std::string& buildingType);
  // building types are industrial, residential, shop, gym and restaurant.

  Node* GetNode(std::pair<int, int> location);

  void AddCar(Car* c);

  void AddIntersection(std::pair<int, int> location);

  Intersection* GetIntersection(std::pair<int, int> location);

  void UpdateIntersections(float deltaTime);

  void DrawIntersections(sf::RenderWindow& window);

  void AddTrafficLight(TrafficLight* t);

  void UpdateCars(float deltaTime, float currentTime);

  void DrawCars(sf::RenderWindow& window);

  void PrintCity(sf::RenderWindow& window);

 private:
  Grid* grid_;
  std::vector<Road*> roads_;
  std::vector<Building*> buildings_;
  std::vector<Intersection*> intersections_;
  std::vector<TrafficLight*> trafficLights_;
  std::vector<Car*> cars_;
  std::vector<Node*> nodes_;
};

#endif
