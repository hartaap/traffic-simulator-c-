#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "building.hpp"

class Residential : public Building {
 public:
    Residential(const std::string& buildingName, const std::pair<int, int>& location)
    : Building(buildingName, location), maxPeopleCapacity_(5), maxCarCapacity_(2) {}

    int GetMaxPeopleCapacity() const override{
        return maxPeopleCapacity_;
    }
    int GetMaxCarCapacity() const override {
        return maxCarCapacity_;
    }
    void Info() const override {
        std::cout << GetName() << " is a residential building!" << std::endl;
    }

 private:
    int maxPeopleCapacity_;
    int maxCarCapacity_;
};

#endif
