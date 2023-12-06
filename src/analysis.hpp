#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <string>
#include <vector>
#include "simulator.hpp"

class Analysis {
public:
    Analysis(City* city);

    // Specify a road to analyze; where to acquire roadID -> changes to road class or?
    void SpecifyRoad(const std::string& roadID);

    // Histogram of amount of cars on the road in respect to hour of the day
    void GenerateHourlyHistogram();

    // Export the analysis results to a CSV file, could be changed to JSON but for now CSV since easier
    void ExportToCSV(const std::string& filename);

    // Analyze multiple roads: if we have enough time this should be implemented
    void AnalyzeMultipleRoads(const std::vector<std::string>& roadIDs);

    // Average over multiple days to get more reliable results: same for this as above
    void AverageOverDays(int numDays);

    // Find and highlight congestion automatically: this is an advanced feature, quite sure that going to skip
    void FindAndHighlightCongestion();

private:
    // string for now, need to change
    std::string currentRoad_;

    // key tells the day, values tell the hourly data
    std::map<int, std::vector<int>> roadHourlyCounts_;

    City* city_;
};

#endif  // ANALYSIS_HPP