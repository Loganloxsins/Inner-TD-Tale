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

#include "grid_type.h"
#include "map.h"
#include "path.h"

using namespace std;

// 地图配置文件
const string map_file = "../map_config_default.txt";
const double PI = 3.14;
const int GRID_SIZE = 100;

class Grid : public QGraphicsItem {
public:
    int x, y;       // 横 纵
    GridType type;  // 格子类型
    bool isplanted; // 是否种植塔 只有PATH和REMOTE才有意义

    QPixmap *looks; // 格子的图片
    QMovie *movie = nullptr;

    Grid();

    Grid(const Grid &c);

    Grid(int x, int y, int s, int d);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QRectF boundingRect() const override;

    void setMovie(QString path);
};

#endif // GRID_H