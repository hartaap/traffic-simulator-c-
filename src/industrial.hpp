#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "building.hpp"

class Industrial : public Building {
 public:
    Industrial(const std::string& buildingName, const std::pair<int, int>& location)
    : Building(buildingName, location) {
        maxPersonCapacity_ = 30;
        maxCarCapacity_ = 25;
    }
    
    void Info() const override {
        std::cout << GetName() << " is an industrial building!" << std::endl;
    }
};

#endif
