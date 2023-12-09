#include "person.hpp"
#include <chrono>  // Include for std::chrono
#include <ctime>   // Include for std::time

Person::Person(const std::string& name, PersonType personType, Node* workplace, Node* home)
           : name_(name), personType_(personType),
             workplace_(workplace), home_(home), status_(false) {
                location_ = home_->GetLocation(); // initial location is at home.
                car_ = new Car(home); // creates a car for a person starting from home.
                car_->SetColor(personType_);
             }

Person::~Person() {
        delete(car_);
        delete(home_);
        delete(workplace_);

        for (auto i : schedule_) {
                delete (i.second);
        }
}

Node* Person::GetWorkplace() const {
        return workplace_;
}

Node* Person::GetResidence() const {
        return home_;
}

Car* Person::GetCar() {
        return car_;
}

void Person::InitializeSchedule(std::map<int, Node*> schedule) {
        schedule_ = schedule;
    }

bool Person::isBusy() const {
        return status_;
}

bool Person::isAtHome() const {
        return (this->GetLocation() == home_->GetLocation());
}

std::pair<int, int> Person::GetLocation() const {
        return {round(location_.first), round(location_.second)};
}

PersonType Person::GetPersonType() const {
        return personType_;
}

std::map<int,Node*> Person::GetSchedule() const {
        return schedule_;
}

void Person::AddEvent(int time, Node* node){
        schedule_.insert({time, node});    
        car_->AddEvent(time, node); // Adds the same event to the corresponding car
}

int Person::TimeUntilNextEvent() const {
      
    }
        // menee kotiin jos on aikaa, kesken


void Person::UpdateLocationFromCar(std::pair<float,float> location) {
    // Update person's location based on car's location, in car.cpp update function, which is called in city.cpp updatecars, so
    // they work in sync.
      location_ = location;
}
