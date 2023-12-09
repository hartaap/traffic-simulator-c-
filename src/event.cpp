#include "event.hpp"
#include <algorithm>
#include <random>

Event::Event(Person* person, std::vector<Node*> buildingNodes) {
    person_ = person;
    buildingNodes_ = buildingNodes;
    std::random_device rd;
    generator_.seed(rd());

    // Shuffle the buildingNodes
    std::shuffle(buildingNodes_.begin(), buildingNodes_.end(), generator_);
}



std::map<int, Node*> Event::CreateSchedule() {
    int lastSelectedIndex = -1;  // Initialize to an invalid index
    int ind;
    do {    
            ind = rand() % buildingNodes_.size();
        } while (buildingNodes_[ind] == person_->GetResidence()); // check that first destination isnt the initial node.
        int timeDiff = (rand() % 5 + 1);
        schedule_[timeDiff] = buildingNodes_[ind];
        lastSelectedIndex = ind;

    for (int time = 70; time <= 1000; time += 100) {
        int index;
        //Cant be two consecutive nodes
        do {
            index = rand() % buildingNodes_.size();
        } while (index == lastSelectedIndex);

        lastSelectedIndex = index;
        // Randomly choose whether to add or subtract time
        int timeDifferenceSign = (rand() % 2 == 0) ? 1 : -1;
        // Add a time difference between 1 and 5 minutes
        int timeDifference = timeDifferenceSign * (rand() % 5 + 1);
        schedule_[time + timeDifference] = buildingNodes_[index];
    }

    return schedule_;
}
