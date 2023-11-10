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


bool City::AddRoad(Road* r){

    //Check if road coordinates are ok
    if((!r->IsHorizontal()) && (!r->IsVertical())){ //Invalid road
         return false;
    }

    if((r->GetStart().first < 0) || (r->GetStart().second < 0) || 
       (r->GetEnd().first >= grid_->GetSizeX()) || (r->GetEnd().second >= grid_->GetSizeY())){
          return false;
       }


    if(r->IsVertical()){ 

        //Check that there are no buildings or other roads between the start and end coordinates
        for(int j = r->GetStart().second; j <= r->GetEnd().second; j++){
            if(grid_->GetCell(j, r->GetStart().first)->IsOccupied()){
                return false;
            }
        }
        
        //Make the road and add it to the grid
        roads_.push_back(r);
        MakeRoad(r);

    }else{

        //Check that there are no buildings or other roads between the start and end coordinates
        for(int i = r->GetStart().first; i <= r->GetEnd().second; i++){
            if(grid_->GetCell(r->GetStart().second, i)->IsOccupied()){
                return false;
            }
        }

        //Make the road and add it to the grid
        roads_.push_back(r);
        MakeRoad(r);

    }

    return true;
}



void City::MakeRoad(Road* r){
    if(r->IsHorizontal()){
        for(int i = r->GetStart().first; i <= r->GetEnd().first; i++){
        grid_->GetCell(r->GetStart().second, i)->Occupy("Road");
       }
    }else{
      for(int j = r->GetStart().second; j <= r->GetEnd().second; j++){
        grid_->GetCell(j, r->GetStart().first)->Occupy("Road");
      }
    }
}

void City::PrintCity(){
    for(int i = 0; i < grid_->GetSizeX(); i++){
        for(int j = 0; j < grid_->GetSizeY(); j++){
            if(grid_->GetCell(i, j)->GetType() == "Road"){
                std::cout << "[R]";
            }else if(grid_->GetCell(i, j)->GetType() == "Building"){
                std::cout << "[B]";
            }else{
                std::cout << "[ ]";
            }
        }
        std::cout << std::endl;
    }
}