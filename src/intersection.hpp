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

      TrafficLight* GetTrafficLightUp(){

        auto it = trafficLights_.find("Up");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }

    TrafficLight* GetTrafficLightDown(){

        auto it = trafficLights_.find("Down");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }


    TrafficLight* GetTrafficLightRight(){

        auto it = trafficLights_.find("Right");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }

    TrafficLight* GetTrafficLightLeft(){

        auto it = trafficLights_.find("Left");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }

 private:
  std::pair<int, int> location_;
  std::vector<Road*> roads_;
  std::map<std::string, TrafficLight*> trafficLights_;
};

#endif