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

    void Info() const override;

 private:
    CommercialType type_;
   
};

#endif

