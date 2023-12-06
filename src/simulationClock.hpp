#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>

class SimulationClock {
public:
    SimulationClock();

    // Start the clock
    void Start();

    // Get the elapsed time in seconds
    double GetElapsedTime();

    int GetDayNumber();

    std::string GetSimulationTime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
    int dayNumber_;
};

#endif  // CLOCK_HPP