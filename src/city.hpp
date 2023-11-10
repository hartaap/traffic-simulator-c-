#ifndef CITY_H
#define CITY_H


#include "grid.hpp"
#include "cell.hpp"
#include "road.hpp"
#include <vector>


class City{

    public:

    City(int sizeX, int sizeY);

    ~City();

   bool AddRoad(std::pair<int, int> start, std::pair<int, int> end, int speedLimit);

   void PrintCity();



    private:

    Grid* grid_;
    std::vector<Road*> roads_;
    
};




#endif