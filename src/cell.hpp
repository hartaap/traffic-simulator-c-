#ifndef CELL_H
#define CELL_H

#include <string>
#include <SFML/Graphics.hpp>

class Cell {
public:

    Cell(std::pair<int, int> location): type_("Empty"), location_(location){}
    
    bool IsOccupied() const;

    void Occupy(std::string type);

    void Clear();

    std::string GetType();

    int GetX(){
        return location_.first;
    }

    int GetY(){
        return location_.second;
    }

    void Draw(sf::RenderWindow& window, int cellSize, int x, int y);

private:

   std::string type_;
   std::pair<int, int> location_;
    
};


#endif 