#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "node.hpp"
#include <map>
#include <queue>
#include <limits>
#include "intersection.hpp"
#include <algorithm>
#include "road.hpp"

enum class PersonType { // person type for setting color and adjusting schedule
    Lazy,
    Active,
    Neutral,
    Gentleman,
    Angry
};

class Car {
public:
    Car(Node* startingNode);

    void Update(float deltaTime, float currentTime, std::vector<Node*> allNodes, std::vector<Intersection*> intersections, 
                std::vector<Car*> cars, std::vector<Road*> roads);
    Intersection* GetIntersection(std::vector<Intersection*> intersections);
    void SetDestination(Node* destination);
    void SetDirection(std::pair<int, int> current, std::pair<int, int> destination);
    void SetSpeedLimit(std::vector<Road*> roads);
    bool AtDestination(float destinationX, float destinationY);
    bool CheckIntersection(Intersection* intersection, std::vector<Car*> cars);
    bool LaneIsFree(Intersection* intersection, std::vector<Car*> cars, std::string nextDirection);
    std::string& GetDirection();
    void Draw(sf::RenderWindow& window, int cellSize);
    void AddEvent(int time, Node* node);
    void InitializeSchedule(std::map<int, Node*> schedule);
    bool CarInFront(std::vector<Car*> cars);
    void SetColor(PersonType pType);
    std::pair<int, int> GetLocation();

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

    float maxSpeed_;
    float acceleration_;
    float currentSpeed_;
    bool idle_;
    float currentSpeedLimit;
    std::string direction_;
    std::pair<float, float> location_;
    Node* destination_;
    std::vector<Node*> path_;
    std::map<int, Node*> schedule_;
    Node* previous_;
    sf::Color color_;
};

#endif
