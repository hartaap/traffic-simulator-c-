#include "simulator.hpp"

Simulator::Simulator()
    : isPaused_(false), guiEnabled_(true), simulationSpeed_(1) {}

Simulator::~Simulator() { delete c_; }

void Simulator::UpdateSimulation(float deltaTime, float currentTime) {
  c_->UpdateCars(deltaTime, currentTime);
}

void Simulator::DrawSimulation(Visualization* gui) {
  sf::Event event;
  while (gui->GetWindow().pollEvent(event)) {
    if (event.type == sf::Event::Closed) gui->GetWindow().setVisible(false);
  }

  gui->GetWindow().clear();

  // Draw the city and the cars
  c_->PrintCity(gui->GetWindow());
  c_->DrawCars(gui->GetWindow());

  gui->GetWindow().display();
}

void Simulator::StartSimulation() {
  std::cout << "Starting simulation..." << std::endl;
  City* c = new City(LoadFile());

  if (c == nullptr) {
    std::cerr << "Error: Failed to load City. Simulation cannot start."
              << std::endl;
    exit(1);
  }

  SetCity(c);
}

void Simulator::SimulatorThread() {
  Visualization* gui = new Visualization(50);
  sf::Clock clock;

  float previousTime = 0.0;

  // Main loop
  while (true) {
    float currentTime = clock.getElapsedTime().asSeconds();
    float deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    std::cout << "Delta time: " << deltaTime << std::endl;
    std::cout << "Total time: " << currentTime << std::endl;
    
    UpdateSimulation(deltaTime, currentTime);

    if (guiEnabled_) {
      DrawSimulation(gui);
    }
  }
  std::cout << "Simulation complete." << std::endl;
}

void Simulator::ResumeSimulation() {
  isPaused_ = false;
  std::cout << "Simulation resumed." << std::endl;
}

void Simulator::PauseSimulation() {
  isPaused_ = true;
  std::cout << "Simulation paused." << std::endl;
}

void Simulator::EndSimulation() {
  // logic here
  std::cout << "Simulation ended." << std::endl;
}

void Simulator::SpeedUpSimulation() {
  // currently just arbitrary coefficient of 2
  simulationSpeed_ *= 2;
  std::cout << "Simulation speed increased. Current speed: " << simulationSpeed_
            << "x" << std::endl;
}

void Simulator::SlowDownSimulation() {
  // currently just arbitrary coefficient of 2
  simulationSpeed_ /= 2;
  std::cout << "Simulation speed decreased. Current speed: " << simulationSpeed_
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
  std::vector<Car*> cars;
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
    cars.push_back(new Car(carX, carY, c.GetNode({carPosX, carPosY})));
  }

  // Extract events
  int i = 0;
  auto eventsArray = json::as_array(jsonData["events"]);
  for (const auto& events : eventsArray) {
    for (const auto& event : events.as_array()) {
      int eventTime = json::to_number<int>(event[0]);
      auto eventPositionArray = json::as_array(event[1]);
      int eventX = json::to_number<float>(eventPositionArray[0]);
      int eventY = json::to_number<float>(eventPositionArray[1]);
      cars[i]->AddEvent(eventTime, c.GetNode({eventX, eventY}));
    }
    i++;
  }

  // add cars into city
  for (auto car : cars) {
    c.AddCar(car);
  }

  auto trafficLightsArray = json::as_array(jsonData["trafficLights"]);
  for (const auto& trafficLight : trafficLightsArray) {
    auto trafficLightPosArray = json::as_array(trafficLight[0]);
    int posX = json::to_number<int>(trafficLightPosArray[0]);
    int posY = json::to_number<int>(trafficLightPosArray[1]);
    int redDuration = json::to_number<int>(trafficLight[1]);
    int yellowDuration = json::to_number<int>(trafficLight[2]);
    int greenDuration = json::to_number<int>(trafficLight[3]);

    c.AddTrafficLight(new TrafficLight({posX, posY}, redDuration,
                                       yellowDuration, greenDuration));
  }

  // close file
  file.close();

  return c;
}

void Simulator::UserInput() {
  std::cout << "Waiting for user input..." << std::endl;
  // logic here
}