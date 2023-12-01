#include "car.hpp"
#include <string>
#include <cmath>

Car::Car(float x, float y, Node* startingNode) {
    
    int cellSize = 50;
    location_ = {x, y};
    speed = 0.6; 
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


void Car::SetDestination(Node* destination){
    destination_ = destination;
}

void Car::SetDirection(std::pair<int, int> current, std::pair<int, int> destination){
    if(destination.first < current.first){
        direction_ = "Left";
    }else if(destination.first > current.first){
        direction_ = "Right";
    }else if(destination.second < current.second){
        direction_ = "Up";
    }else if(destination.second > current.second){
        direction_ = "Down";
    }
}



void Car::Update(float deltaTime, float currentTime, std::vector<Node*> allNodes) {

    if(direction_ == "None"){

        if(path_.empty()){

           auto next = schedule_.find(round(currentTime));

           if(next != schedule_.end()){
               path_ = Dijkstra(previous_, next->second, allNodes);
               destination_ = path_.back();
               path_.pop_back();
               location_ = previous_->GetLocation();
               SetDirection(location_, destination_->GetLocation());
           }

       }else{
           destination_ = path_.back();
           path_.pop_back();
           location_ = previous_->GetLocation();
           SetDirection(location_, destination_->GetLocation());
       }
        
    }
    
    if(destination_ == nullptr){

    } else if((direction_ == "Left") && (fabs(destination_->GetLocation().first - location_.first) <= 0.01) && (fabs(destination_->GetLocation().second - location_.second) <= 0.01)){
        location_ = destination_->GetLocation();
        direction_ = "None";
        previous_ = destination_;    
        
    }else if ((fabs(destination_->GetLocation().first - location_.first) <= 0.01) && (fabs(destination_->GetLocation().second - location_.second) <= 0.01)){
        location_ = destination_->GetLocation();
        direction_ = "None";
        previous_ = destination_;
    } //else{  
     //   SetDirection(location_, destination_->GetLocation());
   // }


    float distance = speed * deltaTime;
    float dx = 0.0;
    float dy = 0.0;


    if (direction_ == "Up") {
        dy = -distance;
    } else if(direction_ == "Down") {
        dy = distance;
    }else if(direction_ == "Right"){
        dx = distance;
    }else if(direction_ == "Left"){
        dx = -distance;
    }
    location_ = {location_.first+dx, location_.second+dy};
    //carShape.move(dx, dy);
}

void Car::AddEvent(int time, Node* node){
    schedule_.insert({time, node});
}

std::vector<Node*> Car::Dijkstra(Node* source, Node* destination, std::vector<Node*> allNodes){

    std::priority_queue<std::pair<int, Node*>, std::vector<std::pair<int, Node*>>, std::greater<>> priority_queue;

    std::unordered_map<Node*, int> distances;

    std::unordered_map<Node*, Node*> previous_list;


    priority_queue.push({0, source});

    for(auto it: allNodes){
        distances[it] = 1000;
    }

    distances[source] = 0;

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

    while(current != nullptr){
        result.push_back(current);
        current = previous_list[current];
    }

    result.pop_back();

    return result;

}



void Car::Draw(sf::RenderWindow& window) {

    int cellSize = 50;


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



