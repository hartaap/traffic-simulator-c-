#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "residential.hpp"
#include "industrial.hpp"
#include "building.hpp"




class Person {
 public:
    Person(std::string name, std::vector<std::map<int, Building&>> schedule,
           std::pair<int, int> location, Industrial& workplace, Residential& home)
           : name_(name), schedule_(schedule), location_(location), workplace_(workplace), home_(home), status_(false)
           {}

    Industrial& GetWorkplace() const {
        return workplace_;
    }
    Residential& GetResidence() const {
        return home_;
    }
    bool isBusy() const {
        return status_;
    }
    std::pair<int,int> GetLocation() const {
        return location_;
    }
    
 private:
    std::string name_;
    Industrial& workplace_;
    Residential& home_;
    std::vector<std::map<int, Building&>> schedule_;
    std::pair<int,int> location_;
    bool status_;
};

#endif


