#ifndef CELL_H
#define CELL_H

#include <string>
#include <SFML/Graphics.hpp>

class Cell {
public:

    Cell(): type_("Empty"){}
    
    bool IsOccupied() const;

    void Occupy(std::string type);

    void Clear();

    std::string GetType() const;

    void Draw(sf::RenderWindow& window, int cellSize, int x, int y);

private:

   std::string type_;
    
};


#endif 