#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "grid.hpp"

class Car {
public:
    Car(float x, float y);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);


private:
    sf::RectangleShape carShape;
    float speed;
    std::string direction_;
    std::pair<int, int> end_location_;
    std::pair<int, int> location_;
};

#endif