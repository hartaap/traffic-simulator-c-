#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <chrono>
#include <thread>
#include "../libs/cpp-json/json.h"
#include "city.hpp"
#include "car.hpp"

class Simulator {
public:
    Simulator(int simulationTime);
    ~Simulator();

    void SimulatorThread();
    void ResumeSimulation();
    void PauseSimulation();
    void EndSimulation();
    void SpeedUpSimulation();
    void SlowDownSimulation();

    void LoadFile();
    void UserInput();

private:
    std::ifstream file;
    int simulationTime;
    bool isPaused;
    int simulationSpeed; // 1x, 2x, 4x, etc.

    void InitializeSimulation(const json::value& jsonData);
    void UpdateSimulation();
    void DrawSimulation();
};

#endif