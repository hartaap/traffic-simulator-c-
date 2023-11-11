#include "grid.hpp"


Grid::Grid(int xSize, int ySize){

    xSize_ = xSize;
    ySize_ = ySize;
    
    for(int j = 0; j < ySize; j++){
        std::vector<Cell*> row;
        for(int i = 0; i < xSize; i++){
            row.push_back(new Cell());
        }
        cells_.push_back(row);
    }
}


Grid::~Grid(){

    for(int i = 0; i < xSize_; i++){
        for(int j = 0; j < ySize_; j++){
            delete(cells_[i][j]);
        }
    }
}


int Grid::GetSizeX() const {
    return xSize_;
}


int Grid::GetSizeY() const {
    return ySize_;
}


Cell* Grid::GetCell(int x, int y) {
return cells_[y][x];
}
