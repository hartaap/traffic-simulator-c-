#include "cell.hpp"




bool Cell::IsOccupied() const {

    return (type_ != "Empty");
}


void Cell::Occupy(std::string type) {

    type_ = type;;
}


void Cell::Clear() {

    type_ = "Empty";
}


std::string Cell::GetType() const {

    return type_;
}