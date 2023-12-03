#include "commercial.hpp"

Commercial::Commercial(const std::string& buildingName, const std::pair<int, int>& location, const std::string& type)
    : Building(buildingName, location, type), type_(type) {
    
    std::string lowertype = type;
    // Compare two strings in a case-insensitive manner
    std::transform(lowertype.begin(), lowertype.end(), lowertype.begin(), [](unsigned char c){ return std::tolower(c); });

    if (lowertype == "gym") {
        maxPersonCapacity_ = 25;
        maxCarCapacity_ = 10;
    } else if (lowertype == "restaurant") {
        maxPersonCapacity_ = 30;
        maxCarCapacity_ = 8;
    } else if (lowertype == "shop") {
        maxPersonCapacity_ = 35;
        maxCarCapacity_ = 30;
    } else {
        throw std::invalid_argument("Invalid type");
    }
}

void Commercial::Info() const {
    std::string lowertype = type_;
    // Compare two strings in a case-insensitive manner again
    std::transform(lowertype.begin(), lowertype.end(), lowertype.begin(), [](unsigned char c){ return std::tolower(c); });

    std::cout << GetName() << " is a perfect place for ";
        if (lowertype == "gym") {
            std::cout << "training!" << std::endl;
         } else if (lowertype == "restaurant") {
            std::cout << "eating!" << std::endl;
         } else {
            std::cout << "shopping!" << std::endl;
         }
    }


