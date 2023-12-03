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
#include <cstdlib>

class Visualization {

    public:

    Visualization(int cellSize): window_(sf::VideoMode(800, 600), "Traffic Simulation"), cellSize_(cellSize){}

    void PrintGrid(Grid* grid);

    void PrintCars(std::vector<Car*> cars);


    private:

    sf::RenderWindow window_;
    int cellSize_;
};