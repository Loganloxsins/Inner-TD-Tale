
#include "include/map/grid.h"

Grid::Grid()
    : x(0), y(0), state(0), next_move(0), looks(nullptr), planted(0) {
    ;
}

Grid::Grid(const Grid &c)
    : row(c.row), col(c.col), state(c.state), next_move(c.next_move),
      looks(c.looks), planted(c.planted) {
    ;
}

Grid::Grid(int x, int y, int s, int d)
    : row(x), col(y), state(s), next_move(d), planted(0) {
    // 根据状态 设置单元格的图片
    switch (state) {
    case WALL: // 0墙
        looks = new QPixmap("../source/empty.png");
        break;
    case PATH: // 1敌人路径
        looks = new QPixmap("../source/treez.png");
        break;
    case BEGIN: // 2起点
        looks = new QPixmap("../source/monster-door.png");
        break;
    case END: // 3终点
        looks = new QPixmap("../source/tower.png");
        break;
    case REMOTE: // 4我方远程
        looks = new QPixmap("../source/remote_path.png");
        break;
    case FLY_PATH: // 5飞行路径
        looks = new QPixmap("../source/fly-path.png");
        break;
    }
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

void Grid::setMovie(QString path) {

}

QRectF Grid::boundingRect() const {
    return nullptr;
}
