#ifndef GRID_H
#define GRID_H

#include <QGraphicsItem>
#include <QMovie>
#include <QPainter>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/utils/grid_type.h"
// #include "unit/base_tower.h"

using namespace std;

// 地图配置文件
const string map_file = "../map_config_default.txt";
const double PI = 3.14;
const int GRID_SIZE = 100;

class Tower;
class Grid : public QGraphicsItem {
  public:
    // 绘制相关
    int x, y; // 横 纵
    bool isHighlighted = false;
    QPixmap *looks; // 格子的图片
    QMovie *movie = nullptr;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QRectF boundingRect() const override;

    bool contains(const QPoint &point) {
        QRect rect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
        return rect.contains(point);
    };

    void highlight() { isHighlighted = !isHighlighted; };

    // 逻辑相关
    GridType type;           // 格子类型
    bool isplanted;          // 是否种植塔 只有PATH和REMOTE才有意义
    Tower *_tower = nullptr; // 如果种植，种植的塔的指针

    Grid();

    Grid(const Grid &c);

    Grid(int x, int y, GridType type, bool isplanted);
};

#endif // GRID_H
