#include <stdlib.h>

class Road {
public:
    Road(const int speedLimit, const std::pair<int, int> start, const std::pair<int, int> end) :
            speedLimit_(speedLimit), start_(start), end_(end) {}

    // const std::pair<Lane*, Lane*> GetLanes() const {
    //      return lanes_;
    // }

    const int GetSpeedLimit() const {
        return speedLimit_;
    }

    const std::pair<int, int> GetStart() const {
        return start_;
    }

    const std::pair<int, int> GetEnd() const {
        return end_;
    }

private:
    // std::pair<Lane*, Lane*> lanes_;
    int speedLimit_;
    const std::pair<int, int> start_;
    const std::pair<int, int> end_; 
};