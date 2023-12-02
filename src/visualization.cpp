#include "visualization.hpp"


void Visualization::PrintGrid(Grid* grid){
    for (int i = 0; i < grid->GetSizeX(); i++) {
        for (int j = 0; j < grid->GetSizeY(); j++) {
           grid->GetCell(i, j)->Draw(window_, cellSize_, i, j);
        }
    }
}