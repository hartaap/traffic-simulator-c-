#ifndef BUILDING_H
#define BUILDING_H


#include <string>

class Building {
public:
    Building(const std::string buildingName, std::pair<int,int> location) :
            buildingName_(buildingName), location_(location) {}


    const std::string GetName() const {
        return buildingName_;
    }
    const std::pair<int,int> GetLocation() const {
        return location_;
    }


private:
    std::string buildingName_;
    std::pair<int,int> location_;
        
};

#endif