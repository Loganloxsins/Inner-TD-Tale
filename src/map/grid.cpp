
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
        looks = new QPixmap("../../assets/TownTree.png");
        break;
    case GridType::PATH:
        looks = new QPixmap("../../assets/box1.png");
        break;
    case GridType::SPAWN:
        looks = new QPixmap("../../assets/redhouse.png");
        break;
    case GridType::DEST:
        looks = new QPixmap("../../assets/bluehouse.png");
        break;
    case GridType::REMOTE:
        looks = new QPixmap("../../assets/TownBlockRed.png");
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
    // 保存当前的 painter 状态
    painter->save();

    // 绘制网格的外观
    painter->drawPixmap(x * GRID_SIZE, y * GRID_SIZE, *looks);

    // 如果网格被高亮显示，绘制红色的边框
    if (isHighlighted) {
        painter->setPen(QPen(Qt::red, 3));
        painter->drawRect(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE);
    }

    // 恢复到之前保存的状态
    painter->restore();
}