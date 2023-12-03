#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "building.hpp"

class Commercial : public Building {
 public:
    Commercial(const std::string& buildingName, const std::pair<int, int>& location, const std::string& commercialType);

    void Info() const override;

 private:
    const std::string type_;
   
};

#endif

