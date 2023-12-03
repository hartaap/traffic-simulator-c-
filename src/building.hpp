#ifndef BUILDING_H
#define BUILDING_H

#include "person.hpp"
#include "car.hpp"
#include <vector>
#include <string>

class Building {
 public:
    Building(const std::string& buildingName, const std::pair<int, int>& location);
    
    virtual ~Building();
    
    virtual int GetMaxPeopleCapacity() const = 0; 

    virtual int GetMaxCarCapacity() const = 0; 

    int GetPeopleAmount() const;

    int GetCarAmount() const;

    const std::string& GetName() const;

    const std::pair<int, int>& GetLocation() const;

 private:
    std::string buildingName_;
    std::pair<int, int> location_;
    std::vector<Person> persons_;
    std::vector<Car> cars_;
};

#endif
