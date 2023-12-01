#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "node.hpp"
#include <map>
#include <queue>
#include <limits>

class Car {
public:
    Car(float x, float y, Node* startingNode);

    void Update(float deltaTime, float currentTime, std::vector<Node*> allNodes);
    void SetDestination(Node* destination);
    void SetDirection(std::pair<int, int> current, std::pair<int, int> destination);
    void Draw(sf::RenderWindow& window);
    void AddEvent(int time, Node* node);

    std::vector<Node*> Dijkstra(Node* source, Node* destination, std::vector<Node*> allNodes);


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
    std::vector<Node*> path_;
    std::map<int, Node*> schedule_;
    Node* previous_;
};

#endif