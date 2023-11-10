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

   bool AddRoad(Road* r);

   void MakeRoad(Road* r);

   bool AddBuilding(std::pair<int, int> location);

   void PrintCity();



    private:

    Grid* grid_;
    std::vector<Road*> roads_;
    
};




#endif