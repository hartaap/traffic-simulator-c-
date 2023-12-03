#include "commercial.hpp"

Commercial::Commercial(const std::string& buildingName, const std::pair<int, int>& location, CommercialType type)
    : Building(buildingName, location), type_(type) {
    
    switch (type) {
        case GYM:
            maxPersonCapacity_ = 25;
            maxCarCapacity_ = 10;
            break;
        case RESTAURANT:
            maxPersonCapacity_ = 30;
            maxCarCapacity_ = 8;
            break;
        case SHOP:
            maxPersonCapacity_ = 35;
            maxCarCapacity_ = 30;
            break;
    }
}

