#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <utility>

class TrafficLight {
 public:
  // Constructor
  TrafficLight(std::pair<int, int> location, int redDuration,
               int yellowDuration, int greenDuration)
      : location_(location),
        redDuration_(redDuration),
        yellowDuration_(yellowDuration),
        greenDuration_(greenDuration){};

  // Returns the coordinates of the traffic light's location
  std::pair<int, int> GetLocation() const { return location_; }

  // Returns the duration that the traffic light stays green
  int GetGreenDuration() const { return greenDuration_; }

  // Returns the duration that the traffic light stays red
  int GetRedDuration() const { return redDuration_; }

  // Returns the duration that the traffic light stays yellow
  int GetYellowDuration() const { return yellowDuration_; }

  // Switches the state of the traffic light to red
  void TurnRed() {
    isRed_ = true;
    isYellow_ = false;
    isGreen_ = false;
  }

  // Switches the state of the traffic light to yellow
  void TurnYellow() {
    isRed_ = false;
    isYellow_ = true;
    isGreen_ = false;
  }

  // Switches the state of the traffic light to green
  void TurnGreen() {
    isRed_ = false;
    isYellow_ = false;
    isGreen_ = true;
  }

 private:
  std::pair<int, int> location_;
  int redDuration_;
  int greenDuration_;
  int yellowDuration_;
  bool isRed_ = false;
  bool isYellow_ = false;
  bool isGreen_ = true;  // In the beginning, the light is green by default
};

#endif