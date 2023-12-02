#include "simulator.hpp"

Simulator::Simulator(int simulationTime)
    : simulationTime(simulationTime), isPaused(false), simulationSpeed(1) {
}

Simulator::~Simulator() {
}

void Simulator::InitializeSimulation() {
    std::cout << "Initializing simulation..." << std::endl;
    // logic here
}

void Simulator::UpdateSimulation() {
    // logic here
}

void Simulator::DrawSimulation() {
    // logic here
}

void Simulator::SimulatorThread() {
    for (int timeStep = 0; timeStep < simulationTime && !isPaused; ++timeStep) {
        UpdateSimulation();
        DrawSimulation();
        std::this_thread::sleep_for(std::chrono::milliseconds(500 / simulationSpeed)); // delay based on speed
    }

    // have to think about when the simulation completes! now just according to user's input
    std::cout << "Simulation complete." << std::endl;
}

void Simulator::ResumeSimulation() {
    isPaused = false;
    std::cout << "Simulation resumed." << std::endl;
}

void Simulator::PauseSimulation() {
    isPaused = true;
    std::cout << "Simulation paused." << std::endl;
}

void Simulator::EndSimulation() {
    // logic here
    std::cout << "Simulation ended." << std::endl;
}

void Simulator::SpeedUpSimulation() {
    // currently just arbitrary coefficient of 2
    simulationSpeed *= 2;
    std::cout << "Simulation speed increased. Current speed: " << simulationSpeed << "x" << std::endl;
}

void Simulator::SlowDownSimulation() {
    // currently just arbitrary coefficient of 2
    simulationSpeed /= 2;
    std::cout << "Simulation speed decreased. Current speed: " << simulationSpeed << "x" << std::endl;
}

void Simulator::LoadFile() {
    // logic here
    std::cout << "Loading simulation file..." << std::endl;
}

void Simulator::UserInput() {
    std::cout << "Waiting for user input..." << std::endl;
    // logic here
}