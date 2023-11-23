#ifndef CITY_H
#define CITY_H

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "cell.hpp"
#include "road.hpp"
#include "building.hpp"
#include "car.hpp"
#include "trafficlight.hpp"
#include "intersection.hpp"
#include "industrial.hpp"
#include <vector>
#include "node.hpp"
#include "intersection.hpp"



class City{

    public:

    City(int sizeX, int sizeY);

    ~City();

    bool IsValidRoad(std::pair<int, int> start, std::pair<int, int> end) const;

    void AddRoad(std::pair<int, int> start, std::pair<int, int> end);

    bool IsValidBuilding(Building* b) const;

    void AddBuilding(std::string name, std::pair<int, int> location);

    Node* GetNode(std::pair<int, int> location);

    void AddCar(Car* c);

    void AddIntersection(std::pair<int, int> location);

    void AddTrafficLight(TrafficLight* t);

    void UpdateCars(float deltaTime);

    void DrawCars(sf::RenderWindow& window);

    void PrintCity(sf::RenderWindow& window);



    private:

    Grid* grid_;
    std::vector<Road*> roads_;
    std::vector<Building*> buildings_;
    std::vector<Intersection*> intersections_;
    std::vector<TrafficLight*> trafficLights_;
    std::vector<Car*> cars_;
    std::vector<Node*> nodes_;
    
};




#endif