#include "simulationClock.hpp"

SimulationClock::SimulationClock() : isRunning_(false) {}

void SimulationClock::Start() {
    if (!isRunning_) {
        startTime_ = std::chrono::high_resolution_clock::now();
        isRunning_ = true;
    }
}

void SimulationClock::Stop() {
    if (isRunning_) {
        stopTime_ = std::chrono::high_resolution_clock::now();
        isRunning_ = false;
    }
}

double SimulationClock::GetElapsedTime() const {
    if (isRunning_) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(currentTime - startTime_).count();
    } else {
        return std::chrono::duration<double>(stopTime_ - startTime_).count();
    }
}