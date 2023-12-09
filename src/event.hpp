#ifndef EVENT_H
#define EVENT_H
#include "node.hpp"
#include "person.hpp"
#include <random>

class Event {
 public:
    Event(Person* person, std::vector<Node*> buildingNodes);

    std::map<int, Node*> CreateSchedule();

 private:
    std::map<int, Node*> schedule_;
    Person* person_;
    std::vector<Node*> buildingNodes_;
    std::default_random_engine generator_; // for randomizing
};


#endif
