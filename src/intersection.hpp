#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>

#include "road.hpp"

class Intersection {
 public:
  Intersection(std::pair<int, int> location)
      : location_(location){}

  std::vector<Road*> GetRoads() const { return roads_; }

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