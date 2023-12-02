#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "building.hpp"

class Industrial : public Building {
public:
    Industrial(const std::string& buildingName, const std::pair<int, int>& location)
    : Building(buildingName, location), maxPeopleCapacity_(30), maxCarCapacity_(25) {}
    
    int GetMaxPeopleCapacity() const override {
        return maxPeopleCapacity_;
    }
    int GetMaxCarCapacity() const override {
        return maxCarCapacity_;
    }

private:
    int maxPeopleCapacity_;
    int maxCarCapacity_;
};

#endif
