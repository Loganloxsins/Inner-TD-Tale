#include "unit/enemy/boar.h"
#include "utils/enemy_state.h"
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <vector>
Boar::Boar(int hp, int speed, std::vector<std::pair<int, int>> path) {
    _hp_full = hp;
    _hp_cur = hp;
    _speed = speed;
    _path = path;
    _path_index = 0;
    _state = EnemyState::MOVING;

    _pic_path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\monster1.png)";

    _x = _path[_path_index].first;
    _y = _path[_path_index].second;
}

void Boar::move() {
    if (_state == EnemyState::MOVING) {
        if (_path_index < _path.size() - 1) {
            _path_index++;
            _x = _path[_path_index].first;
            _y = _path[_path_index].second;
        } else {
            _state = EnemyState::ARRIVED;
        }
    }
}

void Boar::draw(QPainter *painter) {
    QPixmap pixmap(_pic_path);
    if (_isHighlighted) {
        QPen pen(Qt::yellow);
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawRect(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60);
    }
    painter->drawPixmap(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60, pixmap);
}