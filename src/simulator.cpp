#include "simulator.hpp"

Simulator::Simulator()
    : isPaused_(false),
      guiEnabled_(true),
      simulationSpeed_(1),
      clock_(new SimulationClock()) {}

Simulator::~Simulator() { delete c_; }

void Simulator::UpdateSimulation(float deltaTime, float currentTime) {
  c_->UpdateCars(deltaTime, currentTime);
  c_->UpdateIntersections(deltaTime);
}

void Simulator::DrawSimulation(Visualization* gui) {
  sf::Event event;
  while (gui->GetWindow().pollEvent(event)) {
    if (event.type == sf::Event::Closed) gui->GetWindow().setVisible(false);
  }

  gui->GetWindow().clear();

  // Draw the city and the cars
  c_->PrintCity(gui->GetWindow());
  c_->DrawIntersections(gui->GetWindow());
  c_->DrawCars(gui->GetWindow());
  c_->DrawBuildings(gui->GetWindow());

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
  Visualization* gui = new Visualization(50, c_->GetGrid());
  analysis_ = new Analysis(c_, clock_);
  analysis_->SpecifyRoad(1);

  float previousTime = 0.0;

  // Start input thread
  std::promise<void> exitSignal;
  auto inputFuture = std::async(std::launch::async, &Simulator::InputThread,
                                this, std::move(exitSignal));
  // Main loop
  clock_->Start();

  while (true) {
    float currentTime = clock_->GetElapsedTime();
    float deltaTime = simulationSpeed_ * (currentTime - previousTime);
    previousTime = currentTime;

    if (!
    isPaused_) {
      UpdateSimulation(deltaTime, currentTime);
      analysis_->Analyze();
    }

    if (guiEnabled_) {
      DrawSimulation(gui);
    }
  }

  // input thread exits
  exitSignal.set_value();

  // input thread finishes
  inputFuture.get();

  // create a finish simulation function

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
  if (simulationSpeed_ <= 8) {
    simulationSpeed_ *= 2;
    std::cout << "Simulation speed increased. Current speed: "
              << simulationSpeed_ << "x" << std::endl;
  } else {
    std::cout << "Can't go faster! 16x is the maximum speed." << std::endl;
  }
}

void Simulator::SlowDownSimulation() {
  // currently just arbitrary coefficient of 2
  simulationSpeed_ /= 2;
  if (simulationSpeed_ == 0) {
    std::cout << "Can't go below 1x speed!" << std::endl;
    simulationSpeed_ = 1;
  } else {
    std::cout << "Simulation speed decreased. Current speed: "
              << simulationSpeed_ << "x" << std::endl;
  }
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
  std::vector<Person*> persons;
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

      try {
        c.AddBuilding(name, {buildingX, buildingY}, buildingType);
      } catch (InvalidCityException& e) {
        std::cout << "Could not load the city from the JSON file." << std::endl;
        std::cout << e.GetError() << std::endl;
        exit(1);
      }
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
    try {
      c.AddRoad({start_x, start_y}, {end_x, end_y});
    } catch (InvalidCityException& e) {
      std::cout << "Could not load the city from the JSON file." << std::endl;
      std::cout << e.GetError() << std::endl;
      exit(1);
    }
  }

   // Extract persons

  auto personsArray = json::as_array(jsonData["persons"]);
  for (const auto& person : personsArray) {

      const std::string name = json::as_string(person[0]);
      const std::string pType = json::as_string(person[1]);
      auto workplaceObject = json::as_object(person[2]);
      auto homeObject = json::as_object(person[3]);

      // Check if these buildings are valid
      if (!workplaceObject.empty() && !homeObject.empty()) {
          std::string workPlaceName = workplaceObject.begin()->first;
          auto workplaceLocation = json::as_array(workplaceObject.begin()->second[1]);
          int workPosX = json::to_number<int>(workplaceLocation[0]);
          int workPosY = json::to_number<int>(workplaceLocation[1]);
          std::string homeName = homeObject.begin()->first;
          auto homeLocation = json::as_array(homeObject.begin()->second[1]);
          int homePosX = json::to_number<int>(homeLocation[0]);
          int homePosY = json::to_number<int>(homeLocation[1]);

          Industrial* a = new Industrial(workPlaceName, {workPosX, workPosY});
          Residential* b = new Residential(homeName, {homePosX, homePosY});
          persons.push_back(new Person(name, pType, a, b, c.GetNode({round(b->GetLocation().first), round(b->GetLocation().second)})));
           // this also creates a car for each person
      } else {
          std::cerr << "Invalid workplace or home!" << std::endl;
      }
      
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
      persons[i]->AddEvent(eventTime, c.GetNode({eventX, eventY}));
    }
    i++;
  }

  // add persons and their linked cars into city
  for (auto person : persons) {
    c.AddPerson(person);
  }

  auto trafficLightsArray = json::as_array(jsonData["trafficLights"]);
  for (const auto& trafficLight : trafficLightsArray) {
    auto trafficLightPosArray = json::as_array(trafficLight[0]);
    int posX = json::to_number<int>(trafficLightPosArray[0]);
    int posY = json::to_number<int>(trafficLightPosArray[1]);
    int redDuration = json::to_number<int>(trafficLight[1]);
    int yellowDuration = json::to_number<int>(trafficLight[2]);
    int greenDuration = json::to_number<int>(trafficLight[3]);

    try {
      c.AddTrafficLight(new TrafficLight({posX, posY}, redDuration,
                                         yellowDuration, greenDuration));
    } catch (InvalidCityException& e) {
      std::cout << "Could not load the city from the JSON file." << std::endl;
      std::cout << e.GetError() << std::endl;
      exit(1);
    }
  }

  // close file
  file.close();

  return c;
}

void Simulator::InputThread(std::promise<void> exitSignal) {
  std::string command;
  while (true) {
    std::cout << "Enter a command (e.g., status, exit, analyze): ";
    std::cin >> command;

    if (command == "exit") {
      EndSimulation();
      // Signal the main thread to exit
      exitSignal.set_value();
      break;
    } else if (command == "status") {
      std::cout << "Day: " << clock_->GetDayNumber() << " | Time is: " << clock_->GetSimulationTime() << std::endl;
    } else if (command == "analyze") {
      std::cout << analysis_->TestPrint() << std::endl;
    } else {
      std::cout << "Invalid command. Try again." << std::endl;
    }
  }
}
