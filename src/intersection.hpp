#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

#include "road.hpp"

class Intersection {
 public:
  Intersection(std::pair<int, int> location, std::vector<Road*> roads)
      : location_(location), roads_(roads) {}

  std::vector<Road*> GetRoads() const { return roads_; }

  std::pair<int, int> GetLocation() const { return location_; }

 private:
  std::pair<int, int> location_;
  std::vector<Road*> roads_;
};

#endif