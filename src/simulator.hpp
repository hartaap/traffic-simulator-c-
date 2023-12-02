#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

class Simulator {
public:
    Simulator(int simulationTime);
    ~Simulator();

    void StartSimulation();
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

    void InitializeSimulation();
    void UpdateSimulation();
    void RenderSimulation();
};

#endif