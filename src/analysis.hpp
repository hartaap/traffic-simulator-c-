#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <string>
#include <vector>
#include "city.hpp"
#include "simulationClock.hpp"
#include <algorithm> 
#include <iostream> 

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

    // Analyze multiple roads: if we have enough time this should be implemented
    void AnalyzeMultipleRoads(const std::vector<std::string>& roadIDs);

    // Average over multiple days to get more reliable results: same for this as above
    void AverageOverDays(int numDays);

    // Find and highlight congestion automatically: this is an advanced feature, quite sure that going to skip
    void FindAndHighlightCongestion();

    std::string Print();

    std::vector<std::vector<int>> GetData();

    void Init();
private:
    // Current road that is being analyzed
    Road* currentRoad_;

    // key tells the day, values tell the hourly data
    std::vector<std::vector<int>> roadHourlyCounts_;

    City* city_;
    SimulationClock* clock_;
    std::map<int, bool> previousCars_;
};

#endif  // ANALYSIS_HPP