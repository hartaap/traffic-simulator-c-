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
#include "visualization.hpp"
#include <future>
#include "simulationClock.hpp"
#include "analysis.hpp"

class Simulator {
 public:
  Simulator();
  ~Simulator();

  void ResumeSimulation();
  void PauseSimulation();
  void EndSimulation();
  void SpeedUpSimulation();
  void SlowDownSimulation();
  void StartSimulation();
  void SimulatorThread();

  void UpdateSimulation(float deltaTime, float currentTime);
  void DrawSimulation(Visualization* gui);

  City LoadFile();
  void InputThread(std::promise<void> exitSignal);

  void SetCity(City* c) { c_ = c; }

 private:
  bool isPaused_;
  bool guiEnabled_;
  int simulationSpeed_;  // 1x, 2x, 4x, etc.

  City* c_;
  SimulationClock* clock_;
  Analysis* analysis_;
};

#endif