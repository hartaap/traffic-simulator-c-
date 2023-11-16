#include "car.hpp"
#include <string>

Car::Car(float x, float y) {
    carShape.setSize(sf::Vector2f(30, 15));
    carShape.setFillColor(sf::Color::Red);
    location_ = {x, y};
    end_location_ = {x, y};
    carShape.setPosition(x, y);
    speed = 10.0; 
    direction_ = "Right"; 
}



void Car::Update(float deltaTime) {
    float distance = speed * deltaTime;
    float dx = 0.0;
    float dy = 0.0;


    if (direction_ == "Up") {
        dy = -distance;
    } else if(direction_ == "Down") {
        dy = distance;
    }else if(direction_ == "Right"){
        dx = distance;
    }else if(direction_ == "Left"){
        dx = -distance;
    }
    location_ = {location_.first+dx, location_.second+dy};
    carShape.move(dx, dy);
}

void Car::Draw(sf::RenderWindow& window) {
    window.draw(carShape);
}