#ifndef BASE_ENEMY_H
#define BASE_ENEMY_H

#include "unit/base_tower.h"
#include "unit/base_unit.h"
#include "utils/enemy_state.h"
#include <QPainter>
#include <QPoint>
#include <vector>
class Enemy : public Unit {

  public:
    // float _targetX, _targetY; // 目标位置
    std::vector<std::pair<int, int>> _path;
    int _path_index;
    EnemyState _state;
    bool _isArrivedCounted = false;
    int _bleedDamage = 0;
    int _bleedDuration = 0;
    int _jumpCoolDown = 3;

    // 移动函数接口
    virtual void move() = 0;
    virtual void attack() = 0;

    virtual void applyBleedEffect(int damage, int duration) = 0;
    // // 移动的辅助函数
    // void updateTargetPosition() {
    //     if (_path_index < _path.size() - 1) {
    //         _path_index++;
    //         _targetX = _path[_path_index].first;
    //         _targetY = _path[_path_index].second;
    //     } else {
    //         _state = EnemyState::ARRIVED;
    //     }
    // }

    /*
    基本的故方词缀：
  √闪现的：该单位能发动闪现，越过我方近战塔的阻挡前进，但需要有冷却时间
  神速的：该单位的移动速度要超过默认单位
    */

    virtual void buffJump() {
        if (_buffSlot[0] == -1) {
            _buffSlot[0] = 0;
        } else if (_buffSlot[1] == -1) {
            _buffSlot[1] = 0;
        }
    }
    virtual void debuffJump() {
        if (_buffSlot[0] == 0) {
            _buffSlot[0] = -1;
        } else if (_buffSlot[1] == 0) {
            _buffSlot[1] = -1;
        }
    }
    virtual void buffSpeed() {
        if (_buffSlot[0] == -1) {
            _buffSlot[0] = 1;
        } else if (_buffSlot[1] == -1) {
            _buffSlot[1] = 1;
        }
    }
    virtual void debuffSpeed() {
        if (_buffSlot[0] == 1) {
            _buffSlot[0] = -1;
        } else if (_buffSlot[1] == 1) {
            _buffSlot[1] = -1;
        }
    }
};

#endif // BASE_ENEMY_H
