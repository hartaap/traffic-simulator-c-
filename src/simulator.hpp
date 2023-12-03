#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

#include "../libs/cpp-json/json.h"
#include "car.hpp"
#include "city.hpp"

class Simulator {
 public:
  Simulator();
  ~Simulator();

  void ResumeSimulation();
  void PauseSimulation();
  void EndSimulation();
  void SpeedUpSimulation();
  void SlowDownSimulation();
  City StartSimulation();

  City LoadFile();
  void UserInput();

 private:
  std::ifstream file;
  bool isPaused;
  int simulationSpeed;  // 1x, 2x, 4x, etc.

  void SimulatorThread();
  void UpdateSimulation();
  void DrawSimulation();
};

#endif