#include "unit/boar.h"
#include "utils/enemy_state.h"
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <vector>
Boar::Boar(int hp, int speed, std::vector<std::pair<int, int>> path, Map *map) {
    _hp_full = hp;
    _hp_cur = hp;
    _speed = speed;
    _path = path;
    _path_index = 0;
    _state = EnemyState::MOVING;
    _map = map;

    _pic_path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\monster1.png)";

    _x = _path[_path_index].first;
    _y = _path[_path_index].second;
}

void Boar::move() {
    // if (_state == EnemyState::MOVING) {
    //     if (_path_index < _path.size() - 1) {
    //         _path_index++;
    //         _x = _path[_path_index].first;
    //         _y = _path[_path_index].second;
    //     } else {
    //         _state = EnemyState::ARRIVED;
    //     }
    // }
    // 为什么在debug状态生成的敌人却是连续的，打印所有敌人位置信息，可能qt调试器的问题

    if (_state == EnemyState::MOVING) {
        if (_path_index < _path.size() - 1) {
            // 检查下一格是否有近战塔
            int x_next = _path[_path_index + 1].first;
            int y_next = _path[_path_index + 1].second;

            bool isPlanted = _map->_all_grids[x_next][y_next]->isplanted;
            
            //打印格子位置和是否有近战塔
            qDebug() << "Next grid: " << x_next << " " << y_next<< " " << isPlanted;


            if (isPlanted) {
                qDebug() << "Boar is attacking!";
                _state = EnemyState::ATTACKING;
                return;
            } else {
                _path_index++;
                _x = x_next;
                _y = y_next;
                qDebug() << "Boar is moving!";
            }
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
