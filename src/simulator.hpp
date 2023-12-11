#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

#include "../libs/cpp-json/json.h"
#include "analysis.hpp"
#include "car.hpp"
#include "city.hpp"
#include "simulationClock.hpp"
#include "visualization.hpp"

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

  City* LoadCity();
  void InputThread(std::shared_future<void> exitFuture);

  void SetCity(City* c) { c_ = c; }

 private:
  bool isPaused_;
  bool guiEnabled_;
  bool endSimulation_;
  int simulationSpeed_;  // 1x, 2x, 4x, etc.

  City* c_;
  SimulationClock* clock_;
  Analysis* analysis_;

  std::promise<void> exitSignal;  // Declare exitSignal as a member variable
};

#endif