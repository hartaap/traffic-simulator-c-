#ifndef GRID_H
#define GRID_H

#include "cell.hpp"
#include <vector>


class Grid {
public:
    Grid(int xSize, int ySize);

    ~Grid();

    Cell* GetCell(int x, int y);

    int GetSizeX() const;

    int GetSizeY() const;

private:
    int xSize_;
    int ySize_;
    std::vector<std::vector<Cell*>> cells_;
};



#endif
