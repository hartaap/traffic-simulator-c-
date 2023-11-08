#include "building.hpp"
#include <string>
#include <iostream>

class Commercial : public Building {
    public:
    Commercial(const std::string& buildingName, std::pair<int,int> location, std::string& typeOfCommercial) :
                Building(buildingName, location), typeOfCommmercial_(typeOfCommercial) {}

    ~Commercial();

    void Display() {
        std::cout << "This is a " << typeOfCommmercial_ << std::endl;
    }

    private:
    std::string typeOfCommmercial_;
};