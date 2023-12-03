#include "building.hpp"

Building::Building(const std::string& buildingName, const std::pair<int, int>& location)
    : buildingName_(buildingName), location_(location) {}

Building::~Building() {
}

const std::string& Building::GetName() const {
    return buildingName_;
}

const std::pair<int, int>& Building::GetLocation() const {
    return location_;
}

int Building::GetPeopleAmount() const {
        return personAmount_;
}

int Building::GetCarAmount() const {
        return carAmount_;
}
