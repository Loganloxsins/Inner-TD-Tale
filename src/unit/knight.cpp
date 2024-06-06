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
    _damage = 5;
    _attackSpeed = 4;
    _attackCoolDown = 0;
    _target_enemy = nullptr;
    _buff_num = 0;
    _buffSlot[0] = -1;
    _buffSlot[1] = -1;

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
    // 如果敌人_enemies全部为空，说明没有敌人，塔进入idle状态
    if (_enemies.empty()) {
        _state = TowerState::IDLE;
        std::cout << "No enemy to attack!" << std::endl;
        return;
    }
    if (_attackCoolDown < _attackSpeed) {
        _attackCoolDown++;
    } else {
        _attackCoolDown = 0;

        bool hasIce = false;
        bool hasAoE = false;

        for (int i = 0; i < _buff_num; i++) {
            switch (_buffSlot[i]) {
            case 0:
                std::cout << "Fury attack: " << _target_enemy->_x << " "
                          << _target_enemy->_y << " " << _damage;
                break;
            case 1:
                // 输出被攻击对象的坐标和造成的伤害
                std::cout << "Ice attack: " << _target_enemy->_x << " "
                          << _target_enemy->_y << " " << _damage;
                _target_enemy->_state = EnemyState::FROZEN;
                hasIce = true;
                break;
            case 2: {
                hasAoE = true;

                for (auto enemy : _enemies) {
                    if (abs(enemy->_x - _x) + abs(enemy->_y - _y) <= 1 &&
                        enemy->_state != EnemyState::DEAD) {
                        enemy->_hp_cur -= _damage;
                        // 输出被攻击对象的坐标和造成的伤害
                        std::cout << "AoE attack: " << enemy->_x << " "
                                  << enemy->_y << " " << _damage;
                        if (enemy->_hp_cur <= 0) {
                            enemy->_state = EnemyState::DEAD;
                        }
                    }
                }

                break;
            }
            default:
                break;
            }
        }
        if (hasIce && hasAoE) {
            for (auto enemy : _enemies) {
                if (abs(enemy->_x - _x) + abs(enemy->_y - _y) <= 1 &&
                    enemy->_state != EnemyState::DEAD) {
                    enemy->_state = EnemyState::FROZEN;
                }
            }
        } else if (!hasAoE) {
            _target_enemy->_hp_cur -= _damage;
            if (_target_enemy->_hp_cur <= 0) {
                _target_enemy->_state = EnemyState::DEAD;
                _state = TowerState::IDLE;
            }
        }
    }
}
