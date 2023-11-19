#ifndef NODE_H
#define NODE_H

#include <utility>
#include <vector>


enum class NodeType { Building, Intersection };

class Node {

    public:

    Node(NodeType type, const std::pair<int, int> location);

    NodeType GetType() const;

    std::vector<Node*> GetConnections() const;

    void AddConnection(Node* node);

    std::pair<int, int> GetLocation() const;

    private:
    NodeType type_;
    std::pair<int, int> location_;
    std::vector<Node*> connections_;
    
};



#endif