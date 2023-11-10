#include "city.hpp"
#include <iostream>


City::City(int sizeX, int sizeY){
    grid_ = new Grid(sizeX, sizeY);
}



City::~City(){
    
    for(auto it: roads_){
        delete(it);
    }

    delete(grid_);
}


bool City::AddRoad(std::pair<int, int> start, std::pair<int, int> end, int speedLimit){

    //Check if road coordinates are ok
    if((start.first != end.first) && (start.second != end.second)){
         return false;
    }

    if((start.first < 0) || (end.first >= grid_->GetSizeX()) || (start.second < 0) || (end.second >= grid_->GetSizeY())){
        return false;
    }


    if(start.first == end.first){ //If true, road is vertical

        //Check that there are no buildings or other roads between the start and end coordinates
        for(int j = start.second; j <= end.second; j++){
            if(grid_->GetCell(j, start.first)->IsOccupied()){
                return false;
            }
        }
        
        //Make the road and add it to the grid
        Road* road = new Road(start, end, speedLimit);
        roads_.push_back(road);
        road->MakeVertical(grid_, start.first, start.second, end.second);

    }else{ //Road is horizontal

        //Check that there are no buildings or other roads between the start and end coordinates
        for(int i = start.first; i <= end.second; i++){
            if(grid_->GetCell(start.second, i)->IsOccupied()){
                return false;
            }
        }

        //Make the road and add it to the grid
        Road* road = new Road(start, end, speedLimit);
        roads_.push_back(road);
        road->MakeHorizontal(grid_, start.second, start.first, end.first);

    }

    return true;
}

void City::PrintCity(){
    for(int i = 0; i < grid_->GetSizeX(); i++){
        for(int j = 0; j < grid_->GetSizeY(); j++){
            if(grid_->GetCell(i, j)->GetType() == "Road"){
                std::cout << "[R]";
            }else{
                std::cout << "[ ]";
            }
        }
        std::cout << std::endl;
    }
}