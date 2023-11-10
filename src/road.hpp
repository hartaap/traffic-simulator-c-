#ifndef ROAD_H
#define ROAD_H

#include "grid.hpp"


class Road{

    public:

    Road(std::pair<int, int> start, std::pair<int, int> end, int speedLimit): start_(start), end_(end), speedLimit_(speedLimit){}

    std::pair<int, int> GetEnd() const {
        return end_;
    }

    std::pair<int, int> GetStart() const {
        return start_;
    }

    int GetSpeedLimit() const {
        return speedLimit_;
    }

    bool IsVertical() const;

    bool IsHorizontal() const;




    private:

    const std::pair<int, int> start_;
    const std::pair<int, int> end_;
    int speedLimit_;



};


#endif