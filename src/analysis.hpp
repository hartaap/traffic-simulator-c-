#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <string>
#include <vector>
#include "city.hpp"
#include "simulationClock.hpp"
#include <algorithm> 
#include <iostream> 
#include <fstream>

class Analysis {
public:
    Analysis(City* city, SimulationClock* clock);

    Analysis();

    // Main function of this class which is going to be run in the main loop
    void Analyze();

    // Specify a road to analyze; using a palikka implementation of roadIndex for now
    void SpecifyRoad(int roadIndex);

    // Histogram of amount of cars on the road in respect to hour of the day
    void GenerateHourlyHistogram(std::vector<std::vector<int>> data);

    // Export the analysis results to a CSV file, could be changed to JSON but for now CSV since easier
    void ExportToCSV(const std::string& filename);

    std::vector<std::vector<int>> GetData();

    void Init();
private:
    // Current road that is being analyzed
    Road* currentRoad_;

    // first element tells the day, second element tells the hour
    std::vector<std::vector<int>> roadHourlyCounts_;

    City* city_;
    SimulationClock* clock_;
    std::map<int, bool> previousCars_;
};

#endif  // ANALYSIS_HPP