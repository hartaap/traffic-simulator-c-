#include "person.hpp"

void Person::AddEvent(int time, Node* node){
        schedule_.insert({time, node});    
        car_->AddEvent(time, node); // Adds the same event to the corresponding car
}

void Person::UpdateLocationFromCar(std::pair<float,float> location) {
    // Update person's location based on car's location, in car.cpp update function, which is called in city.cpp updatecars, so
    // they work in sync.
      location_ = location;
}

