#ifndef MAP_H
#define MAP_H

#include "grid.h"
#include <string>
#include <vector>
class Map {
  private:
    int width, height;
    std::vector<std::vector<Grid>> grids;

  public:
    Map(int width, int height);
    void loadMap(const std::string &filePath);
    void saveMap(const std::string &filePath);
    Grid *getGrid(int x, int y);
};

#endif // MAP_H