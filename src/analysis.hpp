#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <string>
#include <vector>
#include "city.hpp"

class Analysis {
public:
    Analysis();

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
    

};

#endif  // ANALYSIS_HPP