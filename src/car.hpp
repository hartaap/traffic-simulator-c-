#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "node.hpp"

class Car {
public:
    Car(float x, float y);

    void Update(float deltaTime);
    void SetDestination(Node* destination);
    void Draw(sf::RenderWindow& window);


private:
    sf::RectangleShape carShape;
    sf::RectangleShape leftRearTireShape;
    sf::RectangleShape rightRearTireShape;
    sf::RectangleShape leftFrontTireShape;
    sf::RectangleShape rightFrontTireShape;
    sf::RectangleShape leftFrontLight;
    sf::RectangleShape rightFrontLight;
    sf::RectangleShape frontWindow;

    float speed;
    std::string direction_;
    std::pair<float, float> location_;
    Node* destination_;
};

#endif