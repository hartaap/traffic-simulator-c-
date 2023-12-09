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
      roadHourlyCounts_.resize(1, std::vector<int>(24));
    }

    // Initialization of a specific hour: if it doesn't exist, make it equal 0
    if (!roadHourlyCounts_[clock_->GetDayNumber()][currentHour]) {
      roadHourlyCounts_[clock_->GetDayNumber()][currentHour] = 0;
    }

    for (size_t i = 0; i < cars.size(); ++i) {
      auto car = cars[i];
      auto location = car->GetLocation();

      // checks if the car is on this horizontal road
      if (currentRoad_->IsHorizontal() &&
          (car->GetDirection() == "Right" || car->GetDirection() == "Left")) {
        if (location.first >= roadStart.first &&
            location.first <= roadEnd.first &&
            location.second == roadStart.second) {
          if (previousCars_.find(i) == previousCars_.end()) {
            roadHourlyCounts_[clock_->GetDayNumber()][currentHour]++;
            previousCars_.insert(std::pair<int, Car*>(i, car));
          }
        }
        // checks if the car is on this vertical road
      } else if (currentRoad_->IsVertical() &&
                 (car->GetDirection() == "Up" ||
                  car->GetDirection() == "Down")) {
        if (location.second >= roadStart.second &&
            location.second <= roadEnd.second &&
            location.first == roadStart.first) {
          if (previousCars_.find(i) == previousCars_.end()) {
            roadHourlyCounts_[clock_->GetDayNumber()][currentHour]++;
            previousCars_.insert(std::pair<int, Car*>(i, car));
          }
        }
      }

      if (currentRoad_->IsHorizontal() &&
          (previousCars_.find(i) != previousCars_.end()) &&
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

std::string Analysis::Print() {
  int currentHour = static_cast<int>(clock_->GetElapsedTime()) / 60;

  return "Cars used this road: " +
         std::to_string(roadHourlyCounts_[clock_->GetDayNumber()][currentHour]);
}

void Analysis::GenerateHourlyHistogram(std::vector<std::vector<int>> data) {
    int max_value = *max_element(data[clock_->GetDayNumber()].begin(), data[clock_->GetDayNumber()].end());

  // Calculate the number of digits in the maximum value of the data
  int max_digits = std::to_string(max_value).size();

  // Histogram
  for (int i = max_value; i >= 0; --i) {
    std::cout.width(max_digits + 2);
    std::cout << i << " | ";

    // Marking the values
    for (int j = 0; j < data[clock_->GetDayNumber()].size(); ++j) {
      if (data[clock_->GetDayNumber()][j] >= i) {
        std::cout << "x ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::string(max_digits + 2, ' ') << "---------------------------------------" << std::endl;
  std::cout << std::string(max_digits + 4, ' ');

  // Data printed
  for (int i = 0; i < data[clock_->GetDayNumber()].size(); ++i) {
    std::cout << (i + 1) << " ";
  }

  std::cout << std::endl;
}

std::vector<std::vector<int>> Analysis::GetData() {
  return roadHourlyCounts_;
}