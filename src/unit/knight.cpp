#include "unit/knight.h"
#include "unit/base_tower.h"

Knight::Knight(int x, int y, vector<Enemy *> &enemies) : _enemies(enemies) {
    int hp = 100;
    _hp_full = hp;
    _hp_cur = hp;
    _attackRange = 1;
    _gridType = GridType::PATH;
    _x = x;
    _y = y;
    _state = TowerState::IDLE;
    _damage = 3;
    _attackSpeed = 1;
    _attackCoolDown = 0;
    _target_enemy = nullptr;

    _pic_path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\player2.png)";
}

void Knight::draw(QPainter *painter) {
    QPixmap pixmap(_pic_path);
    drawSelectionBox(painter);
    drawBloodBar(painter);
    painter->drawPixmap(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60, pixmap);
}

void Knight::idle() {
    // 检查周围是否有敌人,近战攻击范围为1
    for (auto enemy : _enemies) {
        if (abs(enemy->_x - _x) + abs(enemy->_y - _y) <= _attackRange &&
            enemy->_state != EnemyState::DEAD) {
            _state = TowerState::ATTACKING;
            _target_enemy = enemy;
            break;
        }
    }
}

void Knight::attack() {
    if (_attackCoolDown < _attackSpeed) {
        _attackCoolDown++;
    } else {
        _attackCoolDown = 0;
        _target_enemy->_hp_cur -= _damage;
        if (_target_enemy->_hp_cur <= 0) {
            _target_enemy->_state = EnemyState::DEAD;
            _state = TowerState::IDLE;
        }
    }
}