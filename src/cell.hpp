#ifndef CELL_H
#define CELL_H

#include <string>

class Cell {
public:

    Cell(): type_("Empty"){}
    
    bool IsOccupied() const;

    void Occupy(std::string type);

    void Clear();

    std::string GetType() const;

private:

   std::string type_;
    
};


#endif 