#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "residential.hpp"
#include "industrial.hpp"
#include "building.hpp"
#include "node.hpp"



enum class PersonType { // initial types for testing purposes, can add more later
    Lazy,
    Active,
    Neutral
};

class Person {
 public:
    Person(const std::string& name, PersonType personType, std::map<int,std::map<int,Node*>> schedule,
           std::pair<int, int> location, Industrial& workplace, Residential& home)
           : name_(name), personType_(personType), schedule_(schedule), location_(location), workplace_(workplace), home_(home), status_(false)
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
    const PersonType& GetPersonType() const {
        return personType_;
    }
    
 private:
    std::string name_;
    PersonType personType_;
    Industrial& workplace_;
    Residential& home_;
    std::map<int,std::map<int,Node*>> schedule_; // multiple days, different days have different schedules, first day = schedule_[0], 
                                                    // second day = schedule_[1], ...

    std::pair<int,int> location_;
    bool status_;
};

#endif





