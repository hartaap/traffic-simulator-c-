#include <utility>

class TrafficLight {
 public:
  TrafficLight(std::pair<int, int> location, int redLightDuration, int greenLighDuration)
      : location_(location),
        redLightDuration_(redLightDuration),
        greenLighDuration_(greenLighDuration){};

  std::pair<int, int> GetLocation() const { return location_; }

  int GetGreenDuration() const { return greenLighDuration_; }

  int GetRedDuration() const { return redLightDuration_; }

 private:
  std::pair<int, int> location_;
  int redLightDuration_;
  int greenLighDuration_;
}