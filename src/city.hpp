#ifndef CITY_H
#define CITY_H


#include "grid.hpp"
#include "cell.hpp"
#include "road.hpp"
#include "building.hpp"
#include <vector>


class City{

    public:

    City(int sizeX, int sizeY);

    ~City();

   bool IsValidRoad(Road* R) const;

   void AddRoad(Road* r);

   bool IsValidBuilding(Building* b) const;

   void AddBuilding(Building* b);

   void PrintCity();



    private:

    Grid* grid_;
    std::vector<Road*> roads_;
    std::vector<Building*> buildings_;
    
};




#endif