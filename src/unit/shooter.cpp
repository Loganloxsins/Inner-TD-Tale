#include "unit/Shooter.h"
#include "unit/Boar.h"
Shooter::Shooter(int x, int y, vector<Enemy *> &enemies) : _enemies(enemies) {
    _x = x;
    _y = y;
    int hp = 200;
    _hp_full = hp;
    _hp_cur = hp;
    _gridType = GridType::REMOTE;
    _state = TowerState::IDLE;
    _attackRange = 2;
    _damage = 30;
    _attackSpeed = 1;
    _attackCoolDown = 0;
    _target_enemy = nullptr;
    _buff_num = 0;
    _buffSlot[0] = -1;
    _buffSlot[1] = -1;
    _pic_path = R"(..\..\.\assets\Fighter.png)";
}

void Shooter::draw(QPainter *painter) {
    QPixmap pixmap(_pic_path);
    drawSelectionBox(painter);
    drawBloodBar(painter);
    painter->drawPixmap(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60, pixmap);
}

void Shooter::idle() {
    // 检查周围是否有敌人
    for (auto enemy : _enemies) {
        if (abs(enemy->_x - _x) * abs(enemy->_x - _x) +
                    abs(enemy->_y - _y) * abs(enemy->_y - _y) <=
                _attackRange * _attackRange &&
            enemy->_state != EnemyState::DEAD) {
            _state = TowerState::ATTACKING;
            _target_enemy = enemy;
            break;
        }
    }
}

void Shooter::attack() {
    if (_attackCoolDown < _attackSpeed) {
        _attackCoolDown++;
    } else {
        _attackCoolDown = 0;
        _target_enemy->_hp_cur -= _damage;

        for (int i = 0; i < _buff_num; i++) {
            if (_buffSlot[i] == 3) {
                // 将enemy转为boar
                Boar *boar = dynamic_cast<Boar *>(_target_enemy);
                boar->applyBleedEffect(10, 2);
            }
        }

        if (_target_enemy->_hp_cur <= 0) {
            _target_enemy->_state = EnemyState::DEAD;
            _state = TowerState::IDLE;
        }
    }
}