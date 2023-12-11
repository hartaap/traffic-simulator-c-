#include <cassert>
#include <iostream>

#include "test_functions.hpp"
#include "../src/car.hpp"
#include "../src/node.hpp"
#include "../src/road.hpp"
#include "../src/intersection.hpp"

void TestCar() {
    //Add two nodes
    Node* n1 = new Node(NodeType::Building, {0, 0});
    Node* n2 = new Node(NodeType::Building, {0, 4});
    std::vector<Node*> allNodes;
    allNodes.push_back(n1);
    allNodes.push_back(n2);
    n1->AddConnection(n2, 4);
    n2->AddConnection(n1, 4);
    std::vector<Intersection*> intersections;
    std::vector<Road*> roads;
    std::vector<Car*> cars;
    
    //Create car
    Car* c = new Car(n1);

    c->AddEvent(1, n2);

    c->Update(0.0001, 1.0, allNodes, intersections, cars, roads);

    assert(c->GetDirection() == "Down");

   for(int i = 0;i < 50; i++){
    c->Update(0.0001, 2.0, allNodes, intersections, cars, roads);
   }

    float i = 0;
    float j = 4;

    assert(c->GetLocation() == std::make_pair(i, j));

    std::cout << "All car tests passed!" << std::endl;

    delete(n1);
    delete(n2);
    delete(c);

    return;
}