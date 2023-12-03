#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include <string>
#include <iostream>


class Building {
 public:
    Building(const std::string& buildingName, const std::pair<int, int>& location);
    
    virtual ~Building();
    
    int GetMaxPeopleCapacity() const {
      return maxPersonCapacity_;
    }

    int GetMaxCarCapacity() const {
      return maxCarCapacity_;
    }

    virtual void Info() const = 0;

    int GetPeopleAmount() const;

    int GetCarAmount() const;

    bool isFull() const {
      return ((maxPersonCapacity_ - personAmount_) > 0);
    }

    const std::string& GetName() const;

    const std::pair<int, int>& GetLocation() const;

 protected:
    std::string buildingName_;
    std::pair<int, int> location_;
    int personAmount_;
    int carAmount_;
    int maxPersonCapacity_;
    int maxCarCapacity_;
};

#endif

