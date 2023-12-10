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
#include "simulationClock.hpp"



class Person {
public:
    Person(const std::string& name, PersonType personType, Industrial* workplace, Residential* home);

    Industrial* GetWorkplace() const;

    Residential* GetResidence() const;

    Car* GetCar();

    void BuyCar(Car* car);

    void InitializeSchedule(std::map<int, Node*> schedule);

    bool isAtHome() const;

    std::pair<int, int> GetLocation() const;

    PersonType GetPersonType() const;

    std::map<int,Node*> GetSchedule() const;

    void AddEvent(int time, Node* node); // add event to schedule, according to the events in class car, car calls the function update()

    void UpdateLocationFromCar(std::pair<float, float> location); // used in car->update() to sync with the location of a car linked to person

private:
    std::string name_;
    PersonType personType_;
    std::map<int, Node*> schedule_; 
    Industrial* workplace_;
    std::pair<float,float> location_;
    Residential* home_;
    Car* car_;
};

#endif


