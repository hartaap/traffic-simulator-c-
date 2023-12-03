#include "simulator.hpp"

Simulator::Simulator() : isPaused(false), simulationSpeed(1) {}

Simulator::~Simulator() {}

void Simulator::UpdateSimulation() {
  // City::UpdateCars();
}

void Simulator::DrawSimulation() {
  // logic here
}

City Simulator::StartSimulation() {
  std::cout << "Starting simulation..." << std::endl;
  City c = LoadFile();
  return c;
}

void Simulator::SimulatorThread() {
  // need to change
  for (int timeStep = 0; timeStep < 1000 && !isPaused; ++timeStep) {
    UpdateSimulation();
    DrawSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(
        500 / simulationSpeed));  // delay based on speed
  }

  // have to think about when the simulation completes! now just according to
  // user's input
  std::cout << "Simulation complete." << std::endl;
}

void Simulator::ResumeSimulation() {
  isPaused = false;
  std::cout << "Simulation resumed." << std::endl;
}

void Simulator::PauseSimulation() {
  isPaused = true;
  std::cout << "Simulation paused." << std::endl;
}

void Simulator::EndSimulation() {
  // logic here
  std::cout << "Simulation ended." << std::endl;
}

void Simulator::SpeedUpSimulation() {
  // currently just arbitrary coefficient of 2
  simulationSpeed *= 2;
  std::cout << "Simulation speed increased. Current speed: " << simulationSpeed
            << "x" << std::endl;
}

void Simulator::SlowDownSimulation() {
  // currently just arbitrary coefficient of 2
  simulationSpeed /= 2;
  std::cout << "Simulation speed decreased. Current speed: " << simulationSpeed
            << "x" << std::endl;
}

City Simulator::LoadFile() {
  // logic here
  std::string filename;
  std::cout << "Please enter JSON file name:" << std::endl;
  std::cin >> filename;
  std::ifstream file("src/" + filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
  }

  // Load the file into a string
  std::string contents = std::string{std::istreambuf_iterator<char>(file),
                                     std::istreambuf_iterator<char>()};

  // Parse the JSON using cpp-json
  json::value jsonData = json::parse(contents);

  // Extract data from the JSON and use it to initialize the simulator
  int x = json::to_number<int>(jsonData["x"]);
  int y = json::to_number<int>(jsonData["y"]);

  // init to max 5 cars for now; using 1 car right now
  Car* cars[5];
  City c(x, y);

  // Extract buildings
  auto buildingsArray = json::as_array(jsonData["buildings"]);
  for (const auto& building : buildingsArray) {
    auto buildingObject = json::as_object(building);

    if (!buildingObject.empty()) {
      // Assuming there's only one key in the building object
      std::string name = buildingObject.begin()->first;
      auto buildingData = json::as_array(buildingObject.begin()->second);

      std::string buildingType = buildingData[0].as_string();
      auto positionArray = json::as_array(buildingData[1]);

      int buildingX = json::to_number<int>(positionArray[0]);
      int buildingY = json::to_number<int>(positionArray[1]);

      c.AddBuilding(name, {buildingX, buildingY}, buildingType);
    } else {
      std::cerr << "Invalid building object in the array." << std::endl;
    }
  }

  // Extract intersections
  auto intersectionsArray = json::as_array(jsonData["intersections"]);
  for (const auto& intersection : intersectionsArray) {
    int intersectionX = json::to_number<int>(intersection[0]);
    int intersectionY = json::to_number<int>(intersection[1]);
    c.AddIntersection({intersectionX, intersectionY});
  }

  // Extract roads
  auto roadsArray = json::as_array(jsonData["roads"]);
  for (const auto& road : roadsArray) {
    int start_x = json::to_number<int>(road[0]);
    int start_y = json::to_number<int>(road[1]);
    int end_x = json::to_number<int>(road[2]);
    int end_y = json::to_number<int>(road[3]);
    c.AddRoad({start_x, start_y}, {end_x, end_y});
  }

  // Extract cars
  auto carsArray = json::as_array(jsonData["cars"]);
  for (const auto& car : carsArray) {
    float carX = json::to_number<float>(car[0]);
    float carY = json::to_number<float>(car[1]);
    auto carPositionArray = json::as_array(car[2]);
    int carPosX = json::to_number<int>(carPositionArray[0]);
    int carPosY = json::to_number<int>(carPositionArray[1]);
    // cars[0] since only one car used in testing now
    cars[0] = new Car(carX, carY, c.GetNode({carPosX, carPosY}));
  }

  // Extract events
  auto eventsArray = json::as_array(jsonData["events"]);
  for (const auto& event : eventsArray) {
    int eventTime = json::to_number<int>(event[0]);
    auto eventPositionArray = json::as_array(event[1]);
    int eventX = json::to_number<float>(eventPositionArray[0]);
    int eventY = json::to_number<float>(eventPositionArray[1]);
    // cars[0] since only one car used in testing now
    // how to add events to specific cars?
    cars[0]->AddEvent(eventTime, c.GetNode({eventX, eventY}));
  }

  c.AddCar(cars[0]);

  // close file
  file.close();

  return c;
}

void Simulator::UserInput() {
  std::cout << "Waiting for user input..." << std::endl;
  // logic here
}