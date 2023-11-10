#include <string>
#include <iostream>
#include <vector>
#include "residential.hpp"
#include "industrial.hpp"

class Person {
    public:
    Industrial& GetWorkplace() const {
        return workplace_;
    }
    Residential& GetResidence() const {
        return residence_;
    }
    
    private:
    std::string name_;
    Industrial& workplace_;
    Residential& residence_;
    std::vector<std::pair<int,const Building&>> schedule_;
    std::pair<int,int> location_;
    bool status_;
};