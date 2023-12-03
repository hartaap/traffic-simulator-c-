#include "city.hpp"
#include <iostream>

// Constructor
City::City(int sizeX, int sizeY){
    grid_ = new Grid(sizeX, sizeY);
}


// Destructor
City::~City(){

    for(auto it: roads_){
        delete(it);
    }

    for(auto it: buildings_){
        delete(it);
    }

    for(auto it: cars_){
        delete(it);
    }

    delete(grid_);
}


bool City::IsValidRoad(std::pair<int, int> start, std::pair<int, int> end) const{

    //If length is zero
    if(start == end){
        return false;
    }

    //Check if road is not vertical or horizontal
    if((start.first != end.first) && (start.second != end.second)){
         return false;
    }

    //Check that road is inside the grid coordinates
    if((start.first < 0) || (start.second < 0) || 
       (end.first < 0) || (end.second < 0)){
          return false;
    }

    int xMax = grid_->GetSizeX();
    int yMax = grid_->GetSizeY();

    if((start.first >= xMax) || (end.second >= yMax) || 
       (end.first >= xMax) || (end.second >= yMax)){
          return false;
    }

    if(start.first == end.first){ //vertical

       //Check that there are no buildings or other roads between the start and end coordinates

       if(start.second > end.second){

          for(int j = start.second+1; j <= end.second-1; j++){
            if(grid_->GetCell(j, start.first)->IsOccupied()){
                return false;
            }
          }
       }else{
          for(int j = end.second+1; j <= start.second-1; j++){
            if(grid_->GetCell(j, end.first)->IsOccupied()){
                return false;
            }
          }
       }
    }else{ //Horizontal

        //Check that there are no buildings or other roads between the start and end coordinates
        if(start.first > end.first){

           for(int i = start.first+1; i <= end.first-1; i++){
              if(grid_->GetCell(start.second, i)->IsOccupied()){
                return false;
             }
           }
        }else {
           for(int i = end.first+1; i <= start.first-1; i++){
              if(grid_->GetCell(start.second, i)->IsOccupied()){
                return false;
             }
           }           
        }
    }


  return true;

}


void City::AddRoad(std::pair<int, int> start, std::pair<int, int> end){


    // Check that the road connects two nodes

    if(GetNode(start) != nullptr && GetNode(end) != nullptr){

        if(IsValidRoad(start, end)){

          auto node1 = GetNode(start);
          auto node2 = GetNode(end);
          roads_.push_back(new Road(start, end, 10));

        // Occupy the cells with the new road

              if(start.first == end.first){ //vertical

                 node1->AddConnection(node2, abs(start.second - end.second));
                 node2->AddConnection(node1, abs(start.second - end.second));

                  if(start.second < end.second){

                    for(int j = start.second+1; j <= end.second-1; j++){
                        grid_->GetCell(start.first, j)->Occupy("Vertical Road");
                    }
                 }else{

                    for(int j = end.second+1; j <= start.second-1; j++){
                        grid_->GetCell(start.first, j)->Occupy("Vertical Road");
                    }
                 }

              }else{ //Horizontal

                 node1->AddConnection(node2, abs(start.first - end.first));
                 node2->AddConnection(node1, abs(start.first - end.first));        

                if(start.first < end.first){

                   for(int i = start.first+1; i <= end.first-1; i++){
                      grid_->GetCell(i, start.second)->Occupy("Horizontal Road");
                  }

               }else {

                  for(int i = end.first+1; i <= start.first-1; i++){
                     grid_->GetCell(i, start.second)->Occupy("Horizontal Road");
                  }           
              }
           }

        }


    }

}


bool City::IsValidBuilding(Building* b) const {
    if(b->GetLocation().first < 0 || b->GetLocation().second < 0){
        return false;
    }

    if(b->GetLocation().first >= grid_->GetSizeX() || b->GetLocation().second >= grid_->GetSizeY()){
        return false;
    }

    if(grid_->GetCell(b->GetLocation().first, b->GetLocation().second)->IsOccupied()){
        return false;
    }

    return true;
}



void City::AddBuilding(std::string name, std::pair<int, int> location){


    Building* b = new Building(name, location);

    //Check that the cell is not occupied or out of bounds
    if(!IsValidBuilding(b)){
        std::cout << "Invalid building location. It will be deleted!" << std::endl;
        delete(b);
    }else{
        buildings_.push_back(b);
        nodes_.push_back(new Node(NodeType::Building, location));
        grid_->GetCell(b->GetLocation().first, b->GetLocation().second)->Occupy("Building");
    }
}

void City::AddIntersection(std::pair<int, int> location){
    if(!grid_->GetCell(location.first, location.second)->IsOccupied()){
       intersections_.push_back(new Intersection(location));
       nodes_.push_back(new Node(NodeType::Intersection, location));
       grid_->GetCell(location.first, location.second)->Occupy("Intersection");
    }
}


Node* City::GetNode(std::pair<int, int> location){
    for(auto node: nodes_){
        if(node->GetLocation() == location){
            return node;
        }
    }
    return nullptr;
}


void City::AddCar(Car* c){
    cars_.push_back(c);
}

void City::AddTrafficLight(TrafficLight* t) {
    trafficLights_.push_back(t);
}

Intersection* City::GetIntersection(std::pair<int, int> location){
    for(auto it: intersections_){
        if(it->GetLocation() == location){
            return it;
        }
    }
    return nullptr;
}

void City::UpdateCars(float deltaTime, float currentTime) {
    for (auto car : cars_) {
        car->Update(deltaTime, currentTime, nodes_);
    }
}

void City::DrawCars(sf::RenderWindow& window) {
    for (const auto car : cars_) {
        car->Draw(window, 50);
    }
}





void City::PrintCity(sf::RenderWindow& window){
  
     const int cellSize = 50;

    for (int i = 0; i < grid_->GetSizeX(); i++) {
        for (int j = 0; j < grid_->GetSizeY(); j++) {
           grid_->GetCell(i, j)->Draw(window, cellSize, i, j);
        }
    }

}