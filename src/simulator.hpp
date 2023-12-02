#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <fstream>
#include <iostream>

class Simulator {

    public:
    Simulator();
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

};


#endif