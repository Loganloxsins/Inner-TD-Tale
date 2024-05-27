
#include "include/map/grid.h"
#include <QMouseEvent>
Grid::Grid() {
    x = 0;
    y = 0;
    type = GridType::WALL;
    isplanted = false;
    looks = new QPixmap("../../assets/wall.png");
}

Grid::Grid(const Grid &c) {
    x = c.x;
    y = c.y;
    type = c.type;
    isplanted = c.isplanted;
    looks = c.looks;
    movie = c.movie;
}

Grid::Grid(int x, int y, GridType type, bool isplanted)
    : x(x), y(y), type(type), isplanted(isplanted) {
    switch (type) {
    case GridType::WALL:
        looks = new QPixmap("../../assets/wall.png");
        break;
    case GridType::PATH:
        looks = new QPixmap("../../assets/path.png");
        break;
    case GridType::SPAWN:
        looks = new QPixmap("../../assets/spawn.png");
        break;
    case GridType::DEST:
        looks = new QPixmap("../../assets/dest.png");
        break;
    case GridType::REMOTE:
        looks = new QPixmap("../../assets/remote.png");
        break;
    }
}

// 实现QGraphicsItem的纯虚函数
QRectF Grid::boundingRect() const {
    // 返回Grid占据的矩形区域，GRID_SIZE应该是您定义的网格尺寸
    return QRectF(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
    painter->drawPixmap(x * GRID_SIZE, y * GRID_SIZE, *looks);
    if (isHighlighted) {
        painter->setPen(QPen(Qt::red, 3));
        painter->drawRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
    }
}