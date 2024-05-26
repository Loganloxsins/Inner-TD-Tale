#ifndef BASE_ENEMY_H
#define BASE_ENEMY_H

#include "unit/base/base_unit.h"
#include "utils/enemy_state.h"
#include <QPoint>
#include <vector>

#include <QPainter>
class Enemy : public Unit {

  public:
    int _speed;
    float _targetX, _targetY; // 目标位置
    std::vector<std::pair<int, int>> _path;
    int _path_index;
    EnemyState _state;


    // 移动函数接口
    virtual void move() = 0;
    // 移动的辅助函数
    void updateTargetPosition() {
        if (_path_index < _path.size() - 1) {
            _path_index++;
            _targetX = _path[_path_index].first;
            _targetY = _path[_path_index].second;
        } else {
            _state = EnemyState::ARRIVED;
        }
    }

    // 攻击函数
};

#endif // BASE_ENEMY_H
