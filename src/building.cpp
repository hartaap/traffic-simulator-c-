#include "building.hpp"

Building::Building(const std::string& buildingName, const std::pair<int, int>& location, const std::string& type)
    : buildingName_(buildingName), location_(location), type_(type), personAmount_(0), carAmount_(0) {
    
}

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
