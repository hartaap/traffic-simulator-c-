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

std::string SimulationClock::GetSimulationTime() {
    // 1 second in real-time equals 1 minute in simulation time
    double elapsedMinutes = GetElapsedTime();

    // Convert elapsed minutes to hours and minutes
    int hours = static_cast<int>(elapsedMinutes) / 60;
    int minutes = static_cast<int>(elapsedMinutes) % 60;

    // Format the time as "hours:minutes"
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":"
       << std::setw(2) << std::setfill('0') << minutes;

    return ss.str();
}
