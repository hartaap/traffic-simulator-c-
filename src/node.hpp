#ifndef NODE_H
#define NODE_H

#include <utility>
#include <vector>
#include "trafficlight.hpp"
#include <map>
#include <string>

enum class NodeType { Building, Intersection };

class Node {

    public:

    Node(NodeType type, const std::pair<int, int> location);

    NodeType GetType() const;

    std::vector<std::pair<Node*, int>> GetConnections() const;

    void AddConnection(Node* node, int weight);

    std::pair<int, int> GetLocation() const;

    TrafficLight* GetTrafficLightUp();

    TrafficLight* GetTrafficLightDown();


    TrafficLight* GetTrafficLightRight();

    TrafficLight* GetTrafficLightLeft();



    private:
    NodeType type_;
    std::pair<int, int> location_;
    std::vector<std::pair<Node*, int>> connections_;

    std::map<std::string, TrafficLight*> trafficLights_;
    
};



#endif