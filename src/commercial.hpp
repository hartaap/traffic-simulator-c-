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

    void Info() const override {
        std::cout << GetName() << " is a perfect place for ";
        if (type_ == GYM) {
            std::cout << "training!" << std::endl;
         } else if (type_== RESTAURANT) {
            std::cout << "eating!" << std::endl;
         } else {
            std::cout << "shopping!" << std::endl;
         }
    }

 private:
    CommercialType type_;
   
};

#endif
