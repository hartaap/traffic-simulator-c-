#include "car.hpp"
#include <string>
#include <cmath>

/*Constructor: Create a Car object and initialize its variables*/
Car::Car(float x, float y, Node* startingNode) {
    
    location_ = {x, y};
    maxSpeed_ = 0.6; 
    currentSpeed_ = 0.0;
    acceleration_ = 0.1;
    direction_ = "None";
    destination_ = nullptr;

    previous_ = startingNode;

    sf::Color LightBlue(173, 216, 230);

    leftFrontTireShape.setFillColor(sf::Color::Black);
    leftRearTireShape.setFillColor(sf::Color::Black);
    rightFrontTireShape.setFillColor(sf::Color::Black);
    rightRearTireShape.setFillColor(sf::Color::Black);
    rightFrontLight.setFillColor(sf::Color::Yellow);
    leftFrontLight.setFillColor(sf::Color::Yellow);
    frontWindow.setFillColor(LightBlue);
     //carShape.setPosition(location_.first*cellSize, location_.second*cellSize);

}

//Set destination for car
void Car::SetDestination(Node* destination){
    destination_ = destination;
}

//Set direction for car
void Car::SetDirection(std::pair<int, int> current, std::pair<int, int> destination){
    if(destination.first < current.first){
        direction_ = "Left";
    }else if(destination.first > current.first){
        direction_ = "Right";
        location_.first += 0.2;
    }else if(destination.second < current.second){
        direction_ = "Up";
    }else if(destination.second > current.second){
        direction_ = "Down";
        location_.second += 0.2;
    }
}

std::pair<int, int> Car::GetLocation(){
    return location_;
}

std::string& Car::GetDirection(){
    return direction_;
}

Intersection* Car::GetIntersection(std::pair<int, int> location, std::vector<Intersection*> intersections){
    for(auto it : intersections){
        if(it->GetLocation() == location){
            return it;
        }
    }
    return nullptr;
}

bool Car::CarInFront(std::vector<Car*> cars) {
    for (auto car : cars) {
        if (car == this) {
            continue; 
        }

        // Check if cars are in the same lane
        if (car->GetDirection() == direction_) {
            auto l = car->GetLocation();


            float minDistance = 1;

            if (direction_ == "Up" && l.first == location_.first){
                if(location_.second - l.second <= minDistance && location_.second - l.second >= 0){
                    return true;
                }
            } else if (direction_ == "Down" && l.first == location_.first) {
                if(((l.second - location_.second) <= minDistance) && ((l.second - location_.second) >= 0)){
                    return true;
                }
            } else if (direction_ == "Left" && l.second == location_.second) {
                if(((location_.first - l.first) <= minDistance) && ((location_.first - l.first) >= 0)){
                    return true;
                }
            } else if (direction_ == "Right" && l.second == location_.second) {
                if(((l.first - location_.first) <= minDistance) && ((l.first - location_.first) >= 0)){
                    return true;
                }
            }
        }
    }

    return false; 
}

bool Car::AtDestination(float destinationX, float destinationY){
    if(direction_ == "Up"){
        if((location_.first == destinationX) && (location_.second - destinationY) < 0.5 ){
            return true;
        }
    }else if(direction_ == "Down"){
        if((location_.first == destinationX) && (destinationY - location_.second) < 0.1 ){
            return true;
        }
    }else if(direction_ == "Right"){
        if((location_.second == destinationY) && (destinationX - location_.first) < 0.1){
            return true;
        }
    }else if(direction_ == "Left"){
        if((location_.second == destinationY) && (location_.first - destinationX) < 0.5){
            return true;
        }
    }
    return false;
}



//Update the cars location and destination
void Car::Update(float deltaTime, float currentTime, std::vector<Node*> allNodes, std::vector<Intersection*> intersections, std::vector<Car*> cars) {

//Car has found current destination
    if(direction_ == "None"){

        if(path_.empty()){ //Car is idle
           //Check if car is supposed to go somewhere
           auto next = schedule_.find(round(currentTime)); 

           //If car has a destination node, find the best path
           if(next != schedule_.end()){
               path_ = Dijkstra(previous_, next->second, allNodes);
               destination_ = path_.back();
               path_.pop_back();
               location_ = previous_->GetLocation();
               SetDirection(location_, destination_->GetLocation());
           }

       }else{ //Car is on the way to final destination
           destination_ = path_.back();
           path_.pop_back();
           location_ = previous_->GetLocation();
           SetDirection(location_, destination_->GetLocation());
       }
        
    }
    
    //Check if current destination has been reached
    if(destination_ == nullptr){

    }else if (AtDestination(destination_->GetLocation().first, destination_->GetLocation().second)){
        location_ = destination_->GetLocation();
        direction_ = "None";
        previous_ = destination_;
        currentSpeed_ = 0.0;
    }

    //Update cars location
    currentSpeed_ = std::min(currentSpeed_ + acceleration_, maxSpeed_);

    float distance = currentSpeed_ * deltaTime;
    float dx = 0.0;
    float dy = 0.0;


    if(CarInFront(cars)){
        currentSpeed_ = 0;
    }else if (direction_ == "Up") {
        auto intersection = GetIntersection({round(location_.first), round(location_.second - 1)}, intersections);

        if(intersection != nullptr){
            if(intersection->AllowVertical()){
                dy = -distance;
            }
        }else{
            dy = -distance;
        }
    } else if(direction_ == "Down") {

        auto intersection = GetIntersection({round(location_.first), round(location_.second + 0.5)}, intersections);

        if(intersection != nullptr){
            if(intersection->AllowVertical()){
                dy = distance;
            }
        }else{
            dy = distance;
        }
    }else if(direction_ == "Right"){
        auto intersection = GetIntersection({round(location_.first + 0.5), round(location_.second)}, intersections);

        if(intersection != nullptr){
            if(intersection->AllowHorizontal()){
                dx = distance;
            }
        }else{
            dx = distance;
        }
    }else if(direction_ == "Left"){
        auto intersection = GetIntersection({round(location_.first - 1), round(location_.second)}, intersections);

        if(intersection != nullptr){
            if(intersection->AllowHorizontal()){
                dx = -distance;
            }
        }else{
            dx = -distance;
        }
    }
    location_ = {location_.first+dx, location_.second+dy};
    //carShape.move(dx, dy);
}



//Add an event to the cars schedule
void Car::AddEvent(int time, Node* node){
    schedule_.insert({time, node});
}

//Dijkstras algorithm to find the best path from source node to destination node
std::vector<Node*> Car::Dijkstra(Node* source, Node* destination, std::vector<Node*> allNodes){

    //Priority queue for finding the path with shortest distance
    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<>> priority_queue;

    //Map every node with its distance from source node
    std::unordered_map<Node*, int> distances;

    //Linked list for reconstructing the path
    std::unordered_map<Node*, Node*> previous_list;

    priority_queue.push({0, source});

    //Initialize distances
    for(auto it: allNodes){
        distances[it] = 1000;
    }

    distances[source] = 0;

    //Loop to get distances and previous nodes for all nodes
    while(!priority_queue.empty()){

        Node* currentNode = priority_queue.top().second;
        priority_queue.pop();

        for(auto it: currentNode->GetConnections()){

            int currentDistance = distances[currentNode] + it.second;

            if(currentDistance < distances[it.first]){
                distances[it.first] = currentDistance;
                previous_list[it.first] = currentNode;
                priority_queue.push({currentDistance, it.first});
            }
        }
    }


    std::vector<Node*> result;

    Node* current = destination;

    //Reconstruct the path to destination node
    while(current != nullptr){
        result.push_back(current);
        current = previous_list[current];
    }

    result.pop_back();

    return result;

}


/*Draw the car-shape according to its direction*/
void Car::Draw(sf::RenderWindow& window, int cellSize) {




    carShape.setFillColor(sf::Color::Red);

    if(direction_ == "Right"){
       carShape.setSize(sf::Vector2f(30, 15));
       leftRearTireShape.setSize(sf::Vector2f(6.0, 2.0));
       rightRearTireShape.setSize(sf::Vector2f(6.0, 2.0));
       leftFrontTireShape.setSize(sf::Vector2f(6.0, 2.0));
       rightFrontTireShape.setSize(sf::Vector2f(6.0, 2.0));

       rightFrontLight.setSize(sf::Vector2f(2.0, 6.0));
       leftFrontLight.setSize(sf::Vector2f(2.0, 6.0));

       rightFrontLight.setPosition(location_.first*cellSize+28, location_.second*cellSize+42);
       leftFrontLight.setPosition(location_.first*cellSize+28, location_.second*cellSize+33);

       frontWindow.setSize(sf::Vector2f(8.0, 13));
       frontWindow.setPosition(location_.first*cellSize+16, location_.second*cellSize+34);


       leftRearTireShape.setPosition(location_.first*cellSize, location_.second*cellSize+31);
       rightRearTireShape.setPosition(location_.first*cellSize, location_.second*cellSize+48);
       leftFrontTireShape.setPosition(location_.first*cellSize+20, location_.second*cellSize+31);
       rightFrontTireShape.setPosition(location_.first*cellSize+20, location_.second*cellSize+48);

       carShape.setPosition(location_.first*cellSize, location_.second*cellSize+32.5);
    }else if(direction_ == "Left"){
        carShape.setSize(sf::Vector2f(30, 15));
        carShape.setPosition(location_.first*cellSize, location_.second*cellSize+2.5);

       leftRearTireShape.setSize(sf::Vector2f(6.0, 2.0));
       rightRearTireShape.setSize(sf::Vector2f(6.0, 2.0));
       leftFrontTireShape.setSize(sf::Vector2f(6.0, 2.0));
       rightFrontTireShape.setSize(sf::Vector2f(6.0, 2.0));

       rightFrontLight.setSize(sf::Vector2f(2.0, 6.0));
       leftFrontLight.setSize(sf::Vector2f(2.0, 6.0));

       rightFrontLight.setPosition(location_.first*cellSize, location_.second*cellSize+2.5);
       leftFrontLight.setPosition(location_.first*cellSize, location_.second*cellSize+11.5);

       frontWindow.setSize(sf::Vector2f(8.0, 13));
       frontWindow.setPosition(location_.first*cellSize+6, location_.second*cellSize+4);


       leftRearTireShape.setPosition(location_.first*cellSize+20, location_.second*cellSize+18);
       rightRearTireShape.setPosition(location_.first*cellSize+20, location_.second*cellSize+1);
       leftFrontTireShape.setPosition(location_.first*cellSize, location_.second*cellSize+18);
       rightFrontTireShape.setPosition(location_.first*cellSize, location_.second*cellSize+1);

    }else if(direction_ == "Down"){
        carShape.setSize(sf::Vector2f(15, 30));
        carShape.setPosition(location_.first*cellSize+2.5, location_.second*cellSize);

       leftRearTireShape.setSize(sf::Vector2f(2.0, 6.0));
       rightRearTireShape.setSize(sf::Vector2f(2.0, 6.0));
       leftFrontTireShape.setSize(sf::Vector2f(2.0, 6.0));
       rightFrontTireShape.setSize(sf::Vector2f(2.0, 6.0));

       rightFrontLight.setSize(sf::Vector2f(6.0, 2.0));
       leftFrontLight.setSize(sf::Vector2f(6.0, 2.0));

       rightFrontLight.setPosition(location_.first*cellSize+2, location_.second*cellSize+28);
       leftFrontLight.setPosition(location_.first*cellSize+11.5, location_.second*cellSize+28);

       frontWindow.setSize(sf::Vector2f(13.0, 8.0));
       frontWindow.setPosition(location_.first*cellSize+2.55, location_.second*cellSize+16);


       leftRearTireShape.setPosition(location_.first*cellSize+17, location_.second*cellSize);
       rightRearTireShape.setPosition(location_.first*cellSize, location_.second*cellSize);
       leftFrontTireShape.setPosition(location_.first*cellSize+17, location_.second*cellSize+20);
       rightFrontTireShape.setPosition(location_.first*cellSize, location_.second*cellSize+20);

    }else if(direction_ == "Up"){
        carShape.setSize(sf::Vector2f(15, 30));
        carShape.setPosition(location_.first*cellSize+32.5, location_.second*cellSize);

       leftRearTireShape.setSize(sf::Vector2f(2.0, 6.0));
       rightRearTireShape.setSize(sf::Vector2f(2.0, 6.0));
       leftFrontTireShape.setSize(sf::Vector2f(2.0, 6.0));
       rightFrontTireShape.setSize(sf::Vector2f(2.0, 6.0));

       rightFrontLight.setSize(sf::Vector2f(6.0, 2.0));
       leftFrontLight.setSize(sf::Vector2f(6.0, 2.0));

       rightFrontLight.setPosition(location_.first*cellSize+41, location_.second*cellSize);
       leftFrontLight.setPosition(location_.first*cellSize+32, location_.second*cellSize);

       frontWindow.setSize(sf::Vector2f(13.0, 8.0));
       frontWindow.setPosition(location_.first*cellSize+32.55, location_.second*cellSize+4);


       leftRearTireShape.setPosition(location_.first*cellSize+30, location_.second*cellSize+23);
       rightRearTireShape.setPosition(location_.first*cellSize+47, location_.second*cellSize+23);
       leftFrontTireShape.setPosition(location_.first*cellSize+30, location_.second*cellSize+4);
       rightFrontTireShape.setPosition(location_.first*cellSize+47, location_.second*cellSize+4);
    }
    window.draw(carShape);
    window.draw(leftRearTireShape);
    window.draw(rightRearTireShape);
    window.draw(leftFrontTireShape);
    window.draw(rightFrontTireShape);
    window.draw(rightFrontLight);
    window.draw(leftFrontLight);
    window.draw(frontWindow);
}



