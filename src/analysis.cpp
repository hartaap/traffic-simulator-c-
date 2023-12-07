#include "analysis.hpp"

Analysis::Analysis(City* city, SimulationClock* clock)
    : city_(city), clock_(clock), currentRoad_(nullptr) {}

void Analysis::Analyze() {
  if (currentRoad_ != nullptr) {
    // Acquire the cars in the city
    auto cars = city_->GetCars();

    // Acquire the start/end coordinates of the road
    auto roadStart = currentRoad_->GetStart();
    auto roadEnd = currentRoad_->GetEnd();

    // Acquire the current hour for hourly statistics
    int currentHour = static_cast<int>(clock_->GetElapsedTime()) / 60;

    // Initialization of roadHourlyCounts_: this should be ran only once at
    // start
    if (roadHourlyCounts_.empty()) {
      roadHourlyCounts_.emplace_back(std::vector<int>());
    }

    // Initialization of a specific hour: if it doesn't exist, make it equal 0
    if (!roadHourlyCounts_[clock_->GetDayNumber()][currentHour]) {
      roadHourlyCounts_[clock_->GetDayNumber()][currentHour] = 0;
    }

    for (size_t i = 0; i < cars.size(); ++i) {
      auto car = cars[i];
      auto location = car->GetLocation();

      if (currentRoad_->IsHorizontal() &&
          (car->GetDirection() == "Right" || car->GetDirection() == "Left")) {
        if (location.first >= roadStart.first &&
            location.first <= roadEnd.first &&
            location.second == roadStart.second) {
          if (!previousCars_[i]) {
            roadHourlyCounts_[clock_->GetDayNumber()][currentHour]++;
            previousCars_.insert(std::pair<int, Car*>(i, car));
          }
        }
      } else if (currentRoad_->IsVertical() &&
                 (car->GetDirection() == "Up" ||
                  car->GetDirection() == "Down")) {
        if (location.first >= roadStart.first &&
            location.first <= roadEnd.first &&
            location.first == roadStart.first) {
          if (!previousCars_[i]) {
            roadHourlyCounts_[clock_->GetDayNumber()][currentHour]++;
            previousCars_.insert(std::pair<int, Car*>(i, car));
          }
        }
      }

      if (currentRoad_->IsHorizontal() && previousCars_[i] &&
          (car->GetDirection() == "Right" || car->GetDirection() == "Left")) {
        if (location.second != roadStart.second) {
          previousCars_.erase(i);
        } else if (currentRoad_->IsVertical() && previousCars_[i] &&
                   (car->GetDirection() == "Up" ||
                    car->GetDirection() == "Down")) {
          if (location.first != roadStart.first) {
            previousCars_.erase(i);
          }
        }
      }
    }
  }
}

void Analysis::SpecifyRoad(int roadIndex) {
  currentRoad_ = city_->GetRoads()[roadIndex];
}