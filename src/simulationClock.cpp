#include "simulationClock.hpp"

SimulationClock::SimulationClock() {}

void SimulationClock::Start() {
  startTime_ = std::chrono::high_resolution_clock::now();
}

double SimulationClock::GetElapsedTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startTime_);
    return elapsedTime.count();
}