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
#include "car.hpp"

/*enum class PersonType {
    Lazy,
    Active,
    Neutral
};
*/

class Person {
public:
    Person(const std::string& name, const std::string& personType, Industrial* workplace, Residential* home, Node* startNode)
           : name_(name), personType_(personType),
             workplace_(workplace), home_(home), status_(false) {
                location_ = home_->GetLocation(); // initial location is at home.
                car_ = new Car(startNode); // creates a car for a person starting from home.
                
             }


    Industrial* GetWorkplace() const {
        return workplace_;
    }

    Residential* GetResidence() const {
        return home_;
    }

    Car* GetCar() const {
        return car_;
    }

    bool isBusy() const {
        return status_; // might be unnecessary function
    }

    std::pair<float, float> GetLocation() const {
        return location_;
    }

    const std::string& GetPersonType() const {
        return personType_; // affects on the schedule
    }

    std::map<int,Node*> GetSchedule() const {
        return schedule_;
    }

    void AddEvent(int time, Node* node); // add event to schedule, according to the events in class car, car calls the function update()

   // int TimeUntilNextEvent() const; // doesnt work currently

    void UpdateLocationFromCar(std::pair<float, float> location); // used in car->update() to sync with the location of a car linked to person

private:
    std::string name_;
    std::string personType_;
    std::map<int, Node*> schedule_; 
    Industrial* workplace_;
    std::pair<float,float> location_;
    Residential* home_;
    bool status_;
    Car* car_;
};

#endif






