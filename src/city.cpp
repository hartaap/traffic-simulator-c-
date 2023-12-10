#include "city.hpp"

#include <iostream>

City::City(int sizeX, int sizeY) { grid_ = new Grid(sizeX, sizeY); }

City::~City() {
  for (auto it : roads_) {
    delete (it);
  }

  for (auto it : buildings_) {
    delete (it);
  }

  for (auto it : personCarMap_) {
    delete (it.first);
    delete (it.second);
  }

  delete (grid_);
}

bool City::IsValidRoad(std::pair<int, int> start,
                       std::pair<int, int> end) const {
  // Check that the length of the road is not zero
  if (start == end) {
    return false;
  }

  // Check that road is not diagonal (only vertical or horizontal roads allowed)
  if ((start.first != end.first) && (start.second != end.second)) {
    return false;
  }

  // Check that road is inside the grid coordinates
  if ((start.first < 0) || (start.second < 0) || (end.first < 0) ||
      (end.second < 0)) {
    return false;
  }

  int xMax = grid_->GetSizeX();
  int yMax = grid_->GetSizeY();

  if ((start.first >= xMax) || (end.second >= yMax) || (end.first >= xMax) ||
      (end.second >= yMax)) {
    return false;
  }

  if (start.first == end.first) {  // vertical

    // Check that there are no buildings or other roads between the start and
    // end coordinates
    if (start.second > end.second) {
      for (int j = start.second + 1; j <= end.second - 1; j++) {
        if (grid_->GetCell(j, start.first)->IsOccupied()) {
          return false;
        }
      }
    } else {
      for (int j = end.second + 1; j <= start.second - 1; j++) {
        if (grid_->GetCell(j, end.first)->IsOccupied()) {
          return false;
        }
      }
    }

  } else {  // Horizontal

    // Check that there are no buildings or other roads between the start and
    // end coordinates
    if (start.first > end.first) {
      for (int i = start.first + 1; i <= end.first - 1; i++) {
        if (grid_->GetCell(start.second, i)->IsOccupied()) {
          return false;
        }
      }
    } else {
      for (int i = end.first + 1; i <= start.first - 1; i++) {
        if (grid_->GetCell(start.second, i)->IsOccupied()) {
          return false;
        }
      }
    }
  }

  return true;
}

void City::AddRoad(std::pair<int, int> start, std::pair<int, int> end) {
  // Check that the road is valid and that it connects two nodes.
  // If not, thwrow an InvalidCityException
  if (IsValidRoad(start, end) && GetNode(start) != nullptr &&
      GetNode(end) != nullptr) {
    auto node1 = GetNode(start);
    auto node2 = GetNode(end);
    roads_.push_back(new Road(start, end, 1));

    // Occupy the cells with the new road
    if (start.first == end.first) {  // vertical

      node1->AddConnection(node2, abs(start.second - end.second));
      node2->AddConnection(node1, abs(start.second - end.second));

      if (start.second < end.second) {
        for (int j = start.second + 1; j <= end.second - 1; j++) {
          grid_->GetCell(start.first, j)->Occupy("Vertical Road");
        }
      } else {
        for (int j = end.second + 1; j <= start.second - 1; j++) {
          grid_->GetCell(start.first, j)->Occupy("Vertical Road");
        }
      }

    } else {  // Horizontal

      node1->AddConnection(node2, abs(start.first - end.first));
      node2->AddConnection(node1, abs(start.first - end.first));

      if (start.first < end.first) {
        for (int i = start.first + 1; i <= end.first - 1; i++) {
          grid_->GetCell(i, start.second)->Occupy("Horizontal Road");
        }
      } else {
        for (int i = end.first + 1; i <= start.first - 1; i++) {
          grid_->GetCell(i, start.second)->Occupy("Horizontal Road");
        }
      }
    }
  } else {
    std::string startX = std::to_string(start.first);
    std::string startY = std::to_string(start.second);
    std::string endX = std::to_string(end.first);
    std::string endY = std::to_string(end.second);
    throw InvalidCityException(("road starting from {" + startX + ", " +
                                startY + "} and ending to {" + endX + ", " +
                                endY + "} is invalid"));
  }
}

bool City::IsValidBuilding(Building* b) const {
  if (b->GetLocation().first < 0 || b->GetLocation().second < 0) {
    return false;
  }

  if (b->GetLocation().first >= grid_->GetSizeX() ||
      b->GetLocation().second >= grid_->GetSizeY()) {
    return false;
  }

  if (grid_->GetCell(b->GetLocation().first, b->GetLocation().second)
          ->IsOccupied()) {
    return false;
  }

  return true;
}

void City::AddBuilding(std::string name, std::pair<int, int> location,
                       const std::string& buildingType) {
  Building* b = nullptr;
  std::string lowertype = buildingType;
  // Compare two strings in a case-insensitive manner
  std::transform(lowertype.begin(), lowertype.end(), lowertype.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  // Check the building type and create the corresponding building
  if (lowertype == "industrial") {
    b = new Industrial(name, location, GetNode(location));
  } else if (lowertype == "residential") {
    b = new Residential(name, location, GetNode(location));
  } else if (lowertype == "shop" || lowertype == "gym" ||
             lowertype == "restaurant") {
    b = new Commercial(name, location, buildingType, GetNode(location));
  } else {
    throw InvalidCityException("building type " + lowertype + " is unknown");
  }

  // Check that the cell is not occupied or out of bounds
  if (!IsValidBuilding(b)) {
    delete (b);
    throw InvalidCityException("invalid building location at: {" +
                               std::to_string(location.first) + ", " +
                               std::to_string(location.second) + "}");
  } else {
    buildings_.push_back(b);
    nodes_.push_back(new Node(NodeType::Building, location));
    grid_->GetCell(b->GetLocation().first, b->GetLocation().second)
        ->Occupy(lowertype);
  }
}

Node* City::GetNode(std::pair<int, int> location) const {
  for (auto node : nodes_) {
    if (node->GetLocation() == location) {
      return node;
    }
  }
  return nullptr;
}

std::vector<Node*> City::GetBuildingNodes() const {
  std::vector<Node*> buildingNodes;
  for (auto node : nodes_) {
    if (node->GetType() == NodeType::Building) {
      buildingNodes.push_back(node);
    }
  }
  return buildingNodes;
}

void City::AddPersonAndCar(Person* p) {
  Event* schedule = new Event(p, this->GetBuildingNodes());
  auto i = schedule->CreateSchedule();
  // Initialize schedule and sync them together with person and its car
  Car* car = new Car(p->GetResidence()->GetNodeFrom()); // creates a car for a person starting from home.
  car->SetColor(p->GetPersonType());
  p->BuyCar(car);
  p->InitializeSchedule(i); // initializes for person and its car
  personCarMap_[p] = car;  // Store person and car
  delete schedule;
}

bool City::IsValidIntersection(Intersection* i) const {
  if (i->GetLocation().first < 0 || i->GetLocation().second < 0) {
    return false;
  }

  if (i->GetLocation().first >= grid_->GetSizeX() ||
      i->GetLocation().second >= grid_->GetSizeY()) {
    return false;
  }

  if (grid_->GetCell(i->GetLocation().first, i->GetLocation().second)
          ->IsOccupied()) {
    return false;
  }

  return true;
}

void City::AddIntersection(std::pair<int, int> location) {
  Intersection* i = new Intersection(location);
  if (IsValidIntersection(i)) {
    intersections_.push_back(i);
    nodes_.push_back(new Node(NodeType::Intersection, location));
    grid_->GetCell(location.first, location.second)->Occupy("Intersection");
  } else {
    delete(i);
    throw InvalidCityException("invalid intersection location at: {" +
                               std::to_string(location.first) + ", " +
                               std::to_string(location.second) + "}");
  }
}

Intersection* City::GetIntersection(std::pair<int, int> location) const {
  for (auto it : intersections_) {
    if (it->GetLocation() == location) {
      return it;
    }
  }
  return nullptr;
}

void City::UpdateIntersections(float deltaTime) const {
  for (auto it : intersections_) {
    it->Update(deltaTime);
  }
}

void City::DrawIntersections(sf::RenderWindow& window) const {
  for (auto it : intersections_) {
    it->Draw(window, 50, grid_);
  }
}

void City::AddTrafficLight(TrafficLight* t) {
  auto intersection = GetIntersection(t->GetLocation());
  if (intersection != nullptr) {
    trafficLights_.push_back(t);
    intersection->AddTrafficLight(t);
  } else {
    throw InvalidCityException("invalid traffic light location at: {" +
                               std::to_string(t->GetLocation().first) + ", " +
                               std::to_string(t->GetLocation().second) +
                               "}, no intersection in the given location");
  }
}

// Update location of person and its car.
void City::UpdateCars(float deltaTime, float currentTime) {
  // Extract cars from personCarMap_
  std::vector<Car*> allCars;
  for (const auto& personCar : personCarMap_) {
    allCars.push_back(personCar.second);
  }

  // Update each car
  for (const auto& personCar : personCarMap_) {
    AddEvent(personCar.first);
    personCar.second->Update(deltaTime, currentTime, nodes_, intersections_,
                             allCars, roads_);
    personCar.first->UpdateLocationFromCar(personCar.second->GetLocation());
  }
}

void City::DrawCars(sf::RenderWindow& window) const {
  for (const auto& personCar : personCarMap_) {
    personCar.second->Draw(window, 50);
  }
}

void City::DrawBuildings(sf::RenderWindow& window) const {
  for (const auto building : buildings_) {
    building->Draw(window, 50);
  }
}

void City::PrintCity(sf::RenderWindow& window) const {
  const int cellSize = 50;
  for (int i = 0; i < grid_->GetSizeX(); i++) {
    for (int j = 0; j < grid_->GetSizeY(); j++) {
      grid_->GetCell(i, j)->Draw(window, cellSize, i, j);
    }
  }
}

Grid* City::GetGrid() const { return grid_; }

std::vector<Road*> City::GetRoads() const { return roads_; }

std::vector<Car*> City::GetCars() const {
  std::vector<Car*> cars;
  for (const auto& personCar : personCarMap_) {
    cars.push_back(personCar.second);
  }
  return cars;
}

int City::TimeUntilNextEvent(Person *p) const { //uusi
        int currentTime = round(clock_->GetElapsedTime());
        auto schedule = p->GetSchedule();
        auto it = schedule.upper_bound(currentTime);

        if (it != schedule.end()) {
                //Next key that is greater than the current time
                int nextEventTime = it->first;
                return nextEventTime - currentTime;
        } else {
                return -1; //If no future events
        }
}

//If there's enough time, person will return home to take a rest.
bool City::IsBusy(Person *p) const {
        return (this->TimeUntilNextEvent(p) < 40 || this->TimeUntilNextEvent(p) == -1); 
}

//Add clock from simulator.cpp
void City::AddClock(SimulationClock* clock) {
        clock_ = clock;
}

//Add event to schedule
void City::AddEvent(Person *p) {
  if (!IsBusy(p) && (p->GetLocation() != p->GetResidence()->GetLocation())) {
      p->AddEvent(clock_->GetElapsedTime(), p->GetResidence()->GetNodeFrom());
  }
}


