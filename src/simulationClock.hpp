#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class SimulationClock {
public:
    SimulationClock();

    // Start the clock
    void Start();

    // Get the elapsed time in seconds
    double GetElapsedTime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
};

#endif  // CLOCK_HPP