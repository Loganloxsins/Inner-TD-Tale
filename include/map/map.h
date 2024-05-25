#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

#include "include/map/grid.h"

class Map {
  private:
    std::vector<std::vector<Grid>> _all_grids;
    std::vector<std::vector<int>> _gridMatrix;
    std::vector<std::vector<std::pair<int, int>>> _monsterPaths;

  public:
    // 构造函数
    Map();

    bool loadMap(const QString &filePath);

    void drawMap(QPainter *painter);
};

#endif // MAP_H