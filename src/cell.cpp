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


std::string Cell::GetType()  {

    return type_;
}

void Cell::Draw(sf::RenderWindow& window, int cellSize, int x, int y){

    sf::RectangleShape cellShape(sf::Vector2f(cellSize,cellSize));

    sf::Color Gray(50, 50, 50);

    if(type_ == "Horizontal Road"){
        cellShape.setFillColor(Gray);
        sf::RectangleShape dot(sf::Vector2f(cellSize / 2.0f, 2.0f));
        dot.setFillColor(sf::Color::White);
        dot.setPosition(y*cellSize, x*cellSize + cellSize/2.0f);
        cellShape.setPosition(y *cellSize, x * cellSize); 
        window.draw(cellShape);
        window.draw(dot);

    }else if(type_ == "Vertical Road"){
        cellShape.setFillColor(Gray);
        sf::RectangleShape dot(sf::Vector2f(2.0f, cellSize / 2.0f));
        dot.setFillColor(sf::Color::White);
        dot.setPosition(y*cellSize + cellSize/2.0f, x*cellSize);
        cellShape.setPosition(y *cellSize, x * cellSize); 
        window.draw(cellShape);
        window.draw(dot);

    }else if(type_ == "Building"){
        cellShape.setFillColor(sf::Color::Blue);
        cellShape.setPosition(y *cellSize, x * cellSize); 
        window.draw(cellShape);
    }else if(type_ == "Intersection"){
    cellShape.setFillColor(Gray);
    cellShape.setPosition(y*cellSize, x*cellSize);
    window.draw(cellShape);
    
    }else {
        cellShape.setFillColor(sf::Color::White);
        cellShape.setPosition(y *cellSize, x * cellSize); 
        window.draw(cellShape);
    }
}