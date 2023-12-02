#include "simulator.hpp"

Simulator::Simulator(int simulationTime)
    : simulationTime(simulationTime) {
}

void Simulator::InitializeSimulation() {
    // initialize simulation state
    std::cout << "Initializing simulation..." << std::endl;
    // logic here
}

void Simulator::UpdateSimulation() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // short delay simulation
    // logic here
}

void Simulator::RenderSimulation() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // short delay simulation
}

void Simulator::StartSimulation() {
    InitializeSimulation();

    for (int timeStep = 0; timeStep < simulationTime; ++timeStep) {
        UpdateSimulation();
        RenderSimulation();
    }

    // assuming that simulation completes with a time duration set by the user, not needed though
    std::cout << "Simulation complete." << std::endl;
}