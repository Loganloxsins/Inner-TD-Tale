#include "unit/boar.h"
#include "utils/enemy_state.h"
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <vector>
Boar::Boar(int hp, int speed, std::vector<std::pair<int, int>> path, Map *map) {
    // _tower_all = tower_all;
    _hp_full = hp;
    _hp_cur = hp;
    _speed = speed;
    _path = path;
    _path_index = 0;
    _state = EnemyState::MOVING;
    _map = map;
    _attackSpeed = 2; // 攻击频率
    _attackCoolDown = 0;
    _attackRange = 1;
    _damage = 10;

    // _target_tower = nullptr;

    _pic_path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\food1.png)";

    _x = _path[_path_index].first;
    _y = _path[_path_index].second;
}

void Boar::move() {

    // 注意：所有地图数据都是以 row col 的形式存储的

    if (_state == EnemyState::MOVING) {
        if (_path_index < _path.size() - 1) {
            // 检查下一格是否有近战塔
            int x_next = _path[_path_index + 1].first;
            int y_next = _path[_path_index + 1].second;

            bool isPlanted = _map->_all_grids[y_next][x_next]->isplanted;

            // // 打印格子位置和是否有近战塔
            // qDebug() << "Next grid: " << x_next << " " << y_next << " "
            //          << isPlanted;

            if (isPlanted) {
                _state = EnemyState::ATTACKING;
                return;
            } else {
                _path_index++;
                _x = x_next;
                _y = y_next;
                // qDebug() << "Boar is moving!";
            }
        } else {
            _state = EnemyState::ARRIVED;
        }
    }
}

// 攻击函数，需要结合_attackSpeed攻击频率
void Boar::attack() {
    // 塔在下一格
    int x_next = _path[_path_index + 1].first;
    int y_next = _path[_path_index + 1].second;

    // 找到下一格的塔
    Tower *tower = _map->_all_grids[y_next][x_next]->_tower;

    _attackCoolDown++;
    if (_attackCoolDown < _attackSpeed) {
        return;
    } else {
        _attackCoolDown = 0;
        // 如果塔还活着
        if (tower) {
            tower->_hp_cur -= _damage;
            // qDebug() << "Boar is attacking!";
            if (tower->_hp_cur <= 0) {
                _state = EnemyState::MOVING;
                _path_index++;
                _x = x_next;
                _y = y_next;
            }
        } else {
            _state = EnemyState::MOVING;
        }
    }
}

void Boar::draw(QPainter *painter) {
    QPixmap pixmap(_pic_path);
    drawSelectionBox(painter);
    drawBloodBar(painter);
    painter->drawPixmap(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60, pixmap);
}
