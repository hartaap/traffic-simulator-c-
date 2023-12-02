#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "building.hpp"

enum CommercialType {
    GYM,
    RESTAURANT,
    SHOP
};

class Commercial : public Building {
public:
    Commercial(const std::string& buildingName, const std::pair<int, int>& location, CommercialType type);

    int GetMaxPeopleCapacity() const override;
    int GetMaxCarCapacity() const override;
    
    // Additional functions for common behavior
    void CommonCommercialFunction() const;

private:
    CommercialType type_;

    // Commercial-specific members
    int maxPeopleCapacity_;
    int maxCarCapacity_;
};

#endif
