#include "road.hpp"


bool Road::IsVertical() const{
    return (GetStart().first == GetEnd().first);
}

bool Road::IsHorizontal() const {
    return (GetStart().second == GetEnd().second);
}

