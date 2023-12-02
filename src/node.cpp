#include "node.hpp"



Node::Node(NodeType type, const std::pair<int, int> location): type_(type), location_(location) {}

std::pair<int, int> Node::GetLocation() const {
    return location_;
}

NodeType Node::GetType() const {
    return type_;
}

 std::vector<std::pair<Node*, int>> Node::GetConnections() const {
    return connections_;
}

void Node::AddConnection(Node* node, int weight) {
    connections_.push_back({node, weight});
}



    TrafficLight* Node::GetTrafficLightUp(){

        auto it = trafficLights_.find("Up");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }

    TrafficLight* Node::GetTrafficLightDown(){

        auto it = trafficLights_.find("Down");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }


    TrafficLight* Node::GetTrafficLightRight(){

        auto it = trafficLights_.find("Right");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }

    TrafficLight* Node::GetTrafficLightLeft(){

        auto it = trafficLights_.find("Left");

        if(it != trafficLights_.end()){
            return it->second;
        }else{
            return nullptr;
        }
    }

