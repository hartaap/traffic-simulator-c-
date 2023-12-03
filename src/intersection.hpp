#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

#include "road.hpp"

class Intersection {
 public:
  // Constructor
  Intersection(std::pair<int, int> location, std::vector<Road*> roads)
      : location_(location), roads_(roads) {}

  // Returns the roads that are connected to this intersection
  std::vector<Road*> GetRoads() const { return roads_; }

  // Returns the coordinates of the intersection
  std::pair<int, int> GetLocation() const { return location_; }

 private:
  std::pair<int, int> location_;
  std::vector<Road*> roads_;
};

#endif