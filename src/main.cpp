#include <iostream>

#include "city.hpp"
#include "simulator.hpp"

int main() {
  Simulator simulator;
  simulator.StartSimulation();
  simulator.SimulatorThread();
  return 0;
}
