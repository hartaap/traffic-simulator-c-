#include "road.hpp"



void Road::MakeVertical(Grid* grid, int x, int yStart, int yEnd){

    for(int j = yStart; j <= yEnd; j++){
        grid->GetCell(j, x)->Occupy("Road");
    }

}


void Road::MakeHorizontal(Grid* grid, int y, int xStart, int xEnd){

    for(int i = xStart; i <= xEnd; i++){
        grid->GetCell(y, i)->Occupy("Road");
    }
    

}