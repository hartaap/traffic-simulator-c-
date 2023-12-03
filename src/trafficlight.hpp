#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <utility>
#include <string>

class TrafficLight {
 public:
  TrafficLight(std::pair<int, int> location, int redDuration, int greenDuration)
      : location_(location),
        redDuration_(redDuration),
        greenDuration_(greenDuration) {};

  std::pair<int, int> GetLocation() const { return location_; }

  int GetGreenDuration() const { return greenDuration_; }

  int GetRedDuration() const { return redDuration_; }

  int GetYellowDuration() const { return yellowDuration_; }


 private:
  std::pair<int, int> location_;
  int redDuration_;
  int greenDuration_;
  int yellowDuration_ = 1; // Same for all TrafficLight instances
};

#endif