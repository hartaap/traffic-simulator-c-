#include "building.hpp"
#include <iostream>
#include <string>

class Residential : public Building {
    public:
    Residential(const std::string& buildingName, std::pair<int,int> location) :
                Building(buildingName, location) {}

    ~Residential();
   
    void Display() {
        std::cout << "This is a residential building" << std::endl;
    }
};