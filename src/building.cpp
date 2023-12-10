#include "building.hpp"

Building::Building(const std::string& buildingName,
                   const std::pair<int, int>& location, const std::string& type)
    : buildingName_(buildingName),
      location_(location),
      personAmount_(0),
      carAmount_(0),
      type_(type)
       {}

Building::~Building() {}

int Building::GetMaxPeopleCapacity() const { return maxPersonCapacity_; }

int Building::GetMaxCarCapacity() const { return maxCarCapacity_; }

int Building::GetPeopleAmount() const { return personAmount_; }

int Building::GetCarAmount() const { return carAmount_; }

bool Building::isFull() const {
  return ((maxPersonCapacity_ - personAmount_) <= 0);
}

const std::string& Building::GetName() const { return buildingName_; }

const std::pair<int, int>& Building::GetLocation() const { return location_; }

