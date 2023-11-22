#include "city.hpp"
#include <iostream>


City::City(int sizeX, int sizeY){
    grid_ = new Grid(sizeX, sizeY);
}



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


bool City::IsValidRoad(Road* r) const{

    //If length is zero
    if(r->GetStart() == r->GetEnd()){
        return false;
    }

    //Check if road is not vertical or horizontal
    if((!r->IsHorizontal()) && (!r->IsVertical())){
         return false;
    }

    //Check that road is inside the grid coordinates
    if((r->GetStart().first < 0) || (r->GetStart().second < 0) || 
       (r->GetEnd().first < 0) || (r->GetEnd().second < 0)){
          return false;
    }

    int xMax = grid_->GetSizeX();
    int yMax = grid_->GetSizeY();

    if((r->GetStart().first >= xMax) || (r->GetStart().second >= yMax) || 
       (r->GetEnd().first >= xMax) || (r->GetEnd().second >= yMax)){
          return false;
    }

    if(r->IsVertical()){ 

        //Check that there are no buildings or other roads between the start and end coordinates
        for(int j = r->GetStart().second+1; j <= r->GetEnd().second-1; j++){
            if(grid_->GetCell(j, r->GetStart().first)->IsOccupied()){
                return false;
            }
        }
    }else{

        //Check that there are no buildings or other roads between the start and end coordinates
        for(int i = r->GetStart().first+1; i <= r->GetEnd().second-1; i++){
            if(grid_->GetCell(r->GetStart().second, i)->IsOccupied()){
                return false;
            }
        }
    }


  return true;

}


void City::AddRoad(Node* node1, Node* node2){

    Road* r = new Road(node1->GetLocation(), node2->GetLocation(), 10);

    if(!IsValidRoad(r)){
        std::cout << "Invalid road. It will be deleted!" << std::endl;
        delete(r);
    }else{

        node1->AddConnection(node2);
        node2->AddConnection(node1);

        roads_.push_back(r);
        if(r->IsHorizontal()){
           for(int i = r->GetStart().first+1; i <= r->GetEnd().first-1; i++){
               grid_->GetCell(i, r->GetStart().second)->Occupy("Horizontal Road");
            }
        }else{
           for(int j = r->GetStart().second+1; j <= r->GetEnd().second-1; j++){
               grid_->GetCell(r->GetStart().first, j)->Occupy("Vertical Road");
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
    intersections_.push_back(new Intersection(location));
    nodes_.push_back(new Node(NodeType::Intersection, location));
    grid_->GetCell(location.first, location.second)->Occupy("Intersection");
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

void City::UpdateCars(float deltaTime) {
    for (auto car : cars_) {
        car->Update(deltaTime);
    }
}

void City::DrawCars(sf::RenderWindow& window) {
    for (const auto car : cars_) {
        car->Draw(window);
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