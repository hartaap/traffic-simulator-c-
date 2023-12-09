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

    int timeDifferenceRange = 5;  // Default time difference range

    // Adjust time difference range based on PersonType
    switch (person_->GetPersonType()) {
        case PersonType::Lazy:
            timeDifferenceRange += 40;  // Additional 10 minutes for Lazy type
            break;
        case PersonType::Active:
            // Active type stays with the default range
            break;
        case PersonType::Neutral:
            timeDifferenceRange -= 5;  // Reduce 5 minutes for Neutral type
            break;
        case PersonType::Gentleman:
            timeDifferenceRange += 20;  // Additional 5 minutes for Gentleman type
            break;
        case PersonType::Angry:
            timeDifferenceRange += 30;  // Reduce 10 minutes for Angry type
            break;
    }

    do {    
        ind = rand() % buildingNodes_.size();
    } while (buildingNodes_[ind] == person_->GetResidence());

    int timeDiff = (rand() % timeDifferenceRange + 1);
    schedule_[timeDiff] = buildingNodes_[ind];
    lastSelectedIndex = ind;

    for (int time = 30; time <= 1000; time += 60) {
        int index;

        do {
            index = rand() % buildingNodes_.size();
        } while (index == lastSelectedIndex || (buildingNodes_[index] == person_->GetResidence()));

        lastSelectedIndex = index;

        int timeDifferenceSign = (rand() % 2 == 0) ? 1 : -1;
        int timeDifference = timeDifferenceSign * (rand() % timeDifferenceRange + 1);
        schedule_[time + timeDifference] = buildingNodes_[index];
    }

    return schedule_;
}


