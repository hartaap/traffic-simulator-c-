#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class SimulationClock {
public:
    SimulationClock();

    // Start the clock
    void Start();

    // Stop the clock
    void Stop();

    // Get the elapsed time in seconds
    double GetElapsedTime() const;

private:
    bool isRunning_;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopTime_;
};

#endif  // CLOCK_HPP