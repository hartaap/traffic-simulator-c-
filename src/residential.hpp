#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "building.hpp"

class Residential : public Building {
 public:
    Residential(const std::string& buildingName, const std::pair<int, int>& location)
    : Building(buildingName, location, "Residential") {
        maxPersonCapacity_ = 5;
        maxCarCapacity_ = 2;
    }

    void Info() const override {
        std::cout << GetName() << " is a residential building!" << std::endl;
    }

};

#endif
